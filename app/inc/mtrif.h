#ifndef _MTRIF_H_
#define _MTRIF_H_

#include <stdint.h>
#include "adc.h"
#include "app.h"
#include "cmsis_gcc.h"

typedef enum {
  MtrCtlMdPos_E = 0,
  MtrCtlMdSpd_E,
  MtrCtlMdIfbk_E,
  MtrCtlMdPwm_E,
  MtrCtlMdInv_E = 255
} MtrCtlMd_T;

typedef struct MtrParams_tag {
  float ind; /* Inductance. */
  float res; /* Resistance. */
  float k_trq; /* Torque constant. */
  float k_frc; /* Friction constant. */
  int32_t ppoles; /* Pole paris. */
  int32_t enc_ofs; /* Encoder offset. */
  float inertia; /* Rotor inertia. */
  float ifbk_ofs[3]; /* Current offsets. */
} MtrParams_S;

typedef struct MtrDbg_tag {
  float i_abc_lpf[3];
  float e_angl;
  float i_dq0[3];
} MtrDbg_S;

#define MTRIF_POS_PH (PwmChA_E)
#define MTRIF_NEG_PH (PwmChC_E)

#define MTRIF_POS_PH_IFBK (IfbkPhA_E)
#define MTRIF_NEG_PH_IFBK (IfbkPhC_E)

/* Might need to add other interrupts that might share data. */
#define MTRIF_LOCK() __disable_irq()
#define MTRIF_UNLOCK() __enable_irq()

#define MTRIF_RPM_RES (1000) /* Represents a resolution of 0.001 RPM */

/* Transforms 0.1 deg/s to 0.001 RPM units */
#define MTRIF_TO_RPM ((60 * MTRIF_RPM_RES / (360 * (APP_PARAMS_POS_RES))))

void MtrIf_Init(void);

void MtrIf_CtrlSlow(void);

void MtrIf_CtrlFast(void);

void MtrIf_SetVin(float mtrvin);

void MtrIf_GetVin(float* vin);

void MtrIf_GetIfbk(float* ifbk);

void MtrIf_GetIfbkDq(float* ifbk);

float MtrIf_GetPos(void);

float MtrIf_GetSpd(void);

float MtrIf_GetPosEst(void);

void MtrIf_SetIfbk(float ifbktgt);

float MtrIf_GetTgt(void);

void MtrIf_SetCtlMd(MtrCtlMd_T ctlmd);

MtrCtlMd_T MtrIf_GetCtlMd(void);

void MtrIf_SetTgt(float tgt);

void MtrIf_SetPwmDc(float* pwm_a);

void MtrIf_GetPwmDc(float* pwm_a);

void MtrIf_GetPwmDq(float* pwm_dq);

void MtrIf_GetModWave(float* mod_wave);

float MtrIf_GetIfbkPh(IfbkPh_E ph); 

float MtrIf_GetPwmDcCh(PwmCh_E ch);

float MtrIf_GetTrq(void);

void MtrIf_GetMtrParams(MtrParams_S* params);

void MtrIf_GetDbg(MtrDbg_S* dbg);

#endif // _MTRIF_H_
