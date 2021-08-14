#include "uart.h"
#include <string.h>
#include "dbg.h"

/*-----------------------------------------------------------------------------
 * Macro definitions.
 *-----------------------------------------------------------------------------*/
#define UART_TX_DELAY (1)                       /* Uart xmit delay. */

/*-----------------------------------------------------------------------------
 * Static global variable definitions.
 *-----------------------------------------------------------------------------*/
static UART_HandleTypeDef gs_uart_init_conf = UART_INIT_CONF;

static DMA_HandleTypeDef gs_uart_dma_conf = DMA_UART_INIT_CONF;

static DMA_HandleTypeDef gs_uart_dma_rx_conf = DMA_UART_RX_INIT_CONF;

#define UART_RX_DMA_BUFF_SIZE (255)

static uint8_t _uart_rx_dma_buff[UART_RX_DMA_BUFF_SIZE];

/* This variable hold the function pointer to callback when a new char */
/* interrupt has been received. */
static uart_rx_callback_t gs_uart_rx_callback;

/*-----------------------------------------------------------------------------
 * Static functions.
 *-----------------------------------------------------------------------------*/
static void _dma_rx_cplt_cb(DMA_HandleTypeDef* dma) { return; }

static void _dma_rx_half_cplt_cb(DMA_HandleTypeDef* dma) { return; }

static void _dma_rx_err_cb(DMA_HandleTypeDef* dma) { return; }

static void _dma_rx_abort_cb(DMA_HandleTypeDef* dma) { return; }

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

  if(HAL_DMA_Init(&gs_uart_dma_rx_conf) != HAL_OK) {
    UART_ErrorHandler("Error initializing UART & DMA");
  }

  /* Set UART RX callbacks. */
  gs_uart_dma_rx_conf.XferCpltCallback = _dma_rx_cplt_cb;
  gs_uart_dma_rx_conf.XferHalfCpltCallback = _dma_rx_half_cplt_cb;
  gs_uart_dma_rx_conf.XferErrorCallback = _dma_rx_err_cb;
  gs_uart_dma_rx_conf.XferAbortCallback = _dma_rx_abort_cb;

  __HAL_LINKDMA(&gs_uart_init_conf, hdmatx, gs_uart_dma_conf);

  __HAL_LINKDMA(&gs_uart_init_conf, hdmarx, gs_uart_dma_rx_conf);

  /* Enable idle line detection interrupt. */
  __HAL_UART_ENABLE_IT(&gs_uart_init_conf, UART_IT_IDLE);

  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, UART_DMA_TX_PRIO, UART_DMA_TX_SUBPRIO);

  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, UART_DMA_RX_PRIO, UART_DMA_RX_SUBPRIO);

  HAL_NVIC_SetPriority(USART2_IRQn, UART_IRQ_PRIO, UART_IRQ_SUBPRIO);

  DBG_DEBUG("Uart enabled.\n\r");
}

void UART_EnableIRQ(void) {
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  DBG_DEBUG("UART IRQ Enabled\n\r");
}

void UART_DisableIRQ(void) {
  HAL_NVIC_DisableIRQ(DMA1_Channel7_IRQn);
  HAL_NVIC_DisableIRQ(DMA1_Channel6_IRQn);
  HAL_NVIC_DisableIRQ(USART2_IRQn);
  DBG_DEBUG("UART IRQ Disabled\n\r");
}

void UART_Init(void) {

  if(HAL_UART_Init(&gs_uart_init_conf) != HAL_OK) {
    UART_ErrorHandler("Error initializing UART");
  }

  HAL_UART_Receive_DMA(&gs_uart_init_conf, _uart_rx_dma_buff, UART_RX_DMA_BUFF_SIZE);

  gs_uart_rx_callback = NULL;

  return;
}

int8_t UART_Getc(uint8_t* ch) {
  int8_t ret = -1;
  HAL_StatusTypeDef st = HAL_UART_Receive(&gs_uart_init_conf, ch, sizeof(uint8_t), 0); 
  if(st == HAL_OK) {
    ret =0;
  }
  return ret;
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

void DMA1_Channel7_IRQHandler(void) {
  HAL_DMA_IRQHandler(&gs_uart_dma_conf);
}

void DMA1_Channel6_IRQHandler(void) {
  HAL_DMA_IRQHandler(&gs_uart_dma_rx_conf);
}

static void _uart_rx_idle_callback(void) {
  size_t cnt;
  if(gs_uart_rx_callback) {
    HAL_UART_DMAStop(&gs_uart_init_conf); 
    cnt = UART_RX_DMA_BUFF_SIZE - __HAL_DMA_GET_COUNTER(&gs_uart_dma_rx_conf);
    gs_uart_rx_callback(&_uart_rx_dma_buff[0], cnt);
    bzero((void*)&_uart_rx_dma_buff[0], UART_RX_DMA_BUFF_SIZE);
    HAL_UART_Receive_DMA(&gs_uart_init_conf, _uart_rx_dma_buff, UART_RX_DMA_BUFF_SIZE);
  }
}

void USART2_IRQHandler(void) {
  /* Manage HAL related work. */
  HAL_UART_IRQHandler(&gs_uart_init_conf);

  /* Manage other interrupts. */
  if(__HAL_UART_GET_FLAG(&gs_uart_init_conf, UART_FLAG_IDLE)) {
    _uart_rx_idle_callback();
    __HAL_UART_CLEAR_IDLEFLAG(&gs_uart_init_conf);
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

void UART_TxPause(void) {
  HAL_UART_DMAPause(&gs_uart_init_conf);
}

void UART_TxResume(void) {
  HAL_UART_DMAResume(&gs_uart_init_conf);
}

void UART_RxPause(void) {
  HAL_NVIC_DisableIRQ(DMA1_Channel6_IRQn);
}

void UART_RxResume(void) {
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
}
