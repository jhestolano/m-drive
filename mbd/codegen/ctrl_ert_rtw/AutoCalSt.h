#ifndef RTW_HEADER_AutoCalSt_h_
#define RTW_HEADER_AutoCalSt_h_
#include "rtwtypes.h"

typedef enum {
  ErrIndTooSmall = -1,                 /* Default value */
  ErrIndTooLarge = -2,
  ErrResTooSmall = -3,
  ErrResTooLarge = -4,
  NotStarted = 0,
  IndID,
  IndIDCoolDown,
  ResID,
  IfbkOfsID,
  TrqCnstID,
  InertiaID,
  Done = 255
} AutoCalSt;

#endif                                 /* RTW_HEADER_AutoCalSt_h_ */
