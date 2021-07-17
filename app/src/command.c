#include <string.h>
#include "command.h"
#include "anchor/console/console.h"
#include "uart.h"
#include "gpio.h"

#define COMMAND_LOCK UART_DisableIRQ
#define COMMAND_UNLOCK UART_EnableIRQ

#define BUFF_SIZE (64)

typedef struct Buff_tag {
  uint8_t mem[BUFF_SIZE]; /* Memory. */
  size_t cnt; /* Number of elements in buffer. */
} Buff_S;

const console_init_t init_console;
Buff_S buff;

/* Command defintions. */
CONSOLE_COMMAND_DEF(led_set, "Set user LED value",
    CONSOLE_INT_ARG_DEF(value, "The value <0-1>")
);
static void led_set_command_handler(const led_set_args_t* args) {
  HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, (GPIO_PinState)args->value);
}

CONSOLE_COMMAND_DEF(set_dc, "Set motor duty cycle Q-Axis",
    CONSOLE_INT_ARG_DEF(value, "The value <0-100>")
);
static void set_dc_command_handler(const set_dc_args_t* args) {

}
/* End of command definitions. */

/* Wrappers for Tx / Rx UART communication. */
static void wrap_write_fnc(const char* str) {
  UART_Puts(str);
}

static void wrap_read_fnc(uint8_t ch) {
  /* This is interrupt context. Keep it short. */
  if(buff.cnt < BUFF_SIZE) {
    buff.mem[buff.cnt] = ch;
    buff.cnt++;
  }
}
/* End of wrappers. */

void command_init(void) {
  const console_init_t init_console = {
    .write_function = wrap_write_fnc,
  };
  bzero((void*)&buff, sizeof(buff));
  console_init(&init_console);
  console_command_register(led_set);
  console_command_register(set_dc);
  UART_AttachRxCallback(wrap_read_fnc);
}

void command_exec(void) {
  /* Handle console processing and buffering here. */
  COMMAND_LOCK();
  console_process(buff.mem, buff.cnt);
  buff.cnt = 0;
  COMMAND_UNLOCK();
}
