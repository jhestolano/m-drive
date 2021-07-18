#include <string.h>
#include "command.h"
#include "anchor/console/console.h"
#include "uart.h"
#include "gpio.h"
#include "pmsm_ctrl_types.h"
#include "mtrif.h"

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

  float tgt;
  float target[3];
  bzero(target, sizeof(target));

  switch(args->mode) {
    case 0:
      md_rqst = CTRL_MD_OFF;
      tgt = 0;
      break;
    case 1:
      tgt = (float)args->target / 100.0f;
      if(tgt > 1.0f) {
        tgt = 1.0f;
      }
      if(tgt < 0.0f) {
        tgt = 0.0f;
      }
      md_rqst = CTRL_MD_DQ_PWM;
      target[1] = tgt; /* Set Q-Component */
      break;
    case 2:
      tgt = (float)args->target / 1000.0f;
      if(tgt > 1.0f) {
        tgt = 1.0f;
      }
      if(tgt < 0.0f) {
        tgt = 0.0f;
      }
      md_rqst = CTRL_MD_IFBK;
      target[0] = tgt;
      break;
    default:
      md_rqst = CTRL_MD_OFF;
      tgt = 0;
  }

  MtrIf_SetCtlMd(md_rqst, target);

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
  console_command_register(set_ctrl);
  UART_AttachRxCallback(wrap_read_fnc);
}

void command_exec(void) {
  /* Handle console processing and buffering here. */
  COMMAND_LOCK();
  console_process(buff.mem, buff.cnt);
  buff.cnt = 0;
  COMMAND_UNLOCK();
}
