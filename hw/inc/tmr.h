#ifndef TMR_H
#define TMR_H

#include <stdint.h>

typedef uint8_t TmrCh_T;

/*******************************************************************************
** Timer channel definitions.
*******************************************************************************/
/* Increase tick for HAL functions that use delay. Used in order to mix */
/* FreeRTOS systick interrupt handling and HAL timeouts. */
#define TMR_CH_INC_TICK ((TmrCh_T)0)
#define TMR_CH_INC_TICK_INSTANCE (TIM6)
#define TMR_CH_INC_TICK_IRQn (TIM6_DAC_IRQn)
/* This Timer will be used to measure execution time of functions and other */
/* general tasks. */
#define TMR_CH_GENERAL ((TmrCh_T)1)
#define TMR_CH_GENERAL_INSTANCE (TIM17)
#define TMR_CH_GENERAL_IRQn (TIM17_IRQn)
#define TMR_ENC_LOCK() HAL_NVIC_DisableIRQ(TMR_CH_INC_TICK_IRQn)
#define TMR_ENC_UNLOCK() HAL_NVIC_EnableIRQ(TMR_CH_INC_TICK_IRQn)
/* Timer channels. */
#define TMR_CH_MAX      ((TmrCh_T)2)
/*******************************************************************************
** Timer channel interrupt configuration.
*******************************************************************************/
#define TMR_IT_CONF {                                                          \
  {                                                                            \
    .Tmr = TMR_CH_INC_TICK,                                                    \
    .IRQn = TMR_CH_INC_TICK_IRQn,                                              \
    .Prio = 7,                                                                 \
    .SubPrio = 0,                                                              \
  },                                                                           \
  {                                                                            \
    .Tmr = TMR_CH_GENERAL,                                                     \
    .IRQn = TMR_CH_GENERAL_IRQn,                                               \
    .Prio = 7,                                                                 \
    .SubPrio = 1,                                                              \
  },                                                                           \
}
/*******************************************************************************
** Tmer used to increase HAL_SysTick. Interrupt @ 1ms.
*******************************************************************************/
#define TMR_INC_TICK {                                                         \
  .Instance = TMR_CH_INC_TICK_INSTANCE,                                        \
  .Init = {                                                                    \
    .Prescaler = 1,                                                            \
    .CounterMode = TIM_COUNTERMODE_UP,                                         \
    .Period = 35999,                                                           \
    .RepetitionCounter = 0,                                                    \
    .ClockDivision = TIM_CLOCKDIVISION_DIV2,                                   \
    .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,                       \
  },                                                                           \
}
/*******************************************************************************
** General purpose timer used to measure execution time.
*******************************************************************************/
#define TMR_GENERAL_CONF {                                                     \
  .Instance = TMR_CH_GENERAL_INSTANCE,                                         \
  .Init = {                                                                    \
    .Prescaler = 15,                                                           \
    .CounterMode = TIM_COUNTERMODE_UP,                                         \
    .Period = UINT16_MAX,                                                      \
    .RepetitionCounter = 0,                                                    \
    .ClockDivision = TIM_CLOCKDIVISION_DIV1,                                   \
    .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,                       \
  },                                                                           \
}
/*******************************************************************************
*******************************************************************************/

void TMR_Init(void);

void TMR_Start(TmrCh_T tmrch);

void TMR_Stop(TmrCh_T tmrch);

void TMR_Reset(TmrCh_T tmrch);

uint32_t TMR_GetCnt(TmrCh_T tmrch);

#endif
