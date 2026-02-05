#pragma once

#ifndef _MOVEMENTS_H_
#define _MOVEMENTS_H_

#include "types.h"
#include <string>
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
    bool isSpecial;

    cl_Movement(std::string n, cl_Type t, int p, int acc, int powpoints, bool special)
        : moveName(n), moveType(t), power(p), accuracy(acc), pp(powpoints), isSpecial(special) {
    }
};


#endif //_MOVEMENTS_H_