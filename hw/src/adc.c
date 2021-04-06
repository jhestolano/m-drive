/* #include "FreeRTOS.h" */
/* #include "task.h" */
/* #include "mtrif.h" */
#include "adc.h"
/* #include "stm32f3xx_hal_gpio.h" */
/* #include "stm32f3xx_hal_rcc.h" */
/* #include "stm32f3xx_hal_cortex.h" */
/* #include "gpio.h" */
#include "dbg.h"
/* #include "app.h" */
/* #include "math.h" */

#define ADC_REG_CH_BUFF_OFS ADC_INJ_CH_MAX

static adc_isr_callback_t gs_adc_isr_callback;

ADC_HandleTypeDef gs_adc_handle = ADC_INIT_CONF;

static DMA_HandleTypeDef gs_dma_handle = DMA_INIT_CONFIG;

uint32_t gs_adc_ch_buf[ADC_CH_MAX_E];

static void adc_dma_init(void);

static void ADC_ErrorHandler(char* errmsg) {
  DBG_ERR("ADC: %s\n\r", errmsg);
  while(1);
  return;
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adc_handle) {
  (void)adc_handle;

  GPIO_InitTypeDef s_gpioa_input_conf = GPIOA_ADC_INPUT_CONF;
  GPIO_InitTypeDef s_gpiob_input_conf = GPIOB_ADC_INPUT_CONF;
  GPIO_InitTypeDef s_gpioc_input_conf = GPIOC_ADC_INPUT_CONF;

  __HAL_RCC_ADC1_CLK_ENABLE();

  if(!__HAL_RCC_GPIOA_IS_CLK_ENABLED()) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }

  if(!__HAL_RCC_GPIOB_IS_CLK_ENABLED()) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }

  if(!__HAL_RCC_GPIOC_IS_CLK_ENABLED()) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }

  HAL_GPIO_Init(GPIOA, &s_gpioa_input_conf);
  HAL_GPIO_Init(GPIOB, &s_gpiob_input_conf);
  HAL_GPIO_Init(GPIOC, &s_gpioc_input_conf);

  return;
}

void ADC_Init(void) {

  ADC_ChannelConfTypeDef s_pot_conf = POT_ADC_CONF;
  ADC_ChannelConfTypeDef s_temp_sense_conf = TEMP_SENS_ADC_CONF;
  ADC_ChannelConfTypeDef s_vbus_conf = VBUS_ADC_CONF;

  ADC_InjectionConfTypeDef s_pha_ifbk_conf = PHA_IFBK_ADC_INJ_CONF;
  ADC_InjectionConfTypeDef s_phb_ifbk_conf = PHB_IFBK_ADC_INJ_CONF;
  ADC_InjectionConfTypeDef s_phc_ifbk_conf = PHC_IFBK_ADC_INJ_CONF;

  DBG_DEBUG("Initializing ADC module... \n\r");

  HAL_NVIC_SetPriority(ADC1_IRQn, ADC_ISR_PRIO, ADC_ISR_SUBPRIO);
  HAL_NVIC_EnableIRQ(ADC1_IRQn);

  if (HAL_ADC_Init(&gs_adc_handle) != HAL_OK)
  {
    ADC_ErrorHandler("Error initializing ADC module.");
  }
  if(HAL_ADCEx_Calibration_Start(&gs_adc_handle, ADC_SINGLE_ENDED) != HAL_OK) {
    DBG_ERR("ADC Cal. Error!!\n\r");
  }
  if (HAL_ADCEx_InjectedConfigChannel(&gs_adc_handle, &s_pha_ifbk_conf) != HAL_OK)
  {
    ADC_ErrorHandler("Error initializing PHA Channel.");
  }
  if (HAL_ADCEx_InjectedConfigChannel(&gs_adc_handle, &s_phb_ifbk_conf) != HAL_OK)
  {
    ADC_ErrorHandler("Error initializing PHB Channel.");
  }
  if (HAL_ADCEx_InjectedConfigChannel(&gs_adc_handle, &s_phc_ifbk_conf) != HAL_OK)
  {
    ADC_ErrorHandler("Error initializing PHC Channel.");
  }
  if(HAL_ADC_ConfigChannel(&gs_adc_handle, &s_pot_conf) != HAL_OK) {
    DBG_ERR("Error initializing Regular POT Channel.");
  }
  if(HAL_ADC_ConfigChannel(&gs_adc_handle, &s_vbus_conf) != HAL_OK) {
    DBG_ERR("Error initializing Regular VBUS Channel.");
  }
  if(HAL_ADC_ConfigChannel(&gs_adc_handle, &s_temp_sense_conf) != HAL_OK) {
    DBG_ERR("Error initializing Regular TEMP Channel.");
  }
  adc_dma_init();
  ADC_Start();
  gs_adc_isr_callback = NULL;
  DBG_DEBUG("Done.\n\r");
  return;
}

void ADC_Start(void) {
  HAL_ADC_Start_DMA(&gs_adc_handle, &gs_adc_ch_buf[ADC_INJ_CH_MAX], ADC_REG_CH_MAX);
  HAL_ADCEx_InjectedStart_IT(&gs_adc_handle);
  return;
}

void ADC1_IRQHandler(void) {
  HAL_ADC_IRQHandler(&gs_adc_handle);
}

void DMA1_Channel1_IRQHandler(void) {
  /* Interrupt triggered when ADC conversion and transfer is complete. */
  HAL_DMA_IRQHandler(&gs_dma_handle);
}

void ADC_AttachISRCallback(adc_isr_callback_t callback) {
  if(callback) {
    gs_adc_isr_callback = callback;
  }
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* adc_handle) {
  (void)adc_handle;
  gs_adc_ch_buf[ADC_PHA_IFBK_CH_E] = HAL_ADCEx_InjectedGetValue(&gs_adc_handle, ADC_INJECTED_RANK_1);
  gs_adc_ch_buf[ADC_PHB_IFBK_CH_E] = HAL_ADCEx_InjectedGetValue(&gs_adc_handle, ADC_INJECTED_RANK_2);
  gs_adc_ch_buf[ADC_PHC_IFBK_CH_E] = HAL_ADCEx_InjectedGetValue(&gs_adc_handle, ADC_INJECTED_RANK_3);
  if ( gs_adc_isr_callback != NULL ) {
    gs_adc_isr_callback((void*)gs_adc_ch_buf);
  }
  return;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* adc_handle) {
  /* Not needed when DMA handles conversions. Use DMA interrupt. */
  (void)adc_handle;
  return;
}

uint32_t ADC_ReadCh(ADC_Channel_E adc_ch_e) {
  uint32_t adc_data = 0;
  if(adc_ch_e  >= ADC_CH_MAX_E) {
    return 0xffffffff;
  }
  HAL_NVIC_DisableIRQ(ADC1_IRQn);
  adc_data = gs_adc_ch_buf[adc_ch_e];
  HAL_NVIC_EnableIRQ(ADC1_IRQn);
  return adc_data;
}

static void adc_dma_init(void) {
  DBG_DEBUG("Initializing ADC DMA...\n\r");
  __HAL_RCC_DMA1_CLK_ENABLE();
  if(HAL_DMA_Init(&gs_dma_handle) != HAL_OK) {
    DBG_ERR("Error initializing ADC DMA.");
  }
  __HAL_LINKDMA(&gs_adc_handle, DMA_Handle, gs_dma_handle);
#ifdef DMA_ENABLE_CH1_IRQ
  /* When DMA interrupts are enabled, OS stops working. Investigate. */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, ADC_DMA_ISR_PRIO, ADC_DMA_ISR_SUBPRIO);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
#endif
  DBG_DEBUG("Done.\n\r");
}
