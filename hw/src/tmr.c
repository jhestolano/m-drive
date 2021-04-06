#include "tmr.h"
#include "adc.h"
#include "stm32f3xx_hal_dma.h"
#include "stm32f3xx_hal_tim.h"
#include "stm32f3xx_hal_tim_ex.h"
#include "stm32f3xx_hal_rcc.h"
#include "stm32f3xx_hal.h"
#include "enc.h"
#include "dbg.h"

/*******************************************************************************
** Private data type definitions.
*******************************************************************************/
typedef struct TMR_IT_Config {
  TmrCh_T Tmr;
  IRQn_Type IRQn;
  uint32_t Prio;
  uint32_t SubPrio;
} TMR_IT_Config_S;

/*******************************************************************************
** Global data definitions.
*******************************************************************************/
static TIM_HandleTypeDef gs_tim_init_conf_a[TMR_CH_MAX] = {
  TMR_INC_TICK,
  TMR_GENERAL_CONF,
};

static const TMR_IT_Config_S tmr_config_a[TMR_CH_MAX] = TMR_IT_CONF;

#define TMR_IS_VALID(tmrch) ((tmrch) < (TMR_CH_MAX))

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* s_tim_conf) {
  UNUSED(s_tim_conf);
  if(!__HAL_RCC_TIM6_IS_CLK_ENABLED()) {
    __HAL_RCC_TIM6_CLK_ENABLE();
  }
  if(!__HAL_RCC_TIM17_IS_CLK_ENABLED()) {
    __HAL_RCC_TIM17_CLK_ENABLE();
  }
}

void TMR_Init(void) {
  size_t idx;
  for(idx = 0; idx < TMR_CH_MAX; idx++) {
    HAL_TIM_Base_Init(&gs_tim_init_conf_a[idx]);
    HAL_NVIC_SetPriority(tmr_config_a[idx].IRQn,
        tmr_config_a[idx].Prio,
        tmr_config_a[idx].SubPrio);
    HAL_NVIC_EnableIRQ(tmr_config_a[idx].IRQn);
  }
  /* Only start timer needed for HAL tick. Other timers */
  /* must be started manually. */
  TMR_Start(TMR_CH_INC_TICK);
}

void TMR_Start(TmrCh_T tmr) {
  if(TMR_IS_VALID(tmr)) {
    HAL_TIM_Base_Start_IT(&gs_tim_init_conf_a[tmr]);
  }
}

void TMR_Stop(TmrCh_T tmr) {
  if(TMR_IS_VALID(tmr)) {
    __HAL_TIM_DISABLE(&gs_tim_init_conf_a[tmr]);
  }
}

void TMR_Resume(TmrCh_T tmr) {
  if(TMR_IS_VALID(tmr)) {
    __HAL_TIM_ENABLE(&gs_tim_init_conf_a[tmr]);
  }
}

void TMR_Reset(TmrCh_T tmr) {
  if(TMR_IS_VALID(tmr)) {
    __HAL_TIM_SET_COUNTER(&gs_tim_init_conf_a[tmr], 0u);
  }
}

uint32_t TMR_GetCnt(TmrCh_T tmr) {
  uint32_t count = UINT32_MAX;
  if(TMR_IS_VALID(tmr)) {
    count = (uint32_t)__HAL_TIM_GET_COUNTER(&gs_tim_init_conf_a[tmr]);
  }
  return count;
}

void TMR_IncTickCallback(void) {
  HAL_IncTick();
}


/*******************************************************************************
** Interrupt Callback handling.
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* tim) { 
  if(tim->Instance == TMR_CH_INC_TICK_INSTANCE) {
    TMR_IncTickCallback();
  }
}

/*******************************************************************************
** Interrupts Section.
*******************************************************************************/
void TIM2_IRQHandler(void) {
  /* General purpose timer to measure execution times. */
  DBG_DEBUG("TIM2 IRQ handler fired!");
  while(1);
}

void TIM6_DAC_IRQHandler(void) {
/* HAL_IncTick interrupt function. */
  HAL_TIM_IRQHandler(&gs_tim_init_conf_a[TMR_CH_INC_TICK]);
}


void TIM17_IRQHandler(void) {
  /* General purpose timer. */
  HAL_TIM_IRQHandler(&gs_tim_init_conf_a[TMR_CH_GENERAL]);
  DBG_DEBUG("General channel timer overflowed!");
}
