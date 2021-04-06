/*
 * ctrl.c
 *
 * Code generation for model "ctrl".
 *
 * Model version              : 1.904
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 *
 */

#include "ctrl.h"
#include "ctrl_private.h"

const DBG_BUS ctrl_rtZDBG_BUS = {
  0.0F,                                /* IfbkTgt */
  0.0F,                                /* Lest */
  0.0F,                                /* Rest */
  0.0F,                                /* KTrqEst */
  0.0F,                                /* IfbkOfs */
  0.0F,                                /* KFrcEst */
  0.0F,                                /* JEst */
  0.0F,                                /* IfbkSteady */
  0.0F,                                /* IfbkMax */
  0.0F,                                /* SpdMax */
  ErrIndTooSmall                       /* Status */
} ;                                    /* DBG_BUS ground */

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void Ctrl_Slow(void)
{
  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Slow_at_outport_1' incorporates:
   *  SubSystem: '<Root>/ctrl_slow'
   */

  /* Inport: '<Root>/MtrIf_Tgt' incorporates:
   *  Inport: '<Root>/MtrIf_Pos'
   *  Outport: '<Root>/DBG_BUS_OUT'
   *  Outport: '<Root>/MtrIf_DistTrqEst'
   *  Outport: '<Root>/MtrIf_IfbkTgt'
   *  Outport: '<Root>/MtrIf_PosEst'
   *  Outport: '<Root>/MtrIf_Ref'
   *  Outport: '<Root>/MtrIf_SpdEst'
   */
  ctrl_slow(rtU.MtrIf_Tgt, rtU.MtrIf_Pos, rtDW.MtrSpdOut, rtDW.Product1,
            rtDW.DiscreteTimeIntegrator, rtDW.Switch1, &rtY.DBG_BUS_OUT,
            &rtY.MtrIf_IfbkTgt, &rtY.MtrIf_SpdEst, &rtY.MtrIf_Ref,
            &rtY.MtrIf_DistTrqEst, &rtY.MtrIf_PosEst, &rtDW.ctrl_slow_e,
            &rtP.ctrl_slow_e);

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Slow_at_outport_1' */
}

/* Model step function */
void Ctrl_Fast(void)
{
  /* RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Fast_at_outport_1' incorporates:
   *  SubSystem: '<Root>/ctrl_fast'
   */

  /* Inport: '<Root>/MtrIf_Pos' incorporates:
   *  Inport: '<Root>/MtrIf_CtrlMd'
   *  Inport: '<Root>/MtrIf_IfbkAct'
   *  Inport: '<Root>/MtrIf_SpdSns'
   *  Outport: '<Root>/DBG_BUS_OUT'
   *  Outport: '<Root>/MtrIf_CtrlCmd'
   *  Outport: '<Root>/MtrIf_IfbkTgt'
   */
  ctrl_fast(rtU.MtrIf_Pos, rtU.MtrIf_IfbkAct, rtY.MtrIf_IfbkTgt,
            rtU.MtrIf_CtrlMd, rtU.MtrIf_SpdSns, &rtDW.MtrSpdOut, &rtDW.Product1,
            &rtDW.DiscreteTimeIntegrator, &rtDW.Switch1, &rtY.MtrIf_CtrlCmd,
            &rtY.DBG_BUS_OUT, &rtDW.ctrl_fast_f, &rtP.ctrl_fast_f);

  /* End of Outputs for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Fast_at_outport_1' */
}

/* Model initialize function */
void Ctrl_Init(void)
{
  /* Registration code */

  /* states (dwork) */
  {
    rtDW.ctrl_fast_f.status = ErrIndTooSmall;
  }

  /* external outputs */
  rtY.DBG_BUS_OUT = ctrl_rtZDBG_BUS;

  /* SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Slow_at_outport_1' incorporates:
   *  SubSystem: '<Root>/ctrl_slow'
   */

  /* SystemInitialize for Outport: '<Root>/MtrIf_IfbkTgt' incorporates:
   *  Outport: '<Root>/MtrIf_DistTrqEst'
   *  Outport: '<Root>/MtrIf_PosEst'
   *  Outport: '<Root>/MtrIf_Ref'
   *  Outport: '<Root>/MtrIf_SpdEst'
   */
  ctrl_slow_Init(&rtY.MtrIf_IfbkTgt, &rtY.MtrIf_SpdEst, &rtY.MtrIf_Ref,
                 &rtY.MtrIf_DistTrqEst, &rtY.MtrIf_PosEst, &rtDW.ctrl_slow_e,
                 &rtP.ctrl_slow_e);

  /* End of SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Slow_at_outport_1' */

  /* SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Fast_at_outport_1' incorporates:
   *  SubSystem: '<Root>/ctrl_fast'
   */

  /* SystemInitialize for Outport: '<Root>/MtrIf_CtrlCmd' incorporates:
   *  Outport: '<Root>/DBG_BUS_OUT'
   */
  ctrl_fast_Init(&rtDW.MtrSpdOut, &rtDW.Product1, &rtDW.DiscreteTimeIntegrator,
                 &rtDW.Switch1, &rtY.MtrIf_CtrlCmd, &rtY.DBG_BUS_OUT,
                 &rtDW.ctrl_fast_f, &rtP.ctrl_fast_f);

  /* End of SystemInitialize for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_Ctrl_Fast_at_outport_1' */
}
