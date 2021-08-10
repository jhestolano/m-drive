#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "mtrif.h"
#include "stdlib.h"
#include "gpio.h"
#include "pmsm_ctrl.h"
#include "pmsm_ctrl_types.h"
#include "pwm.h"
#include "tmr.h"
#include "FreeRTOS.h"
#include "task.h"

#define MTRIF_TGT_ELEM (3)
#define MTRIF_TGT_TYPE (float)
#define MTRIF_TGT_SIZE (MTRIF_TGT_ELEM * sizeof MTRIF_TGT_TYPE)

#define MTRIF_TO_DEG (0.1f) /* App layer position resolution is 0.1 degrees
                               represented as int. For example, a value of
                               13 represents 1.3 degrees. */

extern DBG_Struct_type DBG_Struct;

typedef struct CtrlIn_tag {
  float tgt[MTRIF_TGT_ELEM];
  MtrCtrlMd_T mode;
  MtrCtrlCal_T cal_req;
} CtrlIn_S;

typedef struct MtrIf_State_tag {
  MtrIfCalJob_S job_cal;
  CtrlIn_S inputs;
  uint8_t is_init;
  float pwm_dc[MTRIF_TGT_ELEM];
  float mod_wave[MTRIF_TGT_ELEM];
  float mtr_ifbk[MTRIF_TGT_ELEM];
  float mtr_spd;
  float mtr_trq;
  float pwm_dq[2];
  float ifbk_dq[2];
  float ctrl_tgt[MTRIF_TGT_ELEM];
  MtrCtrlMd_T ctrl_md_rqst;
  MtrCtrlMd_T ctrl_md_act;
  uint8_t is_busy;
  uint32_t ctrl_fast_cnt; /* Clock cycles for FOC control. */
  int32_t status;
  int32_t job_status;
} MtrIf_State_S;

MtrIf_State_S _mtr_if_s = {0};

static void _mtr_if_clear_cal_job(void);

static void _mtr_if_notify(void);

static void _mtr_if_adc_isr_callback(void *params);

RT_MODEL pmsm_ctrl_obj;

void MtrIf_Init(void) {

  CalMgrSt_T cal_mgr_status;

  bzero(&_mtr_if_s, sizeof(MtrIf_State_S));

  MTRIF_LOCK();

  ADC_AttachISRCallback(_mtr_if_adc_isr_callback);

  Trig_Pmsm_Init(&pmsm_ctrl_obj, &cal_mgr_status);

  /* Ignore trivial value. */
  (void)cal_mgr_status;

  _mtr_if_s.is_init = true;

  _mtr_if_s.is_busy = false;

  MTRIF_UNLOCK();

  App_ArmMotor();
}

void MtrIf_CtrlSlow(void) {
  CalMgrSt_T cal_mgr_status;
  int32_t job_status;

  Trig_Pmsm_CtrlMgr(&pmsm_ctrl_obj);
  Trig_Pmsm_Cal(&pmsm_ctrl_obj, &cal_mgr_status);
  Trig_Pmsm_MotnCtrl(&pmsm_ctrl_obj);

  switch(cal_mgr_status) {
    case ST_NOT_STARTED:
      job_status = MTRIF_ST_IDLE;
      break;

    case ST_DONE:
      job_status = MTRIF_ST_OK;
      /* Set state machine back to idle. */
      /* _mtr_if_clear_cal_job(); */
      /* Notify subscriber. */
      /* _mtr_if_notify(); */
      break;

    case ST_FAILED:
      job_status = MTRIF_ST_ERR;
      break;

    default:
      job_status = MTRIF_ST_BUSY;
  }

  MTRIF_LOCK();
  _mtr_if_s.job_status = job_status;
  MTRIF_UNLOCK();
}

void MtrIf_CtrlFast(void) {

  TMR_Reset(TMR_CH_GENERAL);

  TMR_Start(TMR_CH_GENERAL);

  MtrIf_GetIfbk(&_mtr_if_s.mtr_ifbk[0]);

  Trig_Pmsm_SetIn(
    &pmsm_ctrl_obj,
    App_GetEncCnt(), /* Encoder counts */
    (real32_T*)&_mtr_if_s.mtr_ifbk[0], /* Array with phase currents. */
    (real32_T)0.0f, /* Speed sensor */
    _mtr_if_s.inputs.mode, /* Control mode. */
    (real32_T*)&_mtr_if_s.inputs.tgt[0], /* Actual control target. */
    (real32_T)MtrIf_GetVBus(), /* Bus voltage. */
    _mtr_if_s.inputs.cal_req /* Calibration request */
  );

  Trig_Pmsm_Foc(&pmsm_ctrl_obj);

  Trig_Pmsm_GetOut(
    &pmsm_ctrl_obj,
    (real32_T*)&_mtr_if_s.pwm_dc[0],
    (real32_T*)&_mtr_if_s.mod_wave[0],
    (real32_T*)&_mtr_if_s.mtr_trq,
    (real32_T*)&_mtr_if_s.mtr_spd
    /* (real32_T*)&_mtr_if_s.pwm_dq, */
    /* (real32_T*)&_mtr_if_s.ifbk_dq, */
  );

  MtrIf_SetPwmDc(&_mtr_if_s.pwm_dc[0]);

  TMR_Stop(TMR_CH_GENERAL);
  _mtr_if_s.ctrl_fast_cnt = TMR_GetCnt(TMR_CH_GENERAL);
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

void MtrIf_GetCtlMd(MtrCtrlMd_T* ctrl_md, float* target) {
  if(ctrl_md && target) {
    MTRIF_LOCK();
    *ctrl_md = _mtr_if_s.ctrl_md_act;
    target[0] = _mtr_if_s.ctrl_tgt[0];
    target[1] = _mtr_if_s.ctrl_tgt[1];
    target[2] = _mtr_if_s.ctrl_tgt[2];
    MTRIF_UNLOCK();
  }
}

void MtrIf_SetCtlMd(MtrCtrlMd_T ctrl_md, float* target) {
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
    memcpy((void*)params, (void*)&CALIB_PARAM_BUS, sizeof(Calib_ParamType));
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

void MtrIf_GetStats(MtrStats_S* stats) {
  if(stats) {
    MTRIF_LOCK();
    stats->ctrl_fast_cnt = _mtr_if_s.ctrl_fast_cnt;
    MTRIF_UNLOCK();
  }
}


int32_t MtrIf_JobReq(MtrIfCalJob_S* job) {
  if(!job) {
    return MTRIF_ST_ERR;
  }

  /* if(!_mtr_if_set_job(job)) { */
  /*   return MTRIF_ST_NOT_OK; */
  /* } */

  return MTRIF_ST_OK;
}

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

int32_t MtrIf_CalJobReq(MtrIfCalJob_S* job) {
  CtrlIn_S inputs = {0};
  int32_t job_status;
  
  if(!job) {
    return MTRIF_ST_ERR;
  }
  MTRIF_LOCK();
  job_status = _mtr_if_s.job_status;
  MTRIF_UNLOCK();
  if(job_status == MTRIF_ST_BUSY) {
    /* Job already ongoing. Refuse by returning busy. */
    return MTRIF_ST_BUSY;
  }
  if((job->job > CAL_JOB_NONE) && (job->job < CAL_JOB_MAX)) {
    inputs.mode = CTRL_MD_CAL;
    inputs.cal_req = (MtrCtrlCal_T)job->job;
    bzero((void*)&inputs.tgt, MTRIF_TGT_SIZE);
  } else {
    return MTRIF_ST_ERR;
  }
  MTRIF_LOCK();
  /* Update control inputs structure to execute on next cycle. */
  memcpy((void*)&_mtr_if_s.inputs, (void*)&inputs, sizeof(CtrlIn_S));

  /* Update job status to busy, as the job has been accepted and is pending to be */
  /* executed on next interrupt cycle. */
  _mtr_if_s.job_status = MTRIF_ST_BUSY;
  MTRIF_UNLOCK();
  return MTRIF_ST_OK;
}

int32_t MtrIf_CtrlJobReq(int32_t pwm_dc) {
  CtrlIn_S inputs = {0};
  int32_t job_status;
  
  inputs.mode = CTRL_MD_DQ_PWM;
  inputs.tgt[0] = 0.0f;
  inputs.tgt[1] = pwm_dc * 0.01f;
  inputs.cal_req = CAL_NONE;

  MTRIF_LOCK();
  job_status = _mtr_if_s.job_status;
  MTRIF_UNLOCK();
  if(job_status == MTRIF_ST_BUSY) {
    /* Job already ongoing. Refuse by returning busy. */
    return MTRIF_ST_BUSY;
  }
  MTRIF_LOCK();
  /* Update control inputs structure to execute on next cycle. */
  memcpy((void*)&_mtr_if_s.inputs, (void*)&inputs, sizeof(CtrlIn_S));

  /* Update job status to busy, as the job has been accepted and is pending to be */
  /* executed on next interrupt cycle. */
  /* _mtr_if_s.job_status = MTRIF_ST_BUSY; */
  MTRIF_UNLOCK();
  return MTRIF_ST_OK;
}

int32_t MtrIf_GetJobStat(void) {
  int32_t status;
  MTRIF_LOCK();
  status = _mtr_if_s.job_status;
  MTRIF_UNLOCK();
  return status;
}

int32_t MtrIf_WaitPending(void) {
  int32_t status;
  do {
    MTRIF_LOCK();
    status = _mtr_if_s.job_status;
    MTRIF_UNLOCK();

    /* Maybe RTOS functions should no be called here.... */
    taskYIELD();
  } while(status == MTRIF_ST_BUSY);
  return status;
}

static void _mtr_if_clear_cal_job(void) {
  /* This function clears the calibration status from done back to idle. */
  MTRIF_LOCK();
  _mtr_if_s.inputs.mode = CTRL_MD_OFF;
  bzero((void*)&_mtr_if_s.inputs.tgt[0], MTRIF_TGT_SIZE);
  _mtr_if_s.inputs.cal_req = CAL_NONE;
  MTRIF_UNLOCK();
}

static void _mtr_if_notify(void) {
  /* Notify subscriber to calibration done event. */
}
