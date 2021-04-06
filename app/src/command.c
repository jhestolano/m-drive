#include "command.h"
#include "ucmd.h"
#include "line.h"
#include "dbg.h"

extern void GPIO_LedToggle(void);
extern void MtrIf_SetVin(int32_t);

/******************************************************************************/
/* Callback definitions. */
/******************************************************************************/
static ErrCode_e command_led_toggle(Arg_s* args, void* usrargs) {
  (void)args;
  (void)usrargs;
  GPIO_LedToggle();
  return E_OK;
}

static ErrCode_e command_motor_vin(Arg_s* args, void* usrargs) {
  int32_t data = -1;
  (void)usrargs;
  if(UCMD_ARG_IS_VALID(args, 0)) {
    data = UCMD_ARG(args, 0, int32_t);
    MtrIf_SetVin(data);
  }
  DBG_DEBUG("motor data: %d\n\r", data);
  return E_OK;
}

/******************************************************************************/
/* Table definition. */
/******************************************************************************/
const uCmdInfo_s CommandTable_a[] = {
  {"led_toggle", command_led_toggle, UCMD_ARG_NONE, UCMD_ARG_USER_NONE},
  {"motor_vin", command_motor_vin, {{E_ARG_I32, 'v'}}, UCMD_ARG_USER_NONE},
  /* Keep this element last. Denotes end of table. */
  UCMD_TABLE_END,
};

void command_init(void) {
  Line_Init();
  uCmd_InitTable(CommandTable_a, UCMD_GET_TABLE_SIZE(CommandTable_a));
}

void command_update(void) {
  uCmd_Loop();
}

void command_uart_rx_callback(uint8_t data) {
  Line_AddChar(data);
  if(Line_BuffIsFull()) {
    DBG_WARN("Buffer is full!\n\r");
  } if(Line_BuffIsOvrFlwn()) {
    DBG_WARN("Buffer overflow!!\n\r");
  }
}
