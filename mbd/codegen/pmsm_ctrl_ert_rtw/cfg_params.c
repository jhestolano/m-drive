/*
 * File: cfg_params.c
 *
 * Code generated for Simulink model 'pmsm_ctrl'.
 *
 * Model version                  : 1.816
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sun Aug 15 12:19:48 2021
 */

#include "rtwtypes.h"
#include "pmsm_ctrl_types.h"

/* Exported data definition */

/* Definition for custom storage class: ExportToFile */
real32_T Cfg_AnglOfsCalPwmDuty = 0.2F; /* Duty cycle during angle offset cal */
boolean_T Cfg_AutoCalEnbl = 0;         /* Enable ifbk loop autocalibration at startup */
boolean_T Cfg_EnblDynComp = 1;         /* Enable x-coupling and b-emf comp */
boolean_T Cfg_EnblTrajPlan = 1;        /* Enable trajectory planner (speed and position). */
int32_T Cfg_EncCnts = 2400;            /* Encoder counts */
real32_T Cfg_EncOfsCalPwmDuty = 0.2F;  /* Duty cycle during encoder offset cal */
real32_T Cfg_IfbkCtrlBW = 2000.0F;     /* Current controller bandwith (rad/s) */
real32_T Cfg_IndCalPwmDuty = 0.2F;     /* Duty cycle during inductance calibration */
real32_T Cfg_Ls = 0.0013F;             /* Motor inductance (phase) */
real32_T Cfg_MFlux = 0.0058F;          /* Motor flux */
real32_T Cfg_MtrJm = 2.4E-5F;          /* Motor rotor inertia. */
real32_T Cfg_MtrKf = 0.0F;             /* Rotor friction coefficient */
real32_T Cfg_MtrKtrq = 0.035F;         /* Motor torque constant */
real32_T Cfg_OverCurProtMax = 1.0F;    /* Overcurrent protection limit. */
uint8_T Cfg_PolePairs = 4U;            /* Number of pole pairs. */
real32_T Cfg_ResCalPwmDuty = 0.2F;     /* Duty cycle during resistance calibration */
real32_T Cfg_Rs = 1.4F;                /* Motor resistance (phase). */
real32_T Cfg_SpdCtrlBW = 200.0F;       /* Speed controller bandwith. */
boolean_T Cfg_SpdSnsEnbl = 0;          /* System has speed sensor. */
int32_T Cfg_StepToEncCnts = 10;        /* Defines how many encoder counts per step. */
boolean_T Cfg_UseObsPosEst = 0;        /* Use observer position estimate. */
boolean_T Cfg_UseSpdPll = 1;           /* Use Speed PLL instead of observer for speed estimate. */
real32_T Cfg_VBus = 12.0F;             /* Bus voltage */
real32_T DistObs_J = 2.4E-5F;          /* Motor Inertia at Disturbance Observer. */
real32_T DistObs_K1 = 1200.0F;         /* Disturbance obser gain k1. */
real32_T DistObs_K2 = 480000.0F;       /* Disturbance obser gain k2. */
real32_T DistObs_K3 = 6.4E+7F;         /* Disturbance obser gain k3. */
real32_T PosCtrl_Ki = 0.0F;            /* PI integral term for position controller. */
real32_T PosCtrl_Kp = 80.0F;           /* PI proportional term for position controller. */
real32_T TsMain = 0.001F;              /* Main sampling time (1khz) */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
