#ifndef _TRAINER_CC_
#define _TRAINER_CC_

#include "trainer.h"

Trainer::Trainer(std::string n, bool ai) : name(n), isAI(ai) {}

void Trainer::AddPokemon(Pokemon p) {
  if (team.size() < 6) team.push_back(p);
}

Pokemon* Trainer::GetActivePokemon() {
  if (team.empty()) return nullptr;
  return &team[currentPokemonIndex];
}

bool Trainer::HasAvailablePokemon() {
  for (auto& p : team) {
    if (p.currentStats.HP > 0) return true;
  }
  return false;
}
Pokemon Trainer::GetCurrentPokemon(){
  return team[currentPokemonIndex];
}
// Changes the current pokemon player is using
void Trainer::ChangePokemon(int newPokemonIndex){
  currentPokemonIndex = newPokemonIndex;
}

#endif //_TRAINER_CC_