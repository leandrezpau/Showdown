#ifndef _MOVEMENTS_CC_
#define _MOVEMENTS_CC_

#include "movements.h"
#include "sqlfuncs/returnPokeData.h"

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

  moveName = n;
  moveType.InitWithString(move_.type);
  moveClass = (MoveClass) move_.moveClass;
  power = move_.damage;
  accuracy = move_.accuracy;
  pp = move_.pp;
  currentPP = pp;


  //Falta añadir lo de affected stats
}

#endif //_MOVEMENTS_CC_