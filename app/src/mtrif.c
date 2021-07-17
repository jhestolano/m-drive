#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "mtrif.h"
#include "stdlib.h"
#include "gpio.h"
#include "pmsm_ctrl.h"
#include "pmsm_ctrl_types.h"

#define MTRIF_TO_DEG (0.1f) /* App layer position resolution is 0.1 degrees
                               represented as int. For example, a value of
                               13 represents 1.3 degrees. */
#define MTRIF_TO_MILLIS (1.0e3f) /* Convert to millis (amps, volts, etc.) */
#define MTRIF_FROM_MILLIS (1.0e-3f) /* Convert back from millis. */

typedef struct MtrIf_State_tag {
  uint8_t is_init;
  uint8_t cal_done;
  float pwm_dc[3];
  float mod_wave[3];
  float mtr_ifbk[3];
  float mtr_spd;
  float mtr_trq;
  float pwm_dq[2];
  float ifbk_dq[2];
} MtrIf_State_S;

MtrIf_State_S _mtr_if_s = {0};

/* Function called within interrupt context from ADC. */
static void _mtr_if_adc_isr_callback(void *params) {

  if(_mtr_if_s.is_init) {
    MtrIf_CtrlFast();
  }

  /* Heartbeat. */
  /* static int32_t tmr; */
  /* if(tmr++ >= 30e3) { */
  /*   GPIO_LedToggle(); */
  /*   tmr = 0; */
  /* } */

}

RT_MODEL pmsm_ctrl_obj;

void MtrIf_Init(void) {
  MTRIF_LOCK();

  ADC_AttachISRCallback(_mtr_if_adc_isr_callback);

  Trig_Pmsm_Init(&pmsm_ctrl_obj);

  _mtr_if_s.is_init = true;

  MTRIF_UNLOCK();
  App_ArmMotor();
}

void MtrIf_CtrlSlow(void) {

  boolean_T cal_actv;
  Trig_Pmsm_CtrlMgr(&pmsm_ctrl_obj);
  Trig_Pmsm_Cal(&pmsm_ctrl_obj, &cal_actv);
  Trig_Pmsm_MotnCtrl(&pmsm_ctrl_obj);

}

void MtrIf_CtrlFast(void) {

  static uint8_t st = 0;
  static uint32_t tmr = 0;
  MtrCtrlMd_T ctrl_md;
  MtrCtrlCal_T cal_rqst;
  float ctrl_tgt[3] = {0.f};

  switch(st) {
    case 0: /* Offset calibration */
    ctrl_md = CTRL_MD_CAL;
    cal_rqst = CAL_ENC_OFS;
    tmr++;
    if(tmr >= 60e3) {
      st++;
      tmr = 0;
    }
    break;

  /*   case 1: /1* Inductance calibration *1/ */
  /*   ctrl_md = CTRL_MD_CAL; */
  /*   cal_rqst = CAL_IND_ID; */
  /*   tmr++; */
  /*   if(tmr >= 60e3) { */
  /*     st++; */
  /*     tmr = 0; */
  /*   } */
  /*   break; */

  /*   case 2: /1* Resistance calibration *1/ */
  /*   ctrl_md = CTRL_MD_CAL; */
  /*   cal_rqst = CAL_RES_ID; */
  /*   tmr++; */
  /*   if(tmr >= 60e3) { */
  /*     st++; */
  /*     tmr = 0; */
  /*   } */
  /*   break; */

  /*   case 3: /1* Ifbk offset calibration *1/ */
  /*   ctrl_md = CTRL_MD_CAL; */
  /*   cal_rqst = CAL_IFBK_OFS; */
  /*   tmr++; */
  /*   if(tmr >= 60e3) { */
  /*     st++; */
  /*     tmr = 0; */
  /*   } */
  /*   break; */

    default: /* Just spin it. */
    ctrl_md = CTRL_MD_DQ_PWM;
    ctrl_tgt[0] = 0.0f;
    ctrl_tgt[1] = 0.20; /* Q-component */
    ctrl_tgt[2] = 0.0f;
    cal_rqst = CAL_NONE;
    tmr = 0;
    st = 255; /* Stay here @ default */
  }


  MtrIf_GetIfbk(&_mtr_if_s.mtr_ifbk[0]);

  Trig_Pmsm_SetIn(
    &pmsm_ctrl_obj,
    App_GetEncCnt(), /* Encoder counts */
    (real32_T*)&_mtr_if_s.mtr_ifbk[0], /* Array with phase currents. */
    (real32_T)0.0f, /* Speed sensor */
    ctrl_md, /* Control mode */
    (real32_T*)&ctrl_tgt, /* Control target. */
    cal_rqst /* Calibration request. */
  );

  Trig_Pmsm_Foc(&pmsm_ctrl_obj);

  Trig_Pmsm_GetOut(
    &pmsm_ctrl_obj,
    (real32_T*)&_mtr_if_s.pwm_dc[0],
    (real32_T*)&_mtr_if_s.mod_wave[0],
    (real32_T*)&_mtr_if_s.mtr_trq,
    (real32_T*)&_mtr_if_s.mtr_spd,
    (real32_T*)&_mtr_if_s.pwm_dq,
    (real32_T*)&_mtr_if_s.ifbk_dq
  );

  MtrIf_SetPwmDc(&_mtr_if_s.pwm_dc[0]);
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

void MtrIf_SetPwmDc(float* pwm_a) {
  if(pwm_a) {
    for(size_t i = 0; i < PwmChMax_E; i++) {
      App_SetPwmDutyCycle((PwmCh_E)i, pwm_a[i] * (float)APP_PWM_MAX_DC);
    }
  }
}

void MtrIf_GetPwmDc(float* pwm_a) {
  if(pwm_a) {
    for(size_t i = 0; i < PwmChMax_E; i++) {
      pwm_a[i] = (float)App_GetPwmDutyCycle((PwmCh_E)i) / (float)APP_PWM_MAX_DC;
    }
  }
}

float MtrIf_GetPwmDcCh(PwmCh_E ch) {
    return (float)App_GetPwmDutyCycle((PwmCh_E)ch) / (float)APP_PWM_MAX_DC;
}

void MtrIf_GetVin(float* vin) {
  if(vin) {
    for(size_t i = 0; i < PwmChMax_E; i++) {
      vin[i] = MTRIF_FROM_MILLIS * (float)App_GetPwmVoltage((PwmCh_E)i);
    }
  }
}


void MtrIf_GetIfbk(float* ifbk) {
  if(ifbk) {
    for(size_t i = 0; i < IfbkPhMax_E; i++) {
      ifbk[i] = MTRIF_FROM_MILLIS * (float)App_GetCurrent((IfbkPh_E)i);
    }
  }
}

void MtrIf_GetIfbkDq(float* ifbk) {
  if(ifbk) {
    MTRIF_LOCK();
    ifbk[0] = _mtr_if_s.ifbk_dq[0];
    ifbk[1] = _mtr_if_s.ifbk_dq[1];
    MTRIF_UNLOCK();
  }
}

void MtrIf_GetPwmDq(float* pwm_dq) {
  if(pwm_dq) {
    MTRIF_LOCK();
    pwm_dq[0] = _mtr_if_s.pwm_dc[0];
    pwm_dq[1] = _mtr_if_s.pwm_dc[1];
    MTRIF_UNLOCK();
  }
}

float MtrIf_GetIfbkPh(IfbkPh_E ph) {
  return MTRIF_FROM_MILLIS * (float)App_GetCurrent(ph);
}

float MtrIf_GetPos(void) {
  return (float)App_GetPosition() * (MTRIF_TO_DEG);
}

float MtrIf_GetPosEst(void) {
  float pos_est;
  MTRIF_LOCK();
  /* pos_est = _mtr_if_s.pos_est; */
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

float MtrIf_GetTrq(void) {
  float trq;
  MTRIF_LOCK();
  trq = _mtr_if_s.mtr_trq;
  MTRIF_UNLOCK();
  return trq;
}

MtrCtlMd_T MtrIf_GetCtlMd(void) {
  /* return _mtr_if_s.ctrl_md; */
  return (MtrCtlMd_T)0;
}

void MtrIf_SetCtlMd(MtrCtlMd_T ctrl_md) {
  /* _mtr_if_s.ctrl_md = ctrl_md; */
}

void MtrIf_SetTgt(float tgt) {
  /* _mtr_if_s.mtr_tgt = tgt; */
}

void MtrIf_GetModWave(float* mod_wave) {
  if(mod_wave) {
    MTRIF_LOCK();
    mod_wave[0] = _mtr_if_s.mod_wave[0];
    mod_wave[1] = _mtr_if_s.mod_wave[1];
    mod_wave[2] = _mtr_if_s.mod_wave[2];
    MTRIF_UNLOCK();
  }
}

void MtrIf_GetMtrParams(MtrParams_S* params) {
  if(params) {
    MTRIF_LOCK();
    params->ind = CalData_L;
    params->res = CalData_Res;
    params->ppoles = CalData_nPoles;
    params->enc_ofs = CalData_EncOfs;
    params->ifbk_ofs[0] = CalData_IfbkOfs_Abc[0];
    params->ifbk_ofs[1] = CalData_IfbkOfs_Abc[1];
    params->ifbk_ofs[2] = CalData_IfbkOfs_Abc[2];
    MTRIF_UNLOCK();
  } 
}

void MtrIf_GetDbg(MtrDbg_S* dbg) {
  if(dbg) {
    MTRIF_LOCK();
    dbg->e_angl = (float)DBG_e_angl;
    dbg->i_abc_lpf[0] = (float)DBG_i_abc_lpf[0];
    dbg->i_abc_lpf[1] = (float)DBG_i_abc_lpf[1];
    dbg->i_abc_lpf[2] = (float)DBG_i_abc_lpf[2];
    dbg->i_dq0[0] = (float)DBG_i_dq0[0];
    dbg->i_dq0[1] = (float)DBG_i_dq0[1];
    dbg->i_dq0[2] = (float)DBG_i_dq0[2];
    MTRIF_UNLOCK();
  }
}
