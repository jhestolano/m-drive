#ifndef _MTRIF_H_
#define _MTRIF_H_

#include <stdint.h>
#include "adc.h"
#include "app.h"
#include "cmsis_gcc.h"
#include "pmsm_ctrl.h"
#include "MtrCtrlMd_T.h"

#define MTRIF_ST_OK      (0)
#define MTRIF_ST_IDLE    (1)
#define MTRIF_ST_BUSY    (2)
#define MTRIF_ST_DONE    (3)
#define MTRIF_ST_NOT_OK  (4)
#define MTRIF_ST_ERR     (5)

#define MTRIF_TO_MILLIS (1.0e3f) /* Convert to millis (amps, volts, etc.) */
#define MTRIF_FROM_MILLIS (1.0e-3f) /* Convert back from millis. */

typedef enum {
  CAL_JOB_NONE = 0,
  CAL_JOB_ENC_OFS,
  CAL_JOB_RES,
  CAL_JOB_IND,
  CAL_JOB_IFBK_OFS,
  CAL_JOB_MECH_PARAMS,
  CAL_JOB_IFBK_CTRL,
  CAL_JOB_MOTN_CTRL,
  CAL_JOB_MAX,
} CalJob_T;

typedef enum {
  CTRL_JOB_NONE = 0,
  CTRL_JOB_PWM,
  CTRL_JOB_IFBK,
  CTRL_JOB_SPD,
  CTRL_JOB_POS,
  CTRL_JOB_MAX,
} CtrlJob_T;

typedef void (*MtrIfJobCb)(CalJob_T job);

typedef struct MtrIfCtrlJob_tag {
  CtrlJob_T job;
  float tgt;
} MtrIfCtrlJob_S;

typedef struct MtrIfCalJob_tag {
  CalJob_T job;
  MtrIfJobCb on_err;
  MtrIfJobCb on_done;
} MtrIfCalJob_S;

typedef struct MtrStats_tag {
  uint32_t ctrl_fast_cnt;
} MtrStats_S;

typedef DBG_Struct_type MtrDbg_S;

typedef Calib_ParamType MtrParams_S;

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

void MtrIf_SetCtlMd(MtrCtrlMd_T ctlmd, float* target);

void MtrIf_GetCtlMd(MtrCtrlMd_T* ctlmd, float* target);

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

void MtrIf_GetStats(MtrStats_S* stats);

int32_t MtrIf_CalJobReq(MtrIfCalJob_S* job);

int32_t MtrIf_CtrlJobReq(MtrIfCtrlJob_S* job);

int32_t MtrIf_WaitPending(void);

int32_t MtrIf_GetJobStat(void);

#endif // _MTRIF_H_
