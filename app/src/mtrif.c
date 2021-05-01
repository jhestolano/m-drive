#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "mtrif.h"
#include "app.h"
#include "adc.h"
#include "rtwtypes.h"
#include "pmsmctrl.h"
#include "stdlib.h"
#include "gpio.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MTRIF_TO_DEG (0.1f) /* App layer position resolution is 0.1 degrees
                               represented as int. For example, a value of
                               13 represents 1.3 degrees. */
#define MTRIF_TO_MILLIS (1.0e3f) /* Convert to millis (amps, volts, etc.) */
#define MTRIF_FROM_MILLIS (1.0e-3f) /* Convert back from millis. */

#define MTRIF_TO_PWM_DC(x) ((uint32_t)((x) * (float)APP_PWM_MAX_DC)) /* To timer base */

typedef struct MtrIf_tag {

  float mtr_spd; /* Actual motor speed. */
 
  float mtr_spd_fil; /* Actual motor speed after filter. */

  float dist_trq; /* Disturbance torque estimation. */

  float mtr_trq_act; /* Motor unfiltered instantaneous torque */

  float pos_est; /* Position estimation by dustrbance observer. */

  float pwm_rqst[APP_PARAMS_MOTOR_PHASES]; /* Output of 30khz controller. */

  float ifbk_tgt; /* Output of 1khz controller. */

  float motn_ctrl_cmd; /* Output of motion controller */

  float ifbk_act[APP_PARAMS_MOTOR_PHASES]; /* Holds the motor currents. */

  float pwm_mod_wave[APP_PARAMS_MOTOR_PHASES]; /* Holds the modulation wave. */

  float mtr_tgt; /* Target for 1khz controller. The meaning (units) of this
                    depends on the control mode: Position, Speed or Current
                    control mode. */

  uint8_t ctrl_fast_is_init; /* Indicates if 30khz controller is initialized.
                                The controller algorithm will not run until
                                this flag is set.*/

  uint8_t ctrl_is_init; /* Indicates if 1khz controller is initialized.
                           The controller will not run until this flag
                           is set.*/

  MtrCtlMd_T ctrl_md; /* Position, Speed or Current control mode. */


} MtrIf_S;

static volatile MtrIf_S _mtr_if_s;

static RT_MODEL _pmsmctrl_obj_s;

/* Function called within interrupt context from ADC. */
static void _mtr_if_adc_isr_callback(void *params) {
  (void)params;
  /* This is where the fast control task needs to be called. */
  /* This function is attached to the ADC isr. */
  MtrIf_Foc();

}

void MtrIf_Init(void) {
  MTRIF_LOCK();
  ADC_AttachISRCallback(_mtr_if_adc_isr_callback);
  /* Control task at 30khz is ready. */
  _mtr_if_s.ctrl_fast_is_init = true;
  /* Control task at 1khz is ready. */
  _mtr_if_s.ctrl_is_init = true;

  Pmsm_InitCtrl(&_pmsmctrl_obj_s);

  MTRIF_UNLOCK();
  App_ArmMotor();
}

void MtrIf_SetVin(float mtrvin) {
  int32_t vin = (int32_t)(mtrvin * MTRIF_TO_MILLIS);
  if(vin > 0) {
    App_SetPwmVoltage(MTRIF_POS_PH, (uint32_t)vin);
    App_SetPwmVoltage(MTRIF_NEG_PH, 0);
  } else if(vin < 0){
    App_SetPwmVoltage(MTRIF_POS_PH, 0);
    App_SetPwmVoltage(MTRIF_NEG_PH, (uint32_t)(-vin));
  } else {
    App_SetPwmVoltage(MTRIF_POS_PH, 0);
    App_SetPwmVoltage(MTRIF_NEG_PH, 0);
  }
}

void MtrIf_SetPwm(float* pwm) {
  for(uint8_t i = 0; i < (uint8_t)PwmChMax_E; i++) {
    pwm[i] = MIN(-1.0f, pwm[i]);
    pwm[i] = MAX(1.0f, pwm[i]);
    App_SetPwmDutyCycle((PwmCh_E)i, MTRIF_TO_PWM_DC(pwm[i]));
  }
}

float MtrIf_GetVin(void) {
  int32_t vin = (int32_t)App_GetPwmVoltage(MTRIF_POS_PH)
               -(int32_t)App_GetPwmVoltage(MTRIF_NEG_PH);
  return (float)vin * (MTRIF_FROM_MILLIS);
}

float MtrIf_GetIfbk(void) {
  int32_t ret;
  int32_t ifbkpos = App_GetCurrent(MTRIF_POS_PH_IFBK);
  int32_t ifbkneg = App_GetCurrent(MTRIF_NEG_PH_IFBK);
  int32_t vin = MtrIf_GetVin();
  int32_t abs_vin = (vin >= 0) ? vin : -vin;
  if (abs_vin >= APP_PARAMS_RSHUNT_NOT_READABLE) {
    /* In this scenario, one of the phases (the one powered over the threshold) */
    /* is not readable. To overcome this, read the opposite phase. */
    if (vin >= 0) {
      ret = ifbkneg;
    } else {
      ret = -ifbkpos;
    }
  } else {
    /* When both phases are readable, take average of both. */
    ret = (ifbkneg - ifbkpos) / 2;
  }
  return (float)ret * MTRIF_FROM_MILLIS;
}

float MtrIf_GetPos(void) {
  return (float)App_GetPosition() * (MTRIF_TO_DEG);
}

float MtrIf_GetPosEst(void) {
  float pos_est;
  MTRIF_LOCK();
  pos_est = _mtr_if_s.pos_est;
  MTRIF_UNLOCK();
  return pos_est;
}

float MtrIf_GetSpd(void) {
  float spd;
  MTRIF_LOCK();
  spd = _mtr_if_s.mtr_spd;
  MTRIF_UNLOCK();
  return spd;
}

void MtrIf_SetIfbkTgt(float ifbktgt) {
  MTRIF_LOCK();
  _mtr_if_s.ifbk_tgt = (float)ifbktgt;
  MTRIF_UNLOCK();
}

float MtrIf_GetIfbkTgt(void) {
  float ifbk_tgt;
  MTRIF_LOCK();
  ifbk_tgt = _mtr_if_s.ifbk_tgt;
  MTRIF_UNLOCK();
  return ifbk_tgt;
}

MtrCtlMd_T MtrIf_GetCtlMd(void) {
  return _mtr_if_s.ctrl_md;
}

void MtrIf_SetCtlMd(MtrCtlMd_T ctrl_md) {
  _mtr_if_s.ctrl_md = ctrl_md;
}

void MtrIf_SetTgt(float tgt) {
  _mtr_if_s.mtr_tgt = tgt;
}

void MtrIf_Foc(void) {
  Trig_Pmsm_Foc(
    &_pmsmctrl_obj_s,
    (real32_T*)_mtr_if_s.ifbk_act,
    PwmCtrlMd,
    (real32_T*)_mtr_if_s.pwm_mod_wave,
    (real32_T*)_mtr_if_s.pwm_rqst,
    (real32_T*)&_mtr_if_s.mtr_trq_act
  );

  /* Immediately update duty cycle. */
  MtrIf_SetPwm(_mtr_if_s.pwm_rqst);
}

void MtrIf_MotnCtrl(void) {
  Trig_Pmsm_MotnCtrl(
    &_pmsmctrl_obj_s,
    App_GetEncCnts(),
    PwmCtrlMd,
    (real32_T)0.3f, /* Target duty cycle. Control will ramp up over 1s. */
    (real32_T*)&_mtr_if_s.mtr_spd
  );

}
