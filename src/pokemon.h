#define _POKEMON_H_
#ifdef _POKEMON_H_

#include "types.h"
#include <vector>
#include <string>

class Pokemon {
  int id;
  int level;

  std::string name;
  enum en_Type type;

  std::vector<en_Type> movement;
};


#endif //_POKEMON_H_