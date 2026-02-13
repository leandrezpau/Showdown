#pragma once

#include <sqlite/sqlite3.h>
#include <string>
#include <stdexcept>
#include <iostream>

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
};

PokemonData getPokemonById(sqlite3* db, int pokemon_id);

#endif //_RETURN_POKE_DATA_H_