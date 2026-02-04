#define _TYPES_H
#ifdef _TYPES_H

#include <string>

enum en_Types{
  TYPE_FIRE,
  TYPE_WATER,
  TYPE_GRASS,
  TYPE_ELECTRIC,
  TYPE_PSYCHIC,
  TYPE_DARK,
  TYPE_FAIRY,
  TYPE_NORMAL,
  TYPE_FIGHTING,
  TYPE_FLYING,
  TYPE_POISON,
  TYPE_GROUND,
  TYPE_ROCK,
  TYPE_BUG,
  TYPE_GHOST,
  TYPE_STEEL,
  TYPE_ICE,
  TYPE_DRAGON
};

class cl_Type {
  en_Types type;

  int typeID;
  std::string typeName;
};


#endif //_TYPES_H