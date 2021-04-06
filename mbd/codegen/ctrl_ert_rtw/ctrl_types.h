/*
 * ctrl_types.h
 *
 * Code generation for model "ctrl".
 *
 * Model version              : 1.904
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_ctrl_types_h_
#define RTW_HEADER_ctrl_types_h_
#include "rtwtypes.h"
#include "DBG_BUS.h"
#ifndef DEFINED_TYPEDEF_FOR_MtrCtrlMd_
#define DEFINED_TYPEDEF_FOR_MtrCtrlMd_

typedef enum {
  IfbkCtrlMd = 0,                      /* Default value */
  SpdCtrlMd = 1,
  PosCtrlMd = 2,
  TrqCtrlMd = 3,
  OpnLoopCtrlMd = 4,
  OffCtrlMd = 255
} MtrCtrlMd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_CI8nDHNKFYq3miU7okN8NH_
#define DEFINED_TYPEDEF_FOR_struct_CI8nDHNKFYq3miU7okN8NH_

typedef struct {
  real_T R;
  real_T L;
  real_T K;
  real_T Kf;
  real_T J;
  real_T Tau;
  real_T Kdc;
  real_T AccMax;
  real_T PPR;
  real_T IfbkOfs;
} struct_CI8nDHNKFYq3miU7okN8NH;

#endif

/* Parameters for system: '<Root>/ctrl_fast' */
typedef struct P_ctrl_fast_ P_ctrl_fast;

/* Parameters for system: '<Root>/ctrl_slow' */
typedef struct P_ctrl_slow_ P_ctrl_slow;

/* Parameters (default storage) */
typedef struct P_ P;

#endif                                 /* RTW_HEADER_ctrl_types_h_ */
