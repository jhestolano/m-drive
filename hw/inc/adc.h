#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#include "stm32f3xx_hal.h"

#define __ADC_DISABLE_ISR() HAL_NVIC_DisableIRQ(ADC1_IRQn)
#define __ADC_ENABLE_ISR() HAL_NVIC_EnableIRQ(ADC1_IRQn)

typedef enum {
  ADC_PHA_IFBK_CH_E = 0,
  ADC_PHB_IFBK_CH_E,
  ADC_PHC_IFBK_CH_E,
  ADC_POT_CH_E,
  ADC_TEMP_SENS_CH_E,
  ADC_VBUS_CH_E,
  ADC_CH_MAX_E,
  ADC_UNKNOWN_CH_E = 255,
} ADC_Channel_E;

#define ADC_INJ_CH_MAX (3)
#define ADC_REG_CH_MAX (3)

#define ADC_MAX_COUNTS (4095)

/******************************************************************************
 * GENERAL MACRO DEFINITIONS.
******************************************************************************/
#define ADC_ISR_PRIO        (0)
#define ADC_ISR_SUBPRIO     (0)
#define ADC_DMA_ISR_PRIO    (2)
#define ADC_DMA_ISR_SUBPRIO (0)

/******************************************************************************
 * GPIOA ADC CONFIGURATION.
******************************************************************************/
#define PHA_IFBK_ADC_CHANNEL (ADC_CHANNEL_1)
#define PHA_IFBK_ADC_PIN (GPIO_PIN_0)
#define PHA_IFBK_ADC_PORT (GPIOA)

#define VBUS_ADC_CHANNEL (ADC_CHANNEL_2)
#define VBUS_ADC_PIN (GPIO_PIN_1)
#define VBUS_ADC_PORT (GPIOA)

/******************************************************************************
 * GPIOB ADC CONFIGURATION.
******************************************************************************/
#define POT_ADC_CHANNEL (ADC_CHANNEL_12)
#define POT_ADC_PORT (GPIOB)
#define POT_ADC_PIN (GPIO_PIN_1)

/******************************************************************************
 * GPIOC ADC CONFIGURATION.
******************************************************************************/
#define PHB_IFBK_ADC_CHANNEL (ADC_CHANNEL_7)
#define PHB_IFBK_ADC_PIN (GPIO_PIN_1)
#define PHB_IFBK_ADC_PORT (GPIOC)

#define PHC_IFBK_ADC_CHANNEL (ADC_CHANNEL_6)
#define PHC_IFBK_ADC_PIN (GPIO_PIN_0)
#define PHC_IFBK_ADC_PORT (GPIOC)

#define TEMP_SENS_ADC_CHANNEL (ADC_CHANNEL_8)
#define TEMP_SENS_ADC_PIN (GPIO_PIN_2)
#define TEMP_SENS_ADC_PORT (GPIOC)

/*******************************************************************************
 * GPIO INPUT CONFIGURATION: POTENTIOMETER.
*******************************************************************************/
#define GPIOB_ADC_INPUT_CONF {                                                 \
  .Pin = POT_ADC_PIN,                                                          \
  .Mode = GPIO_MODE_ANALOG,                                                    \
  .Pull = GPIO_NOPULL,                                                         \
}

/*******************************************************************************
 * GPIO INPUT CONFIGURATION: PHASE-B, PHASE-C, TEMP. SENSOR.
*******************************************************************************/
#define GPIOC_ADC_INPUT_CONF {                                                 \
  .Pin = PHB_IFBK_ADC_PIN | PHC_IFBK_ADC_PIN | TEMP_SENS_ADC_PIN,              \
  .Mode = GPIO_MODE_ANALOG,                                                    \
  .Pull = GPIO_NOPULL,                                                         \
}

/*******************************************************************************
 * GPIO INPUT CONFIGURATION: PHASE-A, VBUS.
*******************************************************************************/
#define GPIOA_ADC_INPUT_CONF {                                                 \
  .Pin = PHA_IFBK_ADC_PIN | VBUS_ADC_PIN,                                      \
  .Mode = GPIO_MODE_ANALOG,                                                    \
  .Pull = GPIO_NOPULL,                                                         \
}

/*******************************************************************************
* ADC INITIAL CONFIGURATION.
********************************************************************************
* Type: ADC_HandleTypeDef
*******************************************************************************/
#define ADC_INIT_CONF {                                                        \
  .Instance = ADC1,                                                            \
  .Init = {                                                                    \
    .ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1,                                \
    .Resolution = ADC_RESOLUTION_12B,                                          \
    .ScanConvMode = ADC_SCAN_ENABLE,                                           \
    .ContinuousConvMode = ENABLE,                                              \
    .DiscontinuousConvMode = DISABLE,                                          \
    .ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE,                     \
    .ExternalTrigConv = ADC_SOFTWARE_START,                                    \
    .DataAlign = ADC_DATAALIGN_RIGHT,                                          \
    .NbrOfConversion = 3,                                                      \
    .DMAContinuousRequests = ENABLE,                                           \
    .EOCSelection = ADC_EOC_SINGLE_CONV,                                       \
    .LowPowerAutoWait = DISABLE,                                               \
    .Overrun = ADC_OVR_DATA_PRESERVED,                                         \
  },                                                                           \
}
/*******************************************************************************
 * DMA CONFIGURATION FOR REGULAR CONVERSIONS.
********************************************************************************
* Type: DMA_HandleTypeDef
*******************************************************************************/
#define DMA_INIT_CONFIG {                                                      \
  .Instance = DMA1_Channel1,                                                   \
  .Init.Direction = DMA_PERIPH_TO_MEMORY,                                      \
  .Init.MemInc = DMA_MINC_ENABLE,                                              \
  .Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD,                             \
  .Init.MemDataAlignment = DMA_MDATAALIGN_WORD,                                \
  .Init.Mode = DMA_CIRCULAR,                                                   \
  .Init.Priority = DMA_PRIORITY_MEDIUM,                                        \
}
/*******************************************************************************
* ADC INJECTED CHANNEL GROUP CONFIGURATION.
*******************************************************************************/
#define ADC_INJ_GROUP_CONF                                                     \
  .InjectedNbrOfConversion = 3,                                                \
  .ExternalTrigInjecConvEdge = ADC_EXTERNALTRIGINJECCONV_EDGE_RISING,          \
  .ExternalTrigInjecConv = ADC_EXTERNALTRIGINJECCONV_T1_TRGO,                  \
  .AutoInjectedConv = DISABLE,                                                 \
  .InjectedDiscontinuousConvMode = DISABLE,                                    \
  .QueueInjectedContext = DISABLE

/*******************************************************************************
 * ADC REGULAR CHANNEL CONFIG: POTENTIOMETER.
********************************************************************************
* Type: ADC_ChannelConfTypeDef
*******************************************************************************/
#define POT_ADC_CONF {                                                         \
  .Channel = POT_ADC_CHANNEL,                                                  \
  .Rank = ADC_REGULAR_RANK_1,                                                  \
  .SingleDiff = ADC_SINGLE_ENDED,                                              \
  .Offset = 0,                                                                 \
  .OffsetNumber = ADC_OFFSET_NONE,                                             \
  .SamplingTime = ADC_SAMPLETIME_19CYCLES_5,                                   \
}

/*******************************************************************************
 * ADC INJECTED CHANNEL CONFIG: POTENTIOMETER.
********************************************************************************
* Type: ADC_InjectionConfTypeDef
*******************************************************************************/
#define PHA_IFBK_ADC_INJ_CONF {                                                \
  .InjectedChannel = PHA_IFBK_ADC_CHANNEL,                                     \
  .InjectedRank = ADC_INJECTED_RANK_1,                                         \
  .InjectedSingleDiff = ADC_SINGLE_ENDED,                                      \
  .InjectedOffset = 0,                                                         \
  .InjectedOffsetNumber = ADC_OFFSET_NONE,                                     \
  .InjectedSamplingTime = ADC_SAMPLETIME_19CYCLES_5,                           \
  ADC_INJ_GROUP_CONF,                                                          \
}

/*******************************************************************************
 * ADC INJECTED CHANNEL CONFIG: TEMP. SENSOR.
********************************************************************************
* Type: ADC_InjectionConfTypeDef
*******************************************************************************/
#define PHB_IFBK_ADC_INJ_CONF {                                                \
  .InjectedChannel = PHB_IFBK_ADC_CHANNEL,                                     \
  .InjectedRank = ADC_INJECTED_RANK_2,                                         \
  .InjectedSingleDiff = ADC_SINGLE_ENDED,                                      \
  .InjectedSamplingTime = ADC_SAMPLETIME_19CYCLES_5,                           \
  .InjectedOffset = 0,                                                         \
  .InjectedOffsetNumber = ADC_OFFSET_NONE,                                     \
  ADC_INJ_GROUP_CONF,                                                          \
}
/*******************************************************************************
 * ADC REGULAR CHANNEL CONFIG: POTENTIOMETER.
********************************************************************************
* Type: ADC_ChannelConfTypeDef
*******************************************************************************/
#define TEMP_SENS_ADC_CONF {                                                   \
  .Channel = TEMP_SENS_ADC_CHANNEL,                                            \
  .Rank = ADC_REGULAR_RANK_2 ,                                                 \
  .SingleDiff = ADC_SINGLE_ENDED,                                              \
  .Offset = 0,                                                                 \
  .OffsetNumber = ADC_OFFSET_NONE,                                             \
  .SamplingTime = ADC_SAMPLETIME_19CYCLES_5,                                   \
}

/*******************************************************************************
 * ADC INJECTED CHANNEL CONFIG: VOLTAGE BUS.
********************************************************************************
* Type: ADC_InjectionConfTypeDef
*******************************************************************************/
#define PHC_IFBK_ADC_INJ_CONF {                                                \
  .InjectedChannel = PHC_IFBK_ADC_CHANNEL,                                     \
  .InjectedRank = ADC_INJECTED_RANK_3,                                         \
  .InjectedSingleDiff = ADC_SINGLE_ENDED,                                      \
  .InjectedSamplingTime = ADC_SAMPLETIME_19CYCLES_5,                           \
  .InjectedOffset = 0,                                                         \
  .InjectedOffsetNumber = ADC_OFFSET_NONE,                                     \
  ADC_INJ_GROUP_CONF,                                                          \
}
/*******************************************************************************
 * ADC REGULAR CHANNEL CONFIG: POTENTIOMETER.
********************************************************************************
* Type: ADC_ChannelConfTypeDef
*******************************************************************************/
#define VBUS_ADC_CONF {                                                        \
  .Channel = VBUS_ADC_CHANNEL,                                                 \
  .Rank = ADC_REGULAR_RANK_3,                                                  \
  .SingleDiff = ADC_SINGLE_ENDED,                                              \
  .Offset = 0,                                                                 \
  .OffsetNumber = ADC_OFFSET_NONE,                                             \
  .SamplingTime = ADC_SAMPLETIME_19CYCLES_5,                                   \
}

/*******************************************************************************
*******************************************************************************/

typedef void(*adc_isr_callback_t)(void* params);

void ADC_Init(void);

void ADC_Start(void);

void ADC_AttachISRCallback(adc_isr_callback_t callback);

uint32_t ADC_ReadCh(ADC_Channel_E adc_ch_e);

#endif
