#pragma once

#define _TYPES_H
#ifdef _TYPES_H

#include <string>

enum en_Types{
  TYPE_NORMAL,  // Normal
  TYPE_FIRE,    // Fuego
  TYPE_WATER,   // Agua
  TYPE_ELECTRIC,// Electrico
  TYPE_GRASS,   // Planta
  TYPE_ICE,     // Hielo
  TYPE_FIGHTING,// Lucha
  TYPE_POISON,  // Veneno
  TYPE_GROUND,  // Tierra
  TYPE_FLYING,  // Volador
  TYPE_PSYCHIC, // Psiquico
  TYPE_BUG,     // Bicho
  TYPE_ROCK,    // Roca
  TYPE_GHOST,   // Fantasma
  TYPE_DRAGON,  // Dragon
  TYPE_DARK,    // Siniestro
  TYPE_STEEL,   // Acero
  TYPE_FAIRY,   // Hada
  TYPE_NULL,
  //TYPE_STELLAR
};

class cl_Type {
  en_Types type;

  int typeID;
  std::string typeName;

  float Attacking(cl_Type otherType);
  float Defending(cl_Type otherType);
};


#endif //_TYPES_H