/*
 * pmsm_ctrl.c
 *
 * Code generation for model "pmsm_ctrl".
 *
 * Model version              : 1.765
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#include "pmsm_ctrl.h"
#include "pmsm_ctrl_private.h"

/* Named constants for Chart: '<S12>/ResIdCal' */
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_done                        ((uint8_T)1U)
#define IN_res_id_actv                 ((uint8_T)2U)
#define IN_res_id_init                 ((uint8_T)3U)
#define TICK_R_CAL                     (100U)
#define TICK_R_CAL_WAIT_SETTLE         (30U)

/* Named constants for Chart: '<S11>/IndIdCal' */
#define IN_ind_id_actv                 ((uint8_T)2U)
#define IN_neg_cycle                   ((uint8_T)1U)
#define IN_pos_cycle                   ((uint8_T)2U)
#define TICK_L_CAL                     (1000U)
#define TICK_L_CAL_WAIT_SETTLE         (30U)

/* Named constants for Chart: '<S10>/ResIdCal' */
#define IN_mtr_angl_ofs_cal_actv       ((uint8_T)1U)
#define IN_mtr_angl_ofs_cal_done       ((uint8_T)2U)
#define TICK_IFBK_OFS_WAIT_SETTLE      (500U)

/* Named constants for Chart: '<S9>/EncOfsCal' */
#define IN_calc_enc_ofs_move_forward   ((uint8_T)1U)
#define IN_calc_n_poles                ((uint8_T)2U)
#define IN_done_m                      ((uint8_T)3U)
#define IN_enc_cnts_err                ((uint8_T)4U)
#define IN_move_back_calc_enc_ofs      ((uint8_T)5U)
#define IN_mtr_n_poles_enc_ofs_init    ((uint8_T)6U)
#define POLES_CAL_MAX                  (20)
#define POLES_CAL_MIN                  (1)
#define TICK_ENC_OFS_WAIT_SETTLE       (200U)
#define TICK_INC_MIN                   (100)
#define TICK_OFS_CAL_RAMP              (500U)

const Calib_OutType pmsm_ctrl_rtZCalib_OutType = {
  CTRL_MD_OFF,                         /* ctrl_md_rqst */
  ST_FAILED,                           /* cal_mgr_st_rqst */

  {
    0.0F, 0.0F, 0.0F }
  /* mtr_cmd_rqst */
} ;                                    /* Calib_OutType ground */

/* Exported block signals */
Calib_ParamType CALIB_PARAM_BUS;       /* '<S2>/Bus Creator' */

/* Exported block states */
boolean_T _pmsm_ctrl_SharedDataInit_ = false;/* synthesized block */

/* Exported data definition */

/* Definition for custom storage class: Struct */
DBG_Struct_type DBG_Struct;

/* data stores shared across model instances */
SharedDSM rtSharedDSM;
int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

uint32_T div_nzp_usu32_sat(int32_T numerator, uint32_T denominator)
{
  uint32_T quotient;
  if (numerator < 0) {
    quotient = 0U;
  } else {
    quotient = (numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)numerator)
      / denominator;
  }

  return quotient;
}

/*
 * Output and update for atomic system:
 *    '<S28>/calc_pwm_dc'
 *    '<S25>/calc_pwm_dc'
 *    '<S17>/calc_pwm_dc'
 *    '<S56>/calc_pwm_dc'
 */
void calc_pwm_dc(RT_MODEL * const pmsm_ctrl_M, const real32_T rtu_pwm_abc[3],
                 real32_T rty_pwm_dc[3])
{
  real32_T rtb_Gain_j;
  real32_T rtb_Subtract_g_idx_0;
  real32_T rtb_Subtract_g_idx_1;
  (void) (pmsm_ctrl_M);

  /* MinMax: '<S29>/Max' */
  rtb_Gain_j = rtu_pwm_abc[0];
  rtb_Subtract_g_idx_0 = rtu_pwm_abc[1];
  if (!(rtb_Gain_j > rtb_Subtract_g_idx_0)) {
    rtb_Gain_j = rtb_Subtract_g_idx_0;
  }

  rtb_Subtract_g_idx_0 = rtu_pwm_abc[2];
  if (!(rtb_Gain_j > rtb_Subtract_g_idx_0)) {
    rtb_Gain_j = rtb_Subtract_g_idx_0;
  }

  /* MinMax: '<S29>/Max1' */
  rtb_Subtract_g_idx_1 = rtu_pwm_abc[0];
  rtb_Subtract_g_idx_0 = rtu_pwm_abc[1];
  if (!(rtb_Subtract_g_idx_1 < rtb_Subtract_g_idx_0)) {
    rtb_Subtract_g_idx_1 = rtb_Subtract_g_idx_0;
  }

  rtb_Subtract_g_idx_0 = rtu_pwm_abc[2];
  if (!(rtb_Subtract_g_idx_1 < rtb_Subtract_g_idx_0)) {
    rtb_Subtract_g_idx_1 = rtb_Subtract_g_idx_0;
  }

  /* Gain: '<S29>/Gain' incorporates:
   *  MinMax: '<S29>/Max'
   *  MinMax: '<S29>/Max1'
   *  Sum: '<S29>/Add'
   */
  rtb_Gain_j = (rtb_Gain_j + rtb_Subtract_g_idx_1) * 0.5F;

  /* Sum: '<S29>/Subtract' */
  rtb_Subtract_g_idx_0 = rtu_pwm_abc[0] - rtb_Gain_j;
  rtb_Subtract_g_idx_1 = rtu_pwm_abc[1] - rtb_Gain_j;
  rtb_Gain_j = rtu_pwm_abc[2] - rtb_Gain_j;

  /* DataTypeConversion: '<S29>/Data Type Conversion' incorporates:
   *  Constant: '<S29>/Constant'
   *  Constant: '<S29>/Constant1'
   *  Gain: '<S29>/Gain2'
   *  Product: '<S29>/Divide'
   *  Sum: '<S29>/Add1'
   */
  rty_pwm_dc[0] = (rtb_Subtract_g_idx_0 / 0.5F + 1.0F) * 0.5F;
  rty_pwm_dc[1] = (rtb_Subtract_g_idx_1 / 0.5F + 1.0F) * 0.5F;
  rty_pwm_dc[2] = (rtb_Gain_j / 0.5F + 1.0F) * 0.5F;
}

/* System reset for function-call system: '<S20>/get_mtr_ifbk_sum' */
void get_mtr_ifbk_sum_Reset(self_get_mtr_ifbk_sum *pmsm_ctrl_self_arg)
{
  /* InitializeConditions for UnitDelay: '<S23>/Unit Delay' */
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[0] = 0.0F;
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[1] = 0.0F;
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[2] = 0.0F;
}

/* Output and update for function-call system: '<S20>/get_mtr_ifbk_sum' */
void get_mtr_ifbk_sum(self_get_mtr_ifbk_sum *pmsm_ctrl_self_arg, const real32_T
                      rtu_mtr_ifbk_abc[3], real32_T rty_mtr_ifbk_sum_abc[3])
{
  /* Sum: '<S23>/Add' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  rty_mtr_ifbk_sum_abc[0] = rtu_mtr_ifbk_abc[0] +
    pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[0];

  /* Update for UnitDelay: '<S23>/Unit Delay' */
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[0] = rty_mtr_ifbk_sum_abc[0];

  /* Sum: '<S23>/Add' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  rty_mtr_ifbk_sum_abc[1] = rtu_mtr_ifbk_abc[1] +
    pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[1];

  /* Update for UnitDelay: '<S23>/Unit Delay' */
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[1] = rty_mtr_ifbk_sum_abc[1];

  /* Sum: '<S23>/Add' incorporates:
   *  UnitDelay: '<S23>/Unit Delay'
   */
  rty_mtr_ifbk_sum_abc[2] = rtu_mtr_ifbk_abc[2] +
    pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[2];

  /* Update for UnitDelay: '<S23>/Unit Delay' */
  pmsm_ctrl_self_arg->dwork.UnitDelay_DSTATE[2] = rty_mtr_ifbk_sum_abc[2];
}

/* Output and update for function-call system: '<S20>/get_mtr_ifbk_avg' */
void get_mtr_ifbk_avg(RT_MODEL * const pmsm_ctrl_M, const real32_T
                      rtu_mtr_ifbk_sum_abc[3], real32_T rtu_ncycles, real32_T
                      rty_mtr_ifbk_avg_abc[3])
{
  real32_T rtb_Saturation_m;
  (void) (pmsm_ctrl_M);

  /* Saturate: '<S22>/Saturation' */
  if (rtu_ncycles > 1.0E+6F) {
    rtb_Saturation_m = 1.0E+6F;
  } else if (rtu_ncycles < 1.0F) {
    rtb_Saturation_m = 1.0F;
  } else {
    rtb_Saturation_m = rtu_ncycles;
  }

  /* End of Saturate: '<S22>/Saturation' */

  /* Product: '<S22>/Divide' */
  rty_mtr_ifbk_avg_abc[0] = rtu_mtr_ifbk_sum_abc[0] / rtb_Saturation_m;
  rty_mtr_ifbk_avg_abc[1] = rtu_mtr_ifbk_sum_abc[1] / rtb_Saturation_m;
  rty_mtr_ifbk_avg_abc[2] = rtu_mtr_ifbk_sum_abc[2] / rtb_Saturation_m;
}

/*
 * Output and update for atomic system:
 *    '<S9>/calc_mod_wave'
 *    '<S35>/calc_mod_wave'
 */
void calc_mod_wave(RT_MODEL * const pmsm_ctrl_M, const real32_T rtu_dq0[3],
                   real32_T rtu_elec_angle, real32_T rty_pwm_dc[3], real32_T
                   rty_mod_wave[3])
{
  /* Gain: '<S18>/Gain1' incorporates:
   *  Fcn: '<S18>/a'
   *  Fcn: '<S18>/b'
   *  Fcn: '<S18>/c'
   */
  rty_mod_wave[0] = (arm_sin_f32(rtu_elec_angle + 1.57079637F) * rtu_dq0[0] +
                     arm_cos_f32(rtu_elec_angle + 1.57079637F) * rtu_dq0[1]) +
    rtu_dq0[2];
  rty_mod_wave[1] = (arm_sin_f32((rtu_elec_angle + 1.57079637F) - 2.09439516F) *
                     rtu_dq0[0] + arm_cos_f32((rtu_elec_angle + 1.57079637F) -
    2.09439516F) * rtu_dq0[1]) + rtu_dq0[2];
  rty_mod_wave[2] = (arm_sin_f32((rtu_elec_angle + 1.57079637F) + 2.09439516F) *
                     rtu_dq0[0] + arm_cos_f32((rtu_elec_angle + 1.57079637F) +
    2.09439516F) * rtu_dq0[1]) + rtu_dq0[2];

  /* Outputs for Atomic SubSystem: '<S17>/calc_pwm_dc' */
  calc_pwm_dc(pmsm_ctrl_M, rty_mod_wave, rty_pwm_dc);

  /* End of Outputs for SubSystem: '<S17>/calc_pwm_dc' */
}

/* Output and update for atomic system: '<S30>/calc_elec_angle' */
void calc_elec_angle(RT_MODEL * const pmsm_ctrl_M, int32_T rtu_mtr_enc_cnts,
                     real32_T *rty_elec_angle, real32_T *rty_mtr_pos, int32_T
                     rtp_enc_cnts_int, uint8_T rtp_n_poles)
{
  real32_T rtb_Divide_b;
  int32_T u0;
  (void) (pmsm_ctrl_M);

  /* Product: '<S32>/Divide' incorporates:
   *  Constant: '<S32>/Constant2'
   *  Constant: '<S32>/Constant3'
   *  DataTypeConversion: '<S32>/Data Type Conversion'
   */
  rtb_Divide_b = 6.28318548F / (real32_T)rtp_enc_cnts_int;

  /* Gain: '<S32>/Gain' */
  u0 = rtp_n_poles * rtu_mtr_enc_cnts;

  /* Math: '<S32>/Mod' incorporates:
   *  Constant: '<S32>/Constant1'
   */
  if (rtp_enc_cnts_int != 0) {
    u0 -= div_nde_s32_floor(u0, rtp_enc_cnts_int) * rtp_enc_cnts_int;
  }

  /* End of Math: '<S32>/Mod' */

  /* Product: '<S32>/Divide1' incorporates:
   *  DataTypeConversion: '<S32>/Data Type Conversion2'
   */
  *rty_elec_angle = (real32_T)u0 * rtb_Divide_b;

  /* Product: '<S32>/Divide2' incorporates:
   *  DataTypeConversion: '<S32>/Data Type Conversion1'
   */
  *rty_mtr_pos = (real32_T)rtu_mtr_enc_cnts * rtb_Divide_b;
}

/*
 * System reset for atomic system:
 *    '<S49>/PI-Ctrl-Varying-Gains'
 *    '<S50>/PI-Ctrl-Varying-Gains'
 *    '<S63>/PI-Ctrl-Varying-Gains'
 */
void PI_Ctrl_Reset(self_PI_Ctrl *pmsm_ctrl_self_arg)
{
  /* InitializeConditions for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' */
  pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE = 0.0F;
}

/*
 * Output and update for atomic system:
 *    '<S49>/PI-Ctrl-Varying-Gains'
 *    '<S50>/PI-Ctrl-Varying-Gains'
 *    '<S63>/PI-Ctrl-Varying-Gains'
 */
void PI_Ctrl(self_PI_Ctrl *pmsm_ctrl_self_arg, real32_T rtu_y_tgt, real32_T
             rtu_y_act, real32_T rtu_Kp, real32_T rtu_Ki, real32_T *rty_PI_out,
             real32_T rtp_max_lim, real32_T rtp_min_lim)
{
  real32_T rtb_Subtract_ie;

  /* Sum: '<S52>/Subtract' */
  rtb_Subtract_ie = rtu_y_tgt - rtu_y_act;

  /* Sum: '<S52>/Add' incorporates:
   *  DiscreteIntegrator: '<S53>/Discrete-Time Integrator'
   *  Product: '<S52>/Product'
   */
  *rty_PI_out = rtu_Kp * rtb_Subtract_ie +
    pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' incorporates:
   *  Product: '<S52>/Product1'
   */
  pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE += rtb_Subtract_ie *
    rtu_Ki * 0.0001F;
  if (pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE >= rtp_max_lim) {
    pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE = rtp_max_lim;
  } else {
    if (pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE <= rtp_min_lim)
    {
      pmsm_ctrl_self_arg->dwork.DiscreteTimeIntegrator_DSTATE = rtp_min_lim;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S53>/Discrete-Time Integrator' */
}

/* Model step function */
void Trig_Pmsm_SetIn(RT_MODEL *const pmsm_ctrl_M, int32_T rtU_MtrIf_EncCnts,
                     real32_T rtU_MtrIf_IfbkAct[3], real32_T rtU_MtrIf_SpdSns,
                     MtrCtrlMd_T rtU_MtrIf_CtrlMd, real32_T rtU_MtrIf_Tgt[3],
                     real32_T rtU_MtrIf_VBus, MtrCtrlCal_T rtU_MtrIf_CtrlCalRqst)
{
  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_SetIn_at_outport_1' incorporates:
   *  SubSystem: '<Root>/SetInputs'
   */
  /* Sum: '<S89>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_EncCnts'
   */
  DBG_Struct.mtr_if_enc_cnts = rtU_MtrIf_EncCnts - CALIB_PARAM_BUS.enc_ofs;

  /* Sum: '<S88>/Add1' incorporates:
   *  Constant: '<S88>/Constant'
   *  Inport: '<Root>/MtrIf_VBus'
   *  Product: '<S88>/Product'
   *  Product: '<S88>/Product1'
   *  UnitDelay: '<S88>/Unit Delay'
   */
  DBG_Struct.mtrif_v_bus = rtU_MtrIf_VBus * 0.00990092754F + 0.990099072F *
    pmsm_ctrl_M->dwork.UnitDelay_DSTATE;

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_CtrlMd'
   *  Inport: '<Root>/MtrIf_SpdSns'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts = DBG_Struct.mtr_if_enc_cnts;
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_spd_sns = rtU_MtrIf_SpdSns;
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ctrl_md = rtU_MtrIf_CtrlMd;

  /* Sum: '<S90>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  DBG_Struct.mtrif_ifbk_act[0] = rtU_MtrIf_IfbkAct[0] -
    CALIB_PARAM_BUS.ifbk_ofs[0];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0] = DBG_Struct.mtrif_ifbk_act
    [0];
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[0] = rtU_MtrIf_Tgt[0];

  /* Sum: '<S90>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  DBG_Struct.mtrif_ifbk_act[1] = rtU_MtrIf_IfbkAct[1] -
    CALIB_PARAM_BUS.ifbk_ofs[1];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1] = DBG_Struct.mtrif_ifbk_act
    [1];
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[1] = rtU_MtrIf_Tgt[1];

  /* Sum: '<S90>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  DBG_Struct.mtrif_ifbk_act[2] = rtU_MtrIf_IfbkAct[2] -
    CALIB_PARAM_BUS.ifbk_ofs[2];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_CtrlCalRqst'
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2] = DBG_Struct.mtrif_ifbk_act
    [2];
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[2] = rtU_MtrIf_Tgt[2];
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_cal_rqst = rtU_MtrIf_CtrlCalRqst;
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_v_bus = DBG_Struct.mtrif_v_bus;

  /* Update for UnitDelay: '<S88>/Unit Delay' */
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE = DBG_Struct.mtrif_v_bus;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_SetIn_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_CtrlMgr(RT_MODEL *const pmsm_ctrl_M)
{
  boolean_T rtb_LogicalOperator2;
  boolean_T rtb_Compare_p;
  MtrCtrlMd_T rtb_ctrl_md_act;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_CtrlMgr_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlMgr'
   */
  /* Logic: '<S5>/Logical Operator' incorporates:
   *  Constant: '<S79>/Constant'
   *  Constant: '<S80>/Constant'
   *  RelationalOperator: '<S79>/Compare'
   *  RelationalOperator: '<S80>/Compare'
   */
  rtb_LogicalOperator2 = ((pmsm_ctrl_M->blockIO.BusCreator.mtrif_cal_rqst !=
    CAL_NONE) && (pmsm_ctrl_M->blockIO.BusCreator.mtrif_ctrl_md == CTRL_MD_CAL));

  /* Switch: '<S5>/Switch1' */
  if (rtb_LogicalOperator2) {
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0] =
      pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0];
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[1] =
      pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1];
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[2] =
      pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2];
  } else {
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0] =
      pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[0];
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[1] =
      pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[1];
    pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[2] =
      pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[2];
  }

  /* End of Switch: '<S5>/Switch1' */

  /* DataTypeConversion: '<S5>/Data Type Conversion' */
  pmsm_ctrl_M->blockIO.ctrl_cal_act =
    pmsm_ctrl_M->blockIO.BusCreator.mtrif_cal_rqst;

  /* Switch: '<S5>/Switch' */
  if (rtb_LogicalOperator2) {
    rtb_ctrl_md_act = pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst;
  } else {
    rtb_ctrl_md_act = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ctrl_md;
  }

  /* End of Switch: '<S5>/Switch' */

  /* RelationalOperator: '<S84>/Compare' incorporates:
   *  Constant: '<S84>/Constant'
   */
  rtb_Compare_p = (rtb_ctrl_md_act == CTRL_MD_OFF);

  /* Logic: '<S81>/Logical Operator2' */
  rtb_LogicalOperator2 = !rtb_Compare_p;

  /* Logic: '<S81>/Logical Operator1' incorporates:
   *  Constant: '<S83>/Constant'
   *  RelationalOperator: '<S83>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_raw_pwm =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act == CTRL_MD_RAW_PWM));

  /* Logic: '<S81>/Logical Operator3' incorporates:
   *  Constant: '<S85>/Constant'
   *  RelationalOperator: '<S85>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_mod_wave =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_DQ_PWM));

  /* Logic: '<S81>/Logical Operator4' incorporates:
   *  Constant: '<S82>/Constant'
   *  RelationalOperator: '<S82>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_IFBK));

  /* Logic: '<S81>/Logical Operator5' incorporates:
   *  Constant: '<S86>/Constant'
   *  RelationalOperator: '<S86>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_SPD));

  /* Logic: '<S81>/Logical Operator6' incorporates:
   *  Constant: '<S87>/Constant'
   *  RelationalOperator: '<S87>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_POS));

  /* BusCreator: '<S5>/BusConversion_InsertedFor_Bus Creator2_at_inport_3' */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.ctrl_md_off = rtb_Compare_p;

  /* BusCreator: '<S5>/Bus Creator2' */
  pmsm_ctrl_M->blockIO.BusCreator2.ctrl_cal_act =
    pmsm_ctrl_M->blockIO.ctrl_cal_act;
  pmsm_ctrl_M->blockIO.BusCreator2.ctrl_md_act = rtb_ctrl_md_act;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_CtrlMgr_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_Cal(RT_MODEL *const pmsm_ctrl_M)
{
  int8_T rtPrevAction;
  int8_T rtAction;
  real32_T rtb_TmpSignalConversionAtcalc_i[3];
  real32_T rtb_DataTypeConversion_f[3];
  MtrCtrlMd_T rtb_CtrlMdRqst;
  CalMgrSt_T rtb_CalMgrStRqst;
  real32_T rtb_PwmRqst_l;
  int32_T qY;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CalibRoutines'
   */
  /* SwitchCase: '<S2>/Switch Case' incorporates:
   *  Constant: '<S9>/Constant'
   *  DataTypeConversion: '<S9>/Data Type Cnversion1'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Gain: '<S9>/Gain'
   *  Product: '<S9>/Divide'
   */
  rtPrevAction = pmsm_ctrl_M->dwork.SwitchCase_ActiveSubsystem;
  rtAction = -1;
  switch (pmsm_ctrl_M->blockIO.ctrl_cal_act) {
   case CAL_NONE:
    rtAction = 0;
    break;

   case CAL_RES_ID:
    rtAction = 1;
    break;

   case CAL_IND_ID:
    rtAction = 2;
    break;

   case CAL_IFBK_OFS:
    rtAction = 3;
    break;

   case CAL_ENC_OFS:
    rtAction = 4;
    break;
  }

  pmsm_ctrl_M->dwork.SwitchCase_ActiveSubsystem = rtAction;
  switch (rtAction) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S2>/not_active' incorporates:
     *  ActionPort: '<S13>/Action Port'
     */
    /* BusCreator: '<S13>/Bus Creator' incorporates:
     *  Constant: '<S13>/Zero1'
     *  Constant: '<S13>/Zero2'
     */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = CTRL_MD_OFF;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = ST_DONE;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0] = 0.0F;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1] = 0.0F;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2] = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/not_active' */
    break;

   case 1:
    if (rtAction != rtPrevAction) {
      /* SystemReset for IfAction SubSystem: '<S2>/mtr_res_ident' incorporates:
       *  ActionPort: '<S12>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S2>/Switch Case' incorporates:
       *  Chart: '<S12>/ResIdCal'
       */
      pmsm_ctrl_M->dwork.temporalCounter_i1_l = 0U;
      pmsm_ctrl_M->dwork.is_active_c5_pmsm_ctrl = 0U;
      pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.ifbk_sum = 0.0F;
      pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_FAILED;
      pmsm_ctrl_M->blockIO.PwmRqst_g = 0.0F;

      /* End of SystemReset for SubSystem: '<S2>/mtr_res_ident' */
    }

    /* Outputs for IfAction SubSystem: '<S2>/mtr_res_ident' incorporates:
     *  ActionPort: '<S12>/Action Port'
     */
    /* Chart: '<S12>/ResIdCal' */
    if (pmsm_ctrl_M->dwork.temporalCounter_i1_l < 127U) {
      pmsm_ctrl_M->dwork.temporalCounter_i1_l++;
    }

    if (pmsm_ctrl_M->dwork.is_active_c5_pmsm_ctrl == 0U) {
      pmsm_ctrl_M->dwork.is_active_c5_pmsm_ctrl = 1U;
      pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_res_id_init;
      pmsm_ctrl_M->dwork.temporalCounter_i1_l = 0U;
      pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_RAW_PWM;
      pmsm_ctrl_M->blockIO.PwmRqst_g = Cfg_ResCalPwmDuty;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_RES_ID;
      pmsm_ctrl_M->dwork.ifbk_sum = 0.0F;
      rtSharedDSM.CalData_Res = -1.0F;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl) {
       case IN_done:
        pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_DONE;
        pmsm_ctrl_M->blockIO.PwmRqst_g = (real32_T)0.;
        rtSharedDSM.CalData_Res = (real32_T)(Cfg_ResCalPwmDuty *
          0.66666666666666663 * 6.0 / (pmsm_ctrl_M->dwork.ifbk_sum / (real32_T)
          TICK_R_CAL));
        break;

       case IN_res_id_actv:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_l >= (int32_T)TICK_R_CAL) {
          pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_done;
          pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_DONE;
          pmsm_ctrl_M->blockIO.PwmRqst_g = (real32_T)0.;
          rtSharedDSM.CalData_Res = (real32_T)(Cfg_ResCalPwmDuty *
            0.66666666666666663 * 6.0 / (pmsm_ctrl_M->dwork.ifbk_sum / (real32_T)
            TICK_R_CAL));
        } else {
          pmsm_ctrl_M->dwork.ifbk_sum +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        }
        break;

       default:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_l >= (int32_T)
            TICK_R_CAL_WAIT_SETTLE) {
          /*  Wait for current / motor to settle. */
          pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_res_id_actv;
          pmsm_ctrl_M->dwork.temporalCounter_i1_l = 0U;
          pmsm_ctrl_M->dwork.ifbk_sum +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_RAW_PWM;
          pmsm_ctrl_M->blockIO.PwmRqst_g = Cfg_ResCalPwmDuty;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_RES_ID;
          pmsm_ctrl_M->dwork.ifbk_sum = 0.0F;
          rtSharedDSM.CalData_Res = -1.0F;
        }
        break;
      }
    }

    /* End of Chart: '<S12>/ResIdCal' */

    /* SignalConversion: '<S28>/TmpSignal ConversionAtcalc_pwm_dcInport1' incorporates:
     *  Constant: '<S28>/Zero'
     */
    rtb_TmpSignalConversionAtcalc_i[0] = pmsm_ctrl_M->blockIO.PwmRqst_g;
    rtb_TmpSignalConversionAtcalc_i[1] = 0.0F;
    rtb_TmpSignalConversionAtcalc_i[2] = 0.0F;

    /* Outputs for Atomic SubSystem: '<S28>/calc_pwm_dc' */
    calc_pwm_dc(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i,
                rtb_DataTypeConversion_f);

    /* End of Outputs for SubSystem: '<S28>/calc_pwm_dc' */

    /* BusCreator: '<S12>/Bus Creator' */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst_p;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst_h;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0] = rtb_DataTypeConversion_f[0];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1] = rtb_DataTypeConversion_f[1];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2] = rtb_DataTypeConversion_f[2];

    /* End of Outputs for SubSystem: '<S2>/mtr_res_ident' */
    break;

   case 2:
    if (rtAction != rtPrevAction) {
      /* SystemReset for IfAction SubSystem: '<S2>/mtr_ind_ident' incorporates:
       *  ActionPort: '<S11>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S2>/Switch Case' incorporates:
       *  Chart: '<S11>/IndIdCal'
       */
      pmsm_ctrl_M->dwork.is_ind_id_actv = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.temporalCounter_i1_n = 0U;
      pmsm_ctrl_M->dwork.is_active_c1_pmsm_ctrl = 0U;
      pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.ifbk_neg = 0.0F;
      pmsm_ctrl_M->dwork.ifbk_pos = 0.0F;
      pmsm_ctrl_M->dwork.di_dt = 0.0F;
      pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_OFF;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_FAILED;

      /* End of SystemReset for SubSystem: '<S2>/mtr_ind_ident' */
    }

    /* Outputs for IfAction SubSystem: '<S2>/mtr_ind_ident' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Chart: '<S11>/IndIdCal' */
    if (pmsm_ctrl_M->dwork.temporalCounter_i1_n < 1023U) {
      pmsm_ctrl_M->dwork.temporalCounter_i1_n++;
    }

    if (pmsm_ctrl_M->dwork.is_active_c1_pmsm_ctrl == 0U) {
      pmsm_ctrl_M->dwork.is_active_c1_pmsm_ctrl = 1U;
      pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl = IN_res_id_init;
      pmsm_ctrl_M->dwork.temporalCounter_i1_n = 0U;
      pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_RAW_PWM;

      /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
      rtb_TmpSignalConversionAtcalc_i[0] = Cfg_IndCalPwmDuty;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_IND_ID;
      rtSharedDSM.CalData_L = -1.0F;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl) {
       case IN_done:
        pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_DONE;

        /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
        rtb_TmpSignalConversionAtcalc_i[0] = (real32_T)0.;
        pmsm_ctrl_M->dwork.di_dt = (real32_T)((pmsm_ctrl_M->dwork.ifbk_pos -
          pmsm_ctrl_M->dwork.ifbk_neg) / 500.0 / TsMain);
        rtSharedDSM.CalData_L = (real32_T)(Cfg_VBus / 2. * Cfg_IndCalPwmDuty /
          pmsm_ctrl_M->dwork.di_dt);
        break;

       case IN_ind_id_actv:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_n >= (int32_T)TICK_L_CAL) {
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_NO_ACTIVE_CHILD;
          pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl = IN_done;
          pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_DONE;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = (real32_T)0.;
          pmsm_ctrl_M->dwork.di_dt = (real32_T)((pmsm_ctrl_M->dwork.ifbk_pos -
            pmsm_ctrl_M->dwork.ifbk_neg) / 500.0 / TsMain);
          rtSharedDSM.CalData_L = (real32_T)(Cfg_VBus / 2. * Cfg_IndCalPwmDuty /
            pmsm_ctrl_M->dwork.di_dt);
        } else if (pmsm_ctrl_M->dwork.is_ind_id_actv == IN_neg_cycle) {
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_pos_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = Cfg_IndCalPwmDuty;
          pmsm_ctrl_M->dwork.ifbk_neg +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_neg_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = -Cfg_IndCalPwmDuty;
          pmsm_ctrl_M->dwork.ifbk_pos +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        }
        break;

       default:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_n >= (int32_T)
            TICK_L_CAL_WAIT_SETTLE) {
          /*  Wait for current / motor to settle. */
          pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl = IN_ind_id_actv;
          pmsm_ctrl_M->dwork.temporalCounter_i1_n = 0U;
          pmsm_ctrl_M->dwork.ifbk_pos = 0.0F;
          pmsm_ctrl_M->dwork.ifbk_neg = 0.0F;
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_pos_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = Cfg_IndCalPwmDuty;
          pmsm_ctrl_M->dwork.ifbk_neg +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_RAW_PWM;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = Cfg_IndCalPwmDuty;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_IND_ID;
          rtSharedDSM.CalData_L = -1.0F;
        }
        break;
      }
    }

    /* End of Chart: '<S11>/IndIdCal' */

    /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' incorporates:
     *  Constant: '<S25>/Zero'
     */
    rtb_TmpSignalConversionAtcalc_i[1] = 0.0F;
    rtb_TmpSignalConversionAtcalc_i[2] = 0.0F;

    /* Outputs for Atomic SubSystem: '<S25>/calc_pwm_dc' */
    calc_pwm_dc(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i,
                rtb_DataTypeConversion_f);

    /* End of Outputs for SubSystem: '<S25>/calc_pwm_dc' */

    /* BusCreator: '<S11>/Bus Creator' */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst_i;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst_i;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0] = rtb_DataTypeConversion_f[0];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1] = rtb_DataTypeConversion_f[1];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2] = rtb_DataTypeConversion_f[2];

    /* End of Outputs for SubSystem: '<S2>/mtr_ind_ident' */
    break;

   case 3:
    if (rtAction != rtPrevAction) {
      /* SystemReset for IfAction SubSystem: '<S2>/mtr_ifbk_ofs_ident' incorporates:
       *  ActionPort: '<S10>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S2>/Switch Case' incorporates:
       *  Chart: '<S10>/ResIdCal'
       */
      pmsm_ctrl_M->dwork.temporalCounter_i1 = 0U;
      pmsm_ctrl_M->dwork.is_active_c2_pmsm_ctrl = 0U;
      pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.ifbk_abc_sum[0] = 0.0F;
      pmsm_ctrl_M->dwork.ifbk_abc_sum[1] = 0.0F;
      pmsm_ctrl_M->dwork.ifbk_abc_sum[2] = 0.0F;

      /* End of SystemReset for SubSystem: '<S2>/mtr_ifbk_ofs_ident' */

      /* Enable for IfAction SubSystem: '<S2>/mtr_ifbk_ofs_ident' incorporates:
       *  ActionPort: '<S10>/Action Port'
       */

      /* SystemReset for Function Call SubSystem: '<S20>/get_mtr_ifbk_sum' */

      /* Enable for SwitchCase: '<S2>/Switch Case' incorporates:
       *  Chart: '<S10>/ResIdCal'
       */
      get_mtr_ifbk_sum_Reset(&pmsm_ctrl_M->self_get_mtr_ifbk_sum_f);

      /* End of SystemReset for SubSystem: '<S20>/get_mtr_ifbk_sum' */

      /* End of Enable for SubSystem: '<S2>/mtr_ifbk_ofs_ident' */
    }

    /* Outputs for IfAction SubSystem: '<S2>/mtr_ifbk_ofs_ident' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Chart: '<S10>/ResIdCal' */
    if (pmsm_ctrl_M->dwork.temporalCounter_i1 < 511U) {
      pmsm_ctrl_M->dwork.temporalCounter_i1++;
    }

    if (pmsm_ctrl_M->dwork.is_active_c2_pmsm_ctrl == 0U) {
      pmsm_ctrl_M->dwork.is_active_c2_pmsm_ctrl = 1U;
      pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl = IN_mtr_angl_ofs_cal_actv;
      pmsm_ctrl_M->dwork.temporalCounter_i1 = 0U;
      rtb_CtrlMdRqst = CTRL_MD_RAW_PWM;
      rtb_CalMgrStRqst = ST_IFBK_OFS_CAL;
      rtb_TmpSignalConversionAtcalc_i[0] =
        pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
      rtb_TmpSignalConversionAtcalc_i[1] =
        pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1];
      rtb_TmpSignalConversionAtcalc_i[2] =
        pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2];

      /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_sum' */
      get_mtr_ifbk_sum(&pmsm_ctrl_M->self_get_mtr_ifbk_sum_f,
                       rtb_TmpSignalConversionAtcalc_i,
                       pmsm_ctrl_M->blockIO.Add_p);

      /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_sum' */
      pmsm_ctrl_M->dwork.ifbk_abc_sum[0] = pmsm_ctrl_M->blockIO.Add_p[0];
      pmsm_ctrl_M->dwork.ifbk_abc_sum[1] = pmsm_ctrl_M->blockIO.Add_p[1];
      pmsm_ctrl_M->dwork.ifbk_abc_sum[2] = pmsm_ctrl_M->blockIO.Add_p[2];
      rtSharedDSM.CalData_IfbkOfs_Abc[0] = (real32_T)0.;
      rtSharedDSM.CalData_IfbkOfs_Abc[1] = (real32_T)0.;
      rtSharedDSM.CalData_IfbkOfs_Abc[2] = (real32_T)0.;
    } else if (pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl == IN_mtr_angl_ofs_cal_actv) {
      if (pmsm_ctrl_M->dwork.temporalCounter_i1 >= (int32_T)
          TICK_IFBK_OFS_WAIT_SETTLE) {
        /*  Wait for motor to settle. */
        pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl = IN_mtr_angl_ofs_cal_done;
        rtb_CtrlMdRqst = CTRL_MD_OFF;
        rtb_CalMgrStRqst = ST_DONE;
        rtb_TmpSignalConversionAtcalc_i[0] = pmsm_ctrl_M->dwork.ifbk_abc_sum[0];
        rtb_TmpSignalConversionAtcalc_i[1] = pmsm_ctrl_M->dwork.ifbk_abc_sum[1];
        rtb_TmpSignalConversionAtcalc_i[2] = pmsm_ctrl_M->dwork.ifbk_abc_sum[2];

        /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_avg' */
        get_mtr_ifbk_avg(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, (real32_T)
                         TICK_IFBK_OFS_WAIT_SETTLE,
                         rtSharedDSM.CalData_IfbkOfs_Abc);

        /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_avg' */
      } else {
        rtb_CtrlMdRqst = CTRL_MD_RAW_PWM;
        rtb_CalMgrStRqst = ST_IFBK_OFS_CAL;
        rtb_TmpSignalConversionAtcalc_i[0] =
          pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        rtb_TmpSignalConversionAtcalc_i[1] =
          pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1];
        rtb_TmpSignalConversionAtcalc_i[2] =
          pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2];

        /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_sum' */
        get_mtr_ifbk_sum(&pmsm_ctrl_M->self_get_mtr_ifbk_sum_f,
                         rtb_TmpSignalConversionAtcalc_i,
                         pmsm_ctrl_M->blockIO.Add_p);

        /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_sum' */
        pmsm_ctrl_M->dwork.ifbk_abc_sum[0] = pmsm_ctrl_M->blockIO.Add_p[0];
        pmsm_ctrl_M->dwork.ifbk_abc_sum[1] = pmsm_ctrl_M->blockIO.Add_p[1];
        pmsm_ctrl_M->dwork.ifbk_abc_sum[2] = pmsm_ctrl_M->blockIO.Add_p[2];
        rtSharedDSM.CalData_IfbkOfs_Abc[0] = (real32_T)0.;
        rtSharedDSM.CalData_IfbkOfs_Abc[1] = (real32_T)0.;
        rtSharedDSM.CalData_IfbkOfs_Abc[2] = (real32_T)0.;
      }
    } else {
      rtb_CtrlMdRqst = CTRL_MD_OFF;
      rtb_CalMgrStRqst = ST_DONE;
      rtb_TmpSignalConversionAtcalc_i[0] = pmsm_ctrl_M->dwork.ifbk_abc_sum[0];
      rtb_TmpSignalConversionAtcalc_i[1] = pmsm_ctrl_M->dwork.ifbk_abc_sum[1];
      rtb_TmpSignalConversionAtcalc_i[2] = pmsm_ctrl_M->dwork.ifbk_abc_sum[2];

      /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_avg' */
      get_mtr_ifbk_avg(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, (real32_T)
                       TICK_IFBK_OFS_WAIT_SETTLE,
                       rtSharedDSM.CalData_IfbkOfs_Abc);

      /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_avg' */
    }

    /* End of Chart: '<S10>/ResIdCal' */

    /* BusCreator: '<S10>/Bus Creator' incorporates:
     *  Constant: '<S21>/Zero'
     *  SignalConversion: '<S10>/TmpSignal ConversionAtBus CreatorInport3'
     */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = rtb_CtrlMdRqst;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = rtb_CalMgrStRqst;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0] = 0.0F;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1] = 0.0F;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2] = 0.0F;

    /* End of Outputs for SubSystem: '<S2>/mtr_ifbk_ofs_ident' */
    break;

   case 4:
    if (rtAction != rtPrevAction) {
      /* InitializeConditions for IfAction SubSystem: '<S2>/enc_ofs_cal_routine' incorporates:
       *  ActionPort: '<S9>/Action Port'
       */
      /* InitializeConditions for SwitchCase: '<S2>/Switch Case' incorporates:
       *  UnitDelay: '<S14>/Unit Delay'
       */
      pmsm_ctrl_M->dwork.UnitDelay_DSTATE_j = 0.0F;

      /* End of InitializeConditions for SubSystem: '<S2>/enc_ofs_cal_routine' */

      /* SystemReset for IfAction SubSystem: '<S2>/enc_ofs_cal_routine' incorporates:
       *  ActionPort: '<S9>/Action Port'
       */
      /* SystemReset for SwitchCase: '<S2>/Switch Case' incorporates:
       *  Chart: '<S9>/EncOfsCal'
       */
      pmsm_ctrl_M->dwork.temporalCounter_i1_h = 0U;
      pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl = 0U;
      pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.ticks_inc = 0;
      pmsm_ctrl_M->dwork.ticks_start = 0;
      pmsm_ctrl_M->dwork.ticks_end = 0;
      pmsm_ctrl_M->dwork.TICK_TGT = 0;
      pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
      pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_FAILED;
      pmsm_ctrl_M->blockIO.PwmRqst = 0.0F;
      pmsm_ctrl_M->blockIO.Ticks = 0;

      /* End of SystemReset for SubSystem: '<S2>/enc_ofs_cal_routine' */
    }

    /* Outputs for IfAction SubSystem: '<S2>/enc_ofs_cal_routine' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* Chart: '<S9>/EncOfsCal' */
    if (pmsm_ctrl_M->dwork.temporalCounter_i1_h < 255U) {
      pmsm_ctrl_M->dwork.temporalCounter_i1_h++;
    }

    if (pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl == 0U) {
      pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl = 1U;
      pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_mtr_n_poles_enc_ofs_init;
      pmsm_ctrl_M->dwork.temporalCounter_i1_h = 0U;
      if (Cfg_EncCnts > 268435455) {
        pmsm_ctrl_M->dwork.TICK_TGT = MAX_int32_T;
      } else if (Cfg_EncCnts <= -268435456) {
        pmsm_ctrl_M->dwork.TICK_TGT = MIN_int32_T;
      } else {
        pmsm_ctrl_M->dwork.TICK_TGT = Cfg_EncCnts << 3;
      }

      pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_RAW_PWM;
      pmsm_ctrl_M->blockIO.PwmRqst = Cfg_AnglOfsCalPwmDuty;
      pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_ENC_OFS;
      rtSharedDSM.CalData_nPoles = -1;
      pmsm_ctrl_M->blockIO.Ticks = 0;
      pmsm_ctrl_M->dwork.ticks_inc = (int32_T)div_nzp_usu32_sat
        (pmsm_ctrl_M->dwork.TICK_TGT, TICK_OFS_CAL_RAMP);
      rtSharedDSM.CalData_EncOfs =
        pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
      pmsm_ctrl_M->dwork.ticks_start = 0;
      pmsm_ctrl_M->dwork.ticks_end = 0;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl) {
       case IN_calc_enc_ofs_move_forward:
        if ((pmsm_ctrl_M->dwork.ticks_end >= 0) &&
            (pmsm_ctrl_M->dwork.ticks_start < pmsm_ctrl_M->dwork.ticks_end -
             MAX_int32_T)) {
          qY = MAX_int32_T;
        } else if ((pmsm_ctrl_M->dwork.ticks_end < 0) &&
                   (pmsm_ctrl_M->dwork.ticks_start >
                    pmsm_ctrl_M->dwork.ticks_end - MIN_int32_T)) {
          qY = MIN_int32_T;
        } else {
          qY = pmsm_ctrl_M->dwork.ticks_end - pmsm_ctrl_M->dwork.ticks_start;
        }

        if (qY < 0) {
          if (qY <= MIN_int32_T) {
            qY = MAX_int32_T;
          } else {
            qY = -qY;
          }
        }

        if ((pmsm_ctrl_M->blockIO.Ticks >= pmsm_ctrl_M->dwork.TICK_TGT) && (qY <
             TICK_INC_MIN)) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_enc_cnts_err;

          /*  When state machine goes into this state, it means that no encoder movement
             was detected; either because the encoder is not connected, motor has no
             power or something else. So calibration is finished here.
             TODO: Signal & handle error. */
          pmsm_ctrl_M->dwork.ticks_end = 0;
          rtSharedDSM.CalData_nPoles = -1;
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_FAILED;
          if (Cfg_EncCnts <= MIN_int32_T) {
            rtSharedDSM.CalData_EncOfs = MAX_int32_T;
          } else {
            rtSharedDSM.CalData_EncOfs = -Cfg_EncCnts;
          }
        } else if (pmsm_ctrl_M->blockIO.Ticks >= pmsm_ctrl_M->dwork.TICK_TGT) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_calc_n_poles;
          pmsm_ctrl_M->dwork.temporalCounter_i1_h = 0U;
          if ((pmsm_ctrl_M->dwork.ticks_end >= 0) &&
              (pmsm_ctrl_M->dwork.ticks_start < pmsm_ctrl_M->dwork.ticks_end -
               MAX_int32_T)) {
            qY = MAX_int32_T;
          } else if ((pmsm_ctrl_M->dwork.ticks_end < 0) &&
                     (pmsm_ctrl_M->dwork.ticks_start >
                      pmsm_ctrl_M->dwork.ticks_end - MIN_int32_T)) {
            qY = MIN_int32_T;
          } else {
            qY = pmsm_ctrl_M->dwork.ticks_end - pmsm_ctrl_M->dwork.ticks_start;
          }

          if (qY < 0) {
            if (qY <= MIN_int32_T) {
              qY = MAX_int32_T;
            } else {
              qY = -qY;
            }
          }

          rtSharedDSM.CalData_nPoles = pmsm_ctrl_M->blockIO.Ticks / qY;
        } else {
          pmsm_ctrl_M->blockIO.PwmRqst = Cfg_EncOfsCalPwmDuty;
          if ((pmsm_ctrl_M->blockIO.Ticks < 0) && (pmsm_ctrl_M->dwork.ticks_inc <
               MIN_int32_T - pmsm_ctrl_M->blockIO.Ticks)) {
            pmsm_ctrl_M->blockIO.Ticks = MIN_int32_T;
          } else if ((pmsm_ctrl_M->blockIO.Ticks > 0) &&
                     (pmsm_ctrl_M->dwork.ticks_inc > MAX_int32_T
                      - pmsm_ctrl_M->blockIO.Ticks)) {
            pmsm_ctrl_M->blockIO.Ticks = MAX_int32_T;
          } else {
            pmsm_ctrl_M->blockIO.Ticks += pmsm_ctrl_M->dwork.ticks_inc;
          }

          pmsm_ctrl_M->dwork.ticks_end =
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
        }
        break;

       case IN_calc_n_poles:
        if ((rtSharedDSM.CalData_nPoles < POLES_CAL_MIN) ||
            (rtSharedDSM.CalData_nPoles > POLES_CAL_MAX)) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_enc_cnts_err;

          /*  When state machine goes into this state, it means that no encoder movement
             was detected; either because the encoder is not connected, motor has no
             power or something else. So calibration is finished here.
             TODO: Signal & handle error. */
          pmsm_ctrl_M->dwork.ticks_end = 0;
          rtSharedDSM.CalData_nPoles = -1;
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_FAILED;
          if (Cfg_EncCnts <= MIN_int32_T) {
            rtSharedDSM.CalData_EncOfs = MAX_int32_T;
          } else {
            rtSharedDSM.CalData_EncOfs = -Cfg_EncCnts;
          }
        } else if (pmsm_ctrl_M->dwork.temporalCounter_i1_h >= 1) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_move_back_calc_enc_ofs;
          if ((pmsm_ctrl_M->blockIO.Ticks >= 0) && (pmsm_ctrl_M->dwork.ticks_inc
               < pmsm_ctrl_M->blockIO.Ticks - MAX_int32_T)) {
            pmsm_ctrl_M->blockIO.Ticks = MAX_int32_T;
          } else if ((pmsm_ctrl_M->blockIO.Ticks < 0) &&
                     (pmsm_ctrl_M->dwork.ticks_inc > pmsm_ctrl_M->blockIO.Ticks
                      - MIN_int32_T)) {
            pmsm_ctrl_M->blockIO.Ticks = MIN_int32_T;
          } else {
            pmsm_ctrl_M->blockIO.Ticks -= pmsm_ctrl_M->dwork.ticks_inc;
          }
        } else {
          if ((pmsm_ctrl_M->dwork.ticks_end >= 0) &&
              (pmsm_ctrl_M->dwork.ticks_start < pmsm_ctrl_M->dwork.ticks_end -
               MAX_int32_T)) {
            qY = MAX_int32_T;
          } else if ((pmsm_ctrl_M->dwork.ticks_end < 0) &&
                     (pmsm_ctrl_M->dwork.ticks_start >
                      pmsm_ctrl_M->dwork.ticks_end - MIN_int32_T)) {
            qY = MIN_int32_T;
          } else {
            qY = pmsm_ctrl_M->dwork.ticks_end - pmsm_ctrl_M->dwork.ticks_start;
          }

          if (qY < 0) {
            if (qY <= MIN_int32_T) {
              qY = MAX_int32_T;
            } else {
              qY = -qY;
            }
          }

          rtSharedDSM.CalData_nPoles = pmsm_ctrl_M->blockIO.Ticks / qY;
        }
        break;

       case IN_done_m:
        pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_DONE;
        pmsm_ctrl_M->blockIO.PwmRqst = (real32_T)0.;
        break;

       case IN_enc_cnts_err:
        /*  When state machine goes into this state, it means that no encoder movement
           was detected; either because the encoder is not connected, motor has no
           power or something else. So calibration is finished here.
           TODO: Signal & handle error. */
        pmsm_ctrl_M->dwork.ticks_end = 0;
        rtSharedDSM.CalData_nPoles = -1;
        pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_FAILED;
        if (Cfg_EncCnts <= MIN_int32_T) {
          rtSharedDSM.CalData_EncOfs = MAX_int32_T;
        } else {
          rtSharedDSM.CalData_EncOfs = -Cfg_EncCnts;
        }
        break;

       case IN_move_back_calc_enc_ofs:
        if (pmsm_ctrl_M->blockIO.Ticks <= 0) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_done_m;
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_DONE;
          pmsm_ctrl_M->blockIO.PwmRqst = (real32_T)0.;
        } else if ((pmsm_ctrl_M->blockIO.Ticks >= 0) &&
                   (pmsm_ctrl_M->dwork.ticks_inc < pmsm_ctrl_M->blockIO.Ticks -
                    MAX_int32_T)) {
          pmsm_ctrl_M->blockIO.Ticks = MAX_int32_T;
        } else if ((pmsm_ctrl_M->blockIO.Ticks < 0) &&
                   (pmsm_ctrl_M->dwork.ticks_inc > pmsm_ctrl_M->blockIO.Ticks -
                    MIN_int32_T)) {
          pmsm_ctrl_M->blockIO.Ticks = MIN_int32_T;
        } else {
          pmsm_ctrl_M->blockIO.Ticks -= pmsm_ctrl_M->dwork.ticks_inc;
        }
        break;

       default:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_h >= (int32_T)
            TICK_ENC_OFS_WAIT_SETTLE) {
          /*  Wait for motor / current to settle. */
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_calc_enc_ofs_move_forward;
          pmsm_ctrl_M->blockIO.PwmRqst = Cfg_EncOfsCalPwmDuty;
          pmsm_ctrl_M->dwork.ticks_start =
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_RAW_PWM;
          pmsm_ctrl_M->blockIO.PwmRqst = Cfg_AnglOfsCalPwmDuty;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_ENC_OFS;
          rtSharedDSM.CalData_nPoles = -1;
          pmsm_ctrl_M->blockIO.Ticks = 0;
          pmsm_ctrl_M->dwork.ticks_inc = (int32_T)div_nzp_usu32_sat
            (pmsm_ctrl_M->dwork.TICK_TGT, TICK_OFS_CAL_RAMP);
          rtSharedDSM.CalData_EncOfs =
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
          pmsm_ctrl_M->dwork.ticks_start = 0;
          pmsm_ctrl_M->dwork.ticks_end = 0;
        }
        break;
      }
    }

    /* End of Chart: '<S9>/EncOfsCal' */

    /* Sum: '<S14>/Add1' incorporates:
     *  Constant: '<S14>/Constant'
     *  Product: '<S14>/Product'
     *  Product: '<S14>/Product1'
     *  UnitDelay: '<S14>/Unit Delay'
     */
    rtb_PwmRqst_l = pmsm_ctrl_M->blockIO.PwmRqst * 0.038500011F + 0.9615F *
      pmsm_ctrl_M->dwork.UnitDelay_DSTATE_j;

    /* SignalConversion: '<S9>/TmpSignal ConversionAtcalc_mod_waveInport1' incorporates:
     *  Constant: '<S16>/Constant'
     */
    rtb_TmpSignalConversionAtcalc_i[0] = rtb_PwmRqst_l;
    rtb_TmpSignalConversionAtcalc_i[1] = 0.0F;
    rtb_TmpSignalConversionAtcalc_i[2] = 0.0F;

    /* Outputs for Atomic SubSystem: '<S9>/calc_mod_wave' */
    calc_mod_wave(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, 6.28318548F *
                  (real32_T)pmsm_ctrl_M->blockIO.Ticks / (real32_T)Cfg_EncCnts,
                  rtb_DataTypeConversion_f, rtb_DataTypeConversion_f);

    /* End of Outputs for SubSystem: '<S9>/calc_mod_wave' */

    /* BusCreator: '<S9>/Bus Creator' incorporates:
     *  Constant: '<S9>/Constant'
     *  DataTypeConversion: '<S9>/Data Type Cnversion1'
     *  DataTypeConversion: '<S9>/Data Type Conversion'
     *  Gain: '<S9>/Gain'
     *  Product: '<S9>/Divide'
     */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst;
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[0] = rtb_DataTypeConversion_f[0];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[1] = rtb_DataTypeConversion_f[1];
    pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst[2] = rtb_DataTypeConversion_f[2];

    /* Update for UnitDelay: '<S14>/Unit Delay' */
    pmsm_ctrl_M->dwork.UnitDelay_DSTATE_j = rtb_PwmRqst_l;

    /* End of Outputs for SubSystem: '<S2>/enc_ofs_cal_routine' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */

  /* DataStoreRead: '<S2>/Data Store Read4' */
  CALIB_PARAM_BUS.ifbk_ofs[0] = rtSharedDSM.CalData_IfbkOfs_Abc[0];
  CALIB_PARAM_BUS.ifbk_ofs[1] = rtSharedDSM.CalData_IfbkOfs_Abc[1];
  CALIB_PARAM_BUS.ifbk_ofs[2] = rtSharedDSM.CalData_IfbkOfs_Abc[2];

  /* DataStoreRead: '<S2>/Data Store Read' */
  CALIB_PARAM_BUS.enc_ofs = rtSharedDSM.CalData_EncOfs;

  /* DataStoreRead: '<S2>/Data Store Read1' */
  CALIB_PARAM_BUS.inductance = rtSharedDSM.CalData_L;

  /* DataStoreRead: '<S2>/Data Store Read2' */
  CALIB_PARAM_BUS.pole_pairs = rtSharedDSM.CalData_nPoles;

  /* DataStoreRead: '<S2>/Data Store Read3' */
  CALIB_PARAM_BUS.resistance = rtSharedDSM.CalData_Res;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_Foc(RT_MODEL *const pmsm_ctrl_M)
{
  real32_T rtb_DiscreteTimeIntegrator_iz;
  real32_T rtb_Divide2;
  real32_T rtb_Switch1;
  real32_T rtb_Switch_m_idx_0;
  real32_T rtb_Switch_m_idx_1;
  real32_T rtb_Switch_d_idx_0;
  real32_T rtb_Switch_d_idx_1;
  real32_T rtb_Switch_d_idx_2;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Foc_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlFast'
   */
  /* Switch: '<S31>/Switch' incorporates:
   *  Gain: '<S31>/Gain'
   *  Logic: '<S31>/Logical Operator'
   *  Logic: '<S31>/Logical Operator1'
   */
  if (!(pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl ||
        pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl)) {
    rtb_Switch_d_idx_0 = pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0];
    rtb_Switch_d_idx_1 = pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[1];
    rtb_Switch_d_idx_2 = pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[2];
  } else {
    rtb_Switch_d_idx_0 = pmsm_ctrl_M->blockIO.BusCreator_c.motn_ctrl_cmd;
    rtb_Switch_d_idx_1 = 0.0F;
    rtb_Switch_d_idx_2 = 0.0F;
  }

  /* End of Switch: '<S31>/Switch' */

  /* Outputs for Enabled SubSystem: '<S30>/raw_pwm_calc' incorporates:
   *  EnablePort: '<S36>/Enable'
   */
  /* SignalConversion: '<S30>/HiddenBuf_InsertedFor_raw_pwm_calc_at_inport_1' */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_raw_pwm) {
    /* Saturate: '<S36>/Saturation' */
    if (rtb_Switch_d_idx_0 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[0] = 1.0F;
    } else if (rtb_Switch_d_idx_0 < 0.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[0] = 0.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation_g[0] = rtb_Switch_d_idx_0;
    }

    /* SignalConversion: '<S36>/OutportBufferFormod_wave' */
    pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[0] = 0.0F;

    /* Saturate: '<S36>/Saturation' */
    if (rtb_Switch_d_idx_1 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[1] = 1.0F;
    } else if (rtb_Switch_d_idx_1 < 0.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[1] = 0.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation_g[1] = rtb_Switch_d_idx_1;
    }

    /* SignalConversion: '<S36>/OutportBufferFormod_wave' */
    pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[1] = 0.0F;

    /* Saturate: '<S36>/Saturation' */
    if (rtb_Switch_d_idx_2 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[2] = 1.0F;
    } else if (rtb_Switch_d_idx_2 < 0.0F) {
      pmsm_ctrl_M->blockIO.Saturation_g[2] = 0.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation_g[2] = rtb_Switch_d_idx_2;
    }

    /* SignalConversion: '<S36>/OutportBufferFormod_wave' */
    pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[2] = 0.0F;
  }

  /* End of SignalConversion: '<S30>/HiddenBuf_InsertedFor_raw_pwm_calc_at_inport_1' */
  /* End of Outputs for SubSystem: '<S30>/raw_pwm_calc' */

  /* Outputs for Atomic SubSystem: '<S30>/calc_elec_angle' */

  /* SignalConversion: '<S30>/TmpSignal ConversionAtcalc_elec_angleOutport1' incorporates:
   *  DataTypeConversion: '<S30>/Data Type Conversion3'
   */
  calc_elec_angle(pmsm_ctrl_M, pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts,
                  &(DBG_Struct.e_angl), &rtb_Divide2, Cfg_EncCnts, Cfg_PolePairs);

  /* End of Outputs for SubSystem: '<S30>/calc_elec_angle' */

  /* MultiPortSwitch: '<S34>/Multiport Switch' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Constant: '<S34>/Constant3'
   */
  switch (pmsm_ctrl_M->blockIO.BusCreator2.ctrl_md_act) {
   case CTRL_MD_TRQ:
    rtb_DiscreteTimeIntegrator_iz = 1.0F / Cfg_MtrKtrq;
    break;

   case CTRL_MD_IFBK:
    rtb_DiscreteTimeIntegrator_iz = 1.0F;
    break;

   default:
    rtb_DiscreteTimeIntegrator_iz = 1.0F;
    break;
  }

  /* End of MultiPortSwitch: '<S34>/Multiport Switch' */

  /* Product: '<S34>/Product' */
  DBG_Struct.ifbk_q_tgt = rtb_Switch_d_idx_0 * rtb_DiscreteTimeIntegrator_iz;

  /* Sum: '<S44>/Subtract' incorporates:
   *  DiscreteIntegrator: '<S43>/Discrete-Time Integrator'
   */
  rtb_DiscreteTimeIntegrator_iz = rtb_Divide2 -
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h;

  /* Sum: '<S44>/Add' incorporates:
   *  DiscreteIntegrator: '<S45>/Discrete-Time Integrator'
   *  Gain: '<S44>/Gain1'
   */
  DBG_Struct.mtr_spd_pll = 800.0F * rtb_DiscreteTimeIntegrator_iz +
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k;

  /* DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */
  DBG_Struct.mtr_spd_obs = pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg;

  /* Switch: '<S30>/Switch1' incorporates:
   *  Constant: '<S30>/Constant1'
   *  Constant: '<S33>/Constant'
   *  Switch: '<S33>/Switch'
   */
  if (Cfg_SpdSnsEnbl) {
    rtb_Switch1 = pmsm_ctrl_M->blockIO.BusCreator.mtrif_spd_sns;
  } else if (Cfg_UseSpdPll) {
    /* Switch: '<S33>/Switch' */
    rtb_Switch1 = DBG_Struct.mtr_spd_pll;
  } else {
    rtb_Switch1 = DBG_Struct.mtr_spd_obs;
  }

  /* End of Switch: '<S30>/Switch1' */

  /* Sum: '<S46>/Add1' incorporates:
   *  Constant: '<S46>/Constant'
   *  Product: '<S46>/Product'
   *  Product: '<S46>/Product1'
   *  UnitDelay: '<S46>/Unit Delay'
   */
  DBG_Struct.i_abc_lpf[0] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0] *
    0.5F + 0.5F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[0];
  DBG_Struct.i_abc_lpf[1] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1] *
    0.5F + 0.5F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[1];
  DBG_Struct.i_abc_lpf[2] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2] *
    0.5F + 0.5F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[2];

  /* Gain: '<S48>/Gain1' incorporates:
   *  Fcn: '<S48>/0'
   *  Fcn: '<S48>/d'
   *  Fcn: '<S48>/q'
   */
  DBG_Struct.i_dq0[0] = ((arm_sin_f32((DBG_Struct.e_angl + 1.57079637F) -
    2.09439516F) * DBG_Struct.i_abc_lpf[1] + arm_sin_f32(DBG_Struct.e_angl +
    1.57079637F) * DBG_Struct.i_abc_lpf[0]) + arm_sin_f32((DBG_Struct.e_angl +
    1.57079637F) + 2.09439516F) * DBG_Struct.i_abc_lpf[2]) * 0.666666687F;
  DBG_Struct.i_dq0[1] = ((arm_cos_f32((DBG_Struct.e_angl + 1.57079637F) -
    2.09439516F) * DBG_Struct.i_abc_lpf[1] + arm_cos_f32(DBG_Struct.e_angl +
    1.57079637F) * DBG_Struct.i_abc_lpf[0]) + arm_cos_f32((DBG_Struct.e_angl +
    1.57079637F) + 2.09439516F) * DBG_Struct.i_abc_lpf[2]) * 0.666666687F;
  DBG_Struct.i_dq0[2] = ((DBG_Struct.i_abc_lpf[0] + DBG_Struct.i_abc_lpf[1]) +
    DBG_Struct.i_abc_lpf[2]) * 0.5F * 0.666666687F;

  /* Outputs for Enabled SubSystem: '<S34>/IfbkCtrl' incorporates:
   *  EnablePort: '<S47>/Enable'
   */
  /* SignalConversion: '<S34>/HiddenBuf_InsertedFor_IfbkCtrl_at_inport_5' incorporates:
   *  Constant: '<S34>/Constant'
   *  Constant: '<S47>/Constant6'
   */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
    if (!pmsm_ctrl_M->dwork.IfbkCtrl_MODE) {
      /* SystemReset for Atomic SubSystem: '<S50>/PI-Ctrl-Varying-Gains' */
      PI_Ctrl_Reset(&pmsm_ctrl_M->self_PICtrlVaryingGains_p);

      /* End of SystemReset for SubSystem: '<S50>/PI-Ctrl-Varying-Gains' */

      /* SystemReset for Atomic SubSystem: '<S49>/PI-Ctrl-Varying-Gains' */
      PI_Ctrl_Reset(&pmsm_ctrl_M->self_PICtrlVaryingGains);

      /* End of SystemReset for SubSystem: '<S49>/PI-Ctrl-Varying-Gains' */
      pmsm_ctrl_M->dwork.IfbkCtrl_MODE = true;
    }

    /* Switch: '<S50>/Switch' incorporates:
     *  Constant: '<S47>/Constant3'
     *  Constant: '<S47>/Constant4'
     *  Constant: '<S50>/Constant'
     *  Constant: '<S50>/Constant1'
     *  Constant: '<S50>/Constant2'
     *  Product: '<S50>/Product'
     */
    if (Cfg_AutoCalEnbl) {
      rtb_Switch_m_idx_0 = 0.0F;
      rtb_Switch_m_idx_1 = 0.0F;
    } else {
      rtb_Switch_m_idx_0 = Cfg_Ls * Cfg_IfbkCtrlBW;
      rtb_Switch_m_idx_1 = Cfg_Rs * Cfg_IfbkCtrlBW;
    }

    /* End of Switch: '<S50>/Switch' */

    /* Outputs for Atomic SubSystem: '<S50>/PI-Ctrl-Varying-Gains' */
    PI_Ctrl(&pmsm_ctrl_M->self_PICtrlVaryingGains_p, DBG_Struct.ifbk_q_tgt,
            DBG_Struct.i_dq0[1], rtb_Switch_m_idx_0, rtb_Switch_m_idx_1,
            &rtb_Switch_m_idx_1, 12.0F, -12.0F);

    /* End of Outputs for SubSystem: '<S50>/PI-Ctrl-Varying-Gains' */

    /* Outputs for Enabled SubSystem: '<S47>/mtr_coupling_bemf_comp' incorporates:
     *  EnablePort: '<S51>/Enable'
     */
    if (Cfg_EnblDynComp) {
      /* Gain: '<S51>/Gain4' */
      rtb_Switch_m_idx_0 = (real32_T)Cfg_PolePairs * rtb_Switch1;

      /* Gain: '<S51>/Gain3' incorporates:
       *  Gain: '<S51>/Gain2'
       *  Product: '<S51>/Product1'
       *  Sum: '<S51>/Add1'
       */
      pmsm_ctrl_M->blockIO.Gain3 = (Cfg_MFlux / Cfg_Ls * rtb_Switch_m_idx_0 +
        DBG_Struct.i_dq0[0] * rtb_Switch_m_idx_0) * Cfg_Ls;

      /* Product: '<S51>/Product' */
      rtb_Switch_m_idx_0 *= DBG_Struct.i_dq0[1];

      /* Gain: '<S51>/Gain' */
      pmsm_ctrl_M->blockIO.Gain = -Cfg_Ls * rtb_Switch_m_idx_0;
    }

    /* End of Outputs for SubSystem: '<S47>/mtr_coupling_bemf_comp' */

    /* SignalConversion: '<S47>/OutportBufferForvdq0_ctrl' incorporates:
     *  Constant: '<S47>/Constant6'
     *  Sum: '<S47>/Add'
     */
    DBG_Struct.ifbk_ctrl_v_dq0[1] = rtb_Switch_m_idx_1 +
      pmsm_ctrl_M->blockIO.Gain3;

    /* Switch: '<S49>/Switch' incorporates:
     *  Constant: '<S47>/Constant3'
     *  Constant: '<S47>/Constant4'
     *  Constant: '<S49>/Constant'
     *  Constant: '<S49>/Constant1'
     *  Constant: '<S49>/Constant2'
     *  Product: '<S49>/Product'
     */
    if (Cfg_AutoCalEnbl) {
      rtb_Switch_m_idx_0 = 0.0F;
      rtb_Switch_m_idx_1 = 0.0F;
    } else {
      rtb_Switch_m_idx_0 = 0.0013F * Cfg_IfbkCtrlBW;
      rtb_Switch_m_idx_1 = 0.9F * Cfg_IfbkCtrlBW;
    }

    /* End of Switch: '<S49>/Switch' */

    /* Outputs for Atomic SubSystem: '<S49>/PI-Ctrl-Varying-Gains' */
    PI_Ctrl(&pmsm_ctrl_M->self_PICtrlVaryingGains, 0.0F, DBG_Struct.i_dq0[0],
            rtb_Switch_m_idx_0, rtb_Switch_m_idx_1, &rtb_Switch_m_idx_1, 12.0F,
            -12.0F);

    /* End of Outputs for SubSystem: '<S49>/PI-Ctrl-Varying-Gains' */

    /* SignalConversion: '<S47>/OutportBufferForvdq0_ctrl' incorporates:
     *  Constant: '<S34>/Constant'
     *  Constant: '<S47>/Constant2'
     *  Sum: '<S47>/Add1'
     */
    DBG_Struct.ifbk_ctrl_v_dq0[0] = pmsm_ctrl_M->blockIO.Gain +
      rtb_Switch_m_idx_1;
    DBG_Struct.ifbk_ctrl_v_dq0[2] = 0.0F;
  } else {
    if (pmsm_ctrl_M->dwork.IfbkCtrl_MODE) {
      pmsm_ctrl_M->dwork.IfbkCtrl_MODE = false;
    }
  }

  /* End of SignalConversion: '<S34>/HiddenBuf_InsertedFor_IfbkCtrl_at_inport_5' */
  /* End of Outputs for SubSystem: '<S34>/IfbkCtrl' */

  /* Gain: '<S34>/Gain5' */
  rtb_Switch_m_idx_1 = 1.0F / (2.0F * Cfg_VBus);

  /* Outputs for Enabled SubSystem: '<S30>/mod_wave_calc' incorporates:
   *  EnablePort: '<S35>/Enable'
   */
  /* SignalConversion: '<S30>/HiddenBuf_InsertedFor_mod_wave_calc_at_inport_4' */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_mod_wave) {
    /* Switch: '<S35>/Switch' incorporates:
     *  Gain: '<S34>/Gain5'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
      rtb_Switch_d_idx_0 = rtb_Switch_m_idx_1 * DBG_Struct.ifbk_ctrl_v_dq0[0];
    }

    /* Saturate: '<S35>/Saturation1' */
    if (rtb_Switch_d_idx_0 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[0] = 1.0F;
    } else if (rtb_Switch_d_idx_0 < -1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[0] = -1.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation1[0] = rtb_Switch_d_idx_0;
    }

    /* Switch: '<S35>/Switch' incorporates:
     *  Gain: '<S34>/Gain5'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
      rtb_Switch_d_idx_0 = rtb_Switch_m_idx_1 * DBG_Struct.ifbk_ctrl_v_dq0[1];
    } else {
      rtb_Switch_d_idx_0 = rtb_Switch_d_idx_1;
    }

    /* Saturate: '<S35>/Saturation1' */
    if (rtb_Switch_d_idx_0 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[1] = 1.0F;
    } else if (rtb_Switch_d_idx_0 < -1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[1] = -1.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation1[1] = rtb_Switch_d_idx_0;
    }

    /* Switch: '<S35>/Switch' incorporates:
     *  Gain: '<S34>/Gain5'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
      rtb_Switch_d_idx_0 = rtb_Switch_m_idx_1 * DBG_Struct.ifbk_ctrl_v_dq0[2];
    } else {
      rtb_Switch_d_idx_0 = rtb_Switch_d_idx_2;
    }

    /* Saturate: '<S35>/Saturation1' */
    if (rtb_Switch_d_idx_0 > 1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[2] = 1.0F;
    } else if (rtb_Switch_d_idx_0 < -1.0F) {
      pmsm_ctrl_M->blockIO.Saturation1[2] = -1.0F;
    } else {
      pmsm_ctrl_M->blockIO.Saturation1[2] = rtb_Switch_d_idx_0;
    }

    /* Outputs for Atomic SubSystem: '<S35>/calc_mod_wave' */
    calc_mod_wave(pmsm_ctrl_M, pmsm_ctrl_M->blockIO.Saturation1,
                  DBG_Struct.e_angl, pmsm_ctrl_M->blockIO.DataTypeConversion,
                  pmsm_ctrl_M->blockIO.Gain1);

    /* End of Outputs for SubSystem: '<S35>/calc_mod_wave' */
  }

  /* End of SignalConversion: '<S30>/HiddenBuf_InsertedFor_mod_wave_calc_at_inport_4' */
  /* End of Outputs for SubSystem: '<S30>/mod_wave_calc' */

  /* Switch: '<S30>/Switch2' */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_raw_pwm) {
    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[0] =
      pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[0];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[0] = pmsm_ctrl_M->blockIO.Saturation_g[0];

    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[1] =
      pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[1];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[1] = pmsm_ctrl_M->blockIO.Saturation_g[1];

    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[2] =
      pmsm_ctrl_M->blockIO.OutportBufferFormod_wave[2];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[2] = pmsm_ctrl_M->blockIO.Saturation_g[2];
  } else {
    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[0] = pmsm_ctrl_M->blockIO.Gain1[0];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[0] =
      pmsm_ctrl_M->blockIO.DataTypeConversion[0];

    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[1] = pmsm_ctrl_M->blockIO.Gain1[1];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[1] =
      pmsm_ctrl_M->blockIO.DataTypeConversion[1];

    /* DataTypeConversion: '<S30>/Data Type Conversion' */
    pmsm_ctrl_M->blockIO.MtrIf_ModWave[2] = pmsm_ctrl_M->blockIO.Gain1[2];

    /* DataTypeConversion: '<S30>/Data Type Conversion5' */
    pmsm_ctrl_M->blockIO.MtrIf_PwmDc[2] =
      pmsm_ctrl_M->blockIO.DataTypeConversion[2];
  }

  /* End of Switch: '<S30>/Switch2' */

  /* DataTypeConversion: '<S30>/Data Type Conversion7' */
  pmsm_ctrl_M->blockIO.MtrIf_SpdOut[0] = pmsm_ctrl_M->blockIO.Saturation1[0];

  /* DataTypeConversion: '<S30>/Data Type Conversion6' */
  pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[0] = DBG_Struct.i_dq0[0];

  /* DataTypeConversion: '<S30>/Data Type Conversion7' */
  pmsm_ctrl_M->blockIO.MtrIf_SpdOut[1] = pmsm_ctrl_M->blockIO.Saturation1[1];

  /* DataTypeConversion: '<S30>/Data Type Conversion6' */
  pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[1] = DBG_Struct.i_dq0[1];

  /* Gain: '<S30>/Gain2' */
  rtb_Switch_m_idx_1 = Cfg_MtrKtrq * DBG_Struct.i_dq0[1];

  /* Sum: '<S37>/Add3' incorporates:
   *  DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
   */
  rtb_Divide2 -= pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke;

  /* Product: '<S37>/Product1' incorporates:
   *  Constant: '<S33>/ObsInertia'
   *  DiscreteIntegrator: '<S40>/Discrete-Time Integrator'
   */
  DBG_Struct.mtr_load_obs = pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p *
    DistObs_J;

  /* DataTypeConversion: '<S39>/Data Type Conversion4' incorporates:
   *  Constant: '<S39>/Constant'
   *  Constant: '<S39>/Constant2'
   *  DataTypeConversion: '<S39>/Data Type Conversion8'
   *  DiscreteIntegrator: '<S42>/Discrete-Time Integrator'
   *  Product: '<S39>/Product'
   */
  DBG_Struct.obs_enc_cnts = (int32_T)
    (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke * (real32_T)Cfg_EncCnts /
     6.28318548F);

  /* DataTypeConversion: '<S30>/Data Type Conversion2' */
  pmsm_ctrl_M->blockIO.MtrIf_TrqAct = rtb_Switch_m_idx_1;

  /* DataTypeConversion: '<S30>/Data Type Conversion1' */
  pmsm_ctrl_M->blockIO.MtrIf_SpdOut_i = rtb_Switch1;

  /* Update for DiscreteIntegrator: '<S43>/Discrete-Time Integrator' */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h += 0.0001F *
    DBG_Struct.mtr_spd_pll;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h >= 1.0E+6F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h = 1.0E+6F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h <= -1.0E+6F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h = -1.0E+6F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S43>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S44>/Gain'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k += 160000.0F *
    rtb_DiscreteTimeIntegrator_iz * 0.0001F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k >= 1.0E+6F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = 1.0E+6F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k <= -1.0E+6F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = -1.0E+6F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S45>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S33>/ObsInertia'
   *  DiscreteIntegrator: '<S40>/Discrete-Time Integrator'
   *  Gain: '<S37>/Gain1'
   *  Product: '<S37>/Product'
   *  Sum: '<S37>/Add'
   *  Sum: '<S37>/Add1'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg += ((DistObs_K2 *
    rtb_Divide2 + pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p) +
    rtb_Switch_m_idx_1 / DistObs_J) * 0.0001F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_kg = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S41>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S46>/Unit Delay' */
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[0] = DBG_Struct.i_abc_lpf[0];
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[1] = DBG_Struct.i_abc_lpf[1];
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE_o[2] = DBG_Struct.i_abc_lpf[2];

  /* Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S37>/Gain3'
   *  Sum: '<S37>/Add2'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke += (DistObs_K1 *
    rtb_Divide2 + DBG_Struct.mtr_spd_obs) * 0.0001F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S42>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S40>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S37>/Gain'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p += DistObs_K3 * rtb_Divide2
    * 0.0001F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S40>/Discrete-Time Integrator' */
  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Foc_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_MotnCtrl(RT_MODEL *const pmsm_ctrl_M)
{
  real32_T rtb_Product_f;
  real32_T rtb_Add_gh;
  real32_T rtb_Sign_k;
  real32_T rtb_Add1_j;
  real32_T rtb_Sign_g;
  int32_T tmp;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_MotnCtrl_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlMain'
   */
  /* Logic: '<S4>/Logical Operator' */
  DBG_Struct.enbl_motn_ctrl =
    (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl ||
     pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl);

  /* Outputs for Enabled SubSystem: '<S4>/MotnCtrl' incorporates:
   *  EnablePort: '<S60>/Enable'
   */
  if (DBG_Struct.enbl_motn_ctrl) {
    if (!pmsm_ctrl_M->dwork.MotnCtrl_MODE) {
      pmsm_ctrl_M->dwork.MotnCtrl_MODE = true;
    }

    /* Gain: '<S60>/Gain3' incorporates:
     *  DataTypeConversion: '<S60>/Data Type Conversion6'
     */
    DBG_Struct.mtr_cnts_tgt = Cfg_StepToEncCnts * (int32_T)
      pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0];

    /* Product: '<S64>/Product' incorporates:
     *  Constant: '<S64>/Constant'
     *  Constant: '<S64>/Constant1'
     *  DataTypeConversion: '<S64>/Data Type Conversion8'
     *  DataTypeConversion: '<S64>/Data Type Conversion9'
     */
    rtb_Product_f = (real32_T)DBG_Struct.mtr_cnts_tgt / (real32_T)Cfg_EncCnts *
      6.28318548F;

    /* Logic: '<S62>/Logical Operator' incorporates:
     *  Constant: '<S62>/Constant'
     */
    DBG_Struct.traj_plan_is_enbl = (Cfg_EnblTrajPlan &&
      pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl);

    /* Outputs for Enabled SubSystem: '<S62>/PosTrackDiff' incorporates:
     *  EnablePort: '<S69>/Enable'
     */
    if (DBG_Struct.traj_plan_is_enbl) {
      if (!pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* InitializeConditions for DiscreteIntegrator: '<S69>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE = 0.0F;

        /* InitializeConditions for DiscreteIntegrator: '<S69>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE = 0.0F;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = true;
      }

      /* DiscreteIntegrator: '<S69>/Discrete-Time Integrator1' */
      pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1 =
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE;

      /* DiscreteIntegrator: '<S69>/Discrete-Time Integrator' */
      pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator =
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE;

      /* Gain: '<S70>/Gain3' */
      rtb_Add_gh = TsMain * pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* Sum: '<S70>/Add8' incorporates:
       *  Sum: '<S69>/Add'
       */
      rtb_Sign_k = (pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1 - rtb_Product_f)
        + rtb_Add_gh;

      /* Sqrt: '<S71>/Sqrt' incorporates:
       *  Abs: '<S71>/Abs'
       *  Constant: '<S70>/d'
       *  Gain: '<S71>/Gain'
       *  Product: '<S71>/Product'
       *  Sum: '<S71>/Add'
       */
      mw_arm_sqrt_f32((8.0F * (real32_T)fabs(rtb_Sign_k) + 0.00100000016F) *
                      0.00100000016F, &rtb_Add1_j);

      /* Signum: '<S72>/Sign' */
      if (rtb_Sign_k < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else if (rtb_Sign_k > 0.0F) {
        rtb_Sign_g = 1.0F;
      } else {
        rtb_Sign_g = rtb_Sign_k;
      }

      /* End of Signum: '<S72>/Sign' */

      /* Sum: '<S72>/Add1' incorporates:
       *  Constant: '<S70>/d'
       *  Gain: '<S72>/Gain'
       *  Product: '<S72>/Product'
       *  Sum: '<S72>/Add'
       */
      rtb_Add1_j = (rtb_Add1_j - 0.00100000016F) * rtb_Sign_g * 0.5F +
        rtb_Add_gh;

      /* Sum: '<S73>/Add1' */
      rtb_Add_gh = (rtb_Add_gh + rtb_Sign_k) - rtb_Add1_j;

      /* Sum: '<S76>/Add1' incorporates:
       *  Constant: '<S70>/d'
       */
      rtb_Sign_g = 0.00100000016F + rtb_Sign_k;

      /* Sum: '<S76>/Add2' incorporates:
       *  Constant: '<S70>/d'
       */
      rtb_Sign_k -= 0.00100000016F;

      /* Signum: '<S76>/Sign' */
      if (rtb_Sign_g < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else {
        if (rtb_Sign_g > 0.0F) {
          rtb_Sign_g = 1.0F;
        }
      }

      /* End of Signum: '<S76>/Sign' */

      /* Signum: '<S76>/Sign1' */
      if (rtb_Sign_k < 0.0F) {
        rtb_Sign_k = -1.0F;
      } else {
        if (rtb_Sign_k > 0.0F) {
          rtb_Sign_k = 1.0F;
        }
      }

      /* End of Signum: '<S76>/Sign1' */

      /* Sum: '<S73>/Add2' incorporates:
       *  Gain: '<S76>/Gain1'
       *  Product: '<S73>/Product'
       *  Sum: '<S76>/Add'
       */
      rtb_Add1_j += (rtb_Sign_g - rtb_Sign_k) * 0.5F * rtb_Add_gh;

      /* Signum: '<S74>/Sign' */
      if (rtb_Add1_j < 0.0F) {
        rtb_Sign_k = -1.0F;
      } else if (rtb_Add1_j > 0.0F) {
        rtb_Sign_k = 1.0F;
      } else {
        rtb_Sign_k = rtb_Add1_j;
      }

      /* End of Signum: '<S74>/Sign' */

      /* Sum: '<S74>/Add' incorporates:
       *  Constant: '<S70>/d'
       *  Product: '<S74>/Divide'
       */
      rtb_Add_gh = rtb_Add1_j / 0.00100000016F - rtb_Sign_k;

      /* Sum: '<S75>/Add' incorporates:
       *  Constant: '<S70>/d'
       */
      rtb_Sign_g = rtb_Add1_j + 0.00100000016F;

      /* Sum: '<S75>/Add1' incorporates:
       *  Constant: '<S70>/d'
       */
      rtb_Add1_j -= 0.00100000016F;

      /* SignalConversion: '<S69>/OutportBufferForGrd' */
      DBG_Struct.traj_plan_grd = pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* SignalConversion: '<S69>/OutportBufferForRef' */
      DBG_Struct.traj_plan_ref = pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

      /* Update for DiscreteIntegrator: '<S69>/Discrete-Time Integrator1' */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE += 0.001F *
        pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* Signum: '<S75>/Sign' */
      if (rtb_Sign_g < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else {
        if (rtb_Sign_g > 0.0F) {
          rtb_Sign_g = 1.0F;
        }
      }

      /* End of Signum: '<S75>/Sign' */

      /* Signum: '<S75>/Sign1' */
      if (rtb_Add1_j < 0.0F) {
        rtb_Add1_j = -1.0F;
      } else {
        if (rtb_Add1_j > 0.0F) {
          rtb_Add1_j = 1.0F;
        }
      }

      /* End of Signum: '<S75>/Sign1' */

      /* Update for DiscreteIntegrator: '<S69>/Discrete-Time Integrator' incorporates:
       *  Gain: '<S74>/Gain'
       *  Gain: '<S75>/Gain'
       *  Product: '<S74>/Product'
       *  Sum: '<S74>/Add1'
       *  Sum: '<S75>/Add2'
       */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE += ((rtb_Sign_g -
        rtb_Add1_j) * 0.5F * rtb_Add_gh + rtb_Sign_k) * -1000.0F * 0.001F;
    } else {
      if (pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* Disable for DiscreteIntegrator: '<S69>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

        /* Disable for DiscreteIntegrator: '<S69>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = false;
      }
    }

    /* End of Outputs for SubSystem: '<S62>/PosTrackDiff' */

    /* Switch: '<S62>/Switch' */
    if (DBG_Struct.traj_plan_is_enbl) {
      rtb_Product_f = DBG_Struct.traj_plan_ref;
    }

    /* End of Switch: '<S62>/Switch' */

    /* DataTypeConversion: '<S66>/Data Type Conversion4' incorporates:
     *  Constant: '<S66>/Constant'
     *  Constant: '<S66>/Constant2'
     *  DataTypeConversion: '<S66>/Data Type Conversion8'
     *  Product: '<S66>/Product'
     */
    DBG_Struct.mtr_cnts_ref = (int32_T)(rtb_Product_f * (real32_T)Cfg_EncCnts /
      6.28318548F);

    /* Outputs for Enabled SubSystem: '<S60>/PosCtl' incorporates:
     *  EnablePort: '<S61>/Enable'
     */
    /* Switch: '<S60>/Switch1' incorporates:
     *  SignalConversion: '<S60>/HiddenBuf_InsertedFor_PosCtl_at_inport_2'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
      if (!pmsm_ctrl_M->dwork.PosCtl_MODE) {
        /* InitializeConditions for DiscreteIntegrator: '<S68>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        pmsm_ctrl_M->dwork.PosCtl_MODE = true;
      }

      /* Switch: '<S60>/Switch2' incorporates:
       *  Constant: '<S60>/Constant3'
       *  DataTypeConversion: '<S60>/Data Type Conversion5'
       */
      if (Cfg_UseObsPosEst) {
        tmp = DBG_Struct.obs_enc_cnts;
      } else {
        tmp = pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
      }

      /* End of Switch: '<S60>/Switch2' */

      /* Sum: '<S67>/Subtract' incorporates:
       *  Constant: '<S65>/Constant'
       *  Constant: '<S65>/Constant1'
       *  DataTypeConversion: '<S65>/Data Type Conversion8'
       *  DataTypeConversion: '<S65>/Data Type Conversion9'
       *  Product: '<S65>/Product'
       */
      rtb_Product_f -= (real32_T)tmp / (real32_T)Cfg_EncCnts * 6.28318548F;

      /* Sum: '<S67>/Add' incorporates:
       *  DiscreteIntegrator: '<S68>/Discrete-Time Integrator'
       *  Gain: '<S67>/Gain1'
       */
      pmsm_ctrl_M->blockIO.Add = PosCtrl_Kp * rtb_Product_f +
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o;

      /* Update for DiscreteIntegrator: '<S68>/Discrete-Time Integrator' incorporates:
       *  Gain: '<S67>/Gain'
       */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o += PosCtrl_Ki *
        rtb_Product_f * 0.001F;
      if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o >= 1000.0F) {
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o = 1000.0F;
      } else {
        if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o <= -1000.0F) {
          pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o = -1000.0F;
        }
      }

      /* End of Update for DiscreteIntegrator: '<S68>/Discrete-Time Integrator' */
      rtb_Sign_g = pmsm_ctrl_M->blockIO.Add;
    } else {
      if (pmsm_ctrl_M->dwork.PosCtl_MODE) {
        pmsm_ctrl_M->dwork.PosCtl_MODE = false;
      }

      rtb_Sign_g = pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0];
    }

    /* End of Switch: '<S60>/Switch1' */
    /* End of Outputs for SubSystem: '<S60>/PosCtl' */

    /* Sum: '<S60>/Add' */
    DBG_Struct.mtr_spd_tgt = DBG_Struct.traj_plan_grd + rtb_Sign_g;

    /* Outputs for Enabled SubSystem: '<S60>/SpdCtrl' incorporates:
     *  EnablePort: '<S63>/Enable'
     */
    /* SignalConversion: '<S60>/HiddenBuf_InsertedFor_SpdCtrl_at_inport_2' incorporates:
     *  Constant: '<S63>/Constant1'
     *  Constant: '<S63>/Constant3'
     *  DataTypeConversion: '<S60>/Data Type Conversion1'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl) {
      if (!pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        /* SystemReset for Atomic SubSystem: '<S63>/PI-Ctrl-Varying-Gains' */
        PI_Ctrl_Reset(&pmsm_ctrl_M->self_PICtrlVaryingGains_m);

        /* End of SystemReset for SubSystem: '<S63>/PI-Ctrl-Varying-Gains' */
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = true;
      }

      /* Outputs for Atomic SubSystem: '<S63>/PI-Ctrl-Varying-Gains' */
      PI_Ctrl(&pmsm_ctrl_M->self_PICtrlVaryingGains_m, DBG_Struct.mtr_spd_tgt,
              pmsm_ctrl_M->blockIO.MtrIf_SpdOut_i, Cfg_SpdCtrlBW * Cfg_MtrJm,
              Cfg_SpdCtrlBW * Cfg_MtrKf, &rtb_Product_f, 10.0F, -10.0F);

      /* End of Outputs for SubSystem: '<S63>/PI-Ctrl-Varying-Gains' */

      /* Saturate: '<S63>/Saturation' incorporates:
       *  Constant: '<S63>/Constant1'
       *  Constant: '<S63>/Constant3'
       *  DataTypeConversion: '<S60>/Data Type Conversion1'
       */
      if (rtb_Product_f > 10.0F) {
        pmsm_ctrl_M->blockIO.Saturation = 10.0F;
      } else if (rtb_Product_f < -10.0F) {
        pmsm_ctrl_M->blockIO.Saturation = -10.0F;
      } else {
        pmsm_ctrl_M->blockIO.Saturation = rtb_Product_f;
      }

      /* End of Saturate: '<S63>/Saturation' */
    } else {
      if (pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = false;
      }
    }

    /* End of SignalConversion: '<S60>/HiddenBuf_InsertedFor_SpdCtrl_at_inport_2' */
    /* End of Outputs for SubSystem: '<S60>/SpdCtrl' */

    /* DataTypeConversion: '<S60>/Data Type Conversion4' */
    DBG_Struct.motn_ctrl_cmd = pmsm_ctrl_M->blockIO.Saturation;
  } else {
    if (pmsm_ctrl_M->dwork.MotnCtrl_MODE) {
      /* Disable for Enabled SubSystem: '<S62>/PosTrackDiff' */
      if (pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* Disable for DiscreteIntegrator: '<S69>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

        /* Disable for DiscreteIntegrator: '<S69>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = false;
      }

      /* End of Disable for SubSystem: '<S62>/PosTrackDiff' */

      /* Disable for Enabled SubSystem: '<S60>/PosCtl' */
      if (pmsm_ctrl_M->dwork.PosCtl_MODE) {
        pmsm_ctrl_M->dwork.PosCtl_MODE = false;
      }

      /* End of Disable for SubSystem: '<S60>/PosCtl' */

      /* Disable for Enabled SubSystem: '<S60>/SpdCtrl' */
      if (pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = false;
      }

      /* End of Disable for SubSystem: '<S60>/SpdCtrl' */
      pmsm_ctrl_M->dwork.MotnCtrl_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S4>/MotnCtrl' */

  /* BusCreator: '<S4>/Bus Creator' */
  pmsm_ctrl_M->blockIO.BusCreator_c.motn_ctrl_cmd = DBG_Struct.motn_ctrl_cmd;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_MotnCtrl_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_GetOut(RT_MODEL *const pmsm_ctrl_M, real32_T rtY_MtrIf_PwmDc[3],
                      real32_T rtY_MtrIf_ModWave[3], real32_T *rtY_MtrIf_TrqAct,
                      real32_T *rtY_MtrIf_SpdAct, real32_T rtY_MtrIf_IfbkDq[2],
                      real32_T rtY_MtrIf_PwmDq[2])
{
  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_GetOut_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CalcOutputs'
   */
  /* Saturate: '<S1>/Saturation' */
  if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[0] > 1.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[0] = 1.0F;
  } else if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[0] < 0.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[0] = 0.0F;
  } else {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[0] = pmsm_ctrl_M->blockIO.MtrIf_PwmDc[0];
  }

  /* Outport: '<Root>/MtrIf_ModWave' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   */
  rtY_MtrIf_ModWave[0] = pmsm_ctrl_M->blockIO.MtrIf_ModWave[0];

  /* Saturate: '<S1>/Saturation' */
  if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[1] > 1.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[1] = 1.0F;
  } else if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[1] < 0.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[1] = 0.0F;
  } else {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[1] = pmsm_ctrl_M->blockIO.MtrIf_PwmDc[1];
  }

  /* Outport: '<Root>/MtrIf_ModWave' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   */
  rtY_MtrIf_ModWave[1] = pmsm_ctrl_M->blockIO.MtrIf_ModWave[1];

  /* Saturate: '<S1>/Saturation' */
  if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[2] > 1.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[2] = 1.0F;
  } else if (pmsm_ctrl_M->blockIO.MtrIf_PwmDc[2] < 0.0F) {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[2] = 0.0F;
  } else {
    /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
     *  DataTypeConversion: '<S1>/Data Type Conversion'
     */
    rtY_MtrIf_PwmDc[2] = pmsm_ctrl_M->blockIO.MtrIf_PwmDc[2];
  }

  /* Outport: '<Root>/MtrIf_ModWave' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion1'
   */
  rtY_MtrIf_ModWave[2] = pmsm_ctrl_M->blockIO.MtrIf_ModWave[2];

  /* Outport: '<Root>/MtrIf_IfbkDq' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion4'
   */
  rtY_MtrIf_IfbkDq[0] = pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[0];

  /* Outport: '<Root>/MtrIf_PwmDq' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion5'
   */
  rtY_MtrIf_PwmDq[0] = pmsm_ctrl_M->blockIO.MtrIf_SpdOut[0];

  /* Outport: '<Root>/MtrIf_IfbkDq' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion4'
   */
  rtY_MtrIf_IfbkDq[1] = pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[1];

  /* Outport: '<Root>/MtrIf_PwmDq' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion5'
   */
  rtY_MtrIf_PwmDq[1] = pmsm_ctrl_M->blockIO.MtrIf_SpdOut[1];

  /* Outport: '<Root>/MtrIf_TrqAct' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion2'
   */
  *rtY_MtrIf_TrqAct = pmsm_ctrl_M->blockIO.MtrIf_TrqAct;

  /* Outport: '<Root>/MtrIf_SpdAct' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion3'
   */
  *rtY_MtrIf_SpdAct = pmsm_ctrl_M->blockIO.MtrIf_SpdOut_i;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_GetOut_at_outport_1' */
}

/* Model initialize function */
void Trig_Pmsm_Init(RT_MODEL *const pmsm_ctrl_M)
{
  /* Registration code */
  {
    /* Storage classes */
    {
      ((B *) &(pmsm_ctrl_M->blockIO))->Merge = pmsm_ctrl_rtZCalib_OutType;
      ((B *) &(pmsm_ctrl_M->blockIO))->CalMgrStRqst = ST_FAILED;
      ((B *) &(pmsm_ctrl_M->blockIO))->CalMgrStRqst_i = ST_FAILED;
      ((B *) &(pmsm_ctrl_M->blockIO))->CalMgrStRqst_h = ST_FAILED;
    }
  }

  /* Start for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CalibRoutines'
   */
  /* Start for SwitchCase: '<S2>/Switch Case' */
  pmsm_ctrl_M->dwork.SwitchCase_ActiveSubsystem = -1;

  /* Start for DataStoreMemory: '<S2>/Data Store Memory1' incorporates:
   *  DataStoreMemory: '<S2>/Data Store Memory3'
   */
  if (!_pmsm_ctrl_SharedDataInit_) {
    rtSharedDSM.CalData_L = -1.0F;
    rtSharedDSM.CalData_Res = -1.0F;
  }

  /* End of Start for DataStoreMemory: '<S2>/Data Store Memory1' */
  /* End of Start for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' */

  /* SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CalibRoutines'
   */
  /* SystemInitialize for IfAction SubSystem: '<S2>/mtr_res_ident' */
  /* SystemInitialize for Chart: '<S12>/ResIdCal' */
  pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
  pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_FAILED;

  /* End of SystemInitialize for SubSystem: '<S2>/mtr_res_ident' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/mtr_ind_ident' */
  /* SystemInitialize for Chart: '<S11>/IndIdCal' */
  pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_OFF;
  pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_FAILED;

  /* End of SystemInitialize for SubSystem: '<S2>/mtr_ind_ident' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/enc_ofs_cal_routine' */
  /* SystemInitialize for Chart: '<S9>/EncOfsCal' */
  pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
  pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_FAILED;

  /* End of SystemInitialize for SubSystem: '<S2>/enc_ofs_cal_routine' */

  /* SystemInitialize for Merge: '<S2>/Merge' */
  pmsm_ctrl_M->blockIO.Merge = pmsm_ctrl_rtZCalib_OutType;

  /* End of SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' */

  /* SystemInitialize for DataStoreMemory: '<Root>/_pmsm_ctrl_SharedDataInit_' */
  if (!_pmsm_ctrl_SharedDataInit_) {
    _pmsm_ctrl_SharedDataInit_ = true;
  }

  /* End of SystemInitialize for DataStoreMemory: '<Root>/_pmsm_ctrl_SharedDataInit_' */
}
