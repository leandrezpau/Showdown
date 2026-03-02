#ifndef _BATTLEAI_CC_
#define _BATTLEAI_CC_

#include "battleai.h"
#include <iostream>
#include <algorithm>

// Calcula el dano esperado de un movimiento considerando STAB, efectividad de tipos y precision.
// NOTA: Se ejecuta en un entorno simulado, no afecta al combate real.
float BattleAI::PredictDamage(Pokemon* attacker, Pokemon* defender, Movement& move) {
  if (move.moveClass == kClassStatus) return 0.0f; // TODO: Implementar logica para movimientos de estado

  float attackStat = 0.0f;
  float defenseStat = 0.0f;

  if (move.moveClass == kClassPhysical) {
    attackStat = attacker->currentStats.Atk;
    defenseStat = defender->currentStats.Def;
  }
  else if (move.moveClass == kClassSpecial) {
    attackStat = attacker->currentStats.spcAtk;
    defenseStat = defender->currentStats.spcDef;
  }

  // Multiplicadores
  float typeMult = defender->CalculateIncomingDamageMult(move.moveType);
  float stab = (move.moveType.type == attacker->type1.type || move.moveType.type == attacker->type2.type) ? 1.5f : 1.0f;

  // Formula estandar de dano
  float damage = ((float)move.power * (attackStat / defenseStat) * stab * typeMult) + 2.0f;

  // Ajuste por precision (Valor Esperado)
  damage *= ((float)move.accuracy / 100.0f);

  return damage;
}

// Analiza el estado del combate y devuelve una puntuacion. Mayor puntuacion = Mejor para la IA.
float BattleAI::EvaluateBoardState(float aiSimHp, float aiMaxHp, float playerSimHp, float playerMaxHp, bool aiIsFaster) {
  // Comparamos el % de HP restante para que sea justo sin importar el nivel maximo del Pokemon
  float aiHpRatio = std::max(0.0f, aiSimHp) / aiMaxHp;
  float playerHpRatio = std::max(0.0f, playerSimHp) / playerMaxHp;

  float score = (aiHpRatio - playerHpRatio) * 1000.0f;

  // Bonificacion tactica: ser mas rapido da el control del turno
  if (aiIsFaster) score += 50.0f;

  // Bonificaciones criticas: Castigamos o premiamos fuertemente los KO (debilitamientos)
  if (playerSimHp <= 0) score += 5000.0f;
  if (aiSimHp <= 0) score -= 5000.0f;

  return score;
}

// Implementacion de Algoritmo Minimax (Profundidad 1) para elegir ataque
std::pair<int, float> BattleAI::ChooseBestMove(Pokemon* aiPoke, Pokemon* playerPoke) {
  int bestMoveIndex = 0;
  float bestGuaranteedScore = -99999.0f;

  bool aiIsFaster = aiPoke->currentStats.Vel > playerPoke->currentStats.Vel;

  // Iteramos sobre nuestros movimientos (Capa MAX - IA busca la mayor puntuacion)
  for (int i = 0; i < aiPoke->movement.size(); i++) {
    Movement& myMove = aiPoke->movement[i];
    if (myMove.currentPP <= 0) continue; // Ignoramos movimientos invalidos

    float minScoreForThisMove = 99999.0f;

    // Iteramos sobre los movimientos del rival (Capa MIN - Asumimos que el jugador hara su mejor jugada)
    for (int j = 0; j < playerPoke->movement.size(); j++) {
      Movement& enemyMove = playerPoke->movement[j];
      if (enemyMove.currentPP <= 0) continue;

      // Simulamos ambos ataques
      float damageToEnemy = PredictDamage(aiPoke, playerPoke, myMove);
      float damageToMe = PredictDamage(playerPoke, aiPoke, enemyMove);

      float simAiHp = aiPoke->currentStats.HP;
      float simPlayerHp = playerPoke->currentStats.HP;

      // Resolvemos el orden de los ataques en la simulacion segun la velocidad
      if (aiIsFaster) {
        simPlayerHp -= damageToEnemy;
        if (simPlayerHp > 0) simAiHp -= damageToMe; // El jugador ataca solo si sobrevive
      }
      else {
        simAiHp -= damageToMe;
        if (simAiHp > 0) simPlayerHp -= damageToEnemy; // Nosotros atacamos solo si sobrevivimos
      }

      // Evaluamos como queda el tablero despues del cruce de ataques
      float boardScore = EvaluateBoardState(simAiHp, aiPoke->baseStats.maxHP, simPlayerHp, playerPoke->baseStats.maxHP, aiIsFaster);

      // El jugador elegira lo que mas nos perjudique
      if (boardScore < minScoreForThisMove) {
        minScoreForThisMove = boardScore;
      }
    }

    // Nosotros elegimos el movimiento cuyo peor escenario sea el mejor posible
    if (minScoreForThisMove > bestGuaranteedScore) {
      bestGuaranteedScore = minScoreForThisMove;
      bestMoveIndex = i;
    }
  }

  return { bestMoveIndex, bestGuaranteedScore };
}

// Evalua si vale la pena cambiar de Pokemon, asumiendo que el rival nos atacara mientras cambiamos.
std::pair<int, float> BattleAI::ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon) {
  int bestPokemonIndex = -1;
  float bestGuaranteedScore = -99999.0f;

  int currentIdx = aiTrainer->currentPokemonIndex;

  for (int i = 0; i < aiTrainer->team.size(); i++) {
    if (i == currentIdx) continue;
    if (aiTrainer->team[i].currentStats.HP <= 0) continue; // No sacar Pokes debilitados

    Pokemon& candidate = aiTrainer->team[i];
    float minScoreForThisSwitch = 99999.0f;

    // Simulamos que sacamos a este Pokemon y el jugador nos ataca gratis ese turno
    for (int j = 0; j < playerPokemon->movement.size(); j++) {
      Movement& enemyMove = playerPokemon->movement[j];
      if (enemyMove.currentPP <= 0) continue;

      float damageToMe = PredictDamage(playerPokemon, &candidate, enemyMove);

      float simAiHp = candidate.currentStats.HP - damageToMe;
      float simPlayerHp = playerPokemon->currentStats.HP;

      // Evaluamos el tablero TRAS recibir el golpe. 
      // Asumimos velocidad en el proximo turno para la heuristica.
      bool candidateIsFaster = candidate.currentStats.Vel > playerPokemon->currentStats.Vel;

      float boardScore = EvaluateBoardState(simAiHp, candidate.baseStats.maxHP, simPlayerHp, playerPokemon->baseStats.maxHP, candidateIsFaster);

      // Penalizacion heuristica: Perder un turno al cambiar duele, restamos puntos para evitar cambios constantes ("Switch Stalling")
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

// Junta todo: decide si es mejor atacar o cambiar basandose en las puntuaciones obtenidas.
PlayerActions BattleAI::GetBestAction(Trainer* aiTrainer, Pokemon* playerPokemon) {
  PlayerActions actionToTake;
  actionToTake.playerAction[0] = kActionNULL;
  actionToTake.playerIndex[0] = 0;

  Pokemon* activePoke = &aiTrainer->team[aiTrainer->currentPokemonIndex];

  // Calculamos puntuaciones para ambas opciones
  std::pair<int, float> attackOption = ChooseBestMove(activePoke, playerPokemon);
  std::pair<int, float> switchOption = ChooseSwitch(aiTrainer, playerPokemon);

  // Regla de oro: Si nuestro Pokemon actual esta muerto, estamos OBLIGADOS a cambiar
  if (activePoke->currentStats.HP <= 0) {
    actionToTake.playerAction[0] = kActionChangePoke;
    actionToTake.playerIndex[0] = switchOption.first;
    return actionToTake;
  }

  // Comparamos puntuaciones (Ataque vs Cambio)
  if (switchOption.second > attackOption.second && switchOption.first != -1) {
    std::cout << "IA decide CAMBIAR de Pokemon. Score Cambio: " << switchOption.second << " vs Score Ataque: " << attackOption.second; 
    actionToTake.playerAction[0] = kActionChangePoke;
    actionToTake.playerIndex[0] = switchOption.first;
  }
  else {
    std::cout << "IA decide ATACAR. Score Ataque: " << attackOption.second << " vs Score Cambio: " << switchOption.second;
    actionToTake.playerAction[0] = kActionAttack;
    if(attackOption.first >= 3 || attackOption.first >= 0){
      actionToTake.playerIndex[0] = attackOption.first;
    }else{
      actionToTake.playerIndex[0] = 0;
    }
    
  }

  return actionToTake;
}

#endif //_BATTLEAI_CC_