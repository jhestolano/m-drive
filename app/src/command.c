#include <string.h>
#include "command.h"
#include "anchor/console/console.h"
#include "uart.h"
#include "gpio.h"
#include "pmsm_ctrl_types.h"
#include "mtrif.h"
#include "dbg.h"

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

CONSOLE_COMMAND_DEF(set_ctrl, "Set control mode and target",
    CONSOLE_INT_ARG_DEF(mode, "0: DQ PWM; 1: Current; 2: Speed; 3: Position"),
    CONSOLE_INT_ARG_DEF(target, "Control target: 0: %; 1: mA; 2: RPM; 3: Deg")
);
static void set_ctrl_command_handler(const set_ctrl_args_t* args) {
  MtrCtlMd_T md_rqst;

  float target[3];
  bzero(target, sizeof(target));

  target[0] = args->target * 1.0e-3f;

  MtrIf_SetCtlMd(CTRL_MD_IFBK, target);

}
/* End of command definitions. */

/* Wrappers for Tx / Rx UART communication. */
static void wrap_write_fnc(const char* str) {
  DBG_DEBUG("Tx'd char!\n\r");
  UART_Puts(str);
}

#ifdef UART_RX_USE_IT
static void wrap_read_fnc(uint8_t ch) {
  /* This is interrupt context. Keep it short. */
  if(buff.cnt < BUFF_SIZE) {
    buff.mem[buff.cnt] = ch;
    buff.cnt++;
  }
}
#endif
/* End of wrappers. */

void command_init(void) {
  const console_init_t init_console = {
    .write_function = wrap_write_fnc,
  };
  bzero((void*)&buff, sizeof(buff));
  console_init(&init_console);
  console_command_register(led_set);
  console_command_register(set_ctrl);
#ifdef UART_RX_USE_IT
  UART_AttachRxCallback(wrap_read_fnc);
#endif
}

void command_exec(void) {
  /* Handle console processing and buffering here. */
#ifdef UART_RX_USE_IT
  COMMAND_LOCK();
  console_process(buff.mem, buff.cnt);
  buff.cnt = 0;
  COMMAND_UNLOCK();
#else
  uint8_t ch;
  int8_t ret = UART_Getc(&ch);
  if(ret == 0) {
    console_process(&ch, 1);
    DBG_DEBUG("Received char: %c!\n\r", ch);
  } else {
    /* DBG_WARN("UART Rx error!\n\r"); */
  }
#endif
}
