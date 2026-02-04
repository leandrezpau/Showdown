#define _MOVEMENTS_H_
#ifdef _MOVEMENTS_H_

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
  enum en_Type moveType;
  std::string moveName;
};


#endif //_MOVEMENTS_H_