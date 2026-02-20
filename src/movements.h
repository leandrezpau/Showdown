#pragma once

#ifndef _MOVEMENTS_H_
#define _MOVEMENTS_H_

#include "types.h"
#include "sqlite/sqlite3.h"
#include <string>

enum StatID {
  STAT_NONE,
  STAT_ATK,
  STAT_DEF,
  STAT_SPC_ATK,
  STAT_SPC_DEF,
  STAT_VEL,
  STAT_ACC,
  STAT_EVA
};

enum en_Movement {
  mv_Base,
  /*
  *
  * ....
  * ....
  * ....
  * 
  */
  mv_NULL
};

class Movement {
public:
  en_Movement index;      // Movement which indeed is
  std::string moveName;   // Name of this move
  cl_Type moveType;       // Type of the move (e.g., Fire, Water, etc.)
  int power;              // Base damage power of the move
  int accuracy;           // Hit chance percentage (0–100)
  int pp;                 // Maximum number of times the move can be used
  int currentPP;          // Remaining uses available
  bool isState;           // True if the move does not deal damage (status move)
  bool isSpecial;         // True if the move uses special attack/defense instead of physical stats

  StatID affectedStat;    // Stat modified by the move (if it changes stats)
  int stageChange;        // Amount of stat stages increased or decreased

  Movement();          // Default constructor with no data
  Movement(std::string n, en_Types t, int p, int acc, int _pp, bool state, bool special,
    StatID stat = STAT_NONE, int stages = 0);
};


#endif //_MOVEMENTS_H_