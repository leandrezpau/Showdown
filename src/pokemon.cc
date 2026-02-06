#pragma once

#ifndef _POKEMON_CC_ 
#define _POKEMON_CC_

#include "pokemon.h"

void Pokemon::UseMove(Pokemon& target, cl_Movement move){
  SDL_Log("%s usa %s!", this->name.c_str(), move.moveName.c_str());

  int chance = rand() % 100;
  if (chance > move.accuracy) {
    SDL_Log("Pero fallo!");
    return;
  }

  if (move.isState != true) {
    float attackStat = move.isSpecial ? this->stats.spcAtk : this->stats.Atk;
    float defenseStat = move.isSpecial ? target.stats.spcDef : target.stats.Def;

    float damage = (((2.0f * (float)this->level / 5.0f + 2.0f) * (float)move.power * (attackStat / defenseStat)) / 50.0f) + 2.0f;

    if (move.moveType.type == this->type1.type || move.moveType.type == this->type2.type) {
      damage *= 1.5f;
    }

    float typeMult = target.CalculateIncomingDamageMult(move.moveType);
    damage *= typeMult;

    if (damage < 1.0f && typeMult > 0.0f) damage = 1.0f;
    if (typeMult == 0.0f) damage = 0.0f;

    target.stats.HP -= damage;
    if (target.stats.HP < 0) target.stats.HP = 0;

    SDL_Log("Danyo infligido: %.0f (HP restante: %.0f)", damage, target.stats.HP);

    if (typeMult > 1.0f) SDL_Log("!Es super efectivo!");
    else if (typeMult == 0.0f) SDL_Log("No afecta a %s...", target.name.c_str());
    else if (typeMult < 1.0f) SDL_Log("No es muy efectivo...");
  }
}

float Pokemon::CalculateIncomingDamageMult(cl_Type attackType) {
  return attackType.GetEffectivenessAgainst(type1, type2);
}

#endif