#pragma once

#ifndef _TRAINER_H
#define _TRAINER_H

#include <vector>
#include "pokemon.h"

class Trainer {
public:
	std::string name;
	std::vector<Pokemon> team;
	int currentPokemonIndex = 0;
	bool isAI;

	Trainer(std::string n, bool ai) : name(n), isAI(ai) {}

  void AddPokemon(Pokemon p);
  Pokemon* GetActivePokemon();
  bool HasAvailablePokemon();
};
#endif //_TRAINER_H