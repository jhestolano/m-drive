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

#define MTRIF_CTL_SPD_TS (0.05f) /* Speed loop settling time. */
#define MTRIF_CTL_POS_TS (0.3f) /* Position loop settling time. */

#define MTRIF_POS_PH (PwmChA_E)
#define MTRIF_NEG_PH (PwmChC_E)

#define MTRIF_POS_PH_IFBK (IfbkPhA_E)
#define MTRIF_NEG_PH_IFBK (IfbkPhC_E)

/* Might need to add other interrupts that might share data. */
#define MTRIF_LOCK() __disable_irq()
#define MTRIF_UNLOCK() __enable_irq()

#define MTRIF_TS (1e3) /* Execution rate of Motor Interface. */

#define MTRIF_RPM_RES (1000) /* Represents a resolution of 0.001 RPM */

/* Transforms 0.1 deg/s to 0.001 RPM units */
#define MTRIF_TO_RPM ((60 * MTRIF_RPM_RES / (360 * (APP_PARAMS_POS_RES))))

void MtrIf_Init(void);

void MtrIf_SetVin(float mtrvin);

float MtrIf_GetVin(void);

float MtrIf_GetIfbk(void);

float MtrIf_GetPos(void);

float MtrIf_GetSpd(void);

void MtrIf_Ctl(void);

float MtrIf_GetPosEst(void);

void MtrIf_SetIfbk(float ifbktgt);

float MtrIf_GetIfbkTgt(void);

void MtrIf_SetTgt(float tgt);

float MtrIf_GetTgt(void);

void MtrIf_SetCtlMd(MtrCtlMd_T ctlmd);

MtrCtlMd_T MtrIf_GetCtlMd(void);

void MtrIf_SetTgt(float tgt);

#endif // _MTRIF_H_
