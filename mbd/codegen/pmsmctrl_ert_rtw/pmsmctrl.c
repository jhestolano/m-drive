/*
 * pmsmctrl.c
 *
 * Code generation for model "pmsmctrl".
 *
 * Model version              : 1.198
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#include "pmsmctrl.h"

extern real32_T rt_modf(real32_T u0, real32_T u1);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

real32_T rt_modf(real32_T u0, real32_T u1)
{
  real32_T y;
  boolean_T yEq;
  real32_T q;
  y = u0;
  if (u0 == 0.0F) {
    y = 0.0F;
  } else {
    if (u1 != 0.0F) {
      y = fmodf(u0, u1);
      yEq = (y == 0.0F);
      if ((!yEq) && (u1 > floorf(u1))) {
        q = fabsf(u0 / u1);
        yEq = (fabsf(q - floorf(q + 0.5F)) <= FLT_EPSILON * q);
      }

      if (yEq) {
        y = 0.0F;
      } else {
        if ((u0 < 0.0F) != (u1 < 0.0F)) {
          y += u1;
        }
      }
    }
  }

  return y;
}

/* Model step function */
void Trig_Pmsm_MotnCtrl(RT_MODEL *const pmsmctrl_M, int32_T rtU_MtrIf_EncCnts,
  MtrCtrlMd rtU_MtrIf_CtrlMd, real32_T rtU_MtrIf_Tgt, real32_T *rtY_MtrIf_SpdAct)
{
  real32_T rtb_Switch1;
  real32_T rtb_Add_gh;
  real32_T rtb_Add1_j;
  real32_T rtb_Add1;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_MotnCtrl_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlMain'
   */
  /* Outputs for Enabled SubSystem: '<S2>/PosCtl' incorporates:
   *  EnablePort: '<S26>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S27>/PosTrackDiff' incorporates:
   *  EnablePort: '<S31>/Enable'
   */
  /* RelationalOperator: '<S25>/Compare' incorporates:
   *  Constant: '<S25>/Constant'
   *  Inport: '<Root>/MtrIf_CtrlMd'
   */
  if (rtU_MtrIf_CtrlMd == PosCtrlMd) {
    if (!pmsmctrl_M->dwork.PosTrackDiff_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE = 0.0F;

      /* InitializeConditions for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h = 0.0F;
      pmsmctrl_M->dwork.PosTrackDiff_MODE = true;
    }

    /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
    pmsmctrl_M->blockIO.DiscreteTimeIntegrator1 =
      pmsmctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE;

    /* DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
    pmsmctrl_M->blockIO.DiscreteTimeIntegrator =
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h;

    /* Gain: '<S32>/Gain3' */
    rtb_Add_gh = 0.001F * pmsmctrl_M->blockIO.DiscreteTimeIntegrator;

    /* Sum: '<S32>/Add8' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion6'
     *  DataTypeConversion: '<S2>/Data Type Conversion7'
     *  Gain: '<S2>/Gain1'
     *  Gain: '<S2>/Gain3'
     *  Inport: '<Root>/MtrIf_Tgt'
     *  Sum: '<S31>/Add'
     */
    rtb_Switch1 = (pmsmctrl_M->blockIO.DiscreteTimeIntegrator1 - (real32_T)(10 *
      (int32_T)floorf(rtU_MtrIf_Tgt)) * 0.000314159261F) + rtb_Add_gh;

    /* Signum: '<S34>/Sign' */
    if (rtb_Switch1 < 0.0F) {
      rtb_Add1_j = -1.0F;
    } else if (rtb_Switch1 > 0.0F) {
      rtb_Add1_j = 1.0F;
    } else {
      rtb_Add1_j = rtb_Switch1;
    }

    /* End of Signum: '<S34>/Sign' */

    /* Sum: '<S34>/Add1' incorporates:
     *  Abs: '<S33>/Abs'
     *  Constant: '<S32>/d'
     *  Gain: '<S33>/Gain'
     *  Gain: '<S34>/Gain'
     *  Product: '<S33>/Product'
     *  Product: '<S34>/Product'
     *  Sqrt: '<S33>/Sqrt'
     *  Sum: '<S33>/Add'
     *  Sum: '<S34>/Add'
     */
    rtb_Add1_j = (sqrtf((8.0F * fabsf(rtb_Switch1) + 0.005F) * 0.005F) - 0.005F)
      * rtb_Add1_j * 0.5F + rtb_Add_gh;

    /* Sum: '<S35>/Add1' */
    rtb_Add1 = (rtb_Add_gh + rtb_Switch1) - rtb_Add1_j;

    /* Sum: '<S38>/Add1' incorporates:
     *  Constant: '<S32>/d'
     */
    rtb_Add_gh = 0.005F + rtb_Switch1;

    /* Sum: '<S38>/Add2' incorporates:
     *  Constant: '<S32>/d'
     */
    rtb_Switch1 -= 0.005F;

    /* Signum: '<S38>/Sign' */
    if (rtb_Add_gh < 0.0F) {
      rtb_Add_gh = -1.0F;
    } else {
      if (rtb_Add_gh > 0.0F) {
        rtb_Add_gh = 1.0F;
      }
    }

    /* End of Signum: '<S38>/Sign' */

    /* Signum: '<S38>/Sign1' */
    if (rtb_Switch1 < 0.0F) {
      rtb_Switch1 = -1.0F;
    } else {
      if (rtb_Switch1 > 0.0F) {
        rtb_Switch1 = 1.0F;
      }
    }

    /* End of Signum: '<S38>/Sign1' */

    /* Sum: '<S35>/Add2' incorporates:
     *  Gain: '<S38>/Gain1'
     *  Product: '<S35>/Product'
     *  Sum: '<S38>/Add'
     */
    rtb_Add1_j += (rtb_Add_gh - rtb_Switch1) * 0.5F * rtb_Add1;

    /* Signum: '<S36>/Sign' */
    if (rtb_Add1_j < 0.0F) {
      rtb_Switch1 = -1.0F;
    } else if (rtb_Add1_j > 0.0F) {
      rtb_Switch1 = 1.0F;
    } else {
      rtb_Switch1 = rtb_Add1_j;
    }

    /* End of Signum: '<S36>/Sign' */

    /* Sum: '<S36>/Add' incorporates:
     *  Constant: '<S32>/d'
     *  Product: '<S36>/Divide'
     */
    rtb_Add1 = rtb_Add1_j / 0.005F - rtb_Switch1;

    /* Sum: '<S37>/Add' incorporates:
     *  Constant: '<S32>/d'
     */
    rtb_Add_gh = rtb_Add1_j + 0.005F;

    /* Sum: '<S37>/Add1' incorporates:
     *  Constant: '<S32>/d'
     */
    rtb_Add1_j -= 0.005F;

    /* SignalConversion: '<S31>/OutportBufferForGrd' */
    pmsmctrl_M->blockIO.OutportBufferForGrd =
      pmsmctrl_M->blockIO.DiscreteTimeIntegrator;

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
    pmsmctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE += 0.001F *
      pmsmctrl_M->blockIO.DiscreteTimeIntegrator;

    /* Signum: '<S37>/Sign' */
    if (rtb_Add_gh < 0.0F) {
      rtb_Add_gh = -1.0F;
    } else {
      if (rtb_Add_gh > 0.0F) {
        rtb_Add_gh = 1.0F;
      }
    }

    /* End of Signum: '<S37>/Sign' */

    /* Signum: '<S37>/Sign1' */
    if (rtb_Add1_j < 0.0F) {
      rtb_Add1_j = -1.0F;
    } else {
      if (rtb_Add1_j > 0.0F) {
        rtb_Add1_j = 1.0F;
      }
    }

    /* End of Signum: '<S37>/Sign1' */

    /* Update for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' incorporates:
     *  Gain: '<S36>/Gain'
     *  Gain: '<S37>/Gain'
     *  Product: '<S36>/Product'
     *  Sum: '<S36>/Add1'
     *  Sum: '<S37>/Add2'
     */
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h += ((rtb_Add_gh -
      rtb_Add1_j) * 0.5F * rtb_Add1 + rtb_Switch1) * -5000.0F * 0.001F;
    if (!pmsmctrl_M->dwork.PosCtl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S30>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o = 0.0F;
      pmsmctrl_M->dwork.PosCtl_MODE = true;
    }

    /* Sum: '<S29>/Add' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion5'
     *  DiscreteIntegrator: '<S30>/Discrete-Time Integrator'
     *  Gain: '<S29>/Gain1'
     *  Gain: '<S2>/Gain'
     *  Inport: '<Root>/MtrIf_EncCnts'
     *  SignalConversion: '<S31>/OutportBufferForRef'
     *  Sum: '<S29>/Subtract'
     */
    pmsmctrl_M->blockIO.Add = (pmsmctrl_M->blockIO.DiscreteTimeIntegrator1 -
      0.000314159261F * (real32_T)rtU_MtrIf_EncCnts) * 400.0F +
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_o;

    /* Switch: '<S2>/Switch1' */
    rtb_Switch1 = pmsmctrl_M->blockIO.Add;
  } else {
    if (pmsmctrl_M->dwork.PosTrackDiff_MODE) {
      /* Disable for DiscreteIntegrator: '<S31>/Discrete-Time Integrator1' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator1_DSTATE =
        pmsmctrl_M->blockIO.DiscreteTimeIntegrator1;

      /* Disable for DiscreteIntegrator: '<S31>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_h =
        pmsmctrl_M->blockIO.DiscreteTimeIntegrator;
      pmsmctrl_M->dwork.PosTrackDiff_MODE = false;
    }

    if (pmsmctrl_M->dwork.PosCtl_MODE) {
      pmsmctrl_M->dwork.PosCtl_MODE = false;
    }

    /* Switch: '<S2>/Switch1' incorporates:
     *  Inport: '<Root>/MtrIf_Tgt'
     */
    rtb_Switch1 = rtU_MtrIf_Tgt;
  }

  /* End of RelationalOperator: '<S25>/Compare' */
  /* End of Outputs for SubSystem: '<S27>/PosTrackDiff' */
  /* End of Outputs for SubSystem: '<S2>/PosCtl' */

  /* Outputs for Enabled SubSystem: '<S2>/SpdCtrl' incorporates:
   *  EnablePort: '<S28>/Enable'
   */
  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S24>/Constant'
   *  Inport: '<Root>/MtrIf_CtrlMd'
   *  RelationalOperator: '<S24>/Compare'
   */
  if (rtU_MtrIf_CtrlMd >= SpdCtrlMd) {
    if (!pmsmctrl_M->dwork.SpdCtrl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S40>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE = 0.0F;
      pmsmctrl_M->dwork.SpdCtrl_MODE = true;
    }

    /* Sum: '<S39>/Subtract' incorporates:
     *  DataTypeConversion: '<S2>/Data Type Conversion1'
     *  Sum: '<S2>/Add'
     */
    rtb_Switch1 = (pmsmctrl_M->blockIO.OutportBufferForGrd + rtb_Switch1) -
      pmsmctrl_M->blockIO.DataTypeConversion1;

    /* Sum: '<S39>/Add' incorporates:
     *  Constant: '<S28>/Constant3'
     *  DiscreteIntegrator: '<S40>/Discrete-Time Integrator'
     *  Product: '<S39>/Product'
     */
    pmsmctrl_M->blockIO.Saturation = 0.190000013F * rtb_Switch1 +
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE;

    /* Update for DiscreteIntegrator: '<S40>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S28>/Constant1'
     *  Product: '<S39>/Product1'
     */
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE += rtb_Switch1 *
      0.099999994F * 3.33333337E-5F;

    /* DataTypeConversion: '<S2>/Data Type Conversion4' */
    pmsmctrl_M->blockIO.DataTypeConversion4 = pmsmctrl_M->blockIO.Saturation;
  } else {
    if (pmsmctrl_M->dwork.SpdCtrl_MODE) {
      pmsmctrl_M->dwork.SpdCtrl_MODE = false;
    }

    /* MultiPortSwitch: '<S2>/Multiport Switch' incorporates:
     *  Constant: '<S2>/Constant'
     *  Constant: '<S2>/Constant1'
     *  Constant: '<S2>/Constant2'
     */
    switch (rtU_MtrIf_CtrlMd) {
     case TrqCtrlMd:
     case PwmCtrlMd:
      rtb_Add1_j = 1.0F;
      break;

     case IfbkCtrlMd:
      rtb_Add1_j = 0.12F;
      break;

     default:
      rtb_Add1_j = 0.0F;
      break;
    }

    /* End of MultiPortSwitch: '<S2>/Multiport Switch' */

    /* DataTypeConversion: '<S2>/Data Type Conversion4' incorporates:
     *  Product: '<S2>/Product'
     */
    pmsmctrl_M->blockIO.DataTypeConversion4 = rtb_Switch1 * rtb_Add1_j;
  }

  /* End of Switch: '<S2>/Switch' */
  /* End of Outputs for SubSystem: '<S2>/SpdCtrl' */

  /* Outport: '<Root>/MtrIf_SpdAct' incorporates:
   *  DataTypeConversion: '<S2>/Data Type Conversion8'
   */
  *rtY_MtrIf_SpdAct = pmsmctrl_M->blockIO.DataTypeConversion1;

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_MotnCtrl_at_outport_1' */
}

/* Model step function */
void Trig_Pmsm_Foc(RT_MODEL *const pmsmctrl_M, real32_T rtU_MtrIf_IfbkAct[3],
                   MtrCtrlMd rtU_MtrIf_CtrlMd, real32_T rtY_MtrIf_ModWave[3],
                   real32_T rtY_MtrIf_PwmDc[3], real32_T *rtY_MtrIf_TrqAct)
{
  real32_T rtb_error;
  real32_T rtb_Max;
  real32_T rtb_Subtract_o;
  real32_T rtb_pwm_dc;
  real32_T rtb_Gain1_l_idx_1;
  real32_T rtb_pwm_dc_idx_1;
  real32_T rtb_Gain1_l_idx_0;

  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Foc_at_outport_1' incorporates:
   *  SubSystem: '<Root>/CtrlFast'
   */
  /* Gain: '<S7>/Gain3' incorporates:
   *  DiscreteIntegrator: '<S1>/Accumulator'
   *  Gain: '<S1>/Gain1'
   */
  rtb_error = 20000.0F * pmsmctrl_M->dwork.Accumulator_DSTATE * 0.000314159261F;

  /* Math: '<S7>/Mod' incorporates:
   *  Constant: '<S7>/Constant2'
   *  Gain: '<S7>/Gain'
   */
  rtb_Max = rt_modf(12.0F * rtb_error, 6.28318548F);

  /* Sum: '<S14>/Add1' incorporates:
   *  Constant: '<S14>/Constant'
   *  Inport: '<Root>/MtrIf_IfbkAct'
   *  Product: '<S14>/Product'
   *  Product: '<S14>/Product1'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  pmsmctrl_M->dwork.UnitDelay_DSTATE[0] = rtU_MtrIf_IfbkAct[0] * 0.25F + 0.75F *
    pmsmctrl_M->dwork.UnitDelay_DSTATE[0];
  pmsmctrl_M->dwork.UnitDelay_DSTATE[1] = rtU_MtrIf_IfbkAct[1] * 0.25F + 0.75F *
    pmsmctrl_M->dwork.UnitDelay_DSTATE[1];
  pmsmctrl_M->dwork.UnitDelay_DSTATE[2] = rtU_MtrIf_IfbkAct[2] * 0.25F + 0.75F *
    pmsmctrl_M->dwork.UnitDelay_DSTATE[2];

  /* Gain: '<S16>/Gain1' incorporates:
   *  Fcn: '<S16>/d'
   *  Fcn: '<S16>/q'
   *  UnitDelay: '<S14>/Unit Delay'
   */
  rtb_Gain1_l_idx_0 = ((sinf(rtb_Max - 2.09439516F) *
                        pmsmctrl_M->dwork.UnitDelay_DSTATE[1] + sinf(rtb_Max) *
                        pmsmctrl_M->dwork.UnitDelay_DSTATE[0]) + sinf(rtb_Max +
    2.09439516F) * pmsmctrl_M->dwork.UnitDelay_DSTATE[2]) * 0.666666687F;
  rtb_Gain1_l_idx_1 = ((cosf(rtb_Max - 2.09439516F) *
                        pmsmctrl_M->dwork.UnitDelay_DSTATE[1] + cosf(rtb_Max) *
                        pmsmctrl_M->dwork.UnitDelay_DSTATE[0]) + cosf(rtb_Max +
    2.09439516F) * pmsmctrl_M->dwork.UnitDelay_DSTATE[2]) * 0.666666687F;

  /* Outputs for Enabled SubSystem: '<S6>/IfbkCtrl' incorporates:
   *  EnablePort: '<S15>/Enable'
   */
  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Constant: '<S13>/Constant'
   *  Inport: '<Root>/MtrIf_CtrlMd'
   */
  if (rtU_MtrIf_CtrlMd >= IfbkCtrlMd) {
    if (!pmsmctrl_M->dwork.IfbkCtrl_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = 0.0F;

      /* InitializeConditions for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = 0.0F;
      pmsmctrl_M->dwork.IfbkCtrl_MODE = true;
    }

    /* Sum: '<S22>/Subtract' incorporates:
     *  Gain: '<S6>/Gain1'
     */
    rtb_Subtract_o = 8.33333302F * pmsmctrl_M->blockIO.DataTypeConversion4 -
      rtb_Gain1_l_idx_1;

    /* Outputs for Enabled SubSystem: '<S15>/mtr_coupling_bemf_comp' incorporates:
     *  EnablePort: '<S19>/Enable'
     */
    /* SignalConversion: '<S15>/OutportBufferForvdq0_ctrl' incorporates:
     *  Constant: '<S15>/Constant2'
     *  Constant: '<S17>/Constant'
     *  Constant: '<S18>/Constant'
     *  Constant: '<S6>/Constant'
     *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S21>/Discrete-Time Integrator'
     *  DiscreteIntegrator: '<S23>/Discrete-Time Integrator'
     *  Gain: '<S19>/Gain'
     *  Gain: '<S19>/Gain1'
     *  Gain: '<S19>/Gain2'
     *  Gain: '<S19>/Gain3'
     *  Product: '<S19>/Product'
     *  Product: '<S19>/Product1'
     *  Product: '<S20>/Product'
     *  Product: '<S22>/Product'
     *  Sum: '<S15>/Add'
     *  Sum: '<S15>/Add1'
     *  Sum: '<S19>/Add1'
     *  Sum: '<S20>/Add'
     *  Sum: '<S20>/Subtract'
     *  Sum: '<S22>/Add'
     */
    pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[0] = ((0.0F -
      rtb_Gain1_l_idx_0) * 0.28F +
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy) +
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k * rtb_Gain1_l_idx_1 *
      -0.00168F;
    pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[1] = (rtb_Gain1_l_idx_0 *
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k * 12.0F + 571.428589F *
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k) * 0.00014F + (0.28F *
      rtb_Subtract_o + pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n);

    /* End of Outputs for SubSystem: '<S15>/mtr_coupling_bemf_comp' */
    pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[2] = 0.0F;

    /* Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S18>/Constant1'
     *  Product: '<S22>/Product1'
     */
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n += rtb_Subtract_o * 500.0F
      * 3.33333337E-5F;
    if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n >= 12.0F) {
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = 12.0F;
    } else {
      if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n <= -12.0F) {
        pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_n = -12.0F;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S23>/Discrete-Time Integrator' */

    /* Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' incorporates:
     *  Constant: '<S17>/Constant1'
     *  Constant: '<S6>/Constant'
     *  Product: '<S20>/Product1'
     *  Sum: '<S20>/Subtract'
     */
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy += (0.0F -
      rtb_Gain1_l_idx_0) * 500.0F * 3.33333337E-5F;
    if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy >= 12.0F) {
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = 12.0F;
    } else {
      if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy <= -12.0F) {
        pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_oy = -12.0F;
      }
    }

    /* End of Update for DiscreteIntegrator: '<S21>/Discrete-Time Integrator' */
  } else {
    if (pmsmctrl_M->dwork.IfbkCtrl_MODE) {
      pmsmctrl_M->dwork.IfbkCtrl_MODE = false;
    }
  }

  /* End of RelationalOperator: '<S13>/Compare' */
  /* End of Outputs for SubSystem: '<S6>/IfbkCtrl' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S8>/Zero'
   *  Gain: '<S6>/Gain5'
   *  Inport: '<Root>/MtrIf_CtrlMd'
   *  RelationalOperator: '<S3>/Compare'
   */
  if (rtU_MtrIf_CtrlMd > PwmCtrlMd) {
    rtb_Subtract_o = 0.010416667F *
      pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[0];
    rtb_pwm_dc_idx_1 = 0.010416667F *
      pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[1];
    rtb_Gain1_l_idx_0 = 0.010416667F *
      pmsmctrl_M->blockIO.OutportBufferForvdq0_ctrl[2];
  } else {
    rtb_Subtract_o = 0.0F;
    rtb_pwm_dc_idx_1 = pmsmctrl_M->blockIO.DataTypeConversion4;
    rtb_Gain1_l_idx_0 = 0.0F;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Saturate: '<S1>/Saturation1' */
  rtb_pwm_dc = rtb_Subtract_o;
  if (rtb_Subtract_o > 1.0F) {
    rtb_pwm_dc = 1.0F;
  } else {
    if (rtb_Subtract_o < -1.0F) {
      rtb_pwm_dc = -1.0F;
    }
  }

  rtb_Subtract_o = rtb_pwm_dc;
  rtb_pwm_dc = rtb_pwm_dc_idx_1;
  if (rtb_pwm_dc_idx_1 > 1.0F) {
    rtb_pwm_dc = 1.0F;
  } else {
    if (rtb_pwm_dc_idx_1 < -1.0F) {
      rtb_pwm_dc = -1.0F;
    }
  }

  rtb_pwm_dc_idx_1 = rtb_pwm_dc;
  rtb_pwm_dc = rtb_Gain1_l_idx_0;
  if (rtb_Gain1_l_idx_0 > 1.0F) {
    rtb_pwm_dc = 1.0F;
  } else {
    if (rtb_Gain1_l_idx_0 < -1.0F) {
      rtb_pwm_dc = -1.0F;
    }
  }

  /* End of Saturate: '<S1>/Saturation1' */

  /* Fcn: '<S5>/a' */
  rtb_Gain1_l_idx_0 = (sinf(rtb_Max) * rtb_Subtract_o + cosf(rtb_Max) *
                       rtb_pwm_dc_idx_1) + rtb_pwm_dc;

  /* Fcn: '<S5>/b' */
  *rtY_MtrIf_TrqAct = (sinf(rtb_Max - 2.09439516F) * rtb_Subtract_o + cosf
                       (rtb_Max - 2.09439516F) * rtb_pwm_dc_idx_1) + rtb_pwm_dc;

  /* Fcn: '<S5>/c' */
  rtb_Max = (sinf(rtb_Max + 2.09439516F) * rtb_Subtract_o + cosf(rtb_Max +
              2.09439516F) * rtb_pwm_dc_idx_1) + rtb_pwm_dc;

  /* Outport: '<Root>/MtrIf_ModWave' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   */
  rtY_MtrIf_ModWave[0] = rtb_Gain1_l_idx_0;
  rtY_MtrIf_ModWave[1] = *rtY_MtrIf_TrqAct;
  rtY_MtrIf_ModWave[2] = rtb_Max;

  /* Gain: '<S9>/Gain' incorporates:
   *  MinMax: '<S9>/Max'
   *  MinMax: '<S9>/Max1'
   *  Sum: '<S9>/Add'
   */
  rtb_Subtract_o = (fmaxf(fmaxf(rtb_Gain1_l_idx_0, *rtY_MtrIf_TrqAct), rtb_Max)
                    + fminf(fminf(rtb_Gain1_l_idx_0, *rtY_MtrIf_TrqAct), rtb_Max))
    * 0.5F;

  /* Outport: '<Root>/MtrIf_PwmDc' incorporates:
   *  Constant: '<S9>/Constant'
   *  Constant: '<S9>/Constant1'
   *  DataTypeConversion: '<S9>/Data Type Conversion'
   *  Gain: '<S9>/Gain1'
   *  Gain: '<S9>/Gain2'
   *  Product: '<S9>/Divide'
   *  Sum: '<S9>/Add1'
   *  Sum: '<S9>/Subtract'
   */
  rtY_MtrIf_PwmDc[0] = ((rtb_Gain1_l_idx_0 - rtb_Subtract_o) / 0.5F *
                        1.15470052F + 1.0F) * 0.5F;
  rtY_MtrIf_PwmDc[1] = ((*rtY_MtrIf_TrqAct - rtb_Subtract_o) / 0.5F *
                        1.15470052F + 1.0F) * 0.5F;
  rtY_MtrIf_PwmDc[2] = ((rtb_Max - rtb_Subtract_o) / 0.5F * 1.15470052F + 1.0F) *
    0.5F;

  /* Sum: '<S4>/Add3' incorporates:
   *  DiscreteIntegrator: '<S12>/Discrete-Time Integrator'
   */
  rtb_error -= pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke;

  /* Sum: '<S4>/Add2' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   *  Gain: '<S4>/Gain3'
   */
  rtb_Max = 6000.0F * rtb_error +
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k;

  /* Gain: '<S1>/Gain2' */
  *rtY_MtrIf_TrqAct = 0.12F * rtb_Gain1_l_idx_1;

  /* DataTypeConversion: '<S1>/Data Type Conversion1' incorporates:
   *  DiscreteIntegrator: '<S11>/Discrete-Time Integrator'
   */
  pmsmctrl_M->blockIO.DataTypeConversion1 =
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k;

  /* Update for DiscreteIntegrator: '<S1>/Accumulator' incorporates:
   *  Constant: '<S1>/Constant'
   */
  pmsmctrl_M->dwork.Accumulator_DSTATE += 3.33333337E-5F;

  /* Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' incorporates:
   *  Constant: '<S1>/ObsInertia'
   *  DiscreteIntegrator: '<S10>/Discrete-Time Integrator'
   *  Gain: '<S4>/Gain1'
   *  Product: '<S4>/Product'
   *  Sum: '<S4>/Add'
   *  Sum: '<S4>/Add1'
   */
  pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k += ((1.2E+7F * rtb_error +
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p) + *rtY_MtrIf_TrqAct /
    0.00019F) * 3.33333337E-5F;
  if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k >= 1.0E+7F) {
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = 1.0E+7F;
  } else {
    if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k <= -1.0E+7F) {
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_k = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S11>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */
  pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke += 3.33333337E-5F * rtb_Max;
  if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke >= 1.0E+7F) {
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = 1.0E+7F;
  } else {
    if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke <= -1.0E+7F) {
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTAT_ke = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S12>/Discrete-Time Integrator' */

  /* Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S4>/Gain'
   */
  pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p += 8.0E+9F * rtb_error *
    3.33333337E-5F;
  if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p >= 1.0E+7F) {
    pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = 1.0E+7F;
  } else {
    if (pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p <= -1.0E+7F) {
      pmsmctrl_M->dwork.DiscreteTimeIntegrator_DSTATE_p = -1.0E+7F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S10>/Discrete-Time Integrator' */
  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Trig_Pmsm_Foc_at_outport_1' */
}

/* Model initialize function */
void Pmsm_InitCtrl(RT_MODEL *const pmsmctrl_M)
{
  (void) (pmsmctrl_M);

  /* (no initialization code required) */
  UNUSED_PARAMETER(pmsmctrl_M);
}
