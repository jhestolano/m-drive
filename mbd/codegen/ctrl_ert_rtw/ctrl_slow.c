/*
 * Code generation for system system '<Root>/ctrl_slow'
 *
 * Model                      : ctrl
 * Model version              : 1.904
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 * Note that the functions contained in this file are part of a Simulink
 * model, and are not self-contained algorithms.
 */

#include "ctrl_slow.h"

/* Include model header file for global data */
#include "ctrl.h"
#include "ctrl_private.h"

/* System initialize for function-call system: '<Root>/ctrl_slow' */
void ctrl_slow_Init(real32_T *rty_MtrIfbkTgt, real32_T *rty_MtrSpdOut, real32_T *
                    rty_MtrRef, real32_T *rty_MtrDistEst, real32_T
                    *rty_MtrPosEst, DW_ctrl_slow *localDW, P_ctrl_slow *localP)
{
  /* SystemInitialize for Enabled SubSystem: '<S26>/TrackDiff' */
  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = localP->DiscreteTimeIntegrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE = localP->DiscreteTimeIntegrator_IC_e;

  /* SystemInitialize for Outport: '<S31>/Ref' */
  localDW->OutportBufferForRef = localP->Ref_Y0;

  /* SystemInitialize for Outport: '<S31>/Grd' */
  localDW->OutportBufferForGrd = localP->Grd_Y0;

  /* End of SystemInitialize for SubSystem: '<S26>/TrackDiff' */

  /* SystemInitialize for Enabled SubSystem: '<S26>/PosCtl' */
  /* InitializeConditions for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_k = localP->DiscreteTimeIntegrator_IC;

  /* SystemInitialize for Outport: '<S29>/MtrSpdTgt' */
  localDW->Add = localP->MtrSpdTgt_Y0;

  /* End of SystemInitialize for SubSystem: '<S26>/PosCtl' */

  /* SystemInitialize for Enabled SubSystem: '<S26>/SpdCtrl' */
  /* InitializeConditions for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE_g = localP->DiscreteTimeIntegrator_IC_k;

  /* SystemInitialize for Outport: '<S30>/Ctrl' */
  localDW->Saturation = localP->Ctrl_Y0;

  /* End of SystemInitialize for SubSystem: '<S26>/SpdCtrl' */

  /* SystemInitialize for SignalConversion: '<S2>/Signal Conversion4' */
  *rty_MtrRef = localDW->OutportBufferForRef;

  /* SystemInitialize for Outport: '<S2>/MtrIfbkTgt' */
  *rty_MtrIfbkTgt = localP->MtrIfbkTgt_Y0;

  /* SystemInitialize for Outport: '<S2>/MtrSpdOut' */
  *rty_MtrSpdOut = localP->MtrSpdOut_Y0;

  /* SystemInitialize for Outport: '<S2>/MtrDistEst' */
  *rty_MtrDistEst = localP->MtrDistEst_Y0;

  /* SystemInitialize for Outport: '<S2>/MtrPosEst' */
  *rty_MtrPosEst = localP->MtrPosEst_Y0;
}

/* Output and update for function-call system: '<Root>/ctrl_slow' */
void ctrl_slow(real32_T rtu_MtrTgt, real32_T rtu_MtrPos, real32_T rtu_MtrSpd,
               real32_T rtu_MtrDistTrq, real32_T rtu_PosEst, MtrCtrlMd
               rtu_MtrCtrlMd, const DBG_BUS *rtu_Params, real32_T
               *rty_MtrIfbkTgt, real32_T *rty_MtrSpdOut, real32_T *rty_MtrRef,
               real32_T *rty_MtrDistEst, real32_T *rty_MtrPosEst, DW_ctrl_slow
               *localDW, P_ctrl_slow *localP)
{
  boolean_T rtb_Compare_g;
  boolean_T rtb_Compare_d;
  boolean_T rtb_LogicalOperator;
  real32_T rtb_Add_d;
  real32_T rtb_Sign_eq;
  real32_T rtb_Add1_g;
  real32_T rtb_Product1_n;
  real32_T rtb_Switch_i_idx_0;
  real32_T rtb_Switch_i_idx_1;
  real32_T rtb_Switch_i_idx_2;
  real32_T u;

  /* Switch: '<S27>/Switch' incorporates:
   *  Constant: '<S27>/Constant'
   *  Constant: '<S27>/Constant1'
   *  Constant: '<S27>/Constant2'
   *  Constant: '<S27>/Constant3'
   *  Constant: '<S27>/Constant4'
   *  Logic: '<S27>/Logical Operator'
   *  RelationalOperator: '<S27>/Equal'
   */
  if ((rtu_Params->Status == localP->Constant1_Value) && rtP.Cfg_AutoCalEnbl) {
    rtb_Switch_i_idx_0 = rtu_Params->KTrqEst;
    rtb_Switch_i_idx_1 = rtu_Params->JEst;
    rtb_Switch_i_idx_2 = rtu_Params->KFrcEst;
  } else {
    rtb_Switch_i_idx_0 = localP->Constant2_Value;
    rtb_Switch_i_idx_1 = localP->Constant3_Value;
    rtb_Switch_i_idx_2 = localP->Constant4_Value;
  }

  /* End of Switch: '<S27>/Switch' */

  /* RelationalOperator: '<S33>/Compare' incorporates:
   *  Constant: '<S33>/Constant'
   */
  rtb_Compare_g = (rtu_MtrCtrlMd == localP->CompareToConstant_const);

  /* RelationalOperator: '<S34>/Compare' incorporates:
   *  Constant: '<S34>/Constant'
   */
  rtb_Compare_d = (rtu_MtrCtrlMd == localP->CompareToConstant1_const);

  /* Logic: '<S28>/Logical Operator' */
  rtb_LogicalOperator = (rtb_Compare_g || rtb_Compare_d);

  /* Outputs for Enabled SubSystem: '<S26>/TrackDiff' incorporates:
   *  EnablePort: '<S31>/Enable'
   */
  if (rtb_LogicalOperator) {
    if (!localDW->TrackDiff_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
      localDW->DiscreteTimeIntegrator1_DSTATE =
        localP->DiscreteTimeIntegrator1_IC;

      /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
      localDW->DiscreteTimeIntegrator_DSTATE =
        localP->DiscreteTimeIntegrator_IC_e;
      localDW->TrackDiff_MODE = true;
    }

    /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
    localDW->DiscreteTimeIntegrator1 = localDW->DiscreteTimeIntegrator1_DSTATE;

    /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
    localDW->DiscreteTimeIntegrator = localDW->DiscreteTimeIntegrator_DSTATE;

    /* SignalConversion: '<S31>/OutportBufferForGrd' */
    localDW->OutportBufferForGrd = localDW->DiscreteTimeIntegrator;

    /* SignalConversion: '<S31>/OutportBufferForRef' */
    localDW->OutportBufferForRef = localDW->DiscreteTimeIntegrator1;

    /* Gain: '<S39>/Gain3' */
    rtb_Add_d = localP->TrackDiff_h0 * localDW->DiscreteTimeIntegrator;

    /* Sum: '<S39>/Add8' incorporates:
     *  Sum: '<S31>/Add'
     */
    rtb_Sign_eq = (localDW->DiscreteTimeIntegrator1 - rtu_MtrTgt) + rtb_Add_d;

    /* Signum: '<S41>/Sign' */
    if (rtb_Sign_eq < 0.0F) {
      rtb_Add1_g = -1.0F;
    } else if (rtb_Sign_eq > 0.0F) {
      rtb_Add1_g = 1.0F;
    } else {
      rtb_Add1_g = rtb_Sign_eq;
    }

    /* End of Signum: '<S41>/Sign' */

    /* Sum: '<S41>/Add1' incorporates:
     *  Abs: '<S40>/Abs'
     *  Constant: '<S39>/d'
     *  Gain: '<S40>/Gain'
     *  Gain: '<S41>/Gain'
     *  Product: '<S40>/Product'
     *  Product: '<S41>/Product'
     *  Sqrt: '<S40>/Sqrt'
     *  Sum: '<S40>/Add'
     *  Sum: '<S41>/Add'
     */
    rtb_Add1_g = (sqrtf((localP->Gain_Gain * fabsf(rtb_Sign_eq) +
                         localP->d_Value) * localP->d_Value) - localP->d_Value) *
      rtb_Add1_g * localP->Gain_Gain_o + rtb_Add_d;

    /* Sum: '<S42>/Add1' */
    rtb_Add_d = (rtb_Add_d + rtb_Sign_eq) - rtb_Add1_g;

    /* Sum: '<S45>/Add1' incorporates:
     *  Constant: '<S39>/d'
     */
    u = localP->d_Value + rtb_Sign_eq;

    /* Sum: '<S45>/Add2' incorporates:
     *  Constant: '<S39>/d'
     */
    rtb_Sign_eq -= localP->d_Value;

    /* Signum: '<S45>/Sign' */
    if (u < 0.0F) {
      u = -1.0F;
    } else {
      if (u > 0.0F) {
        u = 1.0F;
      }
    }

    /* End of Signum: '<S45>/Sign' */

    /* Signum: '<S45>/Sign1' */
    if (rtb_Sign_eq < 0.0F) {
      rtb_Sign_eq = -1.0F;
    } else {
      if (rtb_Sign_eq > 0.0F) {
        rtb_Sign_eq = 1.0F;
      }
    }

    /* End of Signum: '<S45>/Sign1' */

    /* Sum: '<S42>/Add2' incorporates:
     *  Gain: '<S45>/Gain1'
     *  Product: '<S42>/Product'
     *  Sum: '<S45>/Add'
     */
    rtb_Add1_g += (u - rtb_Sign_eq) * localP->Gain1_Gain * rtb_Add_d;

    /* Signum: '<S43>/Sign' */
    if (rtb_Add1_g < 0.0F) {
      rtb_Sign_eq = -1.0F;
    } else if (rtb_Add1_g > 0.0F) {
      rtb_Sign_eq = 1.0F;
    } else {
      rtb_Sign_eq = rtb_Add1_g;
    }

    /* End of Signum: '<S43>/Sign' */

    /* Sum: '<S43>/Add' incorporates:
     *  Constant: '<S39>/d'
     *  Product: '<S43>/Divide'
     */
    rtb_Add_d = rtb_Add1_g / localP->d_Value - rtb_Sign_eq;

    /* Sum: '<S44>/Add' incorporates:
     *  Constant: '<S39>/d'
     */
    u = rtb_Add1_g + localP->d_Value;

    /* Sum: '<S44>/Add1' incorporates:
     *  Constant: '<S39>/d'
     */
    rtb_Add1_g -= localP->d_Value;

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
    localDW->DiscreteTimeIntegrator1_DSTATE +=
      localP->DiscreteTimeIntegrator1_gainval * localDW->DiscreteTimeIntegrator;

    /* Signum: '<S44>/Sign' */
    if (u < 0.0F) {
      u = -1.0F;
    } else {
      if (u > 0.0F) {
        u = 1.0F;
      }
    }

    /* End of Signum: '<S44>/Sign' */

    /* Signum: '<S44>/Sign1' */
    if (rtb_Add1_g < 0.0F) {
      rtb_Add1_g = -1.0F;
    } else {
      if (rtb_Add1_g > 0.0F) {
        rtb_Add1_g = 1.0F;
      }
    }

    /* End of Signum: '<S44>/Sign1' */

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S43>/Gain'
     *  Gain: '<S44>/Gain'
     *  Product: '<S43>/Product'
     *  Sum: '<S43>/Add1'
     *  Sum: '<S44>/Add2'
     */
    localDW->DiscreteTimeIntegrator_DSTATE += ((u - rtb_Add1_g) *
      localP->Gain_Gain_m * rtb_Add_d + rtb_Sign_eq) * localP->Gain_Gain_c *
      localP->DiscreteTimeIntegrator_gainva_b;
  } else {
    if (localDW->TrackDiff_MODE) {
      /* Disable for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
      localDW->DiscreteTimeIntegrator1_DSTATE = localDW->DiscreteTimeIntegrator1;

      /* Disable for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
      localDW->DiscreteTimeIntegrator_DSTATE = localDW->DiscreteTimeIntegrator;
      localDW->TrackDiff_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S26>/TrackDiff' */

  /* Outputs for Enabled SubSystem: '<S26>/PosCtl' incorporates:
   *  EnablePort: '<S29>/Enable'
   */
  if (rtb_Compare_g) {
    if (!localDW->PosCtl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */
      localDW->DiscreteTimeIntegrator_DSTATE_k =
        localP->DiscreteTimeIntegrator_IC;
      localDW->PosCtl_MODE = true;
    }

    /* Sum: '<S35>/Subtract' incorporates:
     *  Gain: '<S24>/Gain1'
     */
    rtb_Sign_eq = localDW->OutportBufferForRef - localP->Gain1_Gain_f *
      rtu_MtrPos;

    /* Sum: '<S35>/Add' incorporates:
     *  DiscreteIntegrator: '<S36>/Discrete-Time Integrator'
     *  Gain: '<S35>/Gain1'
     */
    localDW->Add = rtP.PosCtrl_Kp * rtb_Sign_eq +
      localDW->DiscreteTimeIntegrator_DSTATE_k;

    /* Update for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S35>/Gain'
     */
    localDW->DiscreteTimeIntegrator_DSTATE_k += (real32_T)(localP->PICtrl_PI_Ki *
      rtb_Sign_eq) * localP->DiscreteTimeIntegrator_gainval;
    if (localDW->DiscreteTimeIntegrator_DSTATE_k >= localP->PICtrl_max_lim) {
      localDW->DiscreteTimeIntegrator_DSTATE_k = localP->PICtrl_max_lim;
    } else {
      if (localDW->DiscreteTimeIntegrator_DSTATE_k <= localP->PICtrl_min_lim) {
        localDW->DiscreteTimeIntegrator_DSTATE_k = localP->PICtrl_min_lim;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S36>/Discrete-Time Integrator' */

    /* Switch: '<S26>/Switch' incorporates:
     *  Sum: '<S26>/Add1'
     *  Switch: '<S28>/Switch3'
     */
    rtb_Sign_eq = localDW->OutportBufferForGrd + localDW->Add;
  } else {
    if (localDW->PosCtl_MODE) {
      localDW->PosCtl_MODE = false;
    }

    /* Switch: '<S26>/Switch' */
    rtb_Sign_eq = localDW->OutportBufferForRef;
  }

  /* End of Outputs for SubSystem: '<S26>/PosCtl' */

  /* Outputs for Enabled SubSystem: '<S26>/SpdCtrl' incorporates:
   *  EnablePort: '<S30>/Enable'
   */
  if (rtb_LogicalOperator) {
    if (!localDW->SpdCtrl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' */
      localDW->DiscreteTimeIntegrator_DSTATE_g =
        localP->DiscreteTimeIntegrator_IC_k;
      localDW->SpdCtrl_MODE = true;
    }

    /* Sum: '<S37>/Subtract' */
    rtb_Sign_eq -= rtu_MtrSpd;

    /* Product: '<S37>/Product1' incorporates:
     *  Constant: '<S30>/Constant3'
     *  DataStoreWrite: '<S27>/Data Store Write2'
     *  Product: '<S30>/Product'
     */
    rtb_Product1_n = rtP.Cfg_SpdCtrlBW * rtb_Switch_i_idx_2 * rtb_Sign_eq;

    /* Sum: '<S37>/Add' incorporates:
     *  Constant: '<S30>/Constant3'
     *  DataStoreWrite: '<S27>/Data Store Write1'
     *  DiscreteIntegrator: '<S38>/Discrete-Time Integrator'
     *  Product: '<S30>/Product'
     *  Product: '<S37>/Product'
     */
    rtb_Sign_eq = rtP.Cfg_SpdCtrlBW * rtb_Switch_i_idx_1 * rtb_Sign_eq +
      localDW->DiscreteTimeIntegrator_DSTATE_g;

    /* Saturate: '<S30>/Saturation' */
    if (rtb_Sign_eq > localP->Saturation_UpperSat_k) {
      localDW->Saturation = localP->Saturation_UpperSat_k;
    } else if (rtb_Sign_eq < localP->Saturation_LowerSat_e) {
      localDW->Saturation = localP->Saturation_LowerSat_e;
    } else {
      localDW->Saturation = rtb_Sign_eq;
    }

    /* End of Saturate: '<S30>/Saturation' */

    /* Switch: '<S28>/Switch2' incorporates:
     *  Constant: '<S28>/Constant'
     *  DataStoreWrite: '<S27>/Data Store Write1'
     *  Product: '<S28>/Product'
     *  Switch: '<S26>/Switch1'
     */
    if (rtb_Compare_d) {
      rtb_Sign_eq = rtb_Switch_i_idx_1 * localDW->OutportBufferForGrd;
    } else {
      rtb_Sign_eq = localP->Constant_Value;
    }

    /* End of Switch: '<S28>/Switch2' */

    /* Product: '<S26>/Divide' incorporates:
     *  DataStoreWrite: '<S27>/Data Store Write'
     *  Sum: '<S26>/Add'
     *  Switch: '<S26>/Switch1'
     */
    rtb_Sign_eq = (rtb_Sign_eq + localDW->Saturation) / rtb_Switch_i_idx_0;

    /* Saturate: '<S26>/Saturation' incorporates:
     *  Switch: '<S26>/Switch1'
     */
    if (rtb_Sign_eq > localP->Saturation_UpperSat) {
      rtb_Sign_eq = localP->Saturation_UpperSat;
    } else {
      if (rtb_Sign_eq < localP->Saturation_LowerSat) {
        rtb_Sign_eq = localP->Saturation_LowerSat;
      }
    }

    /* End of Saturate: '<S26>/Saturation' */
  } else {
    if (localDW->SpdCtrl_MODE) {
      localDW->SpdCtrl_MODE = false;
    }

    /* Saturate: '<S26>/Saturation1' incorporates:
     *  Switch: '<S26>/Switch1'
     */
    if (rtu_MtrTgt > localP->Saturation1_UpperSat) {
      rtb_Sign_eq = localP->Saturation1_UpperSat;
    } else if (rtu_MtrTgt < localP->Saturation1_LowerSat) {
      rtb_Sign_eq = localP->Saturation1_LowerSat;
    } else {
      rtb_Sign_eq = rtu_MtrTgt;
    }

    /* End of Saturate: '<S26>/Saturation1' */
  }

  /* End of Outputs for SubSystem: '<S26>/SpdCtrl' */

  /* SignalConversion: '<S2>/Signal Conversion' incorporates:
   *  Gain: '<S2>/TO_RPM'
   */
  *rty_MtrSpdOut = localP->TO_RPM_Gain * rtu_MtrSpd;

  /* SignalConversion: '<S2>/Signal Conversion4' */
  *rty_MtrRef = localDW->OutportBufferForRef;

  /* SignalConversion: '<S2>/Signal Conversion5' */
  *rty_MtrIfbkTgt = rtb_Sign_eq;

  /* SignalConversion: '<S2>/Signal Conversion2' */
  *rty_MtrDistEst = rtu_MtrDistTrq;

  /* SignalConversion: '<S2>/Signal Conversion3' incorporates:
   *  Gain: '<S25>/Gain1'
   */
  *rty_MtrPosEst = localP->Gain1_Gain_j * rtu_PosEst;

  /* Update for Enabled SubSystem: '<S26>/SpdCtrl' incorporates:
   *  EnablePort: '<S30>/Enable'
   */
  if (localDW->SpdCtrl_MODE) {
    /* Update for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' */
    localDW->DiscreteTimeIntegrator_DSTATE_g +=
      localP->DiscreteTimeIntegrator_gainva_a * rtb_Product1_n;
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

    /* End of Update for DiscreteIntegrator: '<S38>/Discrete-Time Integrator' */
  }

  /* End of Update for SubSystem: '<S26>/SpdCtrl' */
}
