#pragma once

#include <sqlite/sqlite3.h>

#include <string>
#include <stdexcept>
#include <iostream>

#include "../movements.h"

#define _RETURN_POKE_DATA_H_
#ifdef _RETURN_POKE_DATA_H_


struct PokemonData {
  std::string name;
  std::string type1;
  std::string type2;
  int attack;
  int defense;
  int specialAttack;
  int specialDefense;
  int speed;
  int hp;
  int maxhp;
  int generation;
  float weight;
  int evo_phase;
  bool last_evo_phase;
};
struct MovementData {
  std::string id;               // ID
  std::string name;             // Name
  std::string type;             // Type
  MoveClass moveClass;          // Class
  int damage;                   // Damage

  int accuracy;                 // Accuracy
  std::string target;           // Target
  int pp;                       // PP
  std::string secondaryEffect1;
  int secondaryEffect1Chance;

  std::string secondaryEffect2;
  int secondaryEffect2Chance;

  std::string secondaryEffect3;
  int secondaryEffect3Chance;

  std::string secondaryEffect4;
  int secondaryEffect4Chance;

  std::string secondaryEffect5;
  int secondaryEffect5Chance;

  std::string secondaryEffect6;
  int secondaryEffect6Chance;
};

MovementData getMoveByName(sqlite3* db, const std::string& moveName);
PokemonData getPokemonById(sqlite3* db, int pokemon_id);

#endif //_RETURN_POKE_DATA_H_