/*
 * Code generation for system system '<Root>/ctrl_fast'
 * For more details, see corresponding source file ctrl_fast.c
 *
 */

#ifndef RTW_HEADER_ctrl_fast_h_
#define RTW_HEADER_ctrl_fast_h_
#include <math.h>
#ifndef ctrl_COMMON_INCLUDES_
# define ctrl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ctrl_COMMON_INCLUDES_ */

#include "ctrl_types.h"

/* Block signals and states (default storage) for system '<Root>/ctrl_fast' */
typedef struct {
  real32_T Add;                        /* '<S18>/Add' */
  real32_T vout;                       /* '<S3>/autotune' */
  real32_T Lest;                       /* '<S3>/autotune' */
  real32_T Rest;                       /* '<S3>/autotune' */
  real32_T KTrqEst;                    /* '<S3>/autotune' */
  real32_T ifbk_ofs;                   /* '<S3>/autotune' */
  real32_T KFrcEst;                    /* '<S3>/autotune' */
  real32_T JEst;                       /* '<S3>/autotune' */
  real32_T IfbkSteady;                 /* '<S3>/autotune' */
  real32_T IfbkMax;                    /* '<S3>/autotune' */
  real32_T SpdMax;                     /* '<S3>/autotune' */
  real32_T UnitDelay_DSTATE;           /* '<S1>/Unit Delay' */
  real32_T UnitDelay_DSTATE_i;         /* '<S3>/Unit Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S15>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_k;/* '<S17>/Discrete-Time Integrator' */
  real32_T UnitDelay_DSTATE_f;         /* '<S14>/Unit Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_j;/* '<S16>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTAT_j4;/* '<S23>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator_DSTATE_o;/* '<S22>/Discrete-Time Integrator' */
  real32_T UnitDelay_DSTATE_fb;        /* '<S20>/Unit Delay' */
  real32_T DiscreteTimeIntegrator_DSTATE_g;/* '<S19>/Discrete-Time Integrator' */
  real32_T ifbk_neg;                   /* '<S3>/autotune' */
  real32_T ifbk_pos;                   /* '<S3>/autotune' */
  real32_T spd_max;                    /* '<S3>/autotune' */
  real32_T ifbk_max;                   /* '<S3>/autotune' */
  int32_T cycle_cnt;                   /* '<S3>/autotune' */
  int32_T ind_id_cnt;                  /* '<S3>/autotune' */
  uint32_T temporalCounter_i1;         /* '<S3>/autotune' */
  AutoCalSt status;                    /* '<S3>/autotune' */
  uint8_T is_active_c1_ctrl;           /* '<S3>/autotune' */
  uint8_T is_c1_ctrl;                  /* '<S3>/autotune' */
  uint8_T is_autocal_in_progress;      /* '<S3>/autotune' */
  uint8_T is_ifbk_offset_id;           /* '<S3>/autotune' */
  uint8_T is_inductance_id;            /* '<S3>/autotune' */
  uint8_T is_inductance_switching;     /* '<S3>/autotune' */
  uint8_T is_resistance_id;            /* '<S3>/autotune' */
  uint8_T is_motor_inertia_id;         /* '<S3>/autotune' */
  uint8_T is_motor_constant_id;        /* '<S3>/autotune' */
  boolean_T IfbkCtrl_MODE;             /* '<S5>/IfbkCtrl' */
} DW_ctrl_fast;

/* Parameters for system: '<Root>/ctrl_fast' */
struct P_ctrl_fast_ {
  MtrCtrlMd CompareToConstant_const;   /* Mask Parameter: CompareToConstant_const
                                        * Referenced by: '<S9>/Constant'
                                        */
  real32_T PICtrlVaryingGains_max_lim; /* Mask Parameter: PICtrlVaryingGains_max_lim
                                        * Referenced by: '<S19>/Discrete-Time Integrator'
                                        */
  real32_T Integrator_max_lim;         /* Mask Parameter: Integrator_max_lim
                                        * Referenced by: '<S15>/Discrete-Time Integrator'
                                        */
  real32_T Integrator2_max_lim;        /* Mask Parameter: Integrator2_max_lim
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  real32_T Integrator1_max_lim;        /* Mask Parameter: Integrator1_max_lim
                                        * Referenced by: '<S16>/Discrete-Time Integrator'
                                        */
  real32_T Integrator1_max_lim_o;      /* Mask Parameter: Integrator1_max_lim_o
                                        * Referenced by: '<S23>/Discrete-Time Integrator'
                                        */
  real32_T Integrator_max_lim_k;       /* Mask Parameter: Integrator_max_lim_k
                                        * Referenced by: '<S22>/Discrete-Time Integrator'
                                        */
  real32_T PICtrlVaryingGains_min_lim; /* Mask Parameter: PICtrlVaryingGains_min_lim
                                        * Referenced by: '<S19>/Discrete-Time Integrator'
                                        */
  real32_T Integrator_min_lim;         /* Mask Parameter: Integrator_min_lim
                                        * Referenced by: '<S15>/Discrete-Time Integrator'
                                        */
  real32_T Integrator2_min_lim;        /* Mask Parameter: Integrator2_min_lim
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  real32_T Integrator1_min_lim;        /* Mask Parameter: Integrator1_min_lim
                                        * Referenced by: '<S16>/Discrete-Time Integrator'
                                        */
  real32_T Integrator1_min_lim_i;      /* Mask Parameter: Integrator1_min_lim_i
                                        * Referenced by: '<S23>/Discrete-Time Integrator'
                                        */
  real32_T Integrator_min_lim_i;       /* Mask Parameter: Integrator_min_lim_i
                                        * Referenced by: '<S22>/Discrete-Time Integrator'
                                        */
  DBG_BUS DBG_BUS_Y0;                  /* Computed Parameter: DBG_BUS_Y0
                                        * Referenced by: '<S1>/DBG_BUS'
                                        */
  AutoCalSt Constant_Value;            /* Expression: AutoCalSt.Done
                                        * Referenced by: '<S8>/Constant'
                                        */
  AutoCalSt Constant1_Value;           /* Expression: AutoCalSt.NotStarted
                                        * Referenced by: '<S8>/Constant1'
                                        */
  MtrCtrlMd Constant_Value_o;          /* Expression: MtrCtrlMd.OpnLoopCtrlMd
                                        * Referenced by: '<S7>/Constant'
                                        */
  MtrCtrlMd MtrCtrlMd_Y0;              /* Computed Parameter: MtrCtrlMd_Y0
                                        * Referenced by: '<S1>/MtrCtrlMd'
                                        */
  real32_T Gain1_Gain;                 /* Expression: MotorParams.K
                                        * Referenced by: '<S5>/Gain1'
                                        */
  real32_T Ctrl_Y0;                    /* Computed Parameter: Ctrl_Y0
                                        * Referenced by: '<S11>/Ctrl'
                                        */
  real32_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                           * Referenced by: '<S19>/Discrete-Time Integrator'
                                           */
  real32_T DiscreteTimeIntegrator_IC;  /* Computed Parameter: DiscreteTimeIntegrator_IC
                                        * Referenced by: '<S19>/Discrete-Time Integrator'
                                        */
  real32_T Constant2_Value;            /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S13>/Constant2'
                                        */
  real32_T MtrSpd_Y0;                  /* Computed Parameter: MtrSpd_Y0
                                        * Referenced by: '<S1>/MtrSpd'
                                        */
  real32_T MtrDistTrq_Y0;              /* Computed Parameter: MtrDistTrq_Y0
                                        * Referenced by: '<S1>/MtrDistTrq'
                                        */
  real32_T PosEst_Y0;                  /* Computed Parameter: PosEst_Y0
                                        * Referenced by: '<S1>/PosEst'
                                        */
  real32_T CtrlCmd_Y0;                 /* Computed Parameter: CtrlCmd_Y0
                                        * Referenced by: '<S1>/CtrlCmd'
                                        */
  real32_T UnitDelay_InitialCondition; /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S1>/Unit Delay'
                                        */
  real32_T UnitDelay_InitialCondition_m;/* Computed Parameter: UnitDelay_InitialCondition_m
                                         * Referenced by: '<S3>/Unit Delay'
                                         */
  real32_T Gain1_Gain_m;               /* Computed Parameter: Gain1_Gain_m
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_h;/* Computed Parameter: DiscreteTimeIntegrator_gainva_h
                                            * Referenced by: '<S15>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_b;/* Computed Parameter: DiscreteTimeIntegrator_IC_b
                                        * Referenced by: '<S15>/Discrete-Time Integrator'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S5>/Saturation1'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_p;/* Computed Parameter: DiscreteTimeIntegrator_gainva_p
                                            * Referenced by: '<S17>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_n;/* Computed Parameter: DiscreteTimeIntegrator_IC_n
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  real32_T UnitDelay_InitialCondition_b;/* Computed Parameter: UnitDelay_InitialCondition_b
                                         * Referenced by: '<S14>/Unit Delay'
                                         */
  real32_T DiscreteTimeIntegrator_gainva_k;/* Computed Parameter: DiscreteTimeIntegrator_gainva_k
                                            * Referenced by: '<S16>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_f;/* Computed Parameter: DiscreteTimeIntegrator_IC_f
                                        * Referenced by: '<S16>/Discrete-Time Integrator'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_o;/* Computed Parameter: DiscreteTimeIntegrator_gainva_o
                                            * Referenced by: '<S23>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_g;/* Computed Parameter: DiscreteTimeIntegrator_IC_g
                                        * Referenced by: '<S23>/Discrete-Time Integrator'
                                        */
  real32_T DiscreteTimeIntegrator_gainva_i;/* Computed Parameter: DiscreteTimeIntegrator_gainva_i
                                            * Referenced by: '<S22>/Discrete-Time Integrator'
                                            */
  real32_T DiscreteTimeIntegrator_IC_o;/* Computed Parameter: DiscreteTimeIntegrator_IC_o
                                        * Referenced by: '<S22>/Discrete-Time Integrator'
                                        */
  real32_T Constant1_Value_b;          /* Computed Parameter: Constant1_Value_b
                                        * Referenced by: '<S20>/Constant1'
                                        */
  real32_T UnitDelay_InitialCondition_bk;/* Computed Parameter: UnitDelay_InitialCondition_bk
                                          * Referenced by: '<S20>/Unit Delay'
                                          */
  real32_T Saturation_UpperSat;        /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S5>/Saturation'
                                        */
  real32_T Saturation_LowerSat;        /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S5>/Saturation'
                                        */
};

extern void ctrl_fast_Init(real32_T *rty_MtrSpd, real32_T *rty_MtrDistTrq,
  real32_T *rty_PosEst, MtrCtrlMd *rty_MtrCtrlMd, real32_T *rty_CtrlCmd, DBG_BUS
  *rty_DBG_BUS, DW_ctrl_fast *localDW, P_ctrl_fast *localP);
extern void ctrl_fast(real32_T rtu_MtrPos, real32_T rtu_MtrIfbkAct, real32_T
                      rtu_MtrIfbkTgt, MtrCtrlMd rtu_MtrCtrlMd_In, real32_T
                      rtu_MtrSpd, real32_T *rty_MtrSpd, real32_T *rty_MtrDistTrq,
                      real32_T *rty_PosEst, MtrCtrlMd *rty_MtrCtrlMd, real32_T
                      *rty_CtrlCmd, DBG_BUS *rty_DBG_BUS, DW_ctrl_fast *localDW,
                      P_ctrl_fast *localP);

#endif                                 /* RTW_HEADER_ctrl_fast_h_ */
