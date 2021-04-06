#ifndef RTW_HEADER_DBG_BUS_h_
#define RTW_HEADER_DBG_BUS_h_
#include "AutoCalSt.h"
#include "rtwtypes.h"

typedef struct {
  real32_T IfbkTgt;
  real32_T Lest;
  real32_T Rest;
  real32_T KTrqEst;
  real32_T IfbkOfs;
  real32_T KFrcEst;
  real32_T JEst;
  real32_T IfbkSteady;
  real32_T IfbkMax;
  real32_T SpdMax;
  AutoCalSt Status;
} DBG_BUS;

#endif                                 /* RTW_HEADER_DBG_BUS_h_ */
