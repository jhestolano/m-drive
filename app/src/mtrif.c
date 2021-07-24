#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "mtrif.h"
#include "stdlib.h"
#include "gpio.h"
#include "pmsm_ctrl.h"
#include "pmsm_ctrl_types.h"
#include "pwm.h"

#define MTRIF_TO_DEG (0.1f) /* App layer position resolution is 0.1 degrees
                               represented as int. For example, a value of
                               13 represents 1.3 degrees. */
#define MTRIF_TO_MILLIS (1.0e3f) /* Convert to millis (amps, volts, etc.) */
#define MTRIF_FROM_MILLIS (1.0e-3f) /* Convert back from millis. */

extern DBG_Struct_type DBG_Struct;

typedef struct MtrIf_State_tag {
  uint8_t is_init;
  float pwm_dc[3];
  float mod_wave[3];
  float mtr_ifbk[3];
  float mtr_spd;
  float mtr_trq;
  float pwm_dq[2];
  float ifbk_dq[2];
  float ctrl_tgt[3];
  MtrCtrlMd_T ctrl_md_rqst;
  MtrCtrlMd_T ctrl_md_act;
  uint8_t is_busy;
} MtrIf_State_S;

MtrIf_State_S _mtr_if_s = {0};

/* Function called within interrupt context from ADC. */
static void _mtr_if_adc_isr_callback(void *params) {

  if(_mtr_if_s.is_init) {
    MtrIf_CtrlFast();
  }

  /* Heartbeat. */
  /* static int32_t tmr; */
  /* if(tmr++ >= PWM_TMR_FRQ_HZ) { */
  /*   GPIO_LedToggle(); */
  /*   tmr = 0; */
  /* } */

}

RT_MODEL pmsm_ctrl_obj;

void MtrIf_Init(void) {

  bzero(&_mtr_if_s, sizeof(MtrIf_State_S));

  MTRIF_LOCK();

  ADC_AttachISRCallback(_mtr_if_adc_isr_callback);

  Trig_Pmsm_Init(&pmsm_ctrl_obj);

  _mtr_if_s.is_init = true;

  _mtr_if_s.is_busy = false;

  MTRIF_UNLOCK();

  App_ArmMotor();
}

void MtrIf_CtrlSlow(void) {

  Trig_Pmsm_CtrlMgr(&pmsm_ctrl_obj);
  Trig_Pmsm_Cal(&pmsm_ctrl_obj);
  Trig_Pmsm_MotnCtrl(&pmsm_ctrl_obj);

}

void MtrIf_CtrlFast(void) {

  static uint8_t st = 0;
  static uint32_t tmr = 0;
  MtrCtrlMd_T ctrl_md;
  MtrCtrlCal_T cal_rqst;
  float ctrl_tgt[3] = {0.f};

  MtrIf_GetIfbk(&_mtr_if_s.mtr_ifbk[0]);

  switch(st) {
    case 0: /* Offset calibration */
    _mtr_if_s.is_busy = true;
    ctrl_md = CTRL_MD_CAL;
    cal_rqst = CAL_ENC_OFS;
    tmr++;
    if(tmr >= 60e3) {
      st++;
      tmr = 0;
    }
    break;

    case 1: /* Ifbk offset calibration */
    ctrl_md = CTRL_MD_CAL;
    cal_rqst = CAL_IFBK_OFS;
    tmr++;
    if(tmr >= 60e3) {
      st++;
      tmr = 0;
    }
    break;

    /* case 2: /1* Inductance calibration *1/ */
    /* _mtr_if_s.is_busy = true; */
    /* ctrl_md = CTRL_MD_CAL; */
    /* cal_rqst = CAL_IND_ID; */
    /* tmr++; */
    /* if(tmr >= 60e3) { */
    /*   st++; */
    /*   tmr = 0; */
    /* } */
    /* break; */

    /* case 3: /1* Resistance calibration *1/ */
    /* _mtr_if_s.is_busy = true; */
    /* ctrl_md = CTRL_MD_CAL; */
    /* cal_rqst = CAL_RES_ID; */
    /* tmr++; */
    /* if(tmr >= 60e3) { */
    /*   st++; */
    /*   tmr = 0; */
    /* } */
    /* break; */


    default: /* Just spin it. */
    _mtr_if_s.is_busy = false;
    cal_rqst = CAL_NONE;
    tmr = 0;
    st = 255; /* Stay here @ default */
    MtrIf_GetCtlMd(&ctrl_md, &ctrl_tgt[0]);
    ctrl_md = CTRL_MD_IFBK;
    ctrl_tgt[0] = 0.3;

  }

  Trig_Pmsm_SetIn(
    &pmsm_ctrl_obj,
    App_GetEncCnt(), /* Encoder counts */
    (real32_T*)&_mtr_if_s.mtr_ifbk[0], /* Array with phase currents. */
    (real32_T)0.0f, /* Speed sensor */
    ctrl_md, /* Control mode */
    (real32_T*)ctrl_tgt, /* Target */
    (real32_T)MtrIf_GetVBus(), /* Bus voltage. */
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

float MtrIf_GetVBus(void) {
  return (float)App_GetBusVoltage() * MTRIF_FROM_MILLIS;
}

float MtrIf_GetTemp(void) {
  return (float)App_GetTemp() * MTRIF_FROM_MILLIS;
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

void MtrIf_GetCtlMd(MtrCtlMd_T* ctrl_md, float* target) {
  if(ctrl_md && target) {
    MTRIF_LOCK();
    *ctrl_md = _mtr_if_s.ctrl_md_act;
    target[0] = _mtr_if_s.ctrl_tgt[0];
    target[1] = _mtr_if_s.ctrl_tgt[1];
    target[2] = _mtr_if_s.ctrl_tgt[2];
    MTRIF_UNLOCK();
  }
}

void MtrIf_SetCtlMd(MtrCtlMd_T ctrl_md, float* target) {
  if(target) {
    MTRIF_LOCK();
    _mtr_if_s.ctrl_md_rqst = ctrl_md;

    /* For now set actual to request. Later down the road, validation */
    /* checks will be needed to honor a mode request. */
    _mtr_if_s.ctrl_md_act = ctrl_md;

    _mtr_if_s.ctrl_tgt[0] = target[0];
    _mtr_if_s.ctrl_tgt[1] = target[1];
    _mtr_if_s.ctrl_tgt[2] = target[2];

    MTRIF_UNLOCK();

  }
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
    memcpy((void*)dbg, (void*)&DBG_Struct, sizeof(DBG_Struct_type));
    MTRIF_UNLOCK();
  }
}
