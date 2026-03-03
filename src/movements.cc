#ifndef _MOVEMENTS_CC_
#define _MOVEMENTS_CC_

#include "movements.h"
#include "sqlfuncs/returnPokeData.h"

Sprite Movement::typeIcons_s[Type::kNTypes];
Sprite Movement::classAttack_s[3];

Movement::Movement()
  : moveName("NULL"),
    power(0),
    accuracy(0),
    pp(0),
    currentPP(0),
    affectedStat(STAT_NONE),
    stageChange(0)
{
  moveType.InitWithEnum(en_Types::TYPE_NONE);
}

Movement::Movement(std::string n){
  sqlite3* db;
  sqlite3_open("../assets/Database/PokemonDB.db", &db);

  MovementData move_ = getMoveByName(db, n);

  sqlite3_close(db);

  moveName = move_.name;
  moveType.InitWithString(move_.type);
  moveClass = (MoveClass) move_.moveClass;
  power = move_.damage;
  accuracy = move_.accuracy;
  pp = move_.pp;
  currentPP = pp;

  for(int i = 0; i < Type::kNTypes; i++){
    typeIcons_s[i].SetTextureID(typeIcons_s[i].GetTextureID());
    char iconFile[50];
    snprintf(iconFile, 50, "../assets/HUD/UI/%s_ui.png", Type::NameByType((en_Types) i).c_str());
    typeIcons_s[i].SelectSpriteFromRoute(iconFile);
    typeIcons_s[i].InitSpriteSrc(false);
    typeIcons_s[i].InitSpriteDst(0, 0, 1);
  }

  for(int i = 0; i < 3; i++){
    classAttack_s[i].SetTextureID(classAttack_s[i].GetTextureID());
    char iconFile[50];
    switch(i){
      case 0: snprintf(iconFile, 50, "../assets/HUD/UI/physical_ui.png"); break;
      case 1: snprintf(iconFile, 50, "../assets/HUD/UI/special_ui.png");  break;
      case 2: snprintf(iconFile, 50, "../assets/HUD/UI/status_ui.png");   break;
    }
    classAttack_s[i].SelectSpriteFromRoute(iconFile);
    classAttack_s[i].InitSpriteSrc(false);
    classAttack_s[i].InitSpriteDst(0, 0, 1);
  }
  //Falta añadir lo de affected stats
}


#endif //_MOVEMENTS_CC_