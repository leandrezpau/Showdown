#pragma once

#ifndef _BATTLEAI_H
#define _BATTLEAI_H

#include "pokemon.h"
#include "trainer.h"

class BattleAI {
public:
  enum Difficulty { EASY, MEDIUM, HARD };

  static int ChooseBestMove(Pokemon* aiPokemon, Pokemon* playerPokemon);

  static int ChooseSwitch(Trainer* aiTrainer, Pokemon* playerPokemon);
};
#endif //_BATTLEAI_H