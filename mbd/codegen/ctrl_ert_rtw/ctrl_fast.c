/*
 * Code generation for system system '<Root>/ctrl_fast'
 *
 * Model                      : ctrl
 * Model version              : 1.904
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

#include "ctrl_fast.h"

/* Include model header file for global data */
#include "ctrl.h"
#include "ctrl_private.h"

/* Named constants for Chart: '<S3>/autotune' */
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_autocal_done                ((uint8_T)1U)
#define IN_autocal_in_progress         ((uint8_T)2U)
#define IN_ifbk_offset_cal             ((uint8_T)1U)
#define IN_ifbk_offset_calc            ((uint8_T)2U)
#define IN_ifbk_offset_id              ((uint8_T)1U)
#define IN_inductance_calc             ((uint8_T)1U)
#define IN_inductance_id               ((uint8_T)2U)
#define IN_inductance_switching        ((uint8_T)2U)
#define IN_init_outputs                ((uint8_T)3U)
#define IN_max_spd_calc                ((uint8_T)1U)
#define IN_motor_accel_wait            ((uint8_T)1U)
#define IN_motor_constant_id           ((uint8_T)3U)
#define IN_motor_inertia_calc          ((uint8_T)2U)
#define IN_motor_inertia_id            ((uint8_T)4U)
#define IN_off_cycle                   ((uint8_T)1U)
#define IN_on_cycle                    ((uint8_T)2U)
#define IN_resistance_calc             ((uint8_T)1U)
#define IN_resistance_id               ((uint8_T)5U)
#define IN_resistance_id_on            ((uint8_T)2U)
#define IN_trq_cnst_calc               ((uint8_T)2U)

/* Forward declaration for local functions */
static void autocal_in_progress(const real32_T *UnitDelay, const real32_T
  *UnitDelay_k, DW_ctrl_fast *localDW);

/* Function for Chart: '<S3>/autotune' */
static void autocal_in_progress(const real32_T *UnitDelay, const real32_T
  *UnitDelay_k, DW_ctrl_fast *localDW)
{
  switch (localDW->is_autocal_in_progress) {
   case IN_ifbk_offset_id:
    if (localDW->is_ifbk_offset_id == IN_ifbk_offset_cal) {
      if (localDW->cycle_cnt >= rtP.Cfg_OfsIDCntThshld) {
        localDW->is_ifbk_offset_id = IN_ifbk_offset_calc;
        localDW->ifbk_ofs = localDW->ifbk_pos / (real32_T)rtP.Cfg_OfsIDCntThshld;
      } else {
        localDW->ifbk_pos += *UnitDelay_k;
        if (localDW->cycle_cnt > 2147483646) {
          localDW->cycle_cnt = MAX_int32_T;
        } else {
          localDW->cycle_cnt++;
        }
      }
    } else {
      localDW->is_ifbk_offset_id = IN_NO_ACTIVE_CHILD;
      localDW->is_autocal_in_progress = IN_resistance_id;
      localDW->is_resistance_id = IN_resistance_id_on;
      localDW->status = ResID;
      localDW->ifbk_pos = 0.0F;
      localDW->cycle_cnt = 0;
      localDW->vout = rtP.Cfg_ResIDMtrVin;
    }
    break;

   case IN_inductance_id:
    if (localDW->is_inductance_id == IN_inductance_calc) {
      if ((localDW->temporalCounter_i1 >= (uint32_T)rtP.Cfg_IndIDCoolDownTicks) &&
          (*UnitDelay < 5.0F)) {
        localDW->is_inductance_id = IN_NO_ACTIVE_CHILD;
        localDW->is_autocal_in_progress = IN_motor_inertia_id;
        localDW->is_motor_inertia_id = IN_motor_accel_wait;
        localDW->vout = rtP.Cfg_TrqCnstIDMtrVin;
        localDW->status = IndIDCoolDown;
        localDW->cycle_cnt = 1;
        localDW->JEst = 0.0F;
      }
    } else if (localDW->cycle_cnt >= rtP.Cfg_IndIDCntThshld) {
      localDW->is_inductance_switching = IN_NO_ACTIVE_CHILD;
      localDW->is_inductance_id = IN_inductance_calc;
      localDW->temporalCounter_i1 = 0U;
      localDW->Lest = rtP.Cfg_IndIDMtrVin * rtP.Cfg_IndIDTs /
        ((localDW->ifbk_pos - localDW->ifbk_neg) / (real32_T)localDW->ind_id_cnt);
      localDW->vout = 0.0F;
      localDW->status = IndIDCoolDown;
    } else {
      if (localDW->cycle_cnt > 2147483646) {
        localDW->cycle_cnt = MAX_int32_T;
      } else {
        localDW->cycle_cnt++;
      }

      if (localDW->is_inductance_switching == IN_off_cycle) {
        if (localDW->temporalCounter_i1 >= (uint32_T)rtP.Cfg_IndIDSwTicks) {
          localDW->is_inductance_switching = IN_on_cycle;
          localDW->temporalCounter_i1 = 0U;
          localDW->vout = rtP.Cfg_IndIDMtrVin;
          localDW->ifbk_neg += *UnitDelay_k;
          if (localDW->ind_id_cnt > 2147483646) {
            localDW->ind_id_cnt = MAX_int32_T;
          } else {
            localDW->ind_id_cnt++;
          }
        }
      } else {
        if (localDW->temporalCounter_i1 >= (uint32_T)rtP.Cfg_IndIDSwTicks) {
          localDW->is_inductance_switching = IN_off_cycle;
          localDW->temporalCounter_i1 = 0U;
          localDW->vout = -rtP.Cfg_IndIDMtrVin;
          localDW->ifbk_pos += *UnitDelay_k;
        }
      }
    }
    break;

   case IN_motor_constant_id:
    if (localDW->is_motor_constant_id == IN_max_spd_calc) {
      if (localDW->cycle_cnt > rtP.Cfg_TrqCnstIDCntThshld) {
        localDW->is_motor_constant_id = IN_trq_cnst_calc;
        localDW->temporalCounter_i1 = 0U;
        localDW->spd_max /= (real32_T)rtP.Cfg_TrqCnstIDCntThshld;
        localDW->ifbk_pos /= (real32_T)rtP.Cfg_TrqCnstIDCntThshld;
        localDW->KTrqEst = (rtP.Cfg_TrqCnstIDMtrVin - localDW->Rest *
                            localDW->ifbk_pos) / localDW->spd_max;
        localDW->KFrcEst = localDW->KTrqEst * localDW->ifbk_pos /
          localDW->spd_max;
        localDW->SpdMax = localDW->spd_max;
        localDW->IfbkMax = localDW->ifbk_max;
        localDW->IfbkSteady = localDW->ifbk_pos;
        localDW->vout = 0.0F;
      } else {
        localDW->spd_max += *UnitDelay;
        localDW->ifbk_pos += *UnitDelay_k;
        if (localDW->cycle_cnt > 2147483646) {
          localDW->cycle_cnt = MAX_int32_T;
        } else {
          localDW->cycle_cnt++;
        }
      }
    } else {
      if ((localDW->temporalCounter_i1 >= (uint32_T)rtP.Cfg_ResIDCoolDownTicks) &&
          (*UnitDelay < 10.0F)) {
        localDW->is_motor_constant_id = IN_NO_ACTIVE_CHILD;
        localDW->is_autocal_in_progress = IN_inductance_id;
        localDW->is_inductance_id = IN_inductance_switching;
        localDW->status = IndID;
        localDW->ind_id_cnt = 0;
        localDW->cycle_cnt = 0;
        localDW->ifbk_pos = 0.0F;
        localDW->ifbk_neg = 0.0F;
        localDW->is_inductance_switching = IN_on_cycle;
        localDW->temporalCounter_i1 = 0U;
        localDW->vout = rtP.Cfg_IndIDMtrVin;
        localDW->ifbk_neg += *UnitDelay_k;
        if (localDW->ind_id_cnt > 2147483646) {
          localDW->ind_id_cnt = MAX_int32_T;
        } else {
          localDW->ind_id_cnt++;
        }
      }
    }
    break;

   case IN_motor_inertia_id:
    if (localDW->is_motor_inertia_id == IN_motor_accel_wait) {
      if (*UnitDelay >= 0.6321 * localDW->SpdMax) {
        localDW->is_motor_inertia_id = IN_motor_inertia_calc;
        localDW->vout = 0.0F;
        localDW->JEst /= *UnitDelay;
      } else {
        localDW->JEst += (-localDW->KFrcEst * *UnitDelay + localDW->KTrqEst *
                          *UnitDelay_k) * rtP.TsFast;
      }
    } else {
      localDW->is_motor_inertia_id = IN_NO_ACTIVE_CHILD;
      localDW->is_autocal_in_progress = IN_NO_ACTIVE_CHILD;
      localDW->is_c1_ctrl = IN_autocal_done;
      localDW->status = Done;
      localDW->vout = 0.0F;
    }
    break;

   default:
    if (localDW->is_resistance_id == IN_resistance_calc) {
      if (localDW->temporalCounter_i1 >= (uint32_T)rtP.Cfg_ResIDCoolDownTicks) {
        localDW->is_resistance_id = IN_NO_ACTIVE_CHILD;
        localDW->is_autocal_in_progress = IN_motor_constant_id;
        localDW->status = TrqCnstID;
        localDW->cycle_cnt = 0;
        localDW->spd_max = 0.0F;
        localDW->ifbk_pos = 0.0F;
        localDW->is_motor_constant_id = IN_max_spd_calc;
      }
    } else if (localDW->cycle_cnt >= rtP.Cfg_ResIDCntThshld) {
      localDW->is_resistance_id = IN_resistance_calc;
      localDW->temporalCounter_i1 = 0U;
      localDW->Rest = rtP.Cfg_ResIDMtrVin / localDW->ifbk_max;
      localDW->vout = rtP.Cfg_TrqCnstIDMtrVin;
    } else {
      localDW->ifbk_max = fmaxf(localDW->ifbk_max, *UnitDelay_k);
      if (localDW->cycle_cnt > 2147483646) {
        localDW->cycle_cnt = MAX_int32_T;
      } else {
        localDW->cycle_cnt++;
      }
    }
    break;
  }
}

/* System initialize for function-call system: '<Root>/ctrl_fast' */
void ctrl_fast_Init(real32_T *rty_MtrSpd, real32_T *rty_MtrDistTrq, real32_T
                    *rty_PosEst, MtrCtrlMd *rty_MtrCtrlMd, real32_T *rty_CtrlCmd,
                    DBG_BUS *rty_DBG_BUS, DW_ctrl_fast *localDW, P_ctrl_fast
                    *localP)
{
  /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = localP->UnitDelay_InitialCondition_m;

  /* InitializeConditions for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = localP->DiscreteTimeIntegrator_IC_b;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_k = localP->DiscreteTimeIntegrator_IC_n;

  /* InitializeConditions for UnitDelay: '<S14>/Unit Delay' */
  localDW->UnitDelay_DSTATE_f = localP->UnitDelay_InitialCondition_b;

  /* InitializeConditions for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_j = localP->DiscreteTimeIntegrator_IC_f;

  /* InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_j4 = localP->DiscreteTimeIntegrator_IC_g;

  /* InitializeConditions for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_o = localP->DiscreteTimeIntegrator_IC_o;

  /* InitializeConditions for UnitDelay: '<S20>/Unit Delay' */
  localDW->UnitDelay_DSTATE_fb = localP->UnitDelay_InitialCondition_bk;

  /* SystemInitialize for Chart: '<S3>/autotune' */
  localDW->status = NotStarted;
  localDW->Lest = -1.0F;
  localDW->Rest = -1.0F;
  localDW->KTrqEst = -1.0F;
  localDW->ifbk_ofs = -1.0F;
  localDW->KFrcEst = -1.0F;
  localDW->JEst = -1.0F;
  localDW->IfbkSteady = -1.0F;
  localDW->IfbkMax = -1.0F;
  localDW->SpdMax = -1.0F;

  /* SystemInitialize for Enabled SubSystem: '<S5>/IfbkCtrl' */
  /* InitializeConditions for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_g = localP->DiscreteTimeIntegrator_IC;

  /* SystemInitialize for Outport: '<S11>/Ctrl' */
  localDW->Add = localP->Ctrl_Y0;

  /* End of SystemInitialize for SubSystem: '<S5>/IfbkCtrl' */

  /* SystemInitialize for Outport: '<S1>/MtrSpd' */
  *rty_MtrSpd = localP->MtrSpd_Y0;

  /* SystemInitialize for Outport: '<S1>/MtrDistTrq' */
  *rty_MtrDistTrq = localP->MtrDistTrq_Y0;

  /* SystemInitialize for Outport: '<S1>/PosEst' */
  *rty_PosEst = localP->PosEst_Y0;

  /* SystemInitialize for Outport: '<S1>/MtrCtrlMd' */
  *rty_MtrCtrlMd = localP->MtrCtrlMd_Y0;

  /* SystemInitialize for Outport: '<S1>/CtrlCmd' */
  *rty_CtrlCmd = localP->CtrlCmd_Y0;

  /* SystemInitialize for Outport: '<S1>/DBG_BUS' */
  *rty_DBG_BUS = localP->DBG_BUS_Y0;
}

/* Output and update for function-call system: '<Root>/ctrl_fast' */
void ctrl_fast(real32_T rtu_MtrPos, real32_T rtu_MtrIfbkAct, real32_T
               rtu_MtrIfbkTgt, MtrCtrlMd rtu_MtrCtrlMd_In, real32_T rtu_MtrSpd,
               real32_T *rty_MtrSpd, real32_T *rty_MtrDistTrq, real32_T
               *rty_PosEst, MtrCtrlMd *rty_MtrCtrlMd, real32_T *rty_CtrlCmd,
               DBG_BUS *rty_DBG_BUS, DW_ctrl_fast *localDW, P_ctrl_fast *localP)
{
  boolean_T rtb_LogicalOperator;
  real32_T rtb_Add_pf;
  real32_T rtb_error;
  real32_T rtb_Add1_h;
  real32_T UnitDelay;
  real32_T UnitDelay_k;
  real32_T rtb_Switch_idx_0;
  real32_T rtb_Switch_idx_1;

  /* UnitDelay: '<S1>/Unit Delay' */
  UnitDelay = localDW->UnitDelay_DSTATE;

  /* UnitDelay: '<S3>/Unit Delay' */
  UnitDelay_k = localDW->UnitDelay_DSTATE_i;

  /* Chart: '<S3>/autotune' */
  if (localDW->temporalCounter_i1 < 2147483647U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c1_ctrl == 0U) {
    localDW->is_active_c1_ctrl = 1U;
    localDW->is_c1_ctrl = IN_init_outputs;
    localDW->status = NotStarted;
    localDW->vout = 0.0F;
    localDW->Lest = -1.0F;
    localDW->Rest = -1.0F;
    localDW->KTrqEst = -1.0F;
    localDW->ifbk_ofs = 0.0F;
  } else {
    switch (localDW->is_c1_ctrl) {
     case IN_autocal_done:
      break;

     case IN_autocal_in_progress:
      autocal_in_progress(&UnitDelay, &UnitDelay_k, localDW);
      break;

     default:
      if (rtP.Cfg_AutoCalEnbl) {
        localDW->is_c1_ctrl = IN_autocal_in_progress;
        localDW->is_autocal_in_progress = IN_ifbk_offset_id;
        localDW->is_ifbk_offset_id = IN_ifbk_offset_cal;
        localDW->status = IfbkOfsID;
        localDW->cycle_cnt = 0;
        localDW->vout = 0.0F;
        localDW->ifbk_pos = 0.0F;
        localDW->ifbk_ofs = 0.0F;
      } else {
        localDW->status = NotStarted;
        localDW->vout = 0.0F;
        localDW->Lest = -1.0F;
        localDW->Rest = -1.0F;
        localDW->KTrqEst = -1.0F;
        localDW->ifbk_ofs = 0.0F;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/autotune' */

  /* Sum: '<S3>/Add' */
  UnitDelay = rtu_MtrIfbkAct - localDW->ifbk_ofs;

  /* Logic: '<S8>/Logical Operator' incorporates:
   *  Constant: '<S8>/Constant'
   *  Constant: '<S8>/Constant1'
   *  RelationalOperator: '<S8>/Relational Operator'
   *  RelationalOperator: '<S8>/Relational Operator1'
   */
  rtb_LogicalOperator = ((localP->Constant_Value == localDW->status) ||
    (localP->Constant1_Value == localDW->status));

  /* Switch: '<S7>/Switch' incorporates:
   *  Constant: '<S7>/Constant'
   *  Switch: '<S7>/Switch1'
   */
  if (rtb_LogicalOperator) {
    UnitDelay_k = rtu_MtrIfbkTgt;
    *rty_MtrCtrlMd = rtu_MtrCtrlMd_In;
  } else {
    UnitDelay_k = localDW->vout;
    *rty_MtrCtrlMd = localP->Constant_Value_o;
  }

  /* End of Switch: '<S7>/Switch' */

  /* BusCreator: '<S3>/Bus Creator' */
  rty_DBG_BUS->IfbkTgt = UnitDelay_k;
  rty_DBG_BUS->Lest = localDW->Lest;
  rty_DBG_BUS->Rest = localDW->Rest;
  rty_DBG_BUS->KTrqEst = localDW->KTrqEst;
  rty_DBG_BUS->IfbkOfs = localDW->ifbk_ofs;
  rty_DBG_BUS->KFrcEst = localDW->KFrcEst;
  rty_DBG_BUS->JEst = localDW->JEst;
  rty_DBG_BUS->IfbkSteady = localDW->IfbkSteady;
  rty_DBG_BUS->IfbkMax = localDW->IfbkMax;
  rty_DBG_BUS->SpdMax = localDW->SpdMax;
  rty_DBG_BUS->Status = localDW->status;

  /* Gain: '<S4>/Gain1' */
  rtb_Add_pf = localP->Gain1_Gain_m * rtu_MtrPos;

  /* Product: '<S14>/Product1' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
   */
  *rty_MtrDistTrq = localDW->DiscreteTimeIntegrator_DSTATE * rty_DBG_BUS->JEst;

  /* Switch: '<S13>/Switch2' incorporates:
   *  Constant: '<S13>/Constant1'
   *  Constant: '<S13>/Constant2'
   *  Product: '<S13>/Divide'
   */
  if (rtP.Cfg_EnblLoadObs) {
    rtb_error = *rty_MtrDistTrq / rty_DBG_BUS->KTrqEst;
  } else {
    rtb_error = localP->Constant2_Value;
  }

  /* End of Switch: '<S13>/Switch2' */

  /* Sum: '<S5>/Add' */
  rtb_error += UnitDelay_k;

  /* RelationalOperator: '<S9>/Compare' incorporates:
   *  Constant: '<S9>/Constant'
   */
  rtb_LogicalOperator = (*rty_MtrCtrlMd != localP->CompareToConstant_const);

  /* Outputs for Enabled SubSystem: '<S5>/IfbkCtrl' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (rtb_LogicalOperator) {
    if (!localDW->IfbkCtrl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
      localDW->DiscreteTimeIntegrator_DSTATE_g =
        localP->DiscreteTimeIntegrator_IC;
      localDW->IfbkCtrl_MODE = true;
    }

    /* Switch: '<S11>/Switch' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S11>/Constant1'
     *  Constant: '<S11>/Constant2'
     *  Constant: '<S11>/Constant3'
     *  Product: '<S11>/Product'
     */
    if (rtP.Cfg_AutoCalEnbl) {
      rtb_Switch_idx_0 = rtP.Cfg_IfbkCtrlBW * rty_DBG_BUS->Lest;
      rtb_Switch_idx_1 = rtP.Cfg_IfbkCtrlBW * rty_DBG_BUS->Rest;
    } else {
      rtb_Switch_idx_0 = (real32_T)rtP.MotorParams.L * rtP.Cfg_IfbkCtrlBW;
      rtb_Switch_idx_1 = (real32_T)rtP.MotorParams.R * rtP.Cfg_IfbkCtrlBW;
    }

    /* End of Switch: '<S11>/Switch' */

    /* Saturate: '<S5>/Saturation1' */
    if (rtb_error > localP->Saturation1_UpperSat) {
      rtb_error = localP->Saturation1_UpperSat;
    } else {
      if (rtb_error < localP->Saturation1_LowerSat) {
        rtb_error = localP->Saturation1_LowerSat;
      }
    }

    /* End of Saturate: '<S5>/Saturation1' */

    /* Sum: '<S18>/Subtract' */
    rtb_error -= UnitDelay;

    /* Sum: '<S18>/Add' incorporates:
     *  DiscreteIntegrator: '<S19>/Discrete-Time Integrator'
     *  Product: '<S18>/Product'
     */
    localDW->Add = rtb_Switch_idx_0 * rtb_error +
      localDW->DiscreteTimeIntegrator_DSTATE_g;

    /* Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' incorporates:
     *  Product: '<S18>/Product1'
     */
    localDW->DiscreteTimeIntegrator_DSTATE_g += rtb_error * rtb_Switch_idx_1 *
      localP->DiscreteTimeIntegrator_gainval;
    if (localDW->DiscreteTimeIntegrator_DSTATE_g >=
        localP->PICtrlVaryingGains_max_lim) {
      localDW->DiscreteTimeIntegrator_DSTATE_g =
        localP->PICtrlVaryingGains_max_lim;
    } else {
      if (localDW->DiscreteTimeIntegrator_DSTATE_g <=
          localP->PICtrlVaryingGains_min_lim) {
        localDW->DiscreteTimeIntegrator_DSTATE_g =
          localP->PICtrlVaryingGains_min_lim;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S19>/Discrete-Time Integrator' */
  } else {
    if (localDW->IfbkCtrl_MODE) {
      localDW->IfbkCtrl_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S5>/IfbkCtrl' */

  /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
  *rty_PosEst = localDW->DiscreteTimeIntegrator_DSTATE_k;

  /* Sum: '<S14>/Add3' */
  rtb_error = rtb_Add_pf - *rty_PosEst;

  /* Sum: '<S14>/Add1' incorporates:
   *  DiscreteIntegrator: '<S15>/Discrete-Time Integrator'
   *  Gain: '<S14>/Gain1'
   *  Product: '<S10>/Product'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product2'
   *  Sum: '<S14>/Add'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  rtb_Switch_idx_0 = ((rtP.DistObs_K2 * rtb_error +
                       localDW->DiscreteTimeIntegrator_DSTATE) + UnitDelay *
                      rty_DBG_BUS->KTrqEst / rty_DBG_BUS->JEst) - 1.0F /
    rty_DBG_BUS->JEst * rty_DBG_BUS->KFrcEst * localDW->UnitDelay_DSTATE_f;

  /* Sum: '<S21>/Add' incorporates:
   *  DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
   */
  rtb_Add_pf -= localDW->DiscreteTimeIntegrator_DSTAT_j4;

  /* Signum: '<S21>/Sign' */
  if (rtb_Add_pf < 0.0F) {
    rtb_Switch_idx_1 = -1.0F;
  } else if (rtb_Add_pf > 0.0F) {
    rtb_Switch_idx_1 = 1.0F;
  } else {
    rtb_Switch_idx_1 = rtb_Add_pf;
  }

  /* End of Signum: '<S21>/Sign' */

  /* Sum: '<S21>/Add1' incorporates:
   *  Abs: '<S21>/Abs'
   *  DiscreteIntegrator: '<S22>/Discrete-Time Integrator'
   *  Gain: '<S21>/Gain1'
   *  Gain: '<S21>/Gain2'
   *  Product: '<S21>/Product'
   *  Sqrt: '<S21>/Sqrt'
   */
  rtb_Add_pf = sqrtf(fabsf(rtb_Add_pf)) * rtb_Switch_idx_1 * rtP.SmDiff_Kp +
    rtP.SmDiff_Ki * localDW->DiscreteTimeIntegrator_DSTATE_o;

  /* Sum: '<S20>/Add1' incorporates:
   *  Constant: '<S20>/Constant'
   *  Constant: '<S20>/Constant1'
   *  Product: '<S20>/Product'
   *  Product: '<S20>/Product1'
   *  Sum: '<S20>/Add'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  rtb_Add1_h = (localP->Constant1_Value_b - rtP.SmDiff_FiltCnst) * rtb_Add_pf +
    rtP.SmDiff_FiltCnst * localDW->UnitDelay_DSTATE_fb;

  /* MultiPortSwitch: '<S5>/Multiport Switch' incorporates:
   *  Constant: '<S5>/Constant'
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   */
  switch (rtP.Cfg_SpdSnsSrc) {
   case 0:
    *rty_MtrSpd = rtu_MtrSpd;
    break;

   case 1:
    *rty_MtrSpd = rtb_Add1_h;
    break;

   default:
    *rty_MtrSpd = localDW->DiscreteTimeIntegrator_DSTATE_j;
    break;
  }

  /* End of MultiPortSwitch: '<S5>/Multiport Switch' */

  /* Switch: '<S5>/Switch' incorporates:
   *  Sum: '<S5>/Add1'
   */
  if (rtb_LogicalOperator) {
    UnitDelay_k = localDW->Add;
  }

  /* End of Switch: '<S5>/Switch' */

  /* Saturate: '<S5>/Saturation' */
  if (UnitDelay_k > localP->Saturation_UpperSat) {
    UnitDelay_k = localP->Saturation_UpperSat;
  } else {
    if (UnitDelay_k < localP->Saturation_LowerSat) {
      UnitDelay_k = localP->Saturation_LowerSat;
    }
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* SignalConversion: '<S5>/Signal Copy1' */
  *rty_CtrlCmd = UnitDelay_k;

  /* Update for UnitDelay: '<S1>/Unit Delay' */
  localDW->UnitDelay_DSTATE = *rty_MtrSpd;

  /* Update for UnitDelay: '<S3>/Unit Delay' */
  localDW->UnitDelay_DSTATE_i = UnitDelay;

  /* Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S14>/Gain'
   */
  localDW->DiscreteTimeIntegrator_DSTATE += rtP.DistObs_K3 * rtb_error *
    localP->DiscreteTimeIntegrator_gainva_h;
  if (localDW->DiscreteTimeIntegrator_DSTATE >= localP->Integrator_max_lim) {
    localDW->DiscreteTimeIntegrator_DSTATE = localP->Integrator_max_lim;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTATE <= localP->Integrator_min_lim) {
      localDW->DiscreteTimeIntegrator_DSTATE = localP->Integrator_min_lim;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S15>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   *  Gain: '<S14>/Gain3'
   *  Sum: '<S14>/Add2'
   */
  localDW->DiscreteTimeIntegrator_DSTATE_k += (rtP.DistObs_K1 * rtb_error +
    localDW->DiscreteTimeIntegrator_DSTATE_j) *
    localP->DiscreteTimeIntegrator_gainva_p;
  if (localDW->DiscreteTimeIntegrator_DSTATE_k >= localP->Integrator2_max_lim) {
    localDW->DiscreteTimeIntegrator_DSTATE_k = localP->Integrator2_max_lim;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTATE_k <= localP->Integrator2_min_lim)
    {
      localDW->DiscreteTimeIntegrator_DSTATE_k = localP->Integrator2_min_lim;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S14>/Unit Delay' incorporates:
   *  DiscreteIntegrator: '<S16>/Discrete-Time Integrator'
   */
  localDW->UnitDelay_DSTATE_f = localDW->DiscreteTimeIntegrator_DSTATE_j;

  /* Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_j +=
    localP->DiscreteTimeIntegrator_gainva_k * rtb_Switch_idx_0;
  if (localDW->DiscreteTimeIntegrator_DSTATE_j >= localP->Integrator1_max_lim) {
    localDW->DiscreteTimeIntegrator_DSTATE_j = localP->Integrator1_max_lim;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTATE_j <= localP->Integrator1_min_lim)
    {
      localDW->DiscreteTimeIntegrator_DSTATE_j = localP->Integrator1_min_lim;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTAT_j4 +=
    localP->DiscreteTimeIntegrator_gainva_o * rtb_Add_pf;
  if (localDW->DiscreteTimeIntegrator_DSTAT_j4 >= localP->Integrator1_max_lim_o)
  {
    localDW->DiscreteTimeIntegrator_DSTAT_j4 = localP->Integrator1_max_lim_o;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTAT_j4 <=
        localP->Integrator1_min_lim_i) {
      localDW->DiscreteTimeIntegrator_DSTAT_j4 = localP->Integrator1_min_lim_i;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_o +=
    localP->DiscreteTimeIntegrator_gainva_i * rtb_Switch_idx_1;
  if (localDW->DiscreteTimeIntegrator_DSTATE_o >= localP->Integrator_max_lim_k)
  {
    localDW->DiscreteTimeIntegrator_DSTATE_o = localP->Integrator_max_lim_k;
  } else {
    if (localDW->DiscreteTimeIntegrator_DSTATE_o <= localP->Integrator_min_lim_i)
    {
      localDW->DiscreteTimeIntegrator_DSTATE_o = localP->Integrator_min_lim_i;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S22>/Discrete-Time Integrator' */

  /* Update for UnitDelay: '<S20>/Unit Delay' */
  localDW->UnitDelay_DSTATE_fb = rtb_Add1_h;
}
