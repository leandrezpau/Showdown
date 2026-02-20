#pragma once

#ifndef _BATTLEAI_H
#define _BATTLEAI_H

#include "pokemon.h"
#include "trainer.h"
#include "game.h"

class BattleAI {
public:
  enum Difficulty { EASY = 0, MEDIUM, HARD };

  static std::pair<int, float> ChooseBestMove(Pokemon* aiPokemon, Pokemon* playerPokemon);
  static std::pair<int, float> ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon);

  static PlayerActions GetBestAction(Trainer* aiTrainer, Pokemon* playerPokemon);

private:
  static float PredictDamage(Pokemon* attacker, Pokemon* defender, Movement& move);
  static float EvaluateBoardState(float aiSimHp, float aiMaxHp, float playerSimHp, float playerMaxHp, bool aiIsFaster);
};
#endif //_BATTLEAI_H