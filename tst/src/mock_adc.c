#include "adc.h"
#include <stdint.h>

uint32_t gs_adc_ch_buf[ADC_CH_MAX_E];

int8_t MockADC_SetBuffer(uint8_t idx, uint32_t val) {
  gs_adc_ch_buf[idx] = val;
  return 0;
}

uint32_t ADC_ReadCh(ADC_Channel_E adc_ch) {
  if(adc_ch >= ADC_CH_MAX_E) {
    return INT32_MAX;
  }
  return gs_adc_ch_buf[adc_ch];
}
