/*
 * pmsm_ctrl_private.h
 *
 * Code generation for model "pmsm_ctrl".
 *
 * Model version              : 1.676
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_pmsm_ctrl_private_h_
#define RTW_HEADER_pmsm_ctrl_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "pmsm_ctrl.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

extern real32_T sMultiWord2Single(const uint32_T u1[], int32_T n1, int32_T e1);
extern void sMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
extern int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);
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
  rtp_enc_cnts_int, int32_T rtp_n_poles);

#endif                                 /* RTW_HEADER_pmsm_ctrl_private_h_ */
