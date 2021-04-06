/*
 * ctrl.h
 *
 * Code generation for model "ctrl".
 *
 * Model version              : 1.904
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_ctrl_h_
#define RTW_HEADER_ctrl_h_
#ifndef ctrl_COMMON_INCLUDES_
# define ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ctrl_COMMON_INCLUDES_ */

#include "ctrl_types.h"

/* Child system includes */
#include "ctrl_fast.h"
#include "ctrl_slow.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_ctrl_slow ctrl_slow_e;            /* '<Root>/ctrl_slow' */
  DW_ctrl_fast ctrl_fast_f;            /* '<Root>/ctrl_fast' */
  real32_T Product1;                   /* '<S14>/Product1' */
  real32_T DiscreteTimeIntegrator;     /* '<S17>/Discrete-Time Integrator' */
  real32_T MtrSpdOut;                  /* '<S5>/Multiport Switch' */
  MtrCtrlMd Switch1;                   /* '<S7>/Switch1' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real32_T MtrIf_Tgt;                  /* '<Root>/MtrIf_Tgt' */
  real32_T MtrIf_Pos;                  /* '<Root>/MtrIf_Pos' */
  real32_T MtrIf_IfbkAct;              /* '<Root>/MtrIf_IfbkAct' */
  real32_T MtrIf_SpdSns;               /* '<Root>/MtrIf_SpdSns' */
  MtrCtrlMd MtrIf_CtrlMd;              /* '<Root>/MtrIf_CtrlMd' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T MtrIf_CtrlCmd;              /* '<Root>/MtrIf_CtrlCmd' */
  real32_T MtrIf_SpdEst;               /* '<Root>/MtrIf_SpdEst' */
  real32_T MtrIf_IfbkTgt;              /* '<Root>/MtrIf_IfbkTgt' */
  real32_T MtrIf_Ref;                  /* '<Root>/MtrIf_Ref' */
  real32_T MtrIf_DistTrqEst;           /* '<Root>/MtrIf_DistTrqEst' */
  real32_T MtrIf_PosEst;               /* '<Root>/MtrIf_PosEst' */
  DBG_BUS DBG_BUS_OUT;                 /* '<Root>/DBG_BUS_OUT' */
} ExtY;

/* Parameters (default storage) */
struct P_ {
  struct_CI8nDHNKFYq3miU7okN8NH MotorParams;/* Variable: MotorParams
                                             * Referenced by:
                                             *   '<S11>/Constant'
                                             *   '<S11>/Constant1'
                                             */
  int32_T Cfg_IndIDCntThshld;          /* Variable: Cfg_IndIDCntThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_IndIDCoolDownTicks;      /* Variable: Cfg_IndIDCoolDownTicks
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_IndIDSwTicks;            /* Variable: Cfg_IndIDSwTicks
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_OfsIDCntThshld;          /* Variable: Cfg_OfsIDCntThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_ResIDCntThshld;          /* Variable: Cfg_ResIDCntThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_ResIDCoolDownTicks;      /* Variable: Cfg_ResIDCoolDownTicks
                                        * Referenced by: '<S3>/autotune'
                                        */
  int32_T Cfg_TrqCnstIDCntThshld;      /* Variable: Cfg_TrqCnstIDCntThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_IfbkCtrlBW;             /* Variable: Cfg_IfbkCtrlBW
                                        * Referenced by:
                                        *   '<S11>/Constant'
                                        *   '<S11>/Constant1'
                                        *   '<S11>/Constant3'
                                        */
  real32_T Cfg_IndIDMaxThshld;         /* Variable: Cfg_IndIDMaxThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_IndIDMinThshld;         /* Variable: Cfg_IndIDMinThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_IndIDMtrVin;            /* Variable: Cfg_IndIDMtrVin
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_IndIDTs;                /* Variable: Cfg_IndIDTs
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_ResIDMaxThshld;         /* Variable: Cfg_ResIDMaxThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_ResIDMinThshld;         /* Variable: Cfg_ResIDMinThshld
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_ResIDMtrVin;            /* Variable: Cfg_ResIDMtrVin
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T Cfg_SpdCtrlBW;              /* Variable: Cfg_SpdCtrlBW
                                        * Referenced by: '<S30>/Constant3'
                                        */
  real32_T Cfg_TrqCnstIDMtrVin;        /* Variable: Cfg_TrqCnstIDMtrVin
                                        * Referenced by: '<S3>/autotune'
                                        */
  real32_T DistObs_K1;                 /* Variable: DistObs_K1
                                        * Referenced by: '<S14>/Gain3'
                                        */
  real32_T DistObs_K2;                 /* Variable: DistObs_K2
                                        * Referenced by: '<S14>/Gain1'
                                        */
  real32_T DistObs_K3;                 /* Variable: DistObs_K3
                                        * Referenced by: '<S14>/Gain'
                                        */
  real32_T PosCtrl_Kp;                 /* Variable: PosCtrl_Kp
                                        * Referenced by: '<S35>/Gain1'
                                        */
  real32_T SmDiff_FiltCnst;            /* Variable: SmDiff_FiltCnst
                                        * Referenced by: '<S20>/Constant'
                                        */
  real32_T SmDiff_Ki;                  /* Variable: SmDiff_Ki
                                        * Referenced by: '<S21>/Gain2'
                                        */
  real32_T SmDiff_Kp;                  /* Variable: SmDiff_Kp
                                        * Referenced by: '<S21>/Gain1'
                                        */
  real32_T TsFast;                     /* Variable: TsFast
                                        * Referenced by: '<S3>/autotune'
                                        */
  uint32_T Cfg_SpdSnsSrc;              /* Variable: Cfg_SpdSnsSrc
                                        * Referenced by: '<S5>/Constant'
                                        */
  boolean_T Cfg_AutoCalEnbl;           /* Variable: Cfg_AutoCalEnbl
                                        * Referenced by:
                                        *   '<S3>/autotune'
                                        *   '<S27>/Constant'
                                        *   '<S11>/Constant2'
                                        */
  boolean_T Cfg_EnblLoadObs;           /* Variable: Cfg_EnblLoadObs
                                        * Referenced by: '<S13>/Constant1'
                                        */
  P_ctrl_slow ctrl_slow_e;             /* '<Root>/ctrl_slow' */
  P_ctrl_fast ctrl_fast_f;             /* '<Root>/ctrl_fast' */
};

/* Block parameters (default storage) */
extern P rtP;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* External data declarations for dependent source files */
extern const DBG_BUS ctrl_rtZDBG_BUS;  /* DBG_BUS ground */

/* Model entry point functions */
extern void Ctrl_Init(void);

/* Exported entry point function */
extern void Ctrl_Slow(void);

/* Exported entry point function */
extern void Ctrl_Fast(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/CurCtl' : Unused code path elimination
 * Block '<Root>/Speeds' : Unused code path elimination
 * Block '<S46>/Gain1' : Unused code path elimination
 * Block '<S32>/Multiport Switch' : Unused code path elimination
 * Block '<S32>/TO_RADpS' : Unused code path elimination
 * Block '<S47>/Constant' : Unused code path elimination
 * Block '<S47>/Product' : Unused code path elimination
 * Block '<S47>/Product1' : Unused code path elimination
 * Block '<S47>/Round' : Unused code path elimination
 * Block '<Root>/SpdCtl' : Unused code path elimination
 * Block '<S5>/Signal Copy2' : Eliminate redundant signal conversion block
 * Block '<S5>/Signal Copy4' : Eliminate redundant signal conversion block
 * Block '<S12>/Signal Conversion' : Eliminate redundant signal conversion block
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
 * '<Root>' : 'ctrl'
 * '<S1>'   : 'ctrl/ctrl_fast'
 * '<S2>'   : 'ctrl/ctrl_slow'
 * '<S3>'   : 'ctrl/ctrl_fast/AutoCalMgr'
 * '<S4>'   : 'ctrl/ctrl_fast/Degrees to Radians'
 * '<S5>'   : 'ctrl/ctrl_fast/IfbkCtl'
 * '<S6>'   : 'ctrl/ctrl_fast/AutoCalMgr/autotune'
 * '<S7>'   : 'ctrl/ctrl_fast/AutoCalMgr/autotune_ctrlmd_override'
 * '<S8>'   : 'ctrl/ctrl_fast/AutoCalMgr/autotune_ctrlmd_override/autocal_override'
 * '<S9>'   : 'ctrl/ctrl_fast/IfbkCtl/Compare To Constant'
 * '<S10>'  : 'ctrl/ctrl_fast/IfbkCtl/DistObs'
 * '<S11>'  : 'ctrl/ctrl_fast/IfbkCtl/IfbkCtrl'
 * '<S12>'  : 'ctrl/ctrl_fast/IfbkCtl/SpeedObserver'
 * '<S13>'  : 'ctrl/ctrl_fast/IfbkCtl/TrqToIfbkCmd'
 * '<S14>'  : 'ctrl/ctrl_fast/IfbkCtl/DistObs/DistObsJ'
 * '<S15>'  : 'ctrl/ctrl_fast/IfbkCtl/DistObs/DistObsJ/Integrator'
 * '<S16>'  : 'ctrl/ctrl_fast/IfbkCtl/DistObs/DistObsJ/Integrator1'
 * '<S17>'  : 'ctrl/ctrl_fast/IfbkCtl/DistObs/DistObsJ/Integrator2'
 * '<S18>'  : 'ctrl/ctrl_fast/IfbkCtl/IfbkCtrl/PI-Ctrl-Varying-Gains'
 * '<S19>'  : 'ctrl/ctrl_fast/IfbkCtl/IfbkCtrl/PI-Ctrl-Varying-Gains/Integrator'
 * '<S20>'  : 'ctrl/ctrl_fast/IfbkCtl/SpeedObserver/D-1LPF'
 * '<S21>'  : 'ctrl/ctrl_fast/IfbkCtl/SpeedObserver/SM-Differentiator'
 * '<S22>'  : 'ctrl/ctrl_fast/IfbkCtl/SpeedObserver/SM-Differentiator/Integrator'
 * '<S23>'  : 'ctrl/ctrl_fast/IfbkCtl/SpeedObserver/SM-Differentiator/Integrator1'
 * '<S24>'  : 'ctrl/ctrl_slow/Degrees to Radians'
 * '<S25>'  : 'ctrl/ctrl_slow/Degrees to Radians1'
 * '<S26>'  : 'ctrl/ctrl_slow/MtrCtrl'
 * '<S27>'  : 'ctrl/ctrl_slow/write_autotune_params'
 * '<S28>'  : 'ctrl/ctrl_slow/MtrCtrl/CtrlMngr'
 * '<S29>'  : 'ctrl/ctrl_slow/MtrCtrl/PosCtl'
 * '<S30>'  : 'ctrl/ctrl_slow/MtrCtrl/SpdCtrl'
 * '<S31>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff'
 * '<S32>'  : 'ctrl/ctrl_slow/MtrCtrl/scale_tgt'
 * '<S33>'  : 'ctrl/ctrl_slow/MtrCtrl/CtrlMngr/Compare To Constant'
 * '<S34>'  : 'ctrl/ctrl_slow/MtrCtrl/CtrlMngr/Compare To Constant1'
 * '<S35>'  : 'ctrl/ctrl_slow/MtrCtrl/PosCtl/PI-Ctrl'
 * '<S36>'  : 'ctrl/ctrl_slow/MtrCtrl/PosCtl/PI-Ctrl/Integrator'
 * '<S37>'  : 'ctrl/ctrl_slow/MtrCtrl/SpdCtrl/PI-Ctrl-Varying-Gains'
 * '<S38>'  : 'ctrl/ctrl_slow/MtrCtrl/SpdCtrl/PI-Ctrl-Varying-Gains/Integrator'
 * '<S39>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan'
 * '<S40>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/a1_calc'
 * '<S41>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/a2_calc'
 * '<S42>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/a_calc'
 * '<S43>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/fhan_calc'
 * '<S44>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/sa_calc'
 * '<S45>'  : 'ctrl/ctrl_slow/MtrCtrl/TrackDiff/fhan/sy_calc'
 * '<S46>'  : 'ctrl/ctrl_slow/MtrCtrl/scale_tgt/Degrees to Radians'
 * '<S47>'  : 'ctrl/ctrl_slow/MtrCtrl/scale_tgt/encoder_quant'
 */
#endif                                 /* RTW_HEADER_ctrl_h_ */
