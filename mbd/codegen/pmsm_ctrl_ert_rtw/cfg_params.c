/*
 * File: cfg_params.c
 *
 * Code generated for Simulink model 'pmsm_ctrl'.
 *
 * Model version                  : 1.676
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sat Jul 17 12:18:34 2021
 */

#include "rtwtypes.h"
#include "multiword_types.h"
#include "pmsm_ctrl_types.h"

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
boolean_T Cfg_AutoCalEnbl = 0;         /* Enable ifbk loop autocalibration at startup */
boolean_T Cfg_EnblDynComp = 1;         /* Enable x-coupling and b-emf comp */
real32_T Cfg_EncCnts = 2400.0F;        /* Encoder counts */
int32_T Cfg_EncCntsInt = 2400;         /* Encoder counts w/ int32 data type. */
real32_T Cfg_IfbkCtrlBW = 2000.0F;     /* Current controller bandwith (rad/s) */
real32_T Cfg_MtrJm = 2.4E-5F;          /* Motor rotor inertia. */
real32_T Cfg_MtrKf = 0.0F;             /* Rotor friction coefficient */
real32_T Cfg_MtrKtrq = 0.035F;         /* Motor torque constant */
uint8_T Cfg_PolePairs = 4U;            /* Number of pole pairs. */
real32_T Cfg_SpdCtrlBW = 1000.0F;      /* Speed controller bandwith. */
boolean_T Cfg_SpdSnsEnbl = 0;          /* System has speed sensor. */
int32_T Cfg_StepToEncCnts = 10;        /* Defines how many encoder counts per step. */
boolean_T Cfg_UseObsPosEst = 0;        /* Use observer position estimate. */
real32_T DistObs_J = 2.4E-5F;          /* Motor Inertia at Disturbance Observer. */
real32_T DistObs_K1 = 6000.0F;         /* Disturbance obser gain k1. */
real32_T DistObs_K2 = 1.2E+7F;         /* Disturbance obser gain k2. */
real32_T DistObs_K3 = 8.0E+9F;         /* Disturbance obser gain k3. */
real32_T EncCntsToRads = 0.00261799386F;/* Encoder to radians conversion. */
real32_T PosCtrl_Ki = 0.0F;            /* PI integral term for position controller. */
real32_T PosCtrl_Kp = 400.0F;          /* PI proportional term for position controller. */
real32_T TsMain = 0.001F;              /* Main sampling time (1khz) */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */