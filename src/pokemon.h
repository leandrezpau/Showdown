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

  float CalculateIncomingDamageMult(cl_Type attackType);

  void UseMove(Pokemon& target, cl_Movement move);
};


#endif //_POKEMON_H_