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
Pokemon::Pokemon(int _id, int _level, int _gender, bool _shiny, 
     SDL_Renderer* renderer_, en_SpriteType spriteType_)
    : id(_id), level(50), gender(_gender), shiny(_shiny), PokeSprite(renderer_)
  {
    
    sqlite3* db;
    sqlite3_open("../assets/Database/PokemonDB.db", &db);

    PokemonData pokemon_ = getPokemonById(db, _id);

    sqlite3_close(db);

    //Name in UpperCase
    name = pokemon_.name;
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    //Pokemon Types
    type1.InitWithString(pokemon_.type1);
    type2.InitWithString(pokemon_.type2);

    //Stats
    Stats stats_ = {pokemon_.hp, pokemon_.attack, pokemon_.defense, pokemon_.specialAttack, pokemon_.specialDefense, pokemon_.speed, pokemon_.maxhp};
    baseStats = stats_;
    currentStats = stats_;

    //Weight
    weight = pokemon_.weight;
    
    //Stages
    stage = pokemon_.evo_phase;
    fully_evolved = pokemon_.last_evo_phase;

    // GENERATION
    generation = pokemon_.generation;

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

    std::cout << "\nName: " << name;
    std::cout << "\nType 1: " << type1.typeName;
    std::cout << "\nType 2: " << type2.typeName;
    std::cout << "\nWheight: " << weight;
    std::cout << "\nStage: " << stage;
    std::cout << "\nIs Fully Evolved? ";
    if(fully_evolved){
      std::cout <<"Yes";
    }else{
      std::cout <<"No";
    }
    std::cout << "\nGeneration: " << generation;
  }
#endif