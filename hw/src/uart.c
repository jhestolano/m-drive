#include "uart.h"
#include <string.h>
#include "dbg.h"
#include "line.h"

/*-----------------------------------------------------------------------------
 * Macro definitions.
 *-----------------------------------------------------------------------------*/
#define UART_TX_DELAY (1)                       /* Uart xmit delay. */

/* Rx buffer shall remain one to generate an interrupt for each characeter, as the */
/* size of the message cannot be anticipated. Buffering will be done in software. */
#define UART_RX_BUFF_SIZE (1)                   /* Uart rx buffer. */

/*-----------------------------------------------------------------------------
 * Static global variable definitions.
 *-----------------------------------------------------------------------------*/
static UART_HandleTypeDef gs_uart_init_conf = UART_INIT_CONF;

static DMA_HandleTypeDef gs_uart_dma_conf = DMA_UART_INIT_CONF;

static uint8_t _uart_rx_buff[UART_RX_BUFF_SIZE];

/* This variable hold the function pointer to callback when a new char */
/* interrupt has been received. */
static uart_rx_callback_t gs_uart_rx_callback;

/*-----------------------------------------------------------------------------
 * Interface functions.
 *-----------------------------------------------------------------------------*/
void UART_ErrorHandler(char* errmsg) {
  DBG_ERR("%s", errmsg);
}

void HAL_UART_MspInit(UART_HandleTypeDef* s_uart_conf) {
  UNUSED(s_uart_conf);

  GPIO_InitTypeDef s_gpio_tx_conf = GPIOA_UART_TX_CONF;
  GPIO_InitTypeDef s_gpio_rx_conf = GPIOA_UART_RX_CONF;

  if(!__HAL_RCC_GPIOA_IS_CLK_ENABLED()) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }

  if(!__HAL_RCC_USART2_IS_CLK_ENABLED()) {
    __HAL_RCC_USART2_CLK_ENABLE();
  }

  HAL_GPIO_Init(UART_GPIO_PORT, &s_gpio_tx_conf);
  HAL_GPIO_Init(UART_GPIO_PORT, &s_gpio_rx_conf);

  /* Configure DMA. */
  if(!__HAL_RCC_DMA1_IS_CLK_ENABLED()) {
    __HAL_RCC_DMA1_CLK_ENABLE();
  }
  if(HAL_DMA_Init(&gs_uart_dma_conf) != HAL_OK) {
    UART_ErrorHandler("Error initializing UART & DMA");
  }
  __HAL_LINKDMA(&gs_uart_init_conf, hdmatx, gs_uart_dma_conf);

  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, UART_DMA_TX_PRIO, UART_DMA_TX_SUBPRIO);

  /* Transmission interrupt to trigger DMA transfer. */
  HAL_NVIC_SetPriority(USART2_IRQn, UART_DMA_TX_PRIO, UART_DMA_TX_SUBPRIO);

  /* Receive interrupt to handle commands. */
  HAL_NVIC_SetPriority(USART2_IRQn, UART_RX_PRIO, UART_RX_SUBPRIO);

  DBG_DEBUG("Uart enabled.\n\r");
}

void UART_EnableIRQ(void) {
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
  DBG_DEBUG("UART IRQ Enabled\n\r");
}

void UART_DisableIRQ(void) {
  HAL_NVIC_DisableIRQ(USART2_IRQn);
  HAL_NVIC_DisableIRQ(DMA1_Channel7_IRQn);
  DBG_DEBUG("UART IRQ Disabled\n\r");
}

void UART_Init(void) {

  if(HAL_UART_Init(&gs_uart_init_conf) != HAL_OK) {
    UART_ErrorHandler("Error initializing UART");
  }

  /* Should this one be called after Line/uCmd initialization? */
  if(HAL_UART_Receive_IT(&gs_uart_init_conf, _uart_rx_buff, UART_RX_BUFF_SIZE) != HAL_OK) {
    UART_ErrorHandler("Error start rx routine with interrupts.");
  }

  gs_uart_rx_callback = NULL;

  return;
}

void UART_Putc(uint8_t ch) {
  uint8_t buff = ch;
  HAL_UART_Transmit(&gs_uart_init_conf, &buff, 1, UART_TX_DELAY);
  return;
}

void UART_DMAPutBytes(uint8_t* bufdata, size_t bufsz) {
  if(HAL_UART_Transmit_DMA(&gs_uart_init_conf, bufdata, bufsz) != HAL_OK) {
  }
}

void UART_Puts(uint8_t* str) {
  HAL_UART_Transmit(&gs_uart_init_conf, str, strlen((const char*)str), UART_TX_DELAY);
}

void _putchar(char ch) {
  UART_Putc(ch);
}

/*-----------------------------------------------------------------------------
 * UART Interrupt functions. 
 *-----------------------------------------------------------------------------*/
void DMA1_Channel7_IRQHandler(void) {
  HAL_DMA_IRQHandler(&gs_uart_dma_conf);
}

void USART2_IRQHandler(void) {
  HAL_UART_IRQHandler(&gs_uart_init_conf);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  (void)huart;
  if(gs_uart_rx_callback) {
    gs_uart_rx_callback(_uart_rx_buff[0]);
  }
  if(HAL_UART_Receive_IT(&gs_uart_init_conf, _uart_rx_buff, UART_RX_BUFF_SIZE) != HAL_OK) {
    UART_ErrorHandler("Error start rx routine with interrupts.");
  }
}

void UART_AttachRxCallback(uart_rx_callback_t callback) {
  if(callback) {
    DBG_DEBUG("Attaching UART RX callback.\n\r");
    UART_DisableIRQ();
    gs_uart_rx_callback = callback;
    UART_EnableIRQ();
  } else {
    DBG_DEBUG("Invalid UART RX callback.\n\r");
  }
}

void UART_DettachRxCallback(void) {
  UART_DisableIRQ();
  DBG_DEBUG("Dettaching UART RX Callback.\n\r");
  gs_uart_rx_callback = NULL;
  UART_EnableIRQ();
}
