#ifndef _TYPES_CC_
#define _TYPES_CC_

#include "types.h"

static const float TypeChart[TYPE_COUNT][TYPE_COUNT] = {
  /* DEFENSOR ->  NOR  FIR  WAT  ELE  GRA  ICE  FIG  POI  GRO  FLY  PSY  BUG  ROC  GHO  DRA  DAR  STE  FAI */
  /* NOR */ { NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NVE, IMM, NEU, NEU, NVE, NEU },
  /* FIR */ { NEU, NVE, NVE, NEU, SUP, SUP, NEU, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NVE, NEU, SUP, NEU },
  /* WAT */ { NEU, SUP, NVE, NEU, NVE, NEU, NEU, NEU, SUP, NEU, NEU, NEU, SUP, NEU, NVE, NEU, NEU, NEU },
  /* ELE */ { NEU, NEU, SUP, NVE, NVE, NEU, NEU, NEU, IMM, SUP, NEU, NEU, NEU, NEU, NVE, NEU, NEU, NEU },
  /* GRA */ { NEU, NVE, SUP, NEU, NVE, NEU, NEU, NVE, SUP, NVE, NEU, NVE, SUP, NEU, NVE, NEU, NVE, NEU },
  /* ICE */ { NEU, NVE, NVE, NEU, SUP, NVE, NEU, NEU, SUP, SUP, NEU, NEU, NEU, NEU, SUP, NEU, NVE, NEU },
  /* FIG */ { SUP, NEU, NEU, NEU, NEU, SUP, NEU, NVE, NEU, NVE, NVE, NVE, SUP, IMM, NEU, SUP, SUP, NVE },
  /* POI */ { NEU, NEU, NEU, NEU, SUP, NEU, NEU, NVE, NVE, NEU, NEU, NEU, NVE, NVE, NEU, NEU, IMM, SUP },
  /* GRO */ { NEU, SUP, NEU, SUP, NVE, NEU, NEU, SUP, NEU, IMM, NEU, NVE, SUP, NEU, NEU, NEU, SUP, NEU },
  /* FLY */ { NEU, NEU, NEU, NVE, SUP, NEU, SUP, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NEU, NEU, NVE, NEU },
  /* PSY */ { NEU, NEU, NEU, NEU, NEU, NEU, SUP, SUP, NEU, NEU, NVE, NEU, NEU, NEU, NEU, IMM, NVE, NEU },
  /* BUG */ { NEU, NVE, NEU, NEU, SUP, NEU, NVE, NVE, NEU, NVE, SUP, NEU, NEU, NVE, NEU, SUP, NVE, NVE },
  /* ROC */ { NEU, SUP, NEU, NEU, NEU, SUP, NVE, NEU, NVE, SUP, NEU, SUP, NEU, NEU, NEU, NEU, NVE, NEU },
  /* GHO */ { IMM, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NEU, SUP, NEU, NVE, NEU, NEU },
  /* DRA */ { NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NVE, IMM },
  /* DAR */ { NEU, NEU, NEU, NEU, NEU, NEU, NVE, NEU, NEU, NEU, SUP, NEU, NEU, SUP, NEU, NVE, NEU, NVE },
  /* STE */ { NEU, NVE, NVE, NVE, NEU, SUP, NEU, NEU, NEU, NEU, NEU, NEU, SUP, NEU, NEU, NEU, NVE, SUP },
  /* FAI */ { NEU, NVE, NEU, NEU, NEU, NEU, SUP, NVE, NEU, NEU, NEU, NEU, NEU, NEU, SUP, SUP, NVE, NEU }
};

float Type::GetEffectivenessAgainst(Type defender) {
  if (this->type >= TYPE_COUNT || defender.type >= TYPE_COUNT ||
      this->type < 0 || defender.type < 0) {
    return 1.0f;
  }
  return TypeChart[this->type][defender.type];
}

float Type::GetEffectivenessAgainst(Type defender1, Type defender2) {
  float multiplier1 = GetEffectivenessAgainst(defender1);

  float multiplier2 = 1.0f;

  if (defender2.type != TYPE_NONE && defender2.type != defender1.type) {
    multiplier2 = GetEffectivenessAgainst(defender2);
  }

  return multiplier1 * multiplier2;
}

float Type::Attacking(Type defender) {
  return GetEffectivenessAgainst(defender);
}

float Type::Defending(Type attacker) {
  return attacker.GetEffectivenessAgainst(*this);
}

void Type::InitWithEnum(en_Types typeEnum) {
  type = typeEnum;
}

void Type::InitWithString(std::string typeString) {
  // Pasar a mayúsculas para evitar problemas
  std::transform(typeString.begin(), typeString.end(), typeString.begin(), ::toupper);

  static const std::unordered_map<std::string, en_Types> typeMap = {
    {"NORMAL",   en_Types::TYPE_NORMAL},
    {"FIRE",     en_Types::TYPE_FIRE},
    {"WATER",    en_Types::TYPE_WATER},
    {"ELECTRIC", en_Types::TYPE_ELECTRIC},
    {"GRASS",    en_Types::TYPE_GRASS},
    {"ICE",      en_Types::TYPE_ICE},
    {"FIGHTING", en_Types::TYPE_FIGHTING},
    {"POISON",   en_Types::TYPE_POISON},
    {"GROUND",   en_Types::TYPE_GROUND},
    {"FLYING",   en_Types::TYPE_FLYING},
    {"PSYCHIC",  en_Types::TYPE_PSYCHIC},
    {"BUG",      en_Types::TYPE_BUG},
    {"ROCK",     en_Types::TYPE_ROCK},
    {"GHOST",    en_Types::TYPE_GHOST},
    {"DRAGON",   en_Types::TYPE_DRAGON},
    {"DARK",     en_Types::TYPE_DARK},
    {"STEEL",    en_Types::TYPE_STEEL},
    {"FAIRY",    en_Types::TYPE_FAIRY}
  };

  auto it = typeMap.find(typeString);
  if (it != typeMap.end()) {
    type = it->second;
    typeName = typeString;
  } else {
    type = en_Types::TYPE_NONE;
    typeName = "NONE";
  }
}

void Type::SetStringName() {
}
std::string Type::NameByType(en_Types typeEnum){
  switch (typeEnum)
  {
    case en_Types::TYPE_NORMAL:   return "normal";
    case en_Types::TYPE_FIRE:     return "fire";
    case en_Types::TYPE_WATER:    return "water";
    case en_Types::TYPE_ELECTRIC: return "electric";
    case en_Types::TYPE_GRASS:    return "grass";
    case en_Types::TYPE_ICE:      return "ice";
    case en_Types::TYPE_FIGHTING: return "fighting";
    case en_Types::TYPE_POISON:   return "poison";
    case en_Types::TYPE_GROUND:   return "ground";
    case en_Types::TYPE_FLYING:   return "flying";
    case en_Types::TYPE_PSYCHIC:  return "psychic";
    case en_Types::TYPE_BUG:      return "bug";
    case en_Types::TYPE_ROCK:     return "rock";
    case en_Types::TYPE_GHOST:    return "ghost";
    case en_Types::TYPE_DRAGON:   return "dragon";
    case en_Types::TYPE_DARK:     return "dark";
    case en_Types::TYPE_STEEL:    return "steel";
    case en_Types::TYPE_FAIRY:    return "fairy";
    default:                      return "none";
  }
}
#endif //_TYPES_CC_