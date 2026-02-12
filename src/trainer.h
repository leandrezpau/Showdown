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

  void AddPokemon(Pokemon p) {
    if (team.size() < 6) team.push_back(p);
  }

  Pokemon* GetActivePokemon() {
    if (team.empty()) return nullptr;
    return &team[currentPokemonIndex];
  }

  bool HasAvailablePokemon() {
    for (auto& p : team) {
      if (p.currentStats.HP > 0) return true;
    }
    return false;
  }
};
#endif //_TRAINER_H