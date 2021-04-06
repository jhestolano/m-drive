#include "pwm.h"
#include <stdio.h>

uint16_t gs_pwm_ch_buf[PWM_PH_MAX];

void PWM_SetComp(uint32_t pwmch, uint16_t pwmcnt) {
  gs_pwm_ch_buf[pwmch] = pwmcnt;
}

uint16_t PWM_GetComp(uint32_t pwmch) {
  return gs_pwm_ch_buf[pwmch];
}
