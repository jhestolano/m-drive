#ifndef UART_H
#define UART_H

#include "stdint.h"
#include "stddef.h"
#include "stm32f3xx_hal.h"
#include "printf.h"

/*******************************************************************************
 * UART MACRO DEFINITIONS.
*******************************************************************************/
#define UART_GPIO_PORT (GPIOA)
#define UART_TX_PIN (GPIO_PIN_2)
#define UART_RX_PIN (GPIO_PIN_3)

/*******************************************************************************
 * GPIO UART TX CONFIGURATION.
*******************************************************************************/
#define GPIOA_UART_TX_CONF {                                                   \
  .Pin = UART_TX_PIN,                                                          \
  .Mode = GPIO_MODE_AF_PP,                                                     \
  .Pull = GPIO_PULLUP,                                                         \
  .Speed = GPIO_SPEED_FREQ_HIGH,                                               \
  .Alternate = GPIO_AF7_USART2,                                                \
}

/*******************************************************************************
 * GPIO UART RX CONFIGURATION.
*******************************************************************************/
#define GPIOA_UART_RX_CONF {                                                   \
  .Pin = UART_RX_PIN,                                                          \
  .Mode = GPIO_MODE_AF_OD,                                                     \
  .Pull = GPIO_PULLUP,                                                         \
  .Speed = GPIO_SPEED_FREQ_HIGH,                                               \
  .Alternate = GPIO_AF7_USART2                                                 \
}

/*******************************************************************************
* UART INIT CONFIGURATION.
********************************************************************************
* Type: UART_HandleTypeDef. 
*******************************************************************************/
#define UART_INIT_CONF {                                                       \
  .Instance = USART2,                                                          \
  .Init = {                                                                    \
    .BaudRate = 2000000,                                                       \
    .WordLength = UART_WORDLENGTH_8B,                                          \
    .StopBits = UART_STOPBITS_1,                                               \
    .Parity = UART_PARITY_NONE,                                                \
    .HwFlowCtl = UART_HWCONTROL_NONE,                                          \
    .Mode = UART_MODE_TX_RX,                                                   \
  },                                                                           \
}

/*******************************************************************************
 * DMA CONFIGURATION FOR SIGNAL DEBUG
********************************************************************************
* Type: DMA_HandleTypeDef
*******************************************************************************/
#define DMA_UART_INIT_CONF {                                                   \
  .Instance = DMA1_Channel7,                                                   \
  .Init.Direction = DMA_MEMORY_TO_PERIPH,                                      \
  .Init.MemInc = DMA_MINC_ENABLE,                                              \
  .Init.PeriphInc = DMA_PINC_DISABLE,                                          \
  .Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE,                             \
  .Init.MemDataAlignment = DMA_MDATAALIGN_BYTE,                                \
  .Init.Mode = DMA_NORMAL,                                                     \
  .Init.Priority = DMA_PRIORITY_LOW,                                           \
}

#define UART_DMA_TX_PRIO (5)
#define UART_DMA_TX_SUBPRIO (0)

#define UART_RX_PRIO (5)
#define UART_RX_SUBPRIO (1)
/*******************************************************************************
*******************************************************************************/

typedef void(*uart_rx_callback_t)(uint8_t);

void UART_Init(void);

void UART_Putc(uint8_t ch);

void UART_Puts(uint8_t* str);

void UART_DMAPutBytes(uint8_t* bufdata, size_t bufsz);

void UART_AttachRxCallback(uart_rx_callback_t callback);

void UART_DisableIRQ(void);

void UART_EnableIRQ(void);

#endif // UART_H
