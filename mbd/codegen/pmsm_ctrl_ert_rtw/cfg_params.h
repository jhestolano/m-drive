/*
 * File: cfg_params.h
 *
 * Code generated for Simulink model 'pmsm_ctrl'.
 *
 * Model version                  : 1.676
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sat Jul 17 12:18:34 2021
 */

#ifndef RTW_HEADER_cfg_params_h_
#define RTW_HEADER_cfg_params_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "pmsm_ctrl_types.h"

/* Exported data declaration */

/* Declaration for custom storage class: ExportToFile */
extern boolean_T Cfg_AutoCalEnbl;      /* Enable ifbk loop autocalibration at startup */
extern boolean_T Cfg_EnblDynComp;      /* Enable x-coupling and b-emf comp */
extern real32_T Cfg_EncCnts;           /* Encoder counts */
extern int32_T Cfg_EncCntsInt;         /* Encoder counts w/ int32 data type. */
extern real32_T Cfg_IfbkCtrlBW;        /* Current controller bandwith (rad/s) */
extern real32_T Cfg_MtrJm;             /* Motor rotor inertia. */
extern real32_T Cfg_MtrKf;             /* Rotor friction coefficient */
extern real32_T Cfg_MtrKtrq;           /* Motor torque constant */
extern uint8_T Cfg_PolePairs;          /* Number of pole pairs. */
extern real32_T Cfg_SpdCtrlBW;         /* Speed controller bandwith. */
extern boolean_T Cfg_SpdSnsEnbl;       /* System has speed sensor. */
extern int32_T Cfg_StepToEncCnts;      /* Defines how many encoder counts per step. */
extern boolean_T Cfg_UseObsPosEst;     /* Use observer position estimate. */
extern real32_T DistObs_J;             /* Motor Inertia at Disturbance Observer. */
extern real32_T DistObs_K1;            /* Disturbance obser gain k1. */
extern real32_T DistObs_K2;            /* Disturbance obser gain k2. */
extern real32_T DistObs_K3;            /* Disturbance obser gain k3. */
extern real32_T EncCntsToRads;         /* Encoder to radians conversion. */
extern real32_T PosCtrl_Ki;            /* PI integral term for position controller. */
extern real32_T PosCtrl_Kp;            /* PI proportional term for position controller. */
extern real32_T TsMain;                /* Main sampling time (1khz) */

#endif                                 /* RTW_HEADER_cfg_params_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
