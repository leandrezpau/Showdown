#ifndef _POKEMON_CC_ 
#define _POKEMON_CC_

#include "pokemon.h"
using namespace std;

void Pokemon::ModifyStat(StatID stat, int amount) {
  if (stat == STAT_NONE) return;

  int* stage = &statStages[stat];

  if (*stage == 6 && amount > 0) {
    cout << name.c_str() << " no puede subir mas esa estadistica!";
    return;
  }
  if (*stage == -6 && amount < 0) {
    cout << name.c_str() << " no puede bajar mas esa estadistica!";
    return;
  }

  *stage += amount;
  if (*stage > 6) *stage = 6;
  if (*stage < -6) *stage = -6;

  cout << name.c_str() << ": cambio de estadistica " << (int) stat <<" a nivel " << *stage;

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

void Pokemon::UseMove(Pokemon& target, Movement move) {
 cout << "\n" << this->name.c_str() << " usa " << move.moveName.c_str() <<"!";

  int chance = rand() % 100;
  if (chance > move.accuracy) {
    cout << "Pero fallo!";
    return;
  }

  if (move.moveClass != kClassStatus) {
    float attackStat = 0.0f;
    float defenseStat = 0.0f;

    if (move.moveClass == kClassPhysical) {
      attackStat = this->currentStats.Atk;
      defenseStat = target.currentStats.Def;
    }
    else if (move.moveClass == kClassSpecial) {
      attackStat = this->currentStats.spcAtk;
      defenseStat = target.currentStats.spcDef;
    }

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

    cout << "\nDanyo infligido: " << damage << "(HP restante: " << target.currentStats.HP << ")";

    if (typeMult > 1.0f) cout << "!Es super efectivo!";
    else if (typeMult == 0.0f) cout << "No afecta a " << target.name.c_str() << "...";
    else if (typeMult < 1.0f) cout << "No es muy efectivo...";
  }
}

void Pokemon::PrintPokemon(){
  cout << "\nName: " << name;
  cout << "\nType 1: " << type1.typeName;
  cout << "\nType 2: " << type2.typeName;
  cout << "\nWheight: " << weight << " Kg";
  cout << "\nStats: \nHp: " << currentStats.HP << "\nAtk: " << currentStats.Atk << "\nDef: " << currentStats.Def 
    << "\nSpAtk: " << currentStats.spcAtk << "\nSpDef: " << currentStats.spcDef << "\nSpd: " << currentStats.Vel;
  cout << "\nStage: " << stage;

  cout << "\nIs Fully Evolved? ";
  if(fully_evolved){
    cout <<"Yes";
  }else{
    cout <<"No";
  }

  cout << "\nGeneration: " << generation;
}

void Pokemon::InitSprites(){
  textureID = BaseSprite::spriteIndexer++;
  SelectPokemonSprite(shiny, typeSprite, id);
  InitSpriteSrc();
  switch(typeSprite){
    case en_SpriteType::type_Attacker: InitSpriteDst(160, 220, 3, true); break;
    case en_SpriteType::type_Defender: InitSpriteDst(480, 110, 2, true); break;
    case en_SpriteType::type_Icon:     InitSpriteDst(400, 320, 2, true); break;
  }
}

void Pokemon::SetNewPokemon(int _id, int _level, int _gender, bool _shiny, en_SpriteType spriteType_){
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
  Stats stats_ = {  
                    (float) pokemon_.hp, 
                    (float) pokemon_.attack, 
                    (float) pokemon_.defense, 
                    (float) pokemon_.specialAttack, 
                    (float) pokemon_.specialDefense, 
                    (float) pokemon_.speed, 
                    (float) pokemon_.maxhp
                  };

  baseStats = stats_;
  currentStats = stats_;

  //Weight
  weight = pokemon_.weight;
  
  //Stages
  stage = pokemon_.evo_phase;
  fully_evolved = pokemon_.last_evo_phase;
  
  for (int i = 0; i < 8; ++i)
    statStages[i] = 0;

  // GENERATION
  generation = pokemon_.generation;

  //Sprite Things
  typeSprite = spriteType_;
  InitSprites();

  PrintPokemon();
}
void Pokemon::SetMovement(std::string moveName){
  if(movement.size() < 4){
    movement.push_back(Movement{moveName});
  }
}
Pokemon::Pokemon(int _id, int _level, int _gender, bool _shiny, en_SpriteType spriteType_)
    : id(_id), level(50), gender(_gender), shiny(_shiny){
    
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
  Stats stats_ = {(float) pokemon_.hp, 
                  (float) pokemon_.attack, 
                  (float) pokemon_.defense, 
                  (float) pokemon_.specialAttack, 
                  (float) pokemon_.specialDefense, 
                  (float) pokemon_.speed, 
                  (float) pokemon_.maxhp };

  baseStats = stats_;
  currentStats = stats_;
  
  //Movements
  for(int i = 0; i < 4; i++){
    //movement[i]
  }
  //Weight
  weight = pokemon_.weight;
  
  //Stages
  stage = pokemon_.evo_phase;
  fully_evolved = pokemon_.last_evo_phase;
  for (int i = 0; i < 8; ++i)
    statStages[i] = 0;

  //State
  state = PokeState::kStateAlive;

  // GENERATION
  generation = pokemon_.generation;

  //Sprite Things
  typeSprite = spriteType_;
  InitSprites();

  PrintPokemon();
}
#endif