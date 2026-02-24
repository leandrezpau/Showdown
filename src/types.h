#pragma once

#ifndef _TYPES_H
#define _TYPES_H

#include <string>
#include <algorithm>
#include <unordered_map>

constexpr float IMM = 0.0f; // Inmune (Immune)
constexpr float NVE = 0.5f; // No muy efectivo (Not Very Effective)
constexpr float NEU = 1.0f; // Neutro (Neutral)
constexpr float SUP = 2.0f; // Super efectivo (Super Effective)

enum en_Types{
  TYPE_NONE = -1,
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

  TYPE_COUNT    //how many types
  //TYPE_STELLAR
};

class cl_Type {
public:
  static const int kNTypes = 18;
  
  en_Types type;
  std::string typeName;
  float GetEffectivenessAgainst(cl_Type defender1, cl_Type defender2);
  float GetEffectivenessAgainst(cl_Type defender);
  
  float Attacking(cl_Type defender);
  float Defending(cl_Type attacker);

  void InitWithEnum(en_Types typeEnum);
  void InitWithString(std::string typeString);
  void SetStringName();
  cl_Type(en_Types t = TYPE_NORMAL) : type(t) {}
};


#endif //_TYPES_H