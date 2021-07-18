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
  int32_t enc_cnts_ofs;
  float i_abc_ofs[3];
  float v_bus_lpf; /* Bus voltage. */
  float ifbk_q_tgt;
  float ifbk_ctrl_v_dq0[3];
  int32_t obs_enc_cnts;
  float obs_load_trq;
} MtrDbg_S;

/* Might need to add other interrupts that might share data. */
#define MTRIF_LOCK() __disable_irq()
#define MTRIF_UNLOCK() __enable_irq()

#define MTRIF_RPM_RES (1000) /* Represents a resolution of 0.001 RPM */

/* Transforms 0.1 deg/s to 0.001 RPM units */
#define MTRIF_TO_RPM ((60 * MTRIF_RPM_RES / (360 * (APP_PARAMS_POS_RES))))

void MtrIf_Init(void);

void MtrIf_CtrlSlow(void);

void MtrIf_CtrlFast(void);

float MtrIf_GetVBus(void);

float MtrIf_GetTemp(void);

void MtrIf_GetIfbkDq(float* ifbk);

float MtrIf_GetPos(void);

float MtrIf_GetSpd(void);

void MtrIf_SetCtlMd(MtrCtlMd_T ctlmd, float* target);

void MtrIf_GetCtlMd(MtrCtlMd_T* ctlmd, float* target);

void MtrIf_SetPwmDc(float* pwm_a);

void MtrIf_GetPwmDc(float* pwm_a);

void MtrIf_GetPwmDq(float* pwm_dq);

void MtrIf_GetModWave(float* mod_wave);

float MtrIf_GetIfbkPh(IfbkPh_E ph); 

void MtrIf_GetIfbk(float* ifbk);

float MtrIf_GetPwmDcCh(PwmCh_E ch);

float MtrIf_GetTrq(void);

void MtrIf_GetMtrParams(MtrParams_S* params);

void MtrIf_GetDbg(MtrDbg_S* dbg);

#endif // _MTRIF_H_
