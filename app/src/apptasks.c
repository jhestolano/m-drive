#include <string.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "task.h"
#include "apptasks.h"
#include "dbg.h"
#include "uart.h"
#include "app.h"
#include "tmr.h"
#include "mtrif.h"
#include "math.h"
#include "gpio.h"
#include "mtrif.h"
#include "command.h"

#define SLOG_START_FRAME (0x00CD00AB)
/* Size definition in bytes. */
#define SLOG_START_FRAME_SIZE (sizeof(int32_t))
#define SLOG_MOTOR_CONTROL_BUFF_SIZE (sizeof(int32_t) * APP_TASK_MOTOR_CONTROL_N_SIGNALS)
#define SLOG_ADC_ISR_BUFF_SIZE (sizeof(int32_t) * ADC_ISR_N_SIGNALS)
#define SLOG_BUFF_SIZE ((size_t)(SLOG_START_FRAME_SIZE + SLOG_MOTOR_CONTROL_BUFF_SIZE + SLOG_ADC_ISR_BUFF_SIZE))

void AppTask_LowPrio(void* params) {
#ifdef __SLOG__
  const uint32_t SlogStartFrame = (uint32_t)SLOG_START_FRAME;
  uint8_t buff_signal_log[SLOG_BUFF_SIZE] = {0};
  StreamBufferHandle_t stream_buff_motor_control = (StreamBufferHandle_t)params;
#endif
  TickType_t last_wake_time = xTaskGetTickCount();

  command_init();

  for(;;) {

    /* Application code goes here. */
    command_exec();

#ifdef __SLOG__
    /*-----------------------------------------------------------------------------
     * Signal logging. 
     *-----------------------------------------------------------------------------*/
    /* Make sure start header is always correct. */
    memcpy((void*)buff_signal_log, (void*)((uint8_t*)&SlogStartFrame), (size_t)SLOG_START_FRAME_SIZE);
    xStreamBufferReceive(stream_buff_motor_control,
                         /* Element 0 reserved for header. */
                         (void*)&buff_signal_log[SLOG_START_FRAME_SIZE],
                         (size_t)SLOG_MOTOR_CONTROL_BUFF_SIZE,
                         /* Do not wait. */
                         0);
    UART_DMAPutBytes((uint8_t*)buff_signal_log, sizeof(buff_signal_log));
#endif
    /*-----------------------------------------------------------------------------
     * Handle command line. 
     *-----------------------------------------------------------------------------*/
    vTaskDelayUntil(&last_wake_time, APP_TASK_SLOG_TS);
  }
}


void AppTask_MotorControl(void* params) {
  TickType_t last_wake_time = xTaskGetTickCount();
  MtrParams_S mtr_params;
  MtrDbg_S mtr_dbg;
  float ifbk_dq[2];
  float pwm_dq[2];

#ifdef __SLOG__
  StreamBufferHandle_t stream_buff = (StreamBufferHandle_t)params;
  float signal_buff[APP_TASK_MOTOR_CONTROL_N_SIGNALS] = {0};
#endif

  MtrIf_Init();

  for(;;) {

    /* Motor control goes here. */
    MtrIf_CtrlSlow();

    /* Get data from control layer. */
    MtrIf_GetMtrParams(&mtr_params);
    MtrIf_GetDbg(&mtr_dbg);
    MtrIf_GetIfbkDq(ifbk_dq);
    MtrIf_GetPwmDq(pwm_dq);

#ifdef __SLOG__
    signal_buff[0] = (float)MtrIf_GetPos();
    signal_buff[1] = (float)MtrIf_GetSpd();
    signal_buff[2] = (float)MtrIf_GetIfbkPh(IfbkPhA_E);
    signal_buff[3] = (float)MtrIf_GetIfbkPh(IfbkPhB_E);
    signal_buff[4] = (float)MtrIf_GetIfbkPh(IfbkPhC_E);
    signal_buff[5] = (float)MtrIf_GetPwmDcCh(PwmChA_E);
    signal_buff[6] = (float)MtrIf_GetPwmDcCh(PwmChB_E);
    signal_buff[7] = (float)MtrIf_GetPwmDcCh(PwmChC_E);
    signal_buff[8] = mtr_dbg.e_angl; /* Electrical angle. */
    signal_buff[9] = mtr_dbg.i_abc_lpf[0];
    signal_buff[10] = mtr_dbg.i_abc_lpf[1];
    signal_buff[11] = mtr_dbg.i_abc_lpf[2];
    signal_buff[12] = mtr_dbg.i_dq0[0]; /* D-component. */
    signal_buff[13] = mtr_dbg.i_dq0[1]; /* Q-component. */

    xStreamBufferSend(stream_buff,
        (void*)signal_buff,
        sizeof(signal_buff),
        0);
#endif

    vTaskDelayUntil(&last_wake_time, APP_TASK_MOTOR_CONTROL_TS); 
  }
}
