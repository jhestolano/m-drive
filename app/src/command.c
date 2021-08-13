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

/* Callbacks. */
extern void cb_cal_done(CalJob_T);
/* End callbacks. */

char* _cal_job_to_str_map[] = {
  "None",
  "Encoder Offset",
  "Resistance",
  "Inductance",
  "Current Sens. Offset",
  "Mech. Params.",
  "Current Ctrl. Gains",
  "Motion Ctrl. Gains",
  "Invalid",
};

#define BUFF_SIZE (255)

typedef struct Buff_tag {
  uint8_t mem[BUFF_SIZE]; /* Memory. */
  size_t cnt; /* Number of elements in g_buffer. */
} Buff_S;

const console_init_t init_console;
Buff_S g_buff;

/* Command defintions. */
CONSOLE_COMMAND_DEF(led_set, "Set user LED value",
    CONSOLE_INT_ARG_DEF(value, "The value <0-1>")
);
static void led_set_command_handler(const led_set_args_t* args) {
  HAL_GPIO_WritePin(RED_LED_PORT, RED_LED_PIN, (GPIO_PinState)args->value);
}

CONSOLE_COMMAND_DEF(cal, "Calibration routines",
    CONSOLE_INT_ARG_DEF(mode, "Enc. Ofs (0); Res (1); Ind (2); Current Sens. Ofs. (3); Mech. Params (4); Current Ctrl. Gains (5); Motion Ctrl. Gains (6).")
);
static void cal_command_handler(const cal_args_t* args) {
  MtrParams_S params = {0};
  int32_t ret;
  MtrIfCalJob_S job = {
    .job = CAL_JOB_NONE,
    .on_err = NULL,
    .on_done = NULL,
  };
  CalJob_T mode = (CalJob_T)(args->mode + 1);
  if((mode > CAL_JOB_MAX) || (mode <= CAL_JOB_NONE)) {
    printf("Out of range.\n\r");
    return;
  }
  printf("CAL RQST: %s\n\r",  _cal_job_to_str_map[(int32_t)mode]);
  job.job = mode;
  ret = MtrIf_CalJobReq(&job);
  if(ret != MTRIF_ST_OK) {
    printf("Not OK: %d\n\r", ret);
    return;
  }
  printf("OK.\n\r");
  ret = MtrIf_WaitPending();
  if(ret == MTRIF_ST_ERR) {
    printf("CAL ERROR.\n\r");
  } else {
    printf("CAL OK: %d\n\r", ret);
  }
  MtrIf_GetMtrParams(&params);
  switch(mode) {
    case CAL_JOB_ENC_OFS:
      printf("Offset: %d counts\n\r", params.enc_ofs);
      printf("Pole pairs: %d\n\r", params.pole_pairs);
      break;
    case CAL_JOB_RES:
      printf("Resistance: %f ohms\n\r", params.resistance);
      break;
    case CAL_JOB_IND:
      printf("Inductance: %fmH\n\r", params.inductance * MTRIF_TO_MILLIS);
      break;
    case CAL_JOB_IFBK_OFS:
      printf("Phase 1 offset: %fmA\n\r", params.ifbk_ofs[0] * MTRIF_TO_MILLIS);
      printf("Phase 2 offset: %fmA\n\r", params.ifbk_ofs[1] * MTRIF_TO_MILLIS);
      printf("Phase 3 offset: %fmA\n\r", params.ifbk_ofs[2] * MTRIF_TO_MILLIS);
      break;
    case CAL_JOB_MECH_PARAMS:
      break;
    case CAL_JOB_IFBK_CTRL:
      break;
    case CAL_JOB_MOTN_CTRL:
      break;
  }
}

CONSOLE_COMMAND_DEF(info, "Motor state info.");
static void info_command_handler(const info_args_t* args) {
  MtrParams_S params;
  float ifbk[3];
  MtrIf_GetIfbk(&ifbk[0]);
  MtrIf_GetMtrParams(&params);
  printf("Temp: %f deg\n\r", MtrIf_GetTemp());
  printf("Bus voltage: %f volts\n\r", MtrIf_GetVBus());
  printf("Offset: %d counts\n\r", params.enc_ofs);
  printf("Resistance: %f ohm\n\r", params.resistance);
  printf("Inductance: %f mH\n\r", params.inductance * MTRIF_TO_MILLIS);
  printf("Pole pairs: %d\n\r", params.pole_pairs);
  printf("Speed: %f rad/s\n\r", MtrIf_GetSpd());
  printf("Position: %d counts\n\r", App_GetEncCnt());
  printf("Control mode: %d\n\r", 0);
  printf("Status: %d\n\r", 0);
  printf("PhA current: %f mA\n\r", ifbk[0] * MTRIF_TO_MILLIS);
  printf("PhB current: %f mA\n\r", ifbk[1] * MTRIF_TO_MILLIS);
  printf("PhC current: %f mA\n\r", ifbk[2] * MTRIF_TO_MILLIS);
}

CONSOLE_COMMAND_DEF(pwm, "PWM control mode",
    CONSOLE_INT_ARG_DEF(dc, "Duty cycle (%)")
);
static void pwm_command_handler(const pwm_args_t* args) {
  int32_t ret;
  printf("Error: Unimplemented\n\r");
  return;
  if(args->dc > 100 || args->dc < -100) {
    printf("Error: Out of range");
    return;
  }
  /* ret = MtrIf_CtrlJobReq(args->dc); */
  if(ret != MTRIF_ST_OK) {
    printf("Not OK: %d\n\r", ret);
  }
  printf("OK.\n\r");
}

CONSOLE_COMMAND_DEF(ctrl, "Request control job",
    CONSOLE_INT_ARG_DEF(mode, "Control mode: OFF (0), PWM(1, %), IFBK(2, mA), SPD(3, RPM), POS(4, Counts)"),
    CONSOLE_INT_ARG_DEF(target, "Control target")
);
static void ctrl_command_handler(const ctrl_args_t* args) {
  MtrIfCtrlJob_S job;
  int32_t ret;
  const float k_tgt[] = {0.0f, 0.01f, 1.0e-3f, 1.0f, 1.0f};
  if(args->mode < 0 || args->mode > 4) {
    printf("Out of range.\n\r");
    return;
  }
  job.tgt = k_tgt[args->mode] * (float)args->target;
  job.job = (CtrlJob_T)args->mode;
  ret = MtrIf_CtrlJobReq(&job);
  if(ret != MTRIF_ST_OK) {
    printf("Not OK: %d\n\r", ret);
  } else{
    printf("OK.\n\r");
  }
}
/* End of command definitions. */

/* Wrappers for Tx / Rx UART communication. */
static void wrap_write_fnc(const char* str) {
  DBG_DEBUG("Tx'd char!\n\r");
  UART_Puts(str);
}

static void wrap_read_fnc(uint8_t* mem, size_t sz) {
  /* This is interrupt context. Keep it short. */
  if(!mem) {
    return;
  }
  /* Is there space in the buffer? */
  if((g_buff.cnt + sz) < BUFF_SIZE) {
    memcpy((void*)&g_buff.mem[g_buff.cnt], (void*)mem, sz);
    g_buff.cnt += sz;
  } else {
    /* Implement actions for overflow events. */
  }
}
/* End of wrappers. */

void command_init(void) {
  const console_init_t init_console = {
    .write_function = wrap_write_fnc,
  };
  bzero((void*)&g_buff, sizeof(g_buff));
  console_init(&init_console);
  console_command_register(led_set);
  console_command_register(cal);
  console_command_register(pwm);
  console_command_register(info);
  console_command_register(ctrl);

  /* Attach interrupt context callback to copy data into */
  /* local g_buffer. Processing happens in RTOS task. */
  UART_AttachRxCallback(wrap_read_fnc);
}

void command_exec(void) {
  /* Handle console processing and buffering here. */
  COMMAND_LOCK();
  console_process(g_buff.mem, g_buff.cnt);
  g_buff.cnt = 0;
  COMMAND_UNLOCK();
}
