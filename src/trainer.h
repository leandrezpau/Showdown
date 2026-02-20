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

	// Add pokemon to his team
  void AddPokemon(Pokemon p);
	// Returns a list of his active pokemon
  Pokemon* GetActivePokemon();
	// Returns trur if player has pokemon left
  bool HasAvailablePokemon();
	// Returns Current pokemon player is using
	Pokemon GetCurrentPokemon();
	
	// Changes the current pokemon player is using
	void ChangePokemon(int newPokemonIndex);

	Trainer(std::string n, bool ai);
};
#endif //_TRAINER_H