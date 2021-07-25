/*
 * File: cfg_params.h
 *
 * Code generated for Simulink model 'pmsm_ctrl'.
 *
 * Model version                  : 1.765
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sat Jul 24 19:18:11 2021
 */

#ifndef RTW_HEADER_cfg_params_h_
#define RTW_HEADER_cfg_params_h_
#include "rtwtypes.h"
#include "pmsm_ctrl_types.h"

/* Exported data declaration */

/* Declaration for custom storage class: ExportToFile */
extern real32_T Cfg_AnglOfsCalPwmDuty; /* Duty cycle during angle offset cal */
extern boolean_T Cfg_AutoCalEnbl;      /* Enable ifbk loop autocalibration at startup */
extern boolean_T Cfg_EnblDynComp;      /* Enable x-coupling and b-emf comp */
extern boolean_T Cfg_EnblTrajPlan;     /* Enable trajectory planner (speed and position). */
extern int32_T Cfg_EncCnts;            /* Encoder counts */
extern real32_T Cfg_EncOfsCalPwmDuty;  /* Duty cycle during encoder offset cal */
extern real32_T Cfg_IfbkCtrlBW;        /* Current controller bandwith (rad/s) */
extern real32_T Cfg_IndCalPwmDuty;     /* Duty cycle during inductance calibration */
extern real32_T Cfg_Ls;                /* Motor inductance (phase) */
extern real32_T Cfg_MFlux;             /* Motor flux */
extern real32_T Cfg_MtrJm;             /* Motor rotor inertia. */
extern real32_T Cfg_MtrKf;             /* Rotor friction coefficient */
extern real32_T Cfg_MtrKtrq;           /* Motor torque constant */
extern uint8_T Cfg_PolePairs;          /* Number of pole pairs. */
extern real32_T Cfg_ResCalPwmDuty;     /* Duty cycle during resistance calibration */
extern real32_T Cfg_Rs;                /* Motor resistance (phase). */
extern real32_T Cfg_SpdCtrlBW;         /* Speed controller bandwith. */
extern boolean_T Cfg_SpdSnsEnbl;       /* System has speed sensor. */
extern int32_T Cfg_StepToEncCnts;      /* Defines how many encoder counts per step. */
extern boolean_T Cfg_UseObsPosEst;     /* Use observer position estimate. */
extern boolean_T Cfg_UseSpdPll;        /* Use Speed PLL instead of observer for speed estimate. */
extern real32_T Cfg_VBus;              /* Bus voltage */
extern real32_T DistObs_J;             /* Motor Inertia at Disturbance Observer. */
extern real32_T DistObs_K1;            /* Disturbance obser gain k1. */
extern real32_T DistObs_K2;            /* Disturbance obser gain k2. */
extern real32_T DistObs_K3;            /* Disturbance obser gain k3. */
extern real32_T PosCtrl_Ki;            /* PI integral term for position controller. */
extern real32_T PosCtrl_Kp;            /* PI proportional term for position controller. */
extern real32_T TsMain;                /* Main sampling time (1khz) */

#endif                                 /* RTW_HEADER_cfg_params_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
