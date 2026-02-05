#define _POKEMON_H_
#ifdef _POKEMON_H_

#include "types.h"
#include "movements.h"

#include <vector>
#include <string>

class Pokemon {
  int id;
  int level;

  std::string name;
  cl_Type type1; 
  cl_Type type2;

  std::vector<cl_Movement> movement;

  float CalculateIncomingDamageMult(cl_Type attackType) {
      return attackType.GetEffectivenessAgainst(this->type1, this->type2);
  }
};


#endif //_POKEMON_H_