#ifndef _BATTLEAI_CC_
#define _BATTLEAI_CC_

#include "battleai.h"
#include <iostream>
#include <algorithm>

float BattleAI::PredictDamage(Pokemon* attacker, Pokemon* defender, Movement& move) {
  if (move.isState) return 0.0f;

  float atk = move.isSpecial ? attacker->currentStats.spcAtk : attacker->currentStats.Atk;
  float def = move.isSpecial ? defender->currentStats.spcDef : defender->currentStats.Def;

  float typeMult = defender->CalculateIncomingDamageMult(move.moveType);
  float stab = (move.moveType.type == attacker->type1.type || move.moveType.type == attacker->type2.type) ? 1.5f : 1.0f;

  float damage = ((float)move.power * (atk / def) * stab * typeMult) + 2.0f;

  damage *= ((float)move.accuracy / 100.0f);

  return damage;
}

float BattleAI::EvaluateBoardState(float aiSimHp, float aiMaxHp, float playerSimHp, float playerMaxHp, bool aiIsFaster) {
  float aiHpRatio = std::max(0.0f, aiSimHp) / aiMaxHp;
  float playerHpRatio = std::max(0.0f, playerSimHp) / playerMaxHp;

  float score = (aiHpRatio - playerHpRatio) * 1000.0f; 

  if (aiIsFaster) score += 50.0f;

  if (playerSimHp <= 0) score += 5000.0f;
  if (aiSimHp <= 0) score -= 5000.0f;

  return score;
}

std::pair<int, float> BattleAI::ChooseBestMove(Pokemon* aiPoke, Pokemon* playerPoke) {
  int bestMoveIndex = 0;
  float bestGuaranteedScore = -99999.0f;

  bool aiIsFaster = aiPoke->currentStats.Vel > playerPoke->currentStats.Vel;

  for (int i = 0; i < aiPoke->movement.size(); i++) {
    Movement& myMove = aiPoke->movement[i];
    if (myMove.index == mv_NULL || myMove.currentPP <= 0) continue;

    float minScoreForThisMove = 99999.0f;

    for (int j = 0; j < playerPoke->movement.size(); j++) {
      Movement& enemyMove = playerPoke->movement[j];
      if (enemyMove.index == mv_NULL || enemyMove.currentPP <= 0) continue;

      float damageToEnemy = PredictDamage(aiPoke, playerPoke, myMove);
      float damageToMe = PredictDamage(playerPoke, aiPoke, enemyMove);

      float simAiHp = aiPoke->currentStats.HP;
      float simPlayerHp = playerPoke->currentStats.HP;

      if (aiIsFaster) {
        simPlayerHp -= damageToEnemy;
        if (simPlayerHp > 0) simAiHp -= damageToMe;
      }
      else {
        simAiHp -= damageToMe;
        if (simAiHp > 0) simPlayerHp -= damageToEnemy;
      }

      float boardScore = EvaluateBoardState(simAiHp, aiPoke->baseStats.maxHP, simPlayerHp, playerPoke->baseStats.maxHP, aiIsFaster);

      if (boardScore < minScoreForThisMove) {
        minScoreForThisMove = boardScore;
      }
    }

    if (minScoreForThisMove > bestGuaranteedScore) {
      bestGuaranteedScore = minScoreForThisMove;
      bestMoveIndex = i;
    }
  }

  return { bestMoveIndex, bestGuaranteedScore };
}

// NUEVO ChooseSwitch simulando el turno
std::pair<int, float> BattleAI::ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon) {
  int bestPokemonIndex = -1;
  float bestGuaranteedScore = -99999.0f;

  int currentIdx = aiTrainer->currentPokemonIndex;

  for (int i = 0; i < aiTrainer->team.size(); i++) {
    if (i == currentIdx) continue;
    if (aiTrainer->team[i].currentStats.HP <= 0) continue; // No sacar pokes debilitados

    Pokemon& candidate = aiTrainer->team[i];
    float minScoreForThisSwitch = 99999.0f;

    // Simulamos que sacamos a este Pokémon y el jugador nos ataca gratis ese turno
    for (int j = 0; j < playerPokemon->movement.size(); j++) {
      Movement& enemyMove = playerPokemon->movement[j];
      if (enemyMove.index == mv_NULL || enemyMove.currentPP <= 0) continue;

      float damageToMe = PredictDamage(playerPokemon, &candidate, enemyMove);

      float simAiHp = candidate.currentStats.HP - damageToMe;
      float simPlayerHp = playerPokemon->currentStats.HP;

      // Evaluamos el tablero TRAS recibir el golpe. 
      // Asumimos velocidad en el próximo turno para la heurística.
      bool candidateIsFaster = candidate.currentStats.Vel > playerPokemon->currentStats.Vel;

      float boardScore = EvaluateBoardState(simAiHp, candidate.baseStats.maxHP, simPlayerHp, playerPokemon->baseStats.maxHP, candidateIsFaster);

      // Penalización extra por cambiar: perder un turno duele, a menos que sea muy necesario
      boardScore -= 100.0f;

      if (boardScore < minScoreForThisSwitch) {
        minScoreForThisSwitch = boardScore;
      }
    }

    if (minScoreForThisSwitch > bestGuaranteedScore) {
      bestGuaranteedScore = minScoreForThisSwitch;
      bestPokemonIndex = i;
    }
  }

  return { bestPokemonIndex, bestGuaranteedScore };
}

// 3. LA FUNCIÓN MAESTRA QUE UNE TODO
PlayerActions BattleAI::GetBestAction(Trainer* aiTrainer, Pokemon* playerPokemon) {
  PlayerActions actionToTake;
  // Inicializamos con valores seguros
  actionToTake.playerAction[0] = kActionNULL;
  actionToTake.playerIndex[0] = 0;

  Pokemon* activePoke = &aiTrainer->team[aiTrainer->currentPokemonIndex];

  // Calculamos qué tan bueno es atacar
  std::pair<int, float> attackOption = ChooseBestMove(activePoke, playerPokemon);

  // Calculamos qué tan bueno es cambiar
  std::pair<int, float> switchOption = ChooseSwitch(aiTrainer, playerPokemon);

  // Si el Pokémon actual está debilitado, ESTAMOS OBLIGADOS a cambiar
  if (activePoke->currentStats.HP <= 0) {
    actionToTake.playerAction[0] = kActionChangePoke;
    actionToTake.playerIndex[0] = switchOption.first;
    return actionToTake;
  }

  // Comparamos puntuaciones (Ataque vs Cambio)
  if (switchOption.second > attackOption.second && switchOption.first != -1) {
    SDL_Log("IA decide CAMBIAR de Pokémon. Score Cambio: %.2f vs Score Ataque: %.2f", switchOption.second, attackOption.second);
    actionToTake.playerAction[0] = kActionChangePoke;
    actionToTake.playerIndex[0] = switchOption.first;
  }
  else {
    SDL_Log("IA decide ATACAR. Score Ataque: %.2f vs Score Cambio: %.2f", attackOption.second, switchOption.second);
    actionToTake.playerAction[0] = kActionAttack;
    actionToTake.playerIndex[0] = attackOption.first;
  }

  return actionToTake;
}

#endif //_BATTLEAI_CC_