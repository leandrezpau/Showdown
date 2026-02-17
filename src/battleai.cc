#ifndef _BATTLEAI_CC_
#define _BATTLEAI_CC_

#include "battleai.h"
#include <iostream>

int BattleAI::ChooseBestMove(Pokemon* aiPoke, Pokemon* playerPoke) {
  int bestMoveIndex = -1;
  float maxScore = -9999.0f;

  for (int i = 0; i < aiPoke->moves.size(); i++) {
    Movement& move = aiPoke->moves[i];
    float score = 0.0f;

    float predictedDamage = 0;
    if (!move.isState) {
      float atk = move.isSpecial ? aiPoke->currentStats.spcAtk : aiPoke->currentStats.Atk;
      float def = move.isSpecial ? playerPoke->currentStats.spcDef : playerPoke->currentStats.Def;
      float typeMult = playerPoke->CalculateIncomingDamageMult(move.moveType);
      float stab = (move.moveType.type == aiPoke->type1.type || move.moveType.type == aiPoke->type2.type) ? 1.5f : 1.0f;

      predictedDamage = ((float)move.power * (atk / def) * stab * typeMult) + 2.0f;
    }


    if (predictedDamage >= playerPoke->currentStats.HP) {
      score += 500.0f; 
      score += move.accuracy;
    }
    else {
      score += predictedDamage;
    }

    score *= ((float)move.accuracy / 100.0f);

    if (move.isState) {
      if (move.affectedStat == STAT_ATK && move.stageChange > 0) {
        if (aiPoke->statStages[STAT_ATK] >= 6) {
          score = -100.0f;
        }
        else {
          score = 30.0f;
        }
      }
      // WIP (falta a�adir los estados alterados a los pok�mon)
    }

    SDL_Log("Evalunado %s: Da�o estimado %.2f -> Score Final %.2f", move.moveName.c_str(), predictedDamage, score);

    if (score > maxScore) {
      maxScore = score;
      bestMoveIndex = i;
    }
  }

  if (bestMoveIndex == -1) bestMoveIndex = 0;

  return bestMoveIndex;
}

int BattleAI::ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon) {
  int bestPokemonIndex = -1;
  float bestScore = -1000.0f;

  int currentIdx = aiTrainer->currentPokemonIndex;

  for (int i = 0; i < aiTrainer->team.size(); i++) {
    if (i == currentIdx) continue;
    if (aiTrainer->team[i].currentStats.HP <= 0) continue;

    Pokemon& candidate = aiTrainer->team[i];
    float score = 0.0f;

    float defensiveMult1 = candidate.CalculateIncomingDamageMult(playerPokemon->type1);
    float defensiveMult2 = (playerPokemon->type2.type != TYPE_NONE) ?
      candidate.CalculateIncomingDamageMult(playerPokemon->type2) : 1.0f;

    float maxIncoming = std::max(defensiveMult1, defensiveMult2);
    if (maxIncoming > 1.5f) score -= 50.0f;
    if (maxIncoming < 0.8f) score += 40.0f;

    float offensiveMult1 = playerPokemon->CalculateIncomingDamageMult(candidate.type1);
    float offensiveMult2 = (candidate.type2.type != TYPE_NONE) ?
      playerPokemon->CalculateIncomingDamageMult(candidate.type2) : 1.0f;

    float maxOutgoing = std::max(offensiveMult1, offensiveMult2);
    if (maxOutgoing > 1.2f) score += 60.0f;
    if (maxOutgoing < 0.8f) score -= 30.0f;

    if (candidate.currentStats.Vel > playerPokemon->currentStats.Vel) {
      score += 10.0f;
    }

    if (score > bestScore) {
      bestScore = score;
      bestPokemonIndex = i;
    }
  }

  if (bestScore > 20.0f) {
    SDL_Log("AI decide cambiar al pokemon indice %d con puntuacion %.2f", bestPokemonIndex, bestScore);
    return bestPokemonIndex;
  }

  return -1;
}
#endif //_BATTLEAI_CC_