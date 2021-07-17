/*
 * pmsm_ctrl.c
 *
 * Code generation for model "pmsm_ctrl".
 *
 * Model version              : 1.676
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
#define PWM_R_CAL_DUTY                 (0.2F)
#define TICK_R_CAL                     (100U)
#define TICK_WAIT_SETTLE               (30U)

/* Named constants for Chart: '<S11>/IndIdCal' */
#define IN_ind_id_actv                 ((uint8_T)2U)
#define IN_neg_cycle                   ((uint8_T)1U)
#define IN_pos_cycle                   ((uint8_T)2U)
#define PWM_L_CAL_DUTY                 (0.2F)
#define TICK_L_CAL                     (1000U)

/* Named constants for Chart: '<S10>/ResIdCal' */
#define IN_mtr_angl_ofs_cal_actv       ((uint8_T)1U)
#define IN_mtr_angl_ofs_cal_done       ((uint8_T)2U)
#define TICK_WAIT_SETTLE_d             (500U)

/* Named constants for Chart: '<S9>/EncOfsCal' */
#define IN_calc_enc_ofs_move_forward   ((uint8_T)1U)
#define IN_calc_n_poles                ((uint8_T)2U)
#define IN_done_m                      ((uint8_T)3U)
#define IN_enc_cnts_err                ((uint8_T)4U)
#define IN_move_back_calc_enc_ofs      ((uint8_T)5U)
#define IN_mtr_n_poles_enc_ofs_init    ((uint8_T)6U)
#define TICKS_TGT                      (19200)
#define WAIT_SETTLE_TICKS              (100U)

const Calib_OutType pmsm_ctrl_rtZCalib_OutType = {
  CTRL_MD_OFF,                         /* ctrl_md_rqst */
  ST_FAILED,                           /* cal_mgr_st_rqst */

  {
    0.0F, 0.0F, 0.0F }
  /* mtr_cmd_rqst */
} ;                                    /* Calib_OutType ground */

/* Exported block signals */
real32_T DBG_e_angl;                   /* '<S30>/calc_elec_angle' */
real32_T DBG_i_abc_lpf[3];             /* '<S40>/Add1' */
real32_T DBG_i_dq0[3];                 /* '<S42>/Gain1' */

/* Exported block states */
real32_T CalData_L;                    /* '<S2>/Data Store Memory1' */
real32_T CalData_Res;                  /* '<S2>/Data Store Memory3' */
real32_T CalData_IfbkOfs_Abc[3];       /* '<S2>/Data Store Memory4' */
int32_T CalData_EncOfs;                /* '<S2>/Data Store Memory' */
int32_T CalData_nPoles;                /* '<S2>/Data Store Memory2' */
boolean_T _pmsm_ctrl_SharedDataInit_ = false;/* synthesized block */
real32_T sMultiWord2Single(const uint32_T u1[], int32_T n1, int32_T e1)
{
  real32_T y;
  int32_T i;
  int32_T exp_0;
  uint32_T u1i;
  uint32_T cb;
  y = 0.0F;
  exp_0 = e1;
  if ((u1[n1 - 1] & 2147483648U) != 0U) {
    cb = 1U;
    for (i = 0; i < n1; i++) {
      u1i = ~u1[i];
      cb += u1i;
      y -= (real32_T)ldexp((real32_T)cb, exp_0);
      cb = (uint32_T)(cb < u1i);
      exp_0 += 32;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += (real32_T)ldexp((real32_T)u1[i], exp_0);
      exp_0 += 32;
    }
  }

  return y;
}

void sMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[], int32_T
                   n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;
  int32_T nj;
  uint32_T u1i;
  uint32_T yk;
  uint32_T a1;
  uint32_T a0;
  uint32_T b1;
  uint32_T w10;
  uint32_T w01;
  uint32_T cb;
  boolean_T isNegative1;
  boolean_T isNegative2;
  uint32_T cb1;
  uint32_T cb2;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  isNegative2 = ((u2[n2 - 1] & 2147483648U) != 0U);
  cb1 = 1U;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint32_T)(u1i < cb1);
    }

    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    cb2 = 1U;
    k = n - i;
    nj = n2 <= k ? n2 : k;
    k = i;
    for (j = 0; j < nj; j++) {
      yk = y[k];
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint32_T)(u1i < cb2);
      }

      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk += cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1U;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint32_T)(yk < cb);
    }
  }
}

int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/*
 * Output and update for atomic system:
 *    '<S28>/calc_pwm_dc'
 *    '<S25>/calc_pwm_dc'
 *    '<S17>/calc_pwm_dc'
 *    '<S50>/calc_pwm_dc'
 */
void calc_pwm_dc(RT_MODEL * const pmsm_ctrl_M, const real32_T rtu_pwm_abc[3],
                 real32_T rty_pwm_dc[3])
{
  real32_T rtb_Gain_ps;
  real32_T rtb_Subtract_g_idx_0;
  real32_T rtb_Subtract_g_idx_1;
  (void) (pmsm_ctrl_M);

  /* MinMax: '<S29>/Max' */
  rtb_Gain_ps = rtu_pwm_abc[0];
  rtb_Subtract_g_idx_0 = rtu_pwm_abc[1];
  if (!(rtb_Gain_ps > rtb_Subtract_g_idx_0)) {
    rtb_Gain_ps = rtb_Subtract_g_idx_0;
  }

  rtb_Subtract_g_idx_0 = rtu_pwm_abc[2];
  if (!(rtb_Gain_ps > rtb_Subtract_g_idx_0)) {
    rtb_Gain_ps = rtb_Subtract_g_idx_0;
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
  rtb_Gain_ps = (rtb_Gain_ps + rtb_Subtract_g_idx_1) * 0.5F;

  /* Sum: '<S29>/Subtract' */
  rtb_Subtract_g_idx_0 = rtu_pwm_abc[0] - rtb_Gain_ps;
  rtb_Subtract_g_idx_1 = rtu_pwm_abc[1] - rtb_Gain_ps;
  rtb_Gain_ps = rtu_pwm_abc[2] - rtb_Gain_ps;

  /* DataTypeConversion: '<S29>/Data Type Conversion' incorporates:
   *  Constant: '<S29>/Constant'
   *  Constant: '<S29>/Constant1'
   *  Gain: '<S29>/Gain1'
   *  Gain: '<S29>/Gain2'
   *  Product: '<S29>/Divide'
   *  Sum: '<S29>/Add1'
   */
  rty_pwm_dc[0] = (rtb_Subtract_g_idx_0 / 0.5F * 1.15470052F + 1.0F) * 0.5F;
  rty_pwm_dc[1] = (rtb_Subtract_g_idx_1 / 0.5F * 1.15470052F + 1.0F) * 0.5F;
  rty_pwm_dc[2] = (rtb_Gain_ps / 0.5F * 1.15470052F + 1.0F) * 0.5F;
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
                     rtp_enc_cnts_int, int32_T rtp_n_poles)
{
  real32_T rtb_Divide_b;
  int32_T u0;
  (void) (pmsm_ctrl_M);

  /* Product: '<S33>/Divide' incorporates:
   *  Constant: '<S33>/Constant2'
   *  Constant: '<S33>/Constant3'
   *  DataTypeConversion: '<S33>/Data Type Conversion'
   */
  rtb_Divide_b = 6.28318548F / (real32_T)rtp_enc_cnts_int;

  /* Gain: '<S33>/Gain' */
  u0 = rtp_n_poles * rtu_mtr_enc_cnts;

  /* Math: '<S33>/Mod' incorporates:
   *  Constant: '<S33>/Constant1'
   */
  if (rtp_enc_cnts_int != 0) {
    u0 -= div_nde_s32_floor(u0, rtp_enc_cnts_int) * rtp_enc_cnts_int;
  }

  /* End of Math: '<S33>/Mod' */

  /* Product: '<S33>/Divide1' incorporates:
   *  DataTypeConversion: '<S33>/Data Type Conversion2'
   */
  *rty_elec_angle = (real32_T)u0 * rtb_Divide_b;

  /* Product: '<S33>/Divide2' incorporates:
   *  DataTypeConversion: '<S33>/Data Type Conversion1'
   */
  *rty_mtr_pos = (real32_T)rtu_mtr_enc_cnts * rtb_Divide_b;
}

/* Model step function */
void Trig_Pmsm_SetIn(RT_MODEL *const pmsm_ctrl_M, int32_T rtU_MtrIf_EncCnts,
                     real32_T rtU_MtrIf_IfbkAct[3], real32_T rtU_MtrIf_SpdSns,
                     MtrCtrlMd_T rtU_MtrIf_CtrlMd, real32_T rtU_MtrIf_Tgt[3],
                     MtrCtrlCal_T rtU_MtrIf_CtrlCalRqst)
{
  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_SetIn_at_outport_1' incorporates:
   *  SubSystem: '<Root>/SetInputs'
   */
  /* Sum: '<S79>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_EncCnts'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts = rtU_MtrIf_EncCnts -
    pmsm_ctrl_M->blockIO.BusCreator_e.enc_ofs;

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_CtrlMd'
   *  Inport: '<Root>/MtrIf_SpdSns'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_spd_sns = rtU_MtrIf_SpdSns;
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ctrl_md = rtU_MtrIf_CtrlMd;

  /* Sum: '<S80>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0] = rtU_MtrIf_IfbkAct[0] -
    pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[0];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[0] = rtU_MtrIf_Tgt[0];

  /* Sum: '<S80>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1] = rtU_MtrIf_IfbkAct[1] -
    pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[1];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[1] = rtU_MtrIf_Tgt[1];

  /* Sum: '<S80>/Subtract' incorporates:
   *  Inport: '<Root>/MtrIf_IfbkAct'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2] = rtU_MtrIf_IfbkAct[2] -
    pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[2];

  /* BusCreator: '<S6>/Bus Creator' incorporates:
   *  Inport: '<Root>/MtrIf_CtrlCalRqst'
   *  Inport: '<Root>/MtrIf_Tgt'
   */
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_tgt[2] = rtU_MtrIf_Tgt[2];
  pmsm_ctrl_M->blockIO.BusCreator.mtrif_cal_rqst = rtU_MtrIf_CtrlCalRqst;

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
   *  Constant: '<S70>/Constant'
   *  Constant: '<S71>/Constant'
   *  RelationalOperator: '<S70>/Compare'
   *  RelationalOperator: '<S71>/Compare'
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

  /* RelationalOperator: '<S75>/Compare' incorporates:
   *  Constant: '<S75>/Constant'
   */
  rtb_Compare_p = (rtb_ctrl_md_act == CTRL_MD_OFF);

  /* Logic: '<S72>/Logical Operator2' */
  rtb_LogicalOperator2 = !rtb_Compare_p;

  /* Logic: '<S72>/Logical Operator1' incorporates:
   *  Constant: '<S74>/Constant'
   *  RelationalOperator: '<S74>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_raw_pwm =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act == CTRL_MD_RAW_PWM));

  /* Logic: '<S72>/Logical Operator3' incorporates:
   *  Constant: '<S76>/Constant'
   *  RelationalOperator: '<S76>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_mod_wave =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_DQ_PWM));

  /* Logic: '<S72>/Logical Operator4' incorporates:
   *  Constant: '<S73>/Constant'
   *  RelationalOperator: '<S73>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_IFBK));

  /* Logic: '<S72>/Logical Operator5' incorporates:
   *  Constant: '<S77>/Constant'
   *  RelationalOperator: '<S77>/Compare'
   */
  pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl =
    (rtb_LogicalOperator2 && (rtb_ctrl_md_act >= CTRL_MD_SPD));

  /* Logic: '<S72>/Logical Operator6' incorporates:
   *  Constant: '<S78>/Constant'
   *  RelationalOperator: '<S78>/Compare'
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
void Trig_Pmsm_Cal(RT_MODEL *const pmsm_ctrl_M, boolean_T *rtY_cal_actv)
{
  int8_T rtPrevAction;
  int8_T rtAction;
  real32_T rtb_TmpSignalConversionAtcalc_i[3];
  real32_T rtb_PwmRqst_l;
  int32_T qY;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CalibRoutines'
   */
  /* SwitchCase: '<S2>/Switch Case' */
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
      pmsm_ctrl_M->blockIO.PwmRqst_g = PWM_R_CAL_DUTY;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_RES_ID;
      pmsm_ctrl_M->dwork.ifbk_sum = 0.0F;
      CalData_Res = -1.0F;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl) {
       case IN_done:
        pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_DONE;
        pmsm_ctrl_M->blockIO.PwmRqst_g = (real32_T)0.;
        CalData_Res = (real32_T)(0.800000011920929 /
          (pmsm_ctrl_M->dwork.ifbk_sum / (real32_T)TICK_R_CAL));
        break;

       case IN_res_id_actv:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_l >= (int32_T)TICK_R_CAL) {
          pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_done;
          pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_DONE;
          pmsm_ctrl_M->blockIO.PwmRqst_g = (real32_T)0.;
          CalData_Res = (real32_T)(0.800000011920929 /
            (pmsm_ctrl_M->dwork.ifbk_sum / (real32_T)TICK_R_CAL));
        } else {
          pmsm_ctrl_M->dwork.ifbk_sum +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        }
        break;

       default:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_l >= (int32_T)TICK_WAIT_SETTLE)
        {
          /*  Wait for current / motor to settle. */
          pmsm_ctrl_M->dwork.is_c5_pmsm_ctrl = IN_res_id_actv;
          pmsm_ctrl_M->dwork.temporalCounter_i1_l = 0U;
          pmsm_ctrl_M->dwork.ifbk_sum +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst_p = CTRL_MD_RAW_PWM;
          pmsm_ctrl_M->blockIO.PwmRqst_g = PWM_R_CAL_DUTY;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_h = ST_RES_ID;
          pmsm_ctrl_M->dwork.ifbk_sum = 0.0F;
          CalData_Res = -1.0F;
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

    /* BusCreator: '<S12>/Bus Creator' */
    calc_pwm_dc(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i,
                pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst);

    /* End of Outputs for SubSystem: '<S28>/calc_pwm_dc' */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst_p;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst_h;

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
      rtb_TmpSignalConversionAtcalc_i[0] = PWM_L_CAL_DUTY;
      pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_IND_ID;
      CalData_L = -1.0F;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl) {
       case IN_done:
        pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_DONE;

        /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
        rtb_TmpSignalConversionAtcalc_i[0] = (real32_T)0.;
        pmsm_ctrl_M->dwork.di_dt = (real32_T)((pmsm_ctrl_M->dwork.ifbk_pos -
          pmsm_ctrl_M->dwork.ifbk_neg) / 500.0 / 0.0010000000474974513);
        CalData_L = (real32_T)(1.2000000178813934 / pmsm_ctrl_M->dwork.di_dt);
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
            pmsm_ctrl_M->dwork.ifbk_neg) / 500.0 / 0.0010000000474974513);
          CalData_L = (real32_T)(1.2000000178813934 / pmsm_ctrl_M->dwork.di_dt);
        } else if (pmsm_ctrl_M->dwork.is_ind_id_actv == IN_neg_cycle) {
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_pos_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = PWM_L_CAL_DUTY;
          pmsm_ctrl_M->dwork.ifbk_neg +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_neg_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = -0.2F;
          pmsm_ctrl_M->dwork.ifbk_pos +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        }
        break;

       default:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_n >= (int32_T)TICK_WAIT_SETTLE)
        {
          /*  Wait for current / motor to settle. */
          pmsm_ctrl_M->dwork.is_c1_pmsm_ctrl = IN_ind_id_actv;
          pmsm_ctrl_M->dwork.temporalCounter_i1_n = 0U;
          pmsm_ctrl_M->dwork.ifbk_pos = 0.0F;
          pmsm_ctrl_M->dwork.ifbk_neg = 0.0F;
          pmsm_ctrl_M->dwork.is_ind_id_actv = IN_pos_cycle;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = PWM_L_CAL_DUTY;
          pmsm_ctrl_M->dwork.ifbk_neg +=
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0];
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst_i = CTRL_MD_RAW_PWM;

          /* SignalConversion: '<S25>/TmpSignal ConversionAtcalc_pwm_dcInport1' */
          rtb_TmpSignalConversionAtcalc_i[0] = PWM_L_CAL_DUTY;
          pmsm_ctrl_M->blockIO.CalMgrStRqst_i = ST_IND_ID;
          CalData_L = -1.0F;
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

    /* BusCreator: '<S11>/Bus Creator' */
    calc_pwm_dc(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i,
                pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst);

    /* End of Outputs for SubSystem: '<S25>/calc_pwm_dc' */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst_i;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst_i;

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

      /* BusCreator: '<S10>/Bus Creator' */
      pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = CTRL_MD_RAW_PWM;
      pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = ST_IFBK_OFS_CAL;
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
      CalData_IfbkOfs_Abc[0] = (real32_T)0.;
      CalData_IfbkOfs_Abc[1] = (real32_T)0.;
      CalData_IfbkOfs_Abc[2] = (real32_T)0.;
    } else if (pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl == IN_mtr_angl_ofs_cal_actv) {
      if (pmsm_ctrl_M->dwork.temporalCounter_i1 >= (int32_T)TICK_WAIT_SETTLE_d)
      {
        /*  Wait for motor to settle. */
        pmsm_ctrl_M->dwork.is_c2_pmsm_ctrl = IN_mtr_angl_ofs_cal_done;

        /* BusCreator: '<S10>/Bus Creator' */
        pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = ST_DONE;
        rtb_TmpSignalConversionAtcalc_i[0] = pmsm_ctrl_M->dwork.ifbk_abc_sum[0];
        rtb_TmpSignalConversionAtcalc_i[1] = pmsm_ctrl_M->dwork.ifbk_abc_sum[1];
        rtb_TmpSignalConversionAtcalc_i[2] = pmsm_ctrl_M->dwork.ifbk_abc_sum[2];

        /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_avg' */
        get_mtr_ifbk_avg(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, (real32_T)
                         TICK_WAIT_SETTLE_d, CalData_IfbkOfs_Abc);

        /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_avg' */
      } else {
        /* BusCreator: '<S10>/Bus Creator' */
        pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = CTRL_MD_RAW_PWM;
        pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = ST_IFBK_OFS_CAL;
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
        CalData_IfbkOfs_Abc[0] = (real32_T)0.;
        CalData_IfbkOfs_Abc[1] = (real32_T)0.;
        CalData_IfbkOfs_Abc[2] = (real32_T)0.;
      }
    } else {
      /* BusCreator: '<S10>/Bus Creator' */
      pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = CTRL_MD_OFF;
      pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst = ST_DONE;
      rtb_TmpSignalConversionAtcalc_i[0] = pmsm_ctrl_M->dwork.ifbk_abc_sum[0];
      rtb_TmpSignalConversionAtcalc_i[1] = pmsm_ctrl_M->dwork.ifbk_abc_sum[1];
      rtb_TmpSignalConversionAtcalc_i[2] = pmsm_ctrl_M->dwork.ifbk_abc_sum[2];

      /* Outputs for Function Call SubSystem: '<S20>/get_mtr_ifbk_avg' */
      get_mtr_ifbk_avg(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, (real32_T)
                       TICK_WAIT_SETTLE_d, CalData_IfbkOfs_Abc);

      /* End of Outputs for SubSystem: '<S20>/get_mtr_ifbk_avg' */
    }

    /* End of Chart: '<S10>/ResIdCal' */

    /* BusCreator: '<S10>/Bus Creator' incorporates:
     *  Constant: '<S21>/Zero'
     *  SignalConversion: '<S10>/TmpSignal ConversionAtBus CreatorInport3'
     */
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
      pmsm_ctrl_M->dwork.temporalCounter_i1_b = 0U;
      pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl = 0U;
      pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_NO_ACTIVE_CHILD;
      pmsm_ctrl_M->dwork.ticks_inc = 0;
      pmsm_ctrl_M->dwork.ticks_start = 0;
      pmsm_ctrl_M->dwork.ticks_end = 0;
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
    if (pmsm_ctrl_M->dwork.temporalCounter_i1_b < 127U) {
      pmsm_ctrl_M->dwork.temporalCounter_i1_b++;
    }

    if (pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl == 0U) {
      pmsm_ctrl_M->dwork.is_active_c3_pmsm_ctrl = 1U;
      pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_mtr_n_poles_enc_ofs_init;
      pmsm_ctrl_M->dwork.temporalCounter_i1_b = 0U;
      pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_RAW_PWM;
      pmsm_ctrl_M->blockIO.PwmRqst = 0.2F;
      pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_ENC_OFS;
      CalData_nPoles = -1;
      pmsm_ctrl_M->blockIO.Ticks = 0;
      pmsm_ctrl_M->dwork.ticks_inc = 38;
      CalData_EncOfs = pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
      pmsm_ctrl_M->dwork.ticks_start = 0;
      pmsm_ctrl_M->dwork.ticks_end = 0;
    } else {
      switch (pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl) {
       case IN_calc_enc_ofs_move_forward:
        if ((pmsm_ctrl_M->blockIO.Ticks >= TICKS_TGT) &&
            (pmsm_ctrl_M->dwork.ticks_end != pmsm_ctrl_M->dwork.ticks_start)) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_calc_n_poles;
          pmsm_ctrl_M->dwork.temporalCounter_i1_b = 0U;
          pmsm_ctrl_M->dwork.ticks_end =
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
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

          CalData_nPoles = (pmsm_ctrl_M->blockIO.Ticks == MIN_int32_T) && (qY ==
            -1) ? MAX_int32_T : pmsm_ctrl_M->blockIO.Ticks / qY;
        } else if ((pmsm_ctrl_M->blockIO.Ticks >= TICKS_TGT) &&
                   (pmsm_ctrl_M->dwork.ticks_end ==
                    pmsm_ctrl_M->dwork.ticks_start)) {
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_enc_cnts_err;

          /*  When state machine goes into this state, it means that no encoder movement
             was detected; either because the encoder is not connected, motor has no
             power or something else. So calibration is finished here.
             TODO: Signal & handle error. */
          pmsm_ctrl_M->dwork.ticks_end = 0;
          CalData_nPoles = -1;
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_DONE;
          CalData_EncOfs = -2400;
        } else if ((pmsm_ctrl_M->blockIO.Ticks < 0) &&
                   (pmsm_ctrl_M->dwork.ticks_inc < MIN_int32_T
                    - pmsm_ctrl_M->blockIO.Ticks)) {
          pmsm_ctrl_M->blockIO.Ticks = MIN_int32_T;
        } else if ((pmsm_ctrl_M->blockIO.Ticks > 0) &&
                   (pmsm_ctrl_M->dwork.ticks_inc > MAX_int32_T
                    - pmsm_ctrl_M->blockIO.Ticks)) {
          pmsm_ctrl_M->blockIO.Ticks = MAX_int32_T;
        } else {
          pmsm_ctrl_M->blockIO.Ticks += pmsm_ctrl_M->dwork.ticks_inc;
        }
        break;

       case IN_calc_n_poles:
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_b >= 1) {
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

          CalData_nPoles = (pmsm_ctrl_M->blockIO.Ticks == MIN_int32_T) && (qY ==
            -1) ? MAX_int32_T : pmsm_ctrl_M->blockIO.Ticks / qY;
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
        CalData_nPoles = -1;
        pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_OFF;
        pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_DONE;
        CalData_EncOfs = -2400;
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
        if (pmsm_ctrl_M->dwork.temporalCounter_i1_b >= (int32_T)
            WAIT_SETTLE_TICKS) {
          /*  Wait for motor / current to settle. */
          pmsm_ctrl_M->dwork.is_c3_pmsm_ctrl = IN_calc_enc_ofs_move_forward;
          pmsm_ctrl_M->dwork.ticks_start =
            pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
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
        } else {
          pmsm_ctrl_M->blockIO.CtrlMdRqst = CTRL_MD_RAW_PWM;
          pmsm_ctrl_M->blockIO.PwmRqst = 0.2F;
          pmsm_ctrl_M->blockIO.CalMgrStRqst = ST_ENC_OFS;
          CalData_nPoles = -1;
          pmsm_ctrl_M->blockIO.Ticks = 0;
          pmsm_ctrl_M->dwork.ticks_inc = 38;
          CalData_EncOfs = pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
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

    /* BusCreator: '<S9>/Bus Creator' incorporates:
     *  DataTypeConversion: '<S9>/Data Type Conversion'
     *  Gain: '<S9>/Gain'
     */
    calc_mod_wave(pmsm_ctrl_M, rtb_TmpSignalConversionAtcalc_i, 0.00261799386F *
                  (real32_T)pmsm_ctrl_M->blockIO.Ticks,
                  pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst,
                  pmsm_ctrl_M->blockIO.Merge.mtr_cmd_rqst);

    /* End of Outputs for SubSystem: '<S9>/calc_mod_wave' */
    pmsm_ctrl_M->blockIO.Merge.ctrl_md_rqst = pmsm_ctrl_M->blockIO.CtrlMdRqst;
    pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst =
      pmsm_ctrl_M->blockIO.CalMgrStRqst;

    /* Update for UnitDelay: '<S14>/Unit Delay' */
    pmsm_ctrl_M->dwork.UnitDelay_DSTATE_j = rtb_PwmRqst_l;

    /* End of Outputs for SubSystem: '<S2>/enc_ofs_cal_routine' */
    break;
  }

  /* End of SwitchCase: '<S2>/Switch Case' */

  /* DataStoreRead: '<S2>/Data Store Read4' */
  pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[0] = CalData_IfbkOfs_Abc[0];
  pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[1] = CalData_IfbkOfs_Abc[1];
  pmsm_ctrl_M->blockIO.BusCreator_e.ifbk_ofs[2] = CalData_IfbkOfs_Abc[2];

  /* DataStoreRead: '<S2>/Data Store Read' */
  pmsm_ctrl_M->blockIO.BusCreator_e.enc_ofs = CalData_EncOfs;

  /* DataStoreRead: '<S2>/Data Store Read1' */
  pmsm_ctrl_M->blockIO.BusCreator_e.ind = CalData_L;

  /* DataStoreRead: '<S2>/Data Store Read2' */
  pmsm_ctrl_M->blockIO.BusCreator_e.ppoles = CalData_nPoles;

  /* DataStoreRead: '<S2>/Data Store Read3' */
  pmsm_ctrl_M->blockIO.BusCreator_e.res = CalData_Res;

  /* Outport: '<Root>/cal_actv' incorporates:
   *  Constant: '<S7>/Constant'
   *  Constant: '<S8>/Constant'
   *  Logic: '<S2>/Logical Operator'
   *  RelationalOperator: '<S7>/Compare'
   *  RelationalOperator: '<S8>/Compare'
   */
  *rtY_cal_actv = ((pmsm_ctrl_M->blockIO.Merge.cal_mgr_st_rqst != ST_DONE) &&
                   (pmsm_ctrl_M->blockIO.ctrl_cal_act != CAL_NONE));

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Cal_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_Foc(RT_MODEL *const pmsm_ctrl_M)
{
  real32_T rtb_error;
  real32_T rtb_Divide2;
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
                  &DBG_e_angl, &rtb_Divide2, 2400, 4);

  /* End of Outputs for SubSystem: '<S30>/calc_elec_angle' */

  /* MultiPortSwitch: '<S34>/Multiport Switch' incorporates:
   *  Constant: '<S34>/Constant2'
   *  Constant: '<S34>/Constant3'
   */
  switch (pmsm_ctrl_M->blockIO.BusCreator2.ctrl_md_act) {
   case CTRL_MD_TRQ:
    rtb_error = 28.5714283F;
    break;

   case CTRL_MD_IFBK:
    rtb_error = 1.0F;
    break;

   default:
    rtb_error = 1.0F;
    break;
  }

  /* End of MultiPortSwitch: '<S34>/Multiport Switch' */

  /* Product: '<S34>/Product' */
  rtb_error *= rtb_Switch_d_idx_0;

  /* Sum: '<S40>/Add1' incorporates:
   *  Constant: '<S40>/Constant'
   *  Product: '<S40>/Product'
   *  Product: '<S40>/Product1'
   *  UnitDelay: '<S40>/Unit Delay'
   */
  DBG_i_abc_lpf[0] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[0] * 0.25F +
    0.75F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE[0];
  DBG_i_abc_lpf[1] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[1] * 0.25F +
    0.75F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE[1];
  DBG_i_abc_lpf[2] = pmsm_ctrl_M->blockIO.BusCreator.mtrif_ifbk_act[2] * 0.25F +
    0.75F * pmsm_ctrl_M->dwork.UnitDelay_DSTATE[2];

  /* Gain: '<S42>/Gain1' incorporates:
   *  Fcn: '<S42>/0'
   *  Fcn: '<S42>/d'
   *  Fcn: '<S42>/q'
   */
  DBG_i_dq0[0] = ((arm_sin_f32((DBG_e_angl + 1.57079637F) - 2.09439516F) *
                   DBG_i_abc_lpf[1] + arm_sin_f32(DBG_e_angl + 1.57079637F) *
                   DBG_i_abc_lpf[0]) + arm_sin_f32((DBG_e_angl + 1.57079637F) +
    2.09439516F) * DBG_i_abc_lpf[2]) * 0.666666687F;
  DBG_i_dq0[1] = ((arm_cos_f32((DBG_e_angl + 1.57079637F) - 2.09439516F) *
                   DBG_i_abc_lpf[1] + arm_cos_f32(DBG_e_angl + 1.57079637F) *
                   DBG_i_abc_lpf[0]) + arm_cos_f32((DBG_e_angl + 1.57079637F) +
    2.09439516F) * DBG_i_abc_lpf[2]) * 0.666666687F;
  DBG_i_dq0[2] = ((DBG_i_abc_lpf[0] + DBG_i_abc_lpf[1]) + DBG_i_abc_lpf[2]) *
    0.5F * 0.666666687F;

  /* Outputs for Enabled SubSystem: '<S34>/IfbkCtrl' incorporates:
   *  EnablePort: '<S41>/Enable'
   */
  /* SignalConversion: '<S34>/HiddenBuf_InsertedFor_IfbkCtrl_at_inport_5' */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
    if (!pmsm_ctrl_M->dwork.IfbkCtrl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S49>/Discrete-Time Integrator' */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = 0.0F;

      /* InitializeConditions for DiscreteIntegrator: '<S47>/Discrete-Time Integrator' */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = 0.0F;
      pmsm_ctrl_M->dwork.IfbkCtrl_MODE = true;
    }

    /* Sum: '<S48>/Subtract' incorporates:
     *  Gain: '<S34>/Gain1'
     */
    rtb_error = 28.5714283F * rtb_error - DBG_i_dq0[1];

    /* Outputs for Enabled SubSystem: '<S41>/mtr_coupling_bemf_comp' incorporates:
     *  EnablePort: '<S45>/Enable'
     */
    /* SignalConversion: '<S41>/OutportBufferForvdq0_ctrl' incorporates:
     *  Constant: '<S34>/Constant'
     *  Constant: '<S41>/Constant2'
     *  Constant: '<S43>/Constant'
     *  Constant: '<S44>/Constant'
     *  DiscreteIntegrator: '<S38>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S47>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S49>/Discrete-Time Integrator'
     *  Gain: '<S45>/Gain'
     *  Gain: '<S45>/Gain1'
     *  Gain: '<S45>/Gain2'
     *  Gain: '<S45>/Gain3'
     *  Product: '<S45>/Product'
     *  Product: '<S45>/Product1'
     *  Product: '<S46>/Product'
     *  Product: '<S48>/Product'
     *  Sum: '<S41>/Add'
     *  Sum: '<S41>/Add1'
     *  Sum: '<S45>/Add1'
     *  Sum: '<S46>/Add'
     *  Sum: '<S46>/Subtract'
     *  Sum: '<S48>/Add'
     */
    pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[0] = ((0.0F - DBG_i_dq0[0]) *
      2.6F + pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy) +
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k * DBG_i_dq0[1] *
      -0.0052F;
    pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[1] = (DBG_i_dq0[0] *
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k * 4.0F + 17.9487171F *
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k) * 0.0013F + (2.6F *
      rtb_error + pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n);

    /* End of Outputs for SubSystem: '<S41>/mtr_coupling_bemf_comp' */
    pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[2] = 0.0F;

    /* Update for DiscreteIntegrator: '<S49>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S44>/Constant1'
     *  Product: '<S48>/Product1'
     */
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n += rtb_error * 1800.0F *
      3.33333337E-5F;
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n >= 12.0F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = 12.0F;
    } else {
      if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n <= -12.0F) {
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = -12.0F;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S49>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S47>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S34>/Constant'
     *  Constant: '<S43>/Constant1'
     *  Product: '<S46>/Product1'
     *  Sum: '<S46>/Subtract'
     */
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy += (0.0F - DBG_i_dq0[0]) *
      1800.0F * 3.33333337E-5F;
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy >= 12.0F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = 12.0F;
    } else {
      if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy <= -12.0F) {
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = -12.0F;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S47>/Discrete-Time Integrator' */
  } else {
    if (pmsm_ctrl_M->dwork.IfbkCtrl_MODE) {
      pmsm_ctrl_M->dwork.IfbkCtrl_MODE = false;
    }
  }

  /* End of SignalConversion: '<S34>/HiddenBuf_InsertedFor_IfbkCtrl_at_inport_5' */
  /* End of Outputs for SubSystem: '<S34>/IfbkCtrl' */

  /* Outputs for Enabled SubSystem: '<S30>/mod_wave_calc' incorporates:
   *  EnablePort: '<S35>/Enable'
   */
  /* SignalConversion: '<S30>/HiddenBuf_InsertedFor_mod_wave_calc_at_inport_4' */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_mod_wave) {
    /* Switch: '<S35>/Switch' incorporates:
     *  Gain: '<S34>/Gain5'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_ifbk_ctrl) {
      rtb_Switch_d_idx_0 = 0.0416666679F *
        pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[0];
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
      rtb_Switch_d_idx_0 = 0.0416666679F *
        pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[1];
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
      rtb_Switch_d_idx_0 = 0.0416666679F *
        pmsm_ctrl_M->blockIO.OutportBufferForvdq0_ctrl[2];
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
    calc_mod_wave(pmsm_ctrl_M, pmsm_ctrl_M->blockIO.Saturation1, DBG_e_angl,
                  pmsm_ctrl_M->blockIO.DataTypeConversion,
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
  pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[0] = DBG_i_dq0[0];

  /* DataTypeConversion: '<S30>/Data Type Conversion7' */
  pmsm_ctrl_M->blockIO.MtrIf_SpdOut[1] = pmsm_ctrl_M->blockIO.Saturation1[1];

  /* DataTypeConversion: '<S30>/Data Type Conversion6' */
  pmsm_ctrl_M->blockIO.MtrIf_IfbkDq[1] = DBG_i_dq0[1];

  /* Gain: '<S30>/Gain2' */
  rtb_Switch_d_idx_0 = 0.035F * DBG_i_dq0[1];

  /* Sum: '<S32>/Add3' incorporates:
   *  DiscreteIntegrator: '<S39>/Discrete-Time Integrator'
   */
  rtb_error = rtb_Divide2 - pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke;

  /* Sum: '<S32>/Add2' incorporates:
   *  DiscreteIntegrator: '<S38>/Discrete-Time Integrator'
   *  Gain: '<S32>/Gain3'
   */
  rtb_Divide2 = 6000.0F * rtb_error +
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k;

  /* DataTypeConversion: '<S30>/Data Type Conversion2' */
  pmsm_ctrl_M->blockIO.MtrIf_TrqAct = rtb_Switch_d_idx_0;

  /* DataTypeConversion: '<S30>/Data Type Conversion1' incorporates:
   *  DiscreteIntegrator: '<S38>/Discrete-Time Integrator'
   */
  pmsm_ctrl_M->blockIO.MtrIf_SpdOut_i =
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k;

  /* Update for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S30>/ObsInertia'
   *  DiscreteIntegrator: '<S37>/Discrete-Time Integrator'
   *  Gain: '<S32>/Gain1'
   *  Product: '<S32>/Product'
   *  Sum: '<S32>/Add'
   *  Sum: '<S32>/Add1'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k += ((1.2E+7F * rtb_error +
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p) + rtb_Switch_d_idx_0 /
    2.4E-5F) * 3.33333337E-5F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S40>/Unit Delay' */
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE[0] = DBG_i_abc_lpf[0];
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE[1] = DBG_i_abc_lpf[1];
  pmsm_ctrl_M->dwork.UnitDelay_DSTATE[2] = DBG_i_abc_lpf[2];

  /* Update for DiscreteIntegrator: '<S39>/Discrete-Time Integrator' */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke += 3.33333337E-5F *
    rtb_Divide2;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S39>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S37>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S32>/Gain'
   */
  pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p += 8.0E+9F * rtb_error *
    3.33333337E-5F;
  if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p >= 1.0E+7F) {
    pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = 1.0E+7F;
  } else {
    if (pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p <= -1.0E+7F) {
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S37>/Discrete-Time Integrator' */
  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Foc_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_MotnCtrl(RT_MODEL *const pmsm_ctrl_M)
{
  real32_T rtb_Gain1;
  real32_T rtb_Add_gh;
  real32_T rtb_Sign_k;
  real32_T rtb_Add1_j;
  int64m_T tmp;
  uint32_T tmp_0;
  uint32_T tmp_1;
  real32_T rtb_Sign_g;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_MotnCtrl_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlMain'
   */
  /* Outputs for Enabled SubSystem: '<S4>/MotnCtrl' incorporates:
   *  EnablePort: '<S54>/Enable'
   */
  /* Logic: '<S4>/Logical Operator' incorporates:
   *  SignalConversion: '<S54>/HiddenBuf_InsertedFor_PosCtl_at_inport_2'
   *  SignalConversion: '<S54>/HiddenBuf_InsertedFor_SpdCtrl_at_inport_2'
   *  SignalConversion: '<S56>/HiddenBuf_InsertedFor_PosTrackDiff_at_inport_1'
   */
  if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl ||
      pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
    if (!pmsm_ctrl_M->dwork.MotnCtrl_MODE) {
      pmsm_ctrl_M->dwork.MotnCtrl_MODE = true;
    }

    /* Gain: '<S54>/Gain1' incorporates:
     *  DataTypeConversion: '<S54>/Data Type Conversion6'
     *  DataTypeConversion: '<S54>/Data Type Conversion7'
     *  Gain: '<S54>/Gain3'
     */
    rtb_Gain1 = (real32_T)(10 * (int32_T)(real32_T)floor
      (pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0])) * 0.00261799386F;

    /* Outputs for Enabled SubSystem: '<S56>/PosTrackDiff' incorporates:
     *  EnablePort: '<S60>/Enable'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
      if (!pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* InitializeConditions for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE = 0.0F;

        /* InitializeConditions for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h = 0.0F;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = true;
      }

      /* DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
      pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1 =
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE;

      /* DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
      pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator =
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h;

      /* Gain: '<S61>/Gain3' */
      rtb_Add_gh = 0.001F * pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* Sum: '<S61>/Add8' incorporates:
       *  Sum: '<S60>/Add'
       */
      rtb_Sign_k = (pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1 - rtb_Gain1) +
        rtb_Add_gh;

      /* Sqrt: '<S62>/Sqrt' incorporates:
       *  Abs: '<S62>/Abs'
       *  Constant: '<S61>/d'
       *  Gain: '<S62>/Gain'
       *  Product: '<S62>/Product'
       *  Sum: '<S62>/Add'
       */
      mw_arm_sqrt_f32((8.0F * (real32_T)fabs(rtb_Sign_k) + 0.005F) * 0.005F,
                      &rtb_Add1_j);

      /* Signum: '<S63>/Sign' */
      if (rtb_Sign_k < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else if (rtb_Sign_k > 0.0F) {
        rtb_Sign_g = 1.0F;
      } else {
        rtb_Sign_g = rtb_Sign_k;
      }

      /* End of Signum: '<S63>/Sign' */

      /* Sum: '<S63>/Add1' incorporates:
       *  Constant: '<S61>/d'
       *  Gain: '<S63>/Gain'
       *  Product: '<S63>/Product'
       *  Sum: '<S63>/Add'
       */
      rtb_Add1_j = (rtb_Add1_j - 0.005F) * rtb_Sign_g * 0.5F + rtb_Add_gh;

      /* Sum: '<S64>/Add1' */
      rtb_Add_gh = (rtb_Add_gh + rtb_Sign_k) - rtb_Add1_j;

      /* Sum: '<S67>/Add1' incorporates:
       *  Constant: '<S61>/d'
       */
      rtb_Sign_g = 0.005F + rtb_Sign_k;

      /* Sum: '<S67>/Add2' incorporates:
       *  Constant: '<S61>/d'
       */
      rtb_Sign_k -= 0.005F;

      /* Signum: '<S67>/Sign' */
      if (rtb_Sign_g < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else {
        if (rtb_Sign_g > 0.0F) {
          rtb_Sign_g = 1.0F;
        }
      }

      /* End of Signum: '<S67>/Sign' */

      /* Signum: '<S67>/Sign1' */
      if (rtb_Sign_k < 0.0F) {
        rtb_Sign_k = -1.0F;
      } else {
        if (rtb_Sign_k > 0.0F) {
          rtb_Sign_k = 1.0F;
        }
      }

      /* End of Signum: '<S67>/Sign1' */

      /* Sum: '<S64>/Add2' incorporates:
       *  Gain: '<S67>/Gain1'
       *  Product: '<S64>/Product'
       *  Sum: '<S67>/Add'
       */
      rtb_Add1_j += (rtb_Sign_g - rtb_Sign_k) * 0.5F * rtb_Add_gh;

      /* Signum: '<S65>/Sign' */
      if (rtb_Add1_j < 0.0F) {
        rtb_Sign_k = -1.0F;
      } else if (rtb_Add1_j > 0.0F) {
        rtb_Sign_k = 1.0F;
      } else {
        rtb_Sign_k = rtb_Add1_j;
      }

      /* End of Signum: '<S65>/Sign' */

      /* Sum: '<S65>/Add' incorporates:
       *  Constant: '<S61>/d'
       *  Product: '<S65>/Divide'
       */
      rtb_Add_gh = rtb_Add1_j / 0.005F - rtb_Sign_k;

      /* Sum: '<S66>/Add' incorporates:
       *  Constant: '<S61>/d'
       */
      rtb_Sign_g = rtb_Add1_j + 0.005F;

      /* Sum: '<S66>/Add1' incorporates:
       *  Constant: '<S61>/d'
       */
      rtb_Add1_j -= 0.005F;

      /* SignalConversion: '<S60>/OutportBufferForGrd' */
      pmsm_ctrl_M->blockIO.OutportBufferForGrd =
        pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* SignalConversion: '<S60>/OutportBufferForRef' */
      pmsm_ctrl_M->blockIO.OutportBufferForRef =
        pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

      /* Update for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE += 0.001F *
        pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;

      /* Signum: '<S66>/Sign' */
      if (rtb_Sign_g < 0.0F) {
        rtb_Sign_g = -1.0F;
      } else {
        if (rtb_Sign_g > 0.0F) {
          rtb_Sign_g = 1.0F;
        }
      }

      /* End of Signum: '<S66>/Sign' */

      /* Signum: '<S66>/Sign1' */
      if (rtb_Add1_j < 0.0F) {
        rtb_Add1_j = -1.0F;
      } else {
        if (rtb_Add1_j > 0.0F) {
          rtb_Add1_j = 1.0F;
        }
      }

      /* End of Signum: '<S66>/Sign1' */

      /* Update for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' incorporates:
       *  Gain: '<S65>/Gain'
       *  Gain: '<S66>/Gain'
       *  Product: '<S65>/Product'
       *  Sum: '<S65>/Add1'
       *  Sum: '<S66>/Add2'
       */
      pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h += ((rtb_Sign_g -
        rtb_Add1_j) * 0.5F * rtb_Add_gh + rtb_Sign_k) * -5000.0F * 0.001F;
    } else {
      if (pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* Disable for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

        /* Disable for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = false;
      }
    }

    /* End of Outputs for SubSystem: '<S56>/PosTrackDiff' */

    /* Outputs for Enabled SubSystem: '<S54>/PosCtl' incorporates:
     *  EnablePort: '<S55>/Enable'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
      if (!pmsm_ctrl_M->dwork.PosCtl_MODE) {
        /* InitializeConditions for DiscreteIntegrator: '<S59>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o = 0.0F;
        pmsm_ctrl_M->dwork.PosCtl_MODE = true;
      }

      /* Gain: '<S54>/Gain' incorporates:
       *  DataTypeConversion: '<S54>/Data Type Conversion5'
       */
      tmp_0 = 1439257344U;
      tmp_1 = (uint32_T)pmsm_ctrl_M->blockIO.BusCreator.mtrif_enc_cnts;
      sMultiWordMul(&tmp_0, 1, &tmp_1, 1, &tmp.chunks[0U], 2);

      /* Switch: '<S56>/Switch' */
      if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
        rtb_Gain1 = pmsm_ctrl_M->blockIO.OutportBufferForRef;
      }

      /* End of Switch: '<S56>/Switch' */

      /* Sum: '<S58>/Subtract' incorporates:
       *  DataTypeConversion: '<S54>/Data Type Conversion3'
       */
      rtb_Gain1 -= sMultiWord2Single(&tmp.chunks[0U], 2, 0) * 1.8189894E-12F;

      /* Sum: '<S58>/Add' incorporates:
       *  DiscreteIntegrator: '<S59>/Discrete-Time Integrator'
       *  Gain: '<S58>/Gain1'
       */
      pmsm_ctrl_M->blockIO.Add = 400.0F * rtb_Gain1 +
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o;
    } else {
      if (pmsm_ctrl_M->dwork.PosCtl_MODE) {
        pmsm_ctrl_M->dwork.PosCtl_MODE = false;
      }
    }

    /* End of Outputs for SubSystem: '<S54>/PosCtl' */

    /* Outputs for Enabled SubSystem: '<S54>/SpdCtrl' incorporates:
     *  EnablePort: '<S57>/Enable'
     */
    if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_spd_ctrl) {
      if (!pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        /* InitializeConditions for DiscreteIntegrator: '<S69>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE = 0.0F;
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = true;
      }

      /* Switch: '<S54>/Switch1' */
      if (pmsm_ctrl_M->blockIO.BusCreator2.ENBL_CTRL_FLAGS.enbl_pos_ctrl) {
        rtb_Sign_g = pmsm_ctrl_M->blockIO.Add;
      } else {
        rtb_Sign_g = pmsm_ctrl_M->blockIO.BusCreator2.ctrl_tgt[0];
      }

      /* End of Switch: '<S54>/Switch1' */

      /* Saturate: '<S57>/Saturation' incorporates:
       *  Constant: '<S57>/Constant3'
       *  DataTypeConversion: '<S54>/Data Type Conversion1'
       *  DiscreteIntegrator: '<S69>/Discrete-Time Integrator'
       *  Product: '<S68>/Product'
       *  Sum: '<S54>/Add'
       *  Sum: '<S68>/Add'
       *  Sum: '<S68>/Subtract'
       */
      pmsm_ctrl_M->blockIO.Saturation =
        ((pmsm_ctrl_M->blockIO.OutportBufferForGrd + rtb_Sign_g) -
         pmsm_ctrl_M->blockIO.MtrIf_SpdOut_i) * 0.024F +
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE;
    } else {
      if (pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = false;
      }
    }

    /* End of Outputs for SubSystem: '<S54>/SpdCtrl' */

    /* DataTypeConversion: '<S54>/Data Type Conversion4' incorporates:
     *  SignalConversion: '<S54>/HiddenBuf_InsertedFor_PosCtl_at_inport_2'
     *  SignalConversion: '<S54>/HiddenBuf_InsertedFor_SpdCtrl_at_inport_2'
     *  SignalConversion: '<S56>/HiddenBuf_InsertedFor_PosTrackDiff_at_inport_1'
     */
    pmsm_ctrl_M->blockIO.BusCreator_c.motn_ctrl_cmd =
      pmsm_ctrl_M->blockIO.Saturation;
  } else {
    if (pmsm_ctrl_M->dwork.MotnCtrl_MODE) {
      /* Disable for Enabled SubSystem: '<S56>/PosTrackDiff' */
      if (pmsm_ctrl_M->dwork.PosTrackDiff_MODE) {
        /* Disable for DiscreteIntegrator: '<S60>/Discrete-Time Integrator1' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator1;

        /* Disable for DiscreteIntegrator: '<S60>/Discrete-Time Integrator' */
        pmsm_ctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h =
          pmsm_ctrl_M->blockIO.DiscreteTimeIntegrator;
        pmsm_ctrl_M->dwork.PosTrackDiff_MODE = false;
      }

      /* End of Disable for SubSystem: '<S56>/PosTrackDiff' */

      /* Disable for Enabled SubSystem: '<S54>/PosCtl' */
      if (pmsm_ctrl_M->dwork.PosCtl_MODE) {
        pmsm_ctrl_M->dwork.PosCtl_MODE = false;
      }

      /* End of Disable for SubSystem: '<S54>/PosCtl' */

      /* Disable for Enabled SubSystem: '<S54>/SpdCtrl' */
      if (pmsm_ctrl_M->dwork.SpdCtrl_MODE) {
        pmsm_ctrl_M->dwork.SpdCtrl_MODE = false;
      }

      /* End of Disable for SubSystem: '<S54>/SpdCtrl' */
      pmsm_ctrl_M->dwork.MotnCtrl_MODE = false;
    }
  }

  /* End of Logic: '<S4>/Logical Operator' */
  /* End of Outputs for SubSystem: '<S4>/MotnCtrl' */
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
    CalData_L = -1.0F;
    CalData_Res = -1.0F;
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
