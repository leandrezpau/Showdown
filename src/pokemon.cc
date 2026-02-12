#pragma once

#ifndef _POKEMON_CC_ 
#define _POKEMON_CC_

#include "pokemon.h"

void Pokemon::ModifyStat(StatID stat, int amount) {
  if (stat == STAT_NONE) return;

  int* stage = &statStages[stat];

  if (*stage == 6 && amount > 0) {
    SDL_Log("%s no puede subir mas esa estadistica!", name.c_str());
    return;
  }
  if (*stage == -6 && amount < 0) {
    SDL_Log("%s no puede bajar mas esa estadistica!", name.c_str());
    return;
  }

  *stage += amount;
  if (*stage > 6) *stage = 6;
  if (*stage < -6) *stage = -6;

  SDL_Log("%s: cambio de estadistica %d a nivel %d", name.c_str(), stat, *stage);

  RecalculateStats();
}

void Pokemon::RecalculateStats() {
  auto getMult = [](int stage) -> float {
    if (stage >= 0) return (2.0f + stage) / 2.0f;
    else return 2.0f / (2.0f + std::abs(stage));
    };

  currentStats.Atk = baseStats.Atk * getMult(statStages[STAT_ATK]);
  currentStats.Def = baseStats.Def * getMult(statStages[STAT_DEF]);
  currentStats.spcAtk = baseStats.spcAtk * getMult(statStages[STAT_SPC_ATK]);
  currentStats.spcDef = baseStats.spcDef * getMult(statStages[STAT_SPC_DEF]);
  currentStats.Vel = baseStats.Vel * getMult(statStages[STAT_VEL]);
}

float Pokemon::CalculateIncomingDamageMult(cl_Type attackType) {
  return attackType.GetEffectivenessAgainst(type1, type2);
}

void Pokemon::UseMove(Pokemon& target, cl_Movement move) {
  SDL_Log("%s usa %s!", this->name.c_str(), move.moveName.c_str());

  int chance = rand() % 100;
  if (chance > move.accuracy) {
    SDL_Log("Pero fallo!");
    return;
  }

  if (move.isState != true) {
    float attackStat = move.isSpecial ? this->currentStats.spcAtk : this->currentStats.Atk;
    float defenseStat = move.isSpecial ? target.currentStats.spcDef : target.currentStats.Def;

    float damage = (((2.0f * (float)this->level / 5.0f + 2.0f) * (float)move.power * (attackStat / defenseStat)) / 50.0f) + 2.0f;
    
    if (move.moveType.type == this->type1.type || move.moveType.type == this->type2.type) {
      damage *= 1.5f;
    }

    float typeMult = target.CalculateIncomingDamageMult(move.moveType);
    damage *= typeMult;

    if (damage < 1.0f && typeMult > 0.0f) damage = 1.0f;
    if (typeMult == 0.0f) damage = 0.0f;

    target.currentStats.HP -= damage;
    if (target.currentStats.HP < 0) target.currentStats.HP = 0;

    SDL_Log("Danyo infligido: %.0f (HP restante: %.0f)", damage, target.currentStats.HP);

    if (typeMult > 1.0f) SDL_Log("!Es super efectivo!");
    else if (typeMult == 0.0f) SDL_Log("No afecta a %s...", target.name.c_str());
    else if (typeMult < 1.0f) SDL_Log("No es muy efectivo...");
  }
}

Pokemon::Pokemon(int _id, en_Types _t1, en_Types _t2, Stats _stats, int _level, float _weight, int _gender, int _stage,
    bool _fully_evolved, bool _shiny, SDL_Renderer* renderer_, en_SpriteType spriteType_)
    : id(_id), type1(_t1), type2(_t2), baseStats(_stats), currentStats(_stats), level(50), weight(_weight), gender(_gender),
     stage(_stage), fully_evolved(_fully_evolved), shiny(_shiny), PokeSprite(renderer_)
  {
    for (int i = 0; i < 6; i++) statStages[i] = 0;
    currentStats.maxHP = _stats.HP; 

    type1.InitWithEnum(_t1);
    type2.InitWithEnum(_t2);
    
    //Find Pokemon NAME
    std::ifstream file("../assets/SpritesAnimated/pokedex.txt");
    if (!file.is_open()) return;

    std::string nombre;
    int i = 1;
    bool found = false;

    while (std::getline(file, nombre)) {
      if (i == _id) {
        found = true;
        break;
      }
      i++;
    }

    file.close();
    name = nombre; //<-- Selecting name without putting it into constructor

    // GENERATION
    if (_id >= 1   && _id <= 151)  generation = 1;
    else if (_id <= 251)           generation = 2;
    else if (_id <= 386)           generation = 3;
    else if (_id <= 493)           generation = 4;
    else if (_id <= 649)           generation = 5;
    else if (_id <= 721)           generation = 6;
    else if (_id <= 809)           generation = 7;
    else if (_id <= 905)           generation = 8;
    else if (_id <= 1025)          generation = 9;


    //Sprite Things
    typeSprite = spriteType_;
    sRenderer_ = renderer_;
    SelectPokemonSprite(_shiny, spriteType_, _id);
    InitSpriteSrc();
    switch(typeSprite){
      case en_SpriteType::type_Attacker: InitPokemonSpriteDst(160, 350, 3); break;
      case en_SpriteType::type_Defender: InitPokemonSpriteDst(480, 200, 2); break;
      case en_SpriteType::type_Icon:     InitPokemonSpriteDst(400, 400, 2); break;
    }
  }
#endif