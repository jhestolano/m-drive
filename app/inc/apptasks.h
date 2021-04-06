#ifndef APP_TASK_H
#define APP_TASK_H

#include "mtrif.h"

/*-----------------------------------------------------------------------------
 * Signal logging task definitions.
 *-----------------------------------------------------------------------------*/
#define APP_TASK_SLOG_TS (1)
#define APP_TASK_SLOG_PRIO (2)
/* Stack size: word size, not bytes: 300 implies 1200 bytes. */
#define APP_TASK_SLOG_STACK_SIZE (200)

/*-----------------------------------------------------------------------------
 * Motor control task definitions.
 *-----------------------------------------------------------------------------*/
#define APP_TASK_MOTOR_CONTROL_TS (1)
#define APP_TASK_MOTOR_CONTROL_PRIO (3)
#define APP_TASK_MOTOR_CONTROL_STACK_SIZE (200)
#define APP_TASK_MOTOR_CONTROL_N_SIGNALS (15)
#define ADC_ISR_N_SIGNALS (0)

void AppTask_LowPrio(void* params);

void AppTask_MotorControl(void* params);

/* MtrIf_S* AppTask_GetMtrIf(void); */

#endif // APP_TASK_H
