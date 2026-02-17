#ifndef _MOVEMENTS_CC_
#define _MOVEMENTS_CC_

#include "movements.h"

/*
void Movement::ChangeStats() {

}
*/
Movement::Movement()
  : moveName("NULL"),
    power(0),
    accuracy(0),
    pp(0),
    currentPP(0),
    isState(false),
    isSpecial(false),
    affectedStat(STAT_NONE),
    stageChange(0)
{
  moveType.InitWithEnum(en_Types::TYPE_NONE);
}
Movement::Movement(std::string n, en_Types t, int p, int acc, 
                  int _pp, bool state, bool special, StatID stat, int stages)
  : moveName(n), power(p), accuracy(acc), pp(_pp), currentPP(_pp), isState(state), 
  isSpecial(special),affectedStat(stat), stageChange(stages)
{
  moveType.InitWithEnum(t);
}
#endif //_MOVEMENTS_CC_