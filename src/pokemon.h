#pragma once

#ifndef _POKEMON_H_ 
#define _POKEMON_H_

#include <SDL3/SDL.h> 
#include <sqlite/sqlite3.h>

#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <array>

#include "sqlfuncs/returnPokeData.h"

#include "types.h"
#include "movements.h"
#include "sprites/sprites.h"

struct Stats {
  float HP;
  float Atk;
  float Def;
  float spcAtk;
  float spcDef;
  float Vel;
  float maxHP;
};

enum PokeState {
  kStateAlive = 0,
  kStateFainted,
  kStateBurn,
  kStatePoison,
  kStateBadPoison,
  kStateParalysis,
  kStateSleep,
  kStateFreeze,
  kStateNone
};

class Pokemon : public PokeSprite{
public:
  int id;             // Pokedex num of that pokemon
  int level;          // Level of the poke                
  float weight;       // Wheight of that pokemon
  int gender;         // 0 male, 1 fem, 2 genderless
  int generation;     // pokemon generation
  int stage;          // Stage in which he is
  bool fully_evolved; // He is in his last stage?
  bool shiny;         // Shiny?

  Stats baseStats;    // Base stats
  Stats currentStats; // Stats now he is leveled up
  std::string name;   // Name of the pokemon
  cl_Type type1;      // First type
  cl_Type type2;      // Secondary type
  int statStages[8];  // Which stage he is in

  PokeState state;

  std::vector<Movement> movement;  // Movements he can use

  float CalculateIncomingDamageMult(cl_Type attackType);
  void UseMove(Pokemon& target, Movement move);

  void ModifyStat(StatID stat, int amount);

  void SetNewPokemon(int _id, int _level, int _gender, bool _shiny, en_SpriteType spriteType_);

  void SetMovement(std::string moveName);

  void PrintPokemon();
  void InitSprites();
  Pokemon(int _id, int _level, int _gender, bool _shiny, en_SpriteType spriteType_);

private:
  void RecalculateStats();
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

#endif //_POKEMON_H_