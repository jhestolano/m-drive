#include <stdint.h>
#include <stdio.h>
#include "gpio.h"

uint16_t gs_gpio_pin;

void GPIO_Set(uint16_t pin) {
  gs_gpio_pin = pin;
}

void GPIO_Reset(uint16_t pin){
  gs_gpio_pin = pin;
}
