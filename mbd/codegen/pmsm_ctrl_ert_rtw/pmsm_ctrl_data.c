/*
 * File: pmsm_ctrl_data.c
 *
 * Code generated for Simulink model 'pmsm_ctrl'.
 *
 * Model version                  : 1.766
 * Simulink Coder version         : 8.14 (R2018a) 06-Feb-2018
 * C/C++ source code generated on : Sat Jul 31 08:41:10 2021
 */

#include "pmsm_ctrl.h"
#include "pmsm_ctrl_private.h"

/* Constant parameters (default storage) */
const ConstP rtConstP = {
  /* Pooled Parameter (Expression: [ 1   0   1; -1/2  sqrt(3)/2   1; -1/2  -sqrt(3)/2  1 ] )
   * Referenced by:
   *   '<S20>/Gain3'
   *   '<S61>/Gain3'
   */
  { 1.0F, -0.5F, -0.5F, 0.0F, 0.866025388F, -0.866025388F, 1.0F, 1.0F, 1.0F },

  /* Computed Parameter: Gain3_Gain
   * Referenced by: '<S57>/Gain3'
   */
  { 1.0F, 0.0F, 0.5F, -0.5F, 0.866025388F, 0.5F, -0.5F, -0.866025388F, 0.5F }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
