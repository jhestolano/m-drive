#include "gpio.h"
#include "dbg.h"

typedef struct _gpio_pin_map {
  uint16_t pin;
  GPIO_TypeDef* port;
} _gpio_pin_map_s;

static const _gpio_pin_map_s gsc_gpio_pin_map[] = {
  {.pin = UH_PWM_ENABLE_PIN, .port = UH_PWM_ENABLE_PORT},
  {.pin = VH_PWM_ENABLE_PIN, .port = VH_PWM_ENABLE_PORT},
  {.pin = WH_PWM_ENABLE_PIN, .port = WH_PWM_ENABLE_PORT},
  {.pin = BKIN2_PIN, .port = BKIN2_PORT},
  {.pin = RED_LED_PIN, .port = RED_LED_PORT},
};

void GPIO_Init(void) {

  GPIO_InitTypeDef s_gpioc_input_conf = GPIOC_INPUT_CONF;
  GPIO_InitTypeDef s_gpioa_output_conf = GPIOA_OUTPUT_CONF;
  GPIO_InitTypeDef s_gpioa_pwm_enable_conf = GPIOA_PWM_ENABLE_CONF;
  GPIO_InitTypeDef s_gpioa_bkin2_conf = GPIOA_BKIN2_CONF;
  GPIO_InitTypeDef s_gpioa_diag_conf = GPIOA_DIAG_CONF;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  HAL_GPIO_Init(USR_BUTTON_PORT, &s_gpioc_input_conf);
  HAL_GPIO_Init(RED_LED_PORT, &s_gpioa_output_conf);
  HAL_GPIO_Init(XH_PWM_ENABLE_PORT, &s_gpioa_pwm_enable_conf);

  /* Start motor unarmed. Wait for Motor interface to enable it. */
  HAL_GPIO_Init(BKIN2_PORT, &s_gpioa_bkin2_conf);
  HAL_GPIO_WritePin(BKIN2_PORT, BKIN2_PIN, GPIO_PIN_RESET);

  /* Configure DIAG pin external interrupt. */
  HAL_GPIO_Init(DIAG_PORT, &s_gpioa_diag_conf);
  HAL_NVIC_SetPriority(DIAG_IT_EXTI_IRQn, DIAG_IT_PRIO, DIAG_IT_SUBPRIO);
  HAL_NVIC_EnableIRQ(DIAG_IT_EXTI_IRQn);

  HAL_GPIO_WritePin(GREEN_LED_PORT, GREEN_LED_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(XH_PWM_ENABLE_PORT, UH_PWM_ENABLE_PIN | VH_PWM_ENABLE_PIN | WH_PWM_ENABLE_PIN, GPIO_PIN_RESET);

  return;
}

void GPIO_LedToggle(void) {
  HAL_GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
  return;
}

void GPIO_DiagCallback(void) {
  /* Might need to add check if it was us who disabled the motors */
  /* and not the actual motor driver due to overtemperature. */
  HAL_GPIO_WritePin(BKIN2_PORT, BKIN2_PIN, GPIO_PIN_RESET);
  DBG_ERR("Driver overtemperature detected!!!\n\r");
}

void EXTI9_5_IRQHandler(void) {
  HAL_GPIO_EXTI_IRQHandler(DIAG_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin) {
  switch(gpio_pin) {
    case DIAG_PIN: 
      GPIO_DiagCallback();
      break;
#ifdef CONF_ENC_CH_IDX_ENBL
    case ENC_CH_IDX_PIN:
      ENC_ChIdxCallback();
      break;
#endif
  }
}

void GPIO_Set(uint16_t pin) {
  HAL_GPIO_WritePin(gsc_gpio_pin_map[pin].port, gsc_gpio_pin_map[pin].pin, GPIO_PIN_SET);
}

void GPIO_Reset(uint16_t pin){
  HAL_GPIO_WritePin(gsc_gpio_pin_map[pin].port, gsc_gpio_pin_map[pin].pin, GPIO_PIN_RESET);
}

