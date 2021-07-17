#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#include "stm32f3xx_hal.h"

/*******************************************************************************
* PWM API MACRO DEFINITIONS.
*******************************************************************************/
#define PWM_PH_U   (0)
#define PWM_PH_V   (1)
#define PWM_PH_W   (2)
#define PWM_PH_MAX (3)

#define PWM_MAX_DC (10000) /* 100.00% with 0.01 precision. */

/*******************************************************************************
* PWM MACRO DEFINITIONS.
*******************************************************************************/
#define UH_PWM_PORT (GPIOA)
#define VH_PWM_PORT (GPIOA)
#define WH_PWM_PORT (GPIOA)

#define UH_PWM_PIN (GPIO_PIN_8)
#define VH_PWM_PIN (GPIO_PIN_9)
#define WH_PWM_PIN (GPIO_PIN_10)

#define UH_PWM_CHANNEL (TIM_CHANNEL_1)
#define VH_PWM_CHANNEL (TIM_CHANNEL_2)
#define WH_PWM_CHANNEL (TIM_CHANNEL_3)

/*******************************************************************************
* PWM REGISTER CALCULATIONS
********************************************************************************
(PSC + 1) * (ARR + 1) = TIM_CLK * PRD

ARR: Auto-reload register value.
PSC: Prescaler.
TIM_CLK: Timer clock frequency (Hertz).
PRD: Waveform period (Seconds).
*******************************************************************************/
#define PWM_TMR_CLOCK_HZ (72000000)
#define PWM_TMR_FRQ_HZ (30000)
#define PWM_TMR_PSC (0)
#define PWM_TMR_ARR (((PWM_TMR_CLOCK_HZ / (2 * PWM_TMR_FRQ_HZ)) / (PWM_TMR_PSC + 1)) - 1)

#if (PWM_TMR_ARR > 65535) || (PWM_TMR_ARR < 1)
#error("Invalid PWM config: ARR register out of bounds.")
#endif

/*******************************************************************************
* PWM GPIO INITIAL CONFIGURATION.
*******************************************************************************/
#define PWM_GPIO_CONF {                                                        \
  .Pin = UH_PWM_PIN | VH_PWM_PIN | WH_PWM_PIN,                                 \
  .Mode = GPIO_MODE_AF_PP,                                                     \
  .Pull = GPIO_PULLDOWN,                                                       \
  .Speed = GPIO_SPEED_FREQ_HIGH,                                               \
  .Alternate = GPIO_AF6_TIM1,                                                  \
}   

/*******************************************************************************
* PWM INITIAL CONFIGURATION.
********************************************************************************
* Type: TIM_HandleTypeDef
********************************************************************************
* Prescaler: REG: PSC; BITS: PSC.
* CounterMode: REG: CR1; BITS: CMS, DIR.
* Period: REG: ARR; BITS: ARR.
* RepetitionCounter: REG: RCR; BITS: RCR.
* ClockDivision: REG: CR1; BITS: CKD.
* AutoReloadPreload: REG: CR1; BITS: ARPE. 
*******************************************************************************/
#define PWM_INIT_CONF {                                                        \
  .Instance = TIM1,                                                            \
  .Init = {                                                                    \
    .Prescaler = PWM_TMR_PSC,                                                  \
    .CounterMode = TIM_COUNTERMODE_CENTERALIGNED1,                             \
    .Period = PWM_TMR_ARR,                                                     \
    .RepetitionCounter = 0,                                                    \
    .ClockDivision = TIM_CLOCKDIVISION_DIV2,                                   \
    .AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE,                       \
  },                                                                           \
}

/*******************************************************************************
* PWM OUTPUT-COMPARE CONFIGURATION.
********************************************************************************
* Type: TIM_OC_InitTypeDef
********************************************************************************
* OCMode: REG: CCMR1; BITS: OC1M, CC1S.
* Pulse: REG: CCR1.
* OCPolarity: REG: CCER; BITS: CC1P.
* OCNPolarity: REG: CCER; CC1NP.
* OCFastMode: REG: CCMR1; BITS: OC1FE.
* OCIdleState: REG: CR2; BITS: OIS1.
* OCNIdleState: REG: CR2; BITS: OIS1N.
*******************************************************************************/
#define PWM_OC_CONF {                                                          \
  .OCMode = TIM_OCMODE_PWM1,                                                   \
  .Pulse = 0,                                                                  \
  .OCPolarity = TIM_OCPOLARITY_HIGH,                                           \
  .OCNPolarity = TIM_OCNPOLARITY_HIGH,                                         \
  .OCFastMode = TIM_OCFAST_DISABLE,                                            \
  .OCIdleState = TIM_OCIDLESTATE_RESET,                                        \
  .OCNIdleState = TIM_OCNIDLESTATE_RESET,                                      \
}

/*******************************************************************************
* PWM MASTER OUTPUT CONFIGURATION.
********************************************************************************
* Type: TIM_MasterConfigTypeDef
********************************************************************************
* MasterOutputTrigger: REG: CR2; BITS: MMS.
    Related to TIMER synchronization.
* MasterOutputTrigger2: REG: CR2; BITS: MMS2.
    Related to ADC synchronization.
* MasterSlaveMode: REG: SMCR; BITS: MSM.
    When enabled: The effect of an event on the trigger input (TRGI) is
    delayed to allow a perfect synchronization between the current timer
    and its slaves (through TRGO). It is useful if we want to synchronize
    several timers on a single external event.    
*******************************************************************************/
#define PWM_MASTER_OUT_CONF {                                                  \
  .MasterOutputTrigger = TIM_TRGO_OC4REF,                                      \
  .MasterOutputTrigger2 = TIM_TRGO2_RESET,                                     \
  .MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE,                              \
}

/*******************************************************************************
* PWM DEADTIME CONFIGURATION.
********************************************************************************
* Type: TIM_BreakDeadTimeConfigTypeDef
********************************************************************************
* OffStateRunMode: REG: BDTR; BITS: OSSR.
* OffStateIdleMode: REG: BDTR; BITS: OSSI.
* LockLevel: REG: BDTR; BITS: LOCK.
* DeadTime: REG: BDTR; BITS: DTG.
* BreakState: REG: BDTR; BITS: BKE.
* BreakPolarity: REG: BDTR; BITS: BKP.
* BreakFilter: REG: BDTR; BITS: BKF.
* Break2State: REG: BDTR; BITS: BK2E.
* Break2Polarity: REG: BDTR; BITS: BK2P.
* Break2Filter: REG: BDTR; BITS: BK2F.
* AutomaticOutput: REG: BDTR; BITS: AOE.
*******************************************************************************/
#define PWM_DEADTIME_CONF {                                                    \
  .OffStateRunMode = TIM_OSSR_ENABLE,                                          \
  .OffStateIDLEMode = TIM_OSSI_ENABLE,                                         \
  .LockLevel = TIM_LOCKLEVEL_1,                                                \
  .DeadTime = 0,                                                               \
  .BreakState = TIM_BREAK_DISABLE,                                             \
  .BreakPolarity = TIM_BREAKPOLARITY_HIGH,                                     \
  .BreakFilter = 0,                                                            \
  .Break2State = TIM_BREAK2_DISABLE,                                           \
  .Break2Polarity = TIM_BREAK2POLARITY_LOW,                                    \
  .Break2Filter = 7,                                                           \
  .AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE,                              \
}

/*******************************************************************************
*******************************************************************************/

void PWM_Init(void);

void PWM_SetDC(uint32_t pwmch, uint32_t pwmdc);

uint32_t PWM_GetDC(uint32_t pwmch);

void PWM_SetComp(uint32_t pwmch, uint16_t pwmcnt);

uint16_t PWM_GetComp(uint32_t pwmch);

#endif
