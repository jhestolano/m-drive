/*
 * pmsm_ctrl_types.h
 *
 * Code generation for model "pmsm_ctrl".
 *
 * Model version              : 1.676
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#ifndef RTW_HEADER_pmsm_ctrl_types_h_
#define RTW_HEADER_pmsm_ctrl_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "CalMgrSt_T.h"
#ifndef DEFINED_TYPEDEF_FOR_MtrCtrlMd_T_
#define DEFINED_TYPEDEF_FOR_MtrCtrlMd_T_

typedef enum {
  CTRL_MD_OFF = 0,                     /* Default value */
  CTRL_MD_CAL,
  CTRL_MD_RAW_PWM,
  CTRL_MD_DQ_PWM,
  CTRL_MD_IFBK,
  CTRL_MD_TRQ,
  CTRL_MD_SPD,
  CTRL_MD_POS,
  CTRL_MD_STEP_DIR
} MtrCtrlMd_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Calib_OutType_
#define DEFINED_TYPEDEF_FOR_Calib_OutType_

/* This structure holds all calibration routine requests. */
typedef struct {
  MtrCtrlMd_T ctrl_md_rqst;
  CalMgrSt_T cal_mgr_st_rqst;
  real32_T mtr_cmd_rqst[3];
} Calib_OutType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_FoCtrl_OutType_
#define DEFINED_TYPEDEF_FOR_FoCtrl_OutType_

typedef struct {
  real32_T mtrif_mod_wave[3];
  real32_T mtrif_spd_est;
  real32_T mtrif_pwm_dc[3];
  real32_T mtrif_trq_act;
  int32_T obs_enc_cnts;
  real32_T mtrif_ifbk_dq[2];
  real32_T mtrif_pwm_dq[2];
} FoCtrl_OutType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MotnCtrl_OutType_
#define DEFINED_TYPEDEF_FOR_MotnCtrl_OutType_

/* Holds all outputs of main (motion) controller. */
typedef struct {
  real32_T motn_ctrl_cmd;
} MotnCtrl_OutType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtrCtrlCal_T_
#define DEFINED_TYPEDEF_FOR_MtrCtrlCal_T_

typedef enum {
  CAL_ENC_OFS = 0,                     /* Default value */
  CAL_RES_ID = 1,
  CAL_IND_ID = 2,
  CAL_IFBK_OFS = 3,
  CAL_MECH_PARAMS = 4,
  CAL_IFBK_CTRL = 5,
  CAL_MOTN_CTRL = 6,
  CAL_NONE = 255
} MtrCtrlCal_T;

#endif

#ifndef DEFINED_TYPEDEF_FOR_MtrIf_InType_
#define DEFINED_TYPEDEF_FOR_MtrIf_InType_

/* Structure that holds all neccessary controller input signals. */
typedef struct {
  int32_T mtrif_enc_cnts;
  real32_T mtrif_ifbk_act[3];
  real32_T mtrif_spd_sns;
  MtrCtrlMd_T mtrif_ctrl_md;
  real32_T mtrif_tgt[3];
  MtrCtrlCal_T mtrif_cal_rqst;
} MtrIf_InType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Calib_ParamType_
#define DEFINED_TYPEDEF_FOR_Calib_ParamType_

/* This structure holds all calibration (estimated) parameters. */
typedef struct {
  int32_T enc_ofs;
  real32_T ind;
  int32_T ppoles;
  real32_T res;
  real32_T ifbk_ofs[3];
} Calib_ParamType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_enbl_ctrl_flags_type_
#define DEFINED_TYPEDEF_FOR_enbl_ctrl_flags_type_

typedef struct {
  boolean_T ctrl_md_off;
  boolean_T enbl_raw_pwm;
  boolean_T enbl_mod_wave;
  boolean_T enbl_ifbk_ctrl;
  boolean_T enbl_spd_ctrl;
  boolean_T enbl_pos_ctrl;
} enbl_ctrl_flags_type;

#endif

#ifndef DEFINED_TYPEDEF_FOR_CtrlMgr_OutType_
#define DEFINED_TYPEDEF_FOR_CtrlMgr_OutType_

/* Output structured bus of control manager.

   The control manager receives requests for different control modes
   and calibration routines. */
typedef struct {
  real32_T ctrl_tgt[3];
  MtrCtrlCal_T ctrl_cal_act;
  MtrCtrlMd_T ctrl_md_act;
  enbl_ctrl_flags_type ENBL_CTRL_FLAGS;
} CtrlMgr_OutType;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_kzBFVreMZSXyV1yvH3vyCD_
#define DEFINED_TYPEDEF_FOR_struct_kzBFVreMZSXyV1yvH3vyCD_

typedef struct {
  real_T Vdc;
  real_T SpdNom;
  real_T Rs;
  real_T Ls;
  real_T Lm;
  real_T Ms;
  real_T Ld;
  real_T Lq;
  real_T Kf;
  real_T Poles;
  real_T Ktrq;
  real_T MFlux;
  real_T Jm;
  real_T PPR;
  real_T EncCnts;
  real_T IfbkSnsNoise;
  real_T IfbkOfs[3];
} struct_kzBFVreMZSXyV1yvH3vyCD;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#endif                                 /* RTW_HEADER_pmsm_ctrl_types_h_ */
