#include "app.h"
#include "pwm.h"
#include "adc.h"
#include "enc.h"
#include "gpio.h"
#include "stdio.h"
#include "dbg.h"

#define APP_PWM_MAX_DC (10000)
#define APP_ADC_MAX_VOLTS (3300)

static const uint16_t gsc_pwm_ch_map[] = {
  PWM_PH_U,
  PWM_PH_V,
  PWM_PH_W,
  PWM_PH_MAX,
};

static const uint16_t gsc_adc_ch_map[] = {
  ADC_PHA_IFBK_CH_E,
  ADC_PHB_IFBK_CH_E,
  ADC_PHC_IFBK_CH_E,
  ADC_POT_CH_E,
  ADC_TEMP_SENS_CH_E,
  ADC_VBUS_CH_E,
  ADC_CH_MAX_E,
  ADC_UNKNOWN_CH_E,
};

static const uint16_t gsc_gpio_ch_map[] = {
  GPIO_PH_A,
  GPIO_PH_B,
  GPIO_PH_C,
  GPIO_BKIN2,
  GPIO_CH_MAX,
};

uint32_t App_GetVoltage(VAdcCh_E vch) {
  uint32_t adccnts;
  if(vch >= VAdcChMax_E) {
    return INT32_MAX;
  }
  adccnts = ADC_ReadCh(gsc_adc_ch_map[vch]);
  return (uint32_t)((adccnts * (uint32_t)APP_ADC_MAX_VOLTS) / ((uint32_t)ADC_MAX_COUNTS));
}

int32_t App_GetCurrent(IfbkPh_E ifbk) {
  int32_t mvolts;
  if(ifbk >= IfbkPhMax_E) {
    return INT32_MAX;
  }
  mvolts = (int32_t)App_GetVoltage((VAdcCh_E)ifbk) - (int32_t)APP_PARAMS_IFBK_BIAS;
  return (int32_t)(APP_PARAMS_IFBK_R_INV * (mvolts) / (int32_t)APP_PARAMS_IFBK_GAIN);
}

void App_SetPwmDutyCycle(PwmCh_E pwmch, uint32_t pwmdc) {
  uint16_t pwmcnts;
  if(pwmch >= PwmChMax_E) {
    return;
  }
  pwmdc = (pwmdc > APP_PWM_MAX_DC) ? APP_PWM_MAX_DC : pwmdc;
  pwmcnts = (uint16_t)((pwmdc * ((uint32_t)PWM_TMR_ARR)) / ((uint32_t)APP_PWM_MAX_DC));
  PWM_SetComp(pwmch, pwmcnts);
  return;
}

void App_SetPwmVoltage(PwmCh_E pwmch, uint32_t mvolts) {
  mvolts = (mvolts > APP_PARAMS_PWM_VOLTS) ? APP_PARAMS_PWM_VOLTS : mvolts;
  uint32_t dcycle = (uint32_t)(mvolts * (APP_PWM_MAX_DC) / ((uint32_t)APP_PARAMS_PWM_VOLTS));
  App_SetPwmDutyCycle(gsc_pwm_ch_map[pwmch], dcycle);
  return;
}

void App_SetPwmVoltageAll(uint32_t mvolts) {
  App_SetPwmDutyCycle(PwmChA_E, mvolts);
  App_SetPwmDutyCycle(PwmChB_E, mvolts);
  App_SetPwmDutyCycle(PwmChC_E, mvolts);
}

uint32_t App_GetPwmDutyCycle(PwmCh_E pwmch) {
  uint32_t counts;
  if(pwmch >= PwmChMax_E) {
    return UINT32_MAX;
  }
  counts = (uint32_t)PWM_GetComp(pwmch); 
  return (uint32_t)(counts * (uint32_t)APP_PWM_MAX_DC / ((uint32_t)PWM_TMR_ARR));
}

uint32_t App_GetPwmVoltage(PwmCh_E pwmch) {
  uint32_t dcycle;
  if(pwmch >= PwmChMax_E) {
    return UINT32_MAX;
  }
  dcycle = App_GetPwmDutyCycle(pwmch);
  return (uint32_t)((dcycle * (uint32_t)APP_PARAMS_PWM_VOLTS) / (uint32_t)APP_PWM_MAX_DC);
}

uint32_t App_GetBusVoltage(void) {
  uint32_t vbusadc = App_GetVoltage(VAdcChVBus_E);
  return (uint32_t)(vbusadc * (uint32_t)APP_PARAMS_VBUS_DIV / (uint32_t)1000);
}

int32_t App_GetTemp(void) {
  uint32_t vtemp = App_GetVoltage(VAdcChTemp_E);
  return APP_PARAMS_TEMP_GAIN * (int32_t)(vtemp - APP_PARAMS_TEMP_V_BIAS) + (int32_t)APP_PARAMS_TEMP_BIAS;
}

int32_t App_GetPosition(void) {
  int32_t cnts = ENC_GetCnt();
  return (int32_t)(cnts * APP_PARAMS_ENC_RES);
}

void App_DisarmPhase(GpioCh_E pin) {
  if(pin >= GpioChMax_E) {
    return;
  }
  GPIO_Reset(gsc_gpio_ch_map[pin]);  
}

void App_ArmPhase(GpioCh_E pin) {
  if(pin >= GpioChMax_E) {
    return;
  }
  GPIO_Set(gsc_gpio_ch_map[pin]);  
}

void App_ArmDrive(void) {
  GPIO_Set(GpioChBkIn2_E);
  DBG_DEBUG("Arming drive.\n\r");
}

void App_DisarmDrive(void) {
  GPIO_Reset(GpioChBkIn2_E);
  DBG_DEBUG("Disarming drive.\n\r");
}

void App_DisarmMotor(void) {
  App_DisarmDrive();
  App_DisarmPhase(GpioChA_E);
  App_DisarmPhase(GpioChB_E);
  App_DisarmPhase(GpioChC_E);
  App_SetPwmVoltageAll(0);
  DBG_DEBUG("Disarming motor.\n\r");
}

void App_ArmMotor(void) {
  App_ArmDrive();
  App_ArmPhase(GpioChA_E);
  App_ArmPhase(GpioChB_E);
  App_ArmPhase(GpioChC_E);
  App_SetPwmVoltageAll(0);
  DBG_DEBUG("Arming motor.\n\r");
}

