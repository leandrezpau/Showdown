#pragma once

#ifndef _POKEMON_H_ 
#define _POKEMON_H_

#include <SDL3/SDL.h> 

#include "types.h"
#include "movements.h"

#include <math.h>
#include <vector>
#include <string>
#include <array>

struct Stats {
  float Atk;
  float Def;
  float spcAtk;
  float spcDef;
  float Vel;
  float HP;
};

//vec2 natures[5][6] = {
//  ((Atk * 1.1f)), ((Atk * 1.1f)), ((Atk * 1.1f)), ((Atk * 1.1f)), (1.0f, 1.0f),
//  ((Def * 1.1f)), ((Def * 1.1f)), ((Def * 1.1f)), ((Def * 1.1f)), (1.0f, 1.0f),
//  ((spcAtk * 1.1f)), ((spcAtk * 1.1f)), ((spcAtk * 1.1f)), ((spcAtk * 1.1f)), (1.0f, 1.0f),
//  ((spcDef * 1.1f)), ((spcDef * 1.1f)), ((spcDef * 1.1f)), ((spcDef * 1.1f)), (1.0f, 1.0f),
//  ((Vel * 1.1f)), ((Vel * 1.1f)), ((Vel * 1.1f)), ((Vel * 1.1f)), (1.0f, 1.0f),
//};

//struct Natures {
//
//  float Hardy   (0.0f, 0.0f); //Neutra
//  float Docile  (0.0f, 0.0f); //Neutra
//  float Serious (0.0f, 0.0f); //Neutra
//  float Bashful (0.0f, 0.0f); //Neutra
//  float Quirky  (0.0f, 0.0f); //Neutra
//
//  float Lonely  (1.1f, 0.9f); //Atk+ / 
//  float Brave   (1.1f, 0.9f); //Atk+ / 
//  float Naughty (1.1f, 0.9f); //Atk+ / 
//  float Adamant (1.1f, 0.9f); //Atk+ / 
//
//  float Bold    (1.1f, 0.9f); //Def+ /
//  float Relaxed (1.1f, 0.9f); //Def+ /
//  float Impish  (1.1f, 0.9f); //Def+ /
//  float Lax     (1.1f, 0.9f); //Def+ /
//
//  float Timid   (1.1f, 0.9f); //Speed+ /
//  float Naive   (1.1f, 0.9f); //Speed+ /
//  float Jolly   (1.1f, 0.9f); //Speed+ /
//  float Hasty   (1.1f, 0.9f); //Speed+ /
//
//  float Modest  (1.1f, 0.9f); //SpcAtk+ /
//  float Mild    (1.1f, 0.9f); //SpcAtk+ /
//  float Quiet   (1.1f, 0.9f); //SpcAtk+ /
//  float Rash    (1.1f, 0.9f); //SpcAtk+ /
//
//  float Calm    (1.1f, 0.9f); //SpcDef+ /
//  float Gentle  (1.1f, 0.9f); //SpcDef+ /
//  float Sassy   (1.1f, 0.9f); //SpcDef+ /
//  float Carefyl (1.1f, 0.9f); //SpcDef+ /
//};

class Pokemon {
public:
  int id;
  int level;

  Stats stats;
  std::string name;
  cl_Type type1; 
  cl_Type type2;

  std::vector<cl_Movement> movement;

  float CalculateIncomingDamageMult(cl_Type attackType) {
    return attackType.GetEffectivenessAgainst(this->type1, this->type2);
  }

  void UseMove(Pokemon& target, cl_Movement move) {
    SDL_Log("%s usa %s!", this->name.c_str(), move.moveName.c_str());

    int chance = rand() % 100;
    if (chance > move.accuracy) {
      SDL_Log("�Pero fall�!");
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
};


#endif //_POKEMON_H_