/*
 * File: ctrl_data.c
 *
 * Code generated for Simulink model 'ctrl'.
 *
 * Model version                  : 1.904
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Thu Jan 21 19:51:42 2021
 */

#include "ctrl.h"
#include "ctrl_private.h"

/* Block parameters (default storage) */
P rtP = {
  /* Variable: MotorParams
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S11>/Constant1'
   */
  {
    23.6347,
    0.02395,
    0.10028,
    1.6713e-5,
    5.2668e-6,
    0.011042402826855124,
    210.24861219081268,
    572957.79513082327,
    400.0,
    -0.02
  },

  /* Variable: Cfg_IndIDCntThshld
   * Referenced by: '<S3>/autotune'
   */
  15000,

  /* Variable: Cfg_IndIDCoolDownTicks
   * Referenced by: '<S3>/autotune'
   */
  3000,

  /* Variable: Cfg_IndIDSwTicks
   * Referenced by: '<S3>/autotune'
   */
  30,

  /* Variable: Cfg_OfsIDCntThshld
   * Referenced by: '<S3>/autotune'
   */
  1000,

  /* Variable: Cfg_ResIDCntThshld
   * Referenced by: '<S3>/autotune'
   */
  300,

  /* Variable: Cfg_ResIDCoolDownTicks
   * Referenced by: '<S3>/autotune'
   */
  3000,

  /* Variable: Cfg_TrqCnstIDCntThshld
   * Referenced by: '<S3>/autotune'
   */
  6000,

  /* Variable: Cfg_IfbkCtrlBW
   * Referenced by:
   *   '<S11>/Constant'
   *   '<S11>/Constant1'
   *   '<S11>/Constant3'
   */
  2000.0F,

  /* Variable: Cfg_IndIDMaxThshld
   * Referenced by: '<S3>/autotune'
   */
  0.1F,

  /* Variable: Cfg_IndIDMinThshld
   * Referenced by: '<S3>/autotune'
   */
  1.0E-6F,

  /* Variable: Cfg_IndIDMtrVin
   * Referenced by: '<S3>/autotune'
   */
  12.0F,

  /* Variable: Cfg_IndIDTs
   * Referenced by: '<S3>/autotune'
   */
  0.001F,

  /* Variable: Cfg_ResIDMaxThshld
   * Referenced by: '<S3>/autotune'
   */
  1000.0F,

  /* Variable: Cfg_ResIDMinThshld
   * Referenced by: '<S3>/autotune'
   */
  0.0001F,

  /* Variable: Cfg_ResIDMtrVin
   * Referenced by: '<S3>/autotune'
   */
  12.0F,

  /* Variable: Cfg_SpdCtrlBW
   * Referenced by: '<S30>/Constant3'
   */
  1000.0F,

  /* Variable: Cfg_TrqCnstIDMtrVin
   * Referenced by: '<S3>/autotune'
   */
  12.0F,

  /* Variable: DistObs_K1
   * Referenced by: '<S14>/Gain3'
   */
  2400.0F,

  /* Variable: DistObs_K2
   * Referenced by: '<S14>/Gain1'
   */
  1.92E+6F,

  /* Variable: DistObs_K3
   * Referenced by: '<S14>/Gain'
   */
  5.12E+8F,

  /* Variable: PosCtrl_Kp
   * Referenced by: '<S35>/Gain1'
   */
  400.0F,

  /* Variable: SmDiff_FiltCnst
   * Referenced by: '<S20>/Constant'
   */
  0.9615F,

  /* Variable: SmDiff_Ki
   * Referenced by: '<S21>/Gain2'
   */
  99000.0F,

  /* Variable: SmDiff_Kp
   * Referenced by: '<S21>/Gain1'
   */
  300.0F,

  /* Variable: TsFast
   * Referenced by: '<S3>/autotune'
   */
  3.33333337E-5F,

  /* Variable: Cfg_SpdSnsSrc
   * Referenced by: '<S5>/Constant'
   */
  1U,

  /* Variable: Cfg_AutoCalEnbl
   * Referenced by:
   *   '<S3>/autotune'
   *   '<S27>/Constant'
   *   '<S11>/Constant2'
   */
  1,

  /* Variable: Cfg_EnblLoadObs
   * Referenced by: '<S13>/Constant1'
   */
  0,

  /* Start of '<Root>/ctrl_slow' */
  {
    /* Mask Parameter: PICtrl_PI_Ki
     * Referenced by: '<S35>/Gain'
     */
    0.0,

    /* Mask Parameter: CompareToConstant_const
     * Referenced by: '<S33>/Constant'
     */
    PosCtrlMd,

    /* Mask Parameter: CompareToConstant1_const
     * Referenced by: '<S34>/Constant'
     */
    SpdCtrlMd,

    /* Mask Parameter: TrackDiff_h0
     * Referenced by: '<S39>/Gain3'
     */
    0.001F,

    /* Mask Parameter: PICtrl_max_lim
     * Referenced by: '<S36>/Discrete-Time Integrator'
     */
    150.0F,

    /* Mask Parameter: PICtrlVaryingGains_max_lim
     * Referenced by: '<S38>/Discrete-Time Integrator'
     */
    0.5F,

    /* Mask Parameter: PICtrl_min_lim
     * Referenced by: '<S36>/Discrete-Time Integrator'
     */
    -150.0F,

    /* Mask Parameter: PICtrlVaryingGains_min_lim
     * Referenced by: '<S38>/Discrete-Time Integrator'
     */
    -0.5F,

    /* Expression: AutoCalSt.Done
     * Referenced by: '<S27>/Constant1'
     */
    Done,

    /* Computed Parameter: Saturation1_UpperSat
     * Referenced by: '<S26>/Saturation1'
     */
    12.0F,

    /* Computed Parameter: Saturation1_LowerSat
     * Referenced by: '<S26>/Saturation1'
     */
    -12.0F,

    /* Computed Parameter: Constant_Value
     * Referenced by: '<S28>/Constant'
     */
    0.0F,

    /* Computed Parameter: Saturation_UpperSat
     * Referenced by: '<S26>/Saturation'
     */
    0.5F,

    /* Computed Parameter: Saturation_LowerSat
     * Referenced by: '<S26>/Saturation'
     */
    -0.5F,

    /* Computed Parameter: Constant1_Value_j
     * Referenced by: '<S28>/Constant1'
     */
    0.0F,

    /* Computed Parameter: MtrSpdTgt_Y0
     * Referenced by: '<S29>/MtrSpdTgt'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainval
     * Referenced by: '<S36>/Discrete-Time Integrator'
     */
    0.001F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC
     * Referenced by: '<S36>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: Ctrl_Y0
     * Referenced by: '<S30>/Ctrl'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_a
     * Referenced by: '<S38>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_k
     * Referenced by: '<S38>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: Saturation_UpperSat_k
     * Referenced by: '<S30>/Saturation'
     */
    0.5F,

    /* Computed Parameter: Saturation_LowerSat_e
     * Referenced by: '<S30>/Saturation'
     */
    -0.5F,

    /* Computed Parameter: Ref_Y0
     * Referenced by: '<S31>/Ref'
     */
    0.0F,

    /* Computed Parameter: Grd_Y0
     * Referenced by: '<S31>/Grd'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator1_gainval
     * Referenced by: '<S31>/Discrete-Time Integrator1'
     */
    0.001F,

    /* Computed Parameter: DiscreteTimeIntegrator1_IC
     * Referenced by: '<S31>/Discrete-Time Integrator1'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_b
     * Referenced by: '<S31>/Discrete-Time Integrator'
     */
    0.001F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_e
     * Referenced by: '<S31>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: d_Value
     * Referenced by: '<S39>/d'
     */
    0.0002F,

    /* Computed Parameter: Gain_Gain
     * Referenced by: '<S40>/Gain'
     */
    8.0F,

    /* Computed Parameter: Gain_Gain_o
     * Referenced by: '<S41>/Gain'
     */
    0.5F,

    /* Computed Parameter: Gain1_Gain
     * Referenced by: '<S45>/Gain1'
     */
    0.5F,

    /* Computed Parameter: Gain_Gain_m
     * Referenced by: '<S44>/Gain'
     */
    0.5F,

    /* Computed Parameter: Gain_Gain_c
     * Referenced by: '<S43>/Gain'
     */
    -200.0F,

    /* Expression: MotorParams.K
     * Referenced by: '<S27>/Constant2'
     */
    0.10028F,

    /* Expression: MotorParams.J
     * Referenced by: '<S27>/Constant3'
     */
    5.2668E-6F,

    /* Expression: MotorParams.Kf
     * Referenced by: '<S27>/Constant4'
     */
    1.6713E-5F,

    /* Computed Parameter: MtrIfbkTgt_Y0
     * Referenced by: '<S2>/MtrIfbkTgt'
     */
    0.0F,

    /* Computed Parameter: MtrSpdOut_Y0
     * Referenced by: '<S2>/MtrSpdOut'
     */
    0.0F,

    /* Computed Parameter: MtrDistEst_Y0
     * Referenced by: '<S2>/MtrDistEst'
     */
    0.0F,

    /* Computed Parameter: MtrPosEst_Y0
     * Referenced by: '<S2>/MtrPosEst'
     */
    0.0F,

    /* Computed Parameter: Gain1_Gain_f
     * Referenced by: '<S24>/Gain1'
     */
    0.0174532924F,

    /* Computed Parameter: TO_RPM_Gain
     * Referenced by: '<S2>/TO_RPM'
     */
    9.54929638F,

    /* Computed Parameter: Gain1_Gain_j
     * Referenced by: '<S25>/Gain1'
     */
    0.0174532924F,

    /* Computed Parameter: DataStoreMemory_InitialValue
     * Referenced by: '<S2>/Data Store Memory'
     */
    0.0F,

    /* Computed Parameter: DataStoreMemory1_InitialValue
     * Referenced by: '<S2>/Data Store Memory1'
     */
    0.0F,

    /* Computed Parameter: DataStoreMemory2_InitialValue
     * Referenced by: '<S2>/Data Store Memory2'
     */
    0.0F
  }
  ,

  /* End of '<Root>/ctrl_slow' */

  /* Start of '<Root>/ctrl_fast' */
  {
    /* Mask Parameter: CompareToConstant_const
     * Referenced by: '<S9>/Constant'
     */
    OpnLoopCtrlMd,

    /* Mask Parameter: PICtrlVaryingGains_max_lim
     * Referenced by: '<S19>/Discrete-Time Integrator'
     */
    12.0F,

    /* Mask Parameter: Integrator_max_lim
     * Referenced by: '<S15>/Discrete-Time Integrator'
     */
    1.0E+7F,

    /* Mask Parameter: Integrator2_max_lim
     * Referenced by: '<S17>/Discrete-Time Integrator'
     */
    1.0E+7F,

    /* Mask Parameter: Integrator1_max_lim
     * Referenced by: '<S16>/Discrete-Time Integrator'
     */
    1.0E+7F,

    /* Mask Parameter: Integrator1_max_lim_o
     * Referenced by: '<S23>/Discrete-Time Integrator'
     */
    1.0E+6F,

    /* Mask Parameter: Integrator_max_lim_k
     * Referenced by: '<S22>/Discrete-Time Integrator'
     */
    1.0E+6F,

    /* Mask Parameter: PICtrlVaryingGains_min_lim
     * Referenced by: '<S19>/Discrete-Time Integrator'
     */
    -12.0F,

    /* Mask Parameter: Integrator_min_lim
     * Referenced by: '<S15>/Discrete-Time Integrator'
     */
    -1.0E+7F,

    /* Mask Parameter: Integrator2_min_lim
     * Referenced by: '<S17>/Discrete-Time Integrator'
     */
    -1.0E+7F,

    /* Mask Parameter: Integrator1_min_lim
     * Referenced by: '<S16>/Discrete-Time Integrator'
     */
    -1.0E+7F,

    /* Mask Parameter: Integrator1_min_lim_i
     * Referenced by: '<S23>/Discrete-Time Integrator'
     */
    -1.0E+6F,

    /* Mask Parameter: Integrator_min_lim_i
     * Referenced by: '<S22>/Discrete-Time Integrator'
     */
    -1.0E+6F,

    /* Computed Parameter: DBG_BUS_Y0
     * Referenced by: '<S1>/DBG_BUS'
     */
    {
      0.0F,                            /* IfbkTgt */
      0.0F,                            /* Lest */
      0.0F,                            /* Rest */
      0.0F,                            /* KTrqEst */
      0.0F,                            /* IfbkOfs */
      0.0F,                            /* KFrcEst */
      0.0F,                            /* JEst */
      0.0F,                            /* IfbkSteady */
      0.0F,                            /* IfbkMax */
      0.0F,                            /* SpdMax */
      ErrIndTooSmall                   /* Status */
    },

    /* Expression: AutoCalSt.Done
     * Referenced by: '<S8>/Constant'
     */
    Done,

    /* Expression: AutoCalSt.NotStarted
     * Referenced by: '<S8>/Constant1'
     */
    NotStarted,

    /* Expression: MtrCtrlMd.OpnLoopCtrlMd
     * Referenced by: '<S7>/Constant'
     */
    OpnLoopCtrlMd,

    /* Computed Parameter: MtrCtrlMd_Y0
     * Referenced by: '<S1>/MtrCtrlMd'
     */
    IfbkCtrlMd,

    /* Expression: MotorParams.K
     * Referenced by: '<S5>/Gain1'
     */
    0.10028F,

    /* Computed Parameter: Ctrl_Y0
     * Referenced by: '<S11>/Ctrl'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainval
     * Referenced by: '<S19>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC
     * Referenced by: '<S19>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: Constant2_Value
     * Referenced by: '<S13>/Constant2'
     */
    0.0F,

    /* Computed Parameter: MtrSpd_Y0
     * Referenced by: '<S1>/MtrSpd'
     */
    0.0F,

    /* Computed Parameter: MtrDistTrq_Y0
     * Referenced by: '<S1>/MtrDistTrq'
     */
    0.0F,

    /* Computed Parameter: PosEst_Y0
     * Referenced by: '<S1>/PosEst'
     */
    0.0F,

    /* Computed Parameter: CtrlCmd_Y0
     * Referenced by: '<S1>/CtrlCmd'
     */
    0.0F,

    /* Computed Parameter: UnitDelay_InitialCondition
     * Referenced by: '<S1>/Unit Delay'
     */
    0.0F,

    /* Computed Parameter: UnitDelay_InitialCondition_m
     * Referenced by: '<S3>/Unit Delay'
     */
    0.0F,

    /* Computed Parameter: Gain1_Gain_m
     * Referenced by: '<S4>/Gain1'
     */
    0.0174532924F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_h
     * Referenced by: '<S15>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_b
     * Referenced by: '<S15>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: Saturation1_UpperSat
     * Referenced by: '<S5>/Saturation1'
     */
    0.6F,

    /* Computed Parameter: Saturation1_LowerSat
     * Referenced by: '<S5>/Saturation1'
     */
    -0.6F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_p
     * Referenced by: '<S17>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_n
     * Referenced by: '<S17>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: UnitDelay_InitialCondition_b
     * Referenced by: '<S14>/Unit Delay'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_k
     * Referenced by: '<S16>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_f
     * Referenced by: '<S16>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_o
     * Referenced by: '<S23>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_g
     * Referenced by: '<S23>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: DiscreteTimeIntegrator_gainva_i
     * Referenced by: '<S22>/Discrete-Time Integrator'
     */
    3.33333337E-5F,

    /* Computed Parameter: DiscreteTimeIntegrator_IC_o
     * Referenced by: '<S22>/Discrete-Time Integrator'
     */
    0.0F,

    /* Computed Parameter: Constant1_Value_b
     * Referenced by: '<S20>/Constant1'
     */
    1.0F,

    /* Computed Parameter: UnitDelay_InitialCondition_bk
     * Referenced by: '<S20>/Unit Delay'
     */
    0.0F,

    /* Computed Parameter: Saturation_UpperSat
     * Referenced by: '<S5>/Saturation'
     */
    12.0F,

    /* Computed Parameter: Saturation_LowerSat
     * Referenced by: '<S5>/Saturation'
     */
    -12.0F
  }
  /* End of '<Root>/ctrl_fast' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
