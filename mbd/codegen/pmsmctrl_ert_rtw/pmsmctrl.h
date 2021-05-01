/*
 * pmsmctrl.h
 *
 * Code generation for model "pmsmctrl".
 *
 * Model version              : 1.198
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_pmsmctrl_h_
#define RTW_HEADER_pmsmctrl_h_
#include "rtwtypes.h"
#include <float.h>
#include <math.h>
#ifndef pmsmctrl_COMMON_INCLUDES_
# define pmsmctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pmsmctrl_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef DEFINED_TYPEDEF_FOR_MtrCtrlMd_
#define DEFINED_TYPEDEF_FOR_MtrCtrlMd_

typedef enum {
  PwmCtrlMd = 0,                       /* Default value */
  IfbkCtrlMd = 1,
  TrqCtrlMd = 2,
  SpdCtrlMd = 3,
  PosCtrlMd = 4,
  StepDirCtrlMd = 5,
  OffCtrlMd = 255
} MtrCtrlMd;

#endif

/* Block signals (default storage) */
typedef struct {
  real32_T OutportBufferForvdq0_ctrl[3];
  real32_T DataTypeConversion4;        /* '<S2>/Data Type Conversion4' */
  real32_T DiscreteTimeIntegrator1;    /* '<S31>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator;     /* '<S31>/Discrete-Time Integrator' */
  real32_T OutportBufferForGrd;        /* '<S31>/Discrete-Time Integrator' */
  real32_T Add;                        /* '<S29>/Add' */
  real32_T DataTypeConversion1;        /* '<S1>/Data Type Conversion1' */
  real32_T Saturation;                 /* '<S28>/Saturation' */
} B;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T UnitDelay_DSTATE[3];        /* '<S14>/Unit Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S40>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S31>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE_h;/* '<S31>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S30>/Discrete-Time Integrator' */
  real32_T Accumulator_DSTATE;         /* '<S1>/Accumulator' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S11>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_ke;/* '<S12>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_p;/* '<S10>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_n;/* '<S23>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_oy;/* '<S21>/Discrete-Time Integrator' */
  boolean_T SpdCtrl_MODE;              /* '<S2>/SpdCtrl' */
  boolean_T PosTrackDiff_MODE;         /* '<S27>/PosTrackDiff' */
  boolean_T PosCtl_MODE;               /* '<S2>/PosCtl' */
  boolean_T IfbkCtrl_MODE;             /* '<S6>/IfbkCtrl' */
} DW;

/* Self model data, for system '<Root>' */
struct tag_RTM {
  DW dwork;
  B blockIO;
};

/* Model entry point functions */
extern void Pmsm_InitCtrl(RT_MODEL *const pmsmctrl_M);

/* Exported entry point function */
extern void Trig_Pmsm_MotnCtrl(RT_MODEL *const pmsmctrl_M, int32_T
  rtU_MtrIf_EncCnts, MtrCtrlMd rtU_MtrIf_CtrlMd, real32_T rtU_MtrIf_Tgt,
  real32_T *rtY_MtrIf_SpdAct);

/* Exported entry point function */
extern void Trig_Pmsm_Foc(RT_MODEL *const pmsmctrl_M, real32_T
  rtU_MtrIf_IfbkAct[3], MtrCtrlMd rtU_MtrIf_CtrlMd, real32_T rtY_MtrIf_ModWave[3],
  real32_T rtY_MtrIf_PwmDc[3], real32_T *rtY_MtrIf_TrqAct);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Product1' : Unused code path elimination
 * Block '<Root>/DistObs' : Unused code path elimination
 * Block '<Root>/IfbkCtrl' : Unused code path elimination
 * Block '<Root>/Voltages' : Unused code path elimination
 * Block '<S2>/Gain2' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/SpdCtrl' : Unused code path elimination
 * Block '<S1>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S5>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S17>/Switch' : Eliminated due to constant selection input
 * Block '<S18>/Switch' : Eliminated due to constant selection input
 * Block '<S1>/Switch1' : Eliminated due to constant selection input
 * Block '<S2>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S2>/Data Type Conversion3' : Eliminate redundant data type conversion
 * Block '<S2>/Switch2' : Eliminated due to constant selection input
 * Block '<S1>/Constant1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion4' : Unused code path elimination
 * Block '<S1>/Gain4' : Unused code path elimination
 * Block '<S15>/Constant3' : Unused code path elimination
 * Block '<S15>/Constant4' : Unused code path elimination
 * Block '<S17>/Constant2' : Unused code path elimination
 * Block '<S17>/Constant3' : Unused code path elimination
 * Block '<S17>/Product' : Unused code path elimination
 * Block '<S18>/Constant2' : Unused code path elimination
 * Block '<S18>/Constant3' : Unused code path elimination
 * Block '<S18>/Product' : Unused code path elimination
 * Block '<S2>/Constant3' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pmsmctrl'
 * '<S1>'   : 'pmsmctrl/CtrlFast'
 * '<S2>'   : 'pmsmctrl/CtrlMain'
 * '<S3>'   : 'pmsmctrl/CtrlFast/Compare To Constant1'
 * '<S4>'   : 'pmsmctrl/CtrlFast/DistObsJ'
 * '<S5>'   : 'pmsmctrl/CtrlFast/Inverse Park Transform'
 * '<S6>'   : 'pmsmctrl/CtrlFast/Subsystem'
 * '<S7>'   : 'pmsmctrl/CtrlFast/calc_angle'
 * '<S8>'   : 'pmsmctrl/CtrlFast/calc_dq0_vec'
 * '<S9>'   : 'pmsmctrl/CtrlFast/calc_pwm_dc'
 * '<S10>'  : 'pmsmctrl/CtrlFast/DistObsJ/Integrator'
 * '<S11>'  : 'pmsmctrl/CtrlFast/DistObsJ/Integrator1'
 * '<S12>'  : 'pmsmctrl/CtrlFast/DistObsJ/Integrator2'
 * '<S13>'  : 'pmsmctrl/CtrlFast/Subsystem/Compare To Constant'
 * '<S14>'  : 'pmsmctrl/CtrlFast/Subsystem/D-1LPF'
 * '<S15>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl'
 * '<S16>'  : 'pmsmctrl/CtrlFast/Subsystem/Park Transform'
 * '<S17>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_d_ctrl'
 * '<S18>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_q_ctrl'
 * '<S19>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/mtr_coupling_bemf_comp'
 * '<S20>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_d_ctrl/PI-Ctrl-Varying-Gains'
 * '<S21>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_d_ctrl/PI-Ctrl-Varying-Gains/Integrator'
 * '<S22>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_q_ctrl/PI-Ctrl-Varying-Gains'
 * '<S23>'  : 'pmsmctrl/CtrlFast/Subsystem/IfbkCtrl/ifbk_q_ctrl/PI-Ctrl-Varying-Gains/Integrator'
 * '<S24>'  : 'pmsmctrl/CtrlMain/Compare To Constant'
 * '<S25>'  : 'pmsmctrl/CtrlMain/Compare To Constant1'
 * '<S26>'  : 'pmsmctrl/CtrlMain/PosCtl'
 * '<S27>'  : 'pmsmctrl/CtrlMain/PosTrajPlan'
 * '<S28>'  : 'pmsmctrl/CtrlMain/SpdCtrl'
 * '<S29>'  : 'pmsmctrl/CtrlMain/PosCtl/PI-Ctrl'
 * '<S30>'  : 'pmsmctrl/CtrlMain/PosCtl/PI-Ctrl/Integrator'
 * '<S31>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff'
 * '<S32>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan'
 * '<S33>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/a1_calc'
 * '<S34>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/a2_calc'
 * '<S35>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/a_calc'
 * '<S36>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/fhan_calc'
 * '<S37>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/sa_calc'
 * '<S38>'  : 'pmsmctrl/CtrlMain/PosTrajPlan/PosTrackDiff/fhan/sy_calc'
 * '<S39>'  : 'pmsmctrl/CtrlMain/SpdCtrl/PI-Ctrl-Varying-Gains'
 * '<S40>'  : 'pmsmctrl/CtrlMain/SpdCtrl/PI-Ctrl-Varying-Gains/Integrator'
 */

/*-
 * Requirements for '<Root>': pmsmctrl
 */
#endif                                 /* RTW_HEADER_pmsmctrl_h_ */
