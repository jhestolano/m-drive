/*
 * pmsm_ctrl_private.h
 *
 * Code generation for model "pmsm_ctrl".
 *
 * Model version              : 1.765
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_pmsm_ctrl_private_h_
#define RTW_HEADER_pmsm_ctrl_private_h_
#include "rtwtypes.h"
#include "pmsm_ctrl.h"

extern int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);
extern uint32_T div_nzp_usu32_sat(int32_T numerator, uint32_T denominator);
extern void calc_pwm_dc(RT_MODEL * const pmsm_ctrl_M, const real32_T
  rtu_pwm_abc[3], real32_T rty_pwm_dc[3]);
extern void get_mtr_ifbk_sum_Reset(self_get_mtr_ifbk_sum *pmsm_ctrl_self_arg);
extern void get_mtr_ifbk_sum(self_get_mtr_ifbk_sum *pmsm_ctrl_self_arg, const
  real32_T rtu_mtr_ifbk_abc[3], real32_T rty_mtr_ifbk_sum_abc[3]);
extern void get_mtr_ifbk_avg(RT_MODEL * const pmsm_ctrl_M, const real32_T
  rtu_mtr_ifbk_sum_abc[3], real32_T rtu_ncycles, real32_T rty_mtr_ifbk_avg_abc[3]);
extern void calc_mod_wave(RT_MODEL * const pmsm_ctrl_M, const real32_T rtu_dq0[3],
  real32_T rtu_elec_angle, real32_T rty_pwm_dc[3], real32_T rty_mod_wave[3]);
extern void calc_elec_angle(RT_MODEL * const pmsm_ctrl_M, int32_T
  rtu_mtr_enc_cnts, real32_T *rty_elec_angle, real32_T *rty_mtr_pos, int32_T
  rtp_enc_cnts_int, uint8_T rtp_n_poles);
extern void PI_Ctrl_Reset(self_PI_Ctrl *pmsm_ctrl_self_arg);
extern void PI_Ctrl(self_PI_Ctrl *pmsm_ctrl_self_arg, real32_T rtu_y_tgt,
                    real32_T rtu_y_act, real32_T rtu_Kp, real32_T rtu_Ki,
                    real32_T *rty_PI_out, real32_T rtp_max_lim, real32_T
                    rtp_min_lim);

#endif                                 /* RTW_HEADER_pmsm_ctrl_private_h_ */
