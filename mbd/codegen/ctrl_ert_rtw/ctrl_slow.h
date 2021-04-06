/*
 * Code generation for system system '<Root>/ctrl_slow'
 * For more details, see corresponding source file ctrl_slow.c
 *
 */

#ifndef RTW_HEADER_ctrl_slow_h_
#define RTW_HEADER_ctrl_slow_h_
#include <math.h>
#ifndef ctrl_COMMON_INCLUDES_
# define ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ctrl_COMMON_INCLUDES_ */

#include "ctrl_types.h"

/* Block signals and states (default storage) for system '<Root>/ctrl_slow' */
typedef struct {
  real32_T DiscreteTimeIntegrator1;    /* '<S31>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator;     /* '<S31>/Discrete-Time Integrator' */
  real32_T OutportBufferForGrd;        /* '<S31>/Discrete-Time Integrator' */
  real32_T OutportBufferForRef;        /* '<S31>/Discrete-Time Integrator1' */
  real32_T Saturation;                 /* '<S30>/Saturation' */
  real32_T Add;                        /* '<S35>/Add' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S31>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S31>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S38>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S36>/Discrete-Time Integrator' */
  boolean_T TrackDiff_MODE;            /* '<S26>/TrackDiff' */
  boolean_T SpdCtrl_MODE;              /* '<S26>/SpdCtrl' */
  boolean_T PosCtl_MODE;               /* '<S26>/PosCtl' */
} DW_ctrl_slow;

/* Parameters for system: '<Root>/ctrl_slow' */
struct P_ctrl_slow_ {
  real_T PICtrl_PI_Ki;                 /* Mask Parameter: PICtrl_PI_Ki
                                        * Referenced by: '<S35>/Gain'
                                        */
  MtrCtrlMd CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                        * Referenced by: '<S33>/Constant'
                                        */
  MtrCtrlMd CompareToConstant1_const;  /* Mask Parameter: CompareToConstant1_const
                                        * Referenced by: '<S34>/Constant'
                                        */
  real32_T TrackDiff_h0;               /* Mask Parameter: TrackDiff_h0
                                        * Referenced by: '<S39>/Gain3'
                                        */
  real32_T PICtrl_max_lim;             /* Mask Parameter: PICtrl_max_lim
                                        * Referenced by: '<S36>/Discrete-Time Integrator'
                                        */
  real32_T PICtrlVaryingGains_max_lim; /* Mask Parameter: PICtrlVaryingGains_max_lim
                                        * Referenced by: '<S38>/Discrete-Time Integrator'
                                        */
  real32_T PICtrl_min_lim;             /* Mask Parameter: PICtrl_min_lim
                                        * Referenced by: '<S36>/Discrete-Time Integrator'
                                        */
  real32_T PICtrlVaryingGains_min_lim; /* Mask Parameter: PICtrlVaryingGains_min_lim
                                        * Referenced by: '<S38>/Discrete-Time Integrator'
                                        */
  AutoCalSt Constant1_Value;           /* Expression: AutoCalSt.Done
                                        * Referenced by: '<S27>/Constant1'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S26>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S26>/Saturation1'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S28>/Constant'
                                        */
  real32_T Saturation_UpperSat;        /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S26>/Saturation'
                                        */
  real32_T Saturation_LowerSat;        /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S26>/Saturation'
                                        */
  real32_T Constant1_Value_j;          /* Computed Parameter: Constant1_Value_j
                                        * Referenced by: '<S28>/Constant1'
                                        */
  real32_T MtrSpdTgt_Y0;               /* Computed Parameter: MtrSpdTgt_Y0
                                        * Referenced by: '<S29>/MtrSpdTgt'
                                        */
  real32_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                           * Referenced by: '<S36>/Discrete-Time Integrator'
                                           */
  real32_T DiscreteTimeIntegrator_IC;  /* Computed Parameter: DiscreteTimeIntegrator_IC
                                        * Referenced by: '<S36>/Discrete-Time Integrator'
                                        */
  real32_T Ctrl_Y0;                    /* Computed Parameter: Ctrl_Y0
                                        * Referenced by: '<S30>/Ctrl'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_a;/* Computed Parameter: DiscreteTimeIntegrator_gainva_a
                                            * Referenced by: '<S38>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_k;/* Computed Parameter: DiscreteTimeIntegrator_IC_k
                                        * Referenced by: '<S38>/Discrete-Time Integrator'
                                        */
  real32_T Saturation_UpperSat_k;      /* Computed Parameter: Saturation_UpperSat_k
                                        * Referenced by: '<S30>/Saturation'
                                        */
  real32_T Saturation_LowerSat_e;      /* Computed Parameter: Saturation_LowerSat_e
                                        * Referenced by: '<S30>/Saturation'
                                        */
  real32_T Ref_Y0;                     /* Computed Parameter: Ref_Y0
                                        * Referenced by: '<S31>/Ref'
                                        */
  real32_T Grd_Y0;                     /* Computed Parameter: Grd_Y0
                                        * Referenced by: '<S31>/Grd'
                                        */
  real32_T DiscreteTimeIntegrator1_gainval;/* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                            * Referenced by: '<S31>/Discrete-Time Integrator1'
                                            */
  real32_T DiscreteTimeIntegrator1_IC; /* Computed Parameter: DiscreteTimeIntegrator1_IC
                                        * Referenced by: '<S31>/Discrete-Time Integrator1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_b;/* Computed Parameter: DiscreteTimeIntegrator_gainva_b
                                            * Referenced by: '<S31>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_e;/* Computed Parameter: DiscreteTimeIntegrator_IC_e
                                        * Referenced by: '<S31>/Discrete-Time Integrator'
                                        */
  real32_T d_Value;                    /* Computed Parameter: d_Value
                                        * Referenced by: '<S39>/d'
                                        */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S40>/Gain'
                                        */
  real32_T Gain_Gain_o;                /* Computed Parameter: Gain_Gain_o
                                        * Referenced by: '<S41>/Gain'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S45>/Gain1'
                                        */
  real32_T Gain_Gain_m;                /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S44>/Gain'
                                        */
  real32_T Gain_Gain_c;                /* Computed Parameter: Gain_Gain_c
                                        * Referenced by: '<S43>/Gain'
                                        */
  real32_T Constant2_Value;            /* Expression: MotorParams.K
                                        * Referenced by: '<S27>/Constant2'
                                        */
  real32_T Constant3_Value;            /* Expression: MotorParams.J
                                        * Referenced by: '<S27>/Constant3'
                                        */
  real32_T Constant4_Value;            /* Expression: MotorParams.Kf
                                        * Referenced by: '<S27>/Constant4'
                                        */
  real32_T MtrIfbkTgt_Y0;              /* Computed Parameter: MtrIfbkTgt_Y0
                                        * Referenced by: '<S2>/MtrIfbkTgt'
                                        */
  real32_T MtrSpdOut_Y0;               /* Computed Parameter: MtrSpdOut_Y0
                                        * Referenced by: '<S2>/MtrSpdOut'
                                        */
  real32_T MtrDistEst_Y0;              /* Computed Parameter: MtrDistEst_Y0
                                        * Referenced by: '<S2>/MtrDistEst'
                                        */
  real32_T MtrPosEst_Y0;               /* Computed Parameter: MtrPosEst_Y0
                                        * Referenced by: '<S2>/MtrPosEst'
                                        */
  real32_T Gain1_Gain_f;               /* Computed Parameter: Gain1_Gain_f
                                        * Referenced by: '<S24>/Gain1'
                                        */
  real32_T TO_RPM_Gain;                /* Computed Parameter: TO_RPM_Gain
                                        * Referenced by: '<S2>/TO_RPM'
                                        */
  real32_T Gain1_Gain_j;               /* Computed Parameter: Gain1_Gain_j
                                        * Referenced by: '<S25>/Gain1'
                                        */
  real32_T DataStoreMemory_InitialValue;/* Computed Parameter: DataStoreMemory_InitialValue
                                         * Referenced by: '<S2>/Data Store Memory'
                                         */
  real32_T DataStoreMemory1_InitialValue;/* Computed Parameter: DataStoreMemory1_InitialValue
                                          * Referenced by: '<S2>/Data Store Memory1'
                                          */
  real32_T DataStoreMemory2_InitialValue;/* Computed Parameter: DataStoreMemory2_InitialValue
                                          * Referenced by: '<S2>/Data Store Memory2'
                                          */
};

extern void ctrl_slow_Init(real32_T *rty_MtrIfbkTgt, real32_T *rty_MtrSpdOut,
  real32_T *rty_MtrRef, real32_T *rty_MtrDistEst, real32_T *rty_MtrPosEst,
  DW_ctrl_slow *localDW, P_ctrl_slow *localP);
extern void ctrl_slow(real32_T rtu_MtrTgt, real32_T rtu_MtrPos, real32_T
                      rtu_MtrSpd, real32_T rtu_MtrDistTrq, real32_T rtu_PosEst,
                      MtrCtrlMd rtu_MtrCtrlMd, const DBG_BUS *rtu_Params,
                      real32_T *rty_MtrIfbkTgt, real32_T *rty_MtrSpdOut,
                      real32_T *rty_MtrRef, real32_T *rty_MtrDistEst, real32_T
                      *rty_MtrPosEst, DW_ctrl_slow *localDW, P_ctrl_slow *localP);

#endif                                 /* RTW_HEADER_ctrl_slow_h_ */
