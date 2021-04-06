#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <stdint.h>

void command_init(void);

void command_update(void);

void command_uart_rx_callback(uint8_t);

#endif // _COMMAND_H_
