#pragma once

#ifndef _MOVEMENTS_H_
#define _MOVEMENTS_H_

#include "types.h"
#include "pokemon.h"
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

class cl_Movement {
public:
    std::string moveName;
    cl_Type moveType;
    int power;
    int accuracy;
    int pp;
    bool isState;
    bool isSpecial;

    StatID affectedStat;
    int stageChange;

    cl_Movement(std::string n, cl_Type t, int p, int acc, int _pp, bool state, bool special,
      StatID stat = STAT_NONE, int stages = 0)
      : moveName(n), moveType(t), power(p), accuracy(acc), pp(_pp),
      isState(state), isSpecial(special),
      affectedStat(stat), stageChange(stages)
    {
    }
};


#endif //_MOVEMENTS_H_