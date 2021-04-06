#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"
#include "adc.h"
#include "gpio.h"
#include "tmr.h"
#include "pwm.h"
#include "enc.h"
#include "uart.h"
#include "dbg.h"
#include "apptasks.h"
#include "command.h"

__attribute__((section("ccmram")))
uint8_t ucHeap[configTOTAL_HEAP_SIZE];

static void SystemClock_Config(void);
static void Error_Handler(void);
static void HwInit(void);
void vAssertCalled( const char *pcFile, int32_t ulLine );

int main(void)
{

  StreamBufferHandle_t buff_motor_control = xStreamBufferCreate (
      APP_TASK_MOTOR_CONTROL_N_SIGNALS * sizeof(int32_t),
      /* Read buffer when all signals have been transmitted. */
      /* This should happen regardless, since the OS is not */
      /* in preemptive mode. */
      APP_TASK_MOTOR_CONTROL_N_SIGNALS * sizeof(int32_t)
  );

  HwInit();
  /* command_init(); */
  /* UART_AttachRxCallback(command_uart_rx_callback); */
  /* UART_EnableIRQ(); */

  /*-----------------------------------------------------------------------------
   * Low priority task for logging, command line, etc. 
   *-----------------------------------------------------------------------------*/
  xTaskCreate (
      AppTask_LowPrio,
      (const char* const)"SignalLog",
      APP_TASK_SLOG_STACK_SIZE,
      /* pvParameters. */
      (void*)buff_motor_control,
      APP_TASK_SLOG_PRIO,
      /* pxCreatedTask. */
      NULL
  );

  /*-----------------------------------------------------------------------------
   * High priority task for motor control @ 1ms. 
   *-----------------------------------------------------------------------------*/
  xTaskCreate (
      AppTask_MotorControl,
      (const char* const)"MotorControl",
      APP_TASK_MOTOR_CONTROL_STACK_SIZE,
      /* pvParameters. */
      (void*)buff_motor_control,
      APP_TASK_MOTOR_CONTROL_PRIO,
      /* pxCreatedTask. */
      NULL
  );

  vTaskStartScheduler();
  for(;;) {  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                              | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

static void Error_Handler(void)
{
  while(1)
  {
  }
}

void vAssertCalled( const char *pcFile, int32_t ulLine )
{
volatile unsigned long ul = 0;

  ( void ) pcFile;
  ( void ) ulLine;

  taskENTER_CRITICAL();
  {
    /* Set ul to a non-zero value using the debugger to step out of this
       function. */
    DBG_ERR("Assertion Error: %s : %d\n\r", pcFile, ulLine);

    /* Invoke debugger if this line is reached. */
    __asm("BKPT #0\n");

    while( ul == 0 )
    {
      __NOP();
    }
  }
  taskEXIT_CRITICAL();
}

void HwInit(void) {
  HAL_Init();
  SystemClock_Config();
  GPIO_Init();
  UART_Init();
  TMR_Init();
  PWM_Init();
  ENC_Init();
  ADC_Init();
}

