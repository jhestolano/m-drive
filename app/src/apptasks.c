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
#include "command.h"
#include "ctrl.h"
#include "DBG_BUS.h"

extern int32_t IfbkBuffer[300];

#define SLOG_START_FRAME (0x00CD00AB)
/* Size definition in bytes. */
#define SLOG_START_FRAME_SIZE (sizeof(int32_t))
#define SLOG_MOTOR_CONTROL_BUFF_SIZE (sizeof(int32_t) * APP_TASK_MOTOR_CONTROL_N_SIGNALS)
#define SLOG_ADC_ISR_BUFF_SIZE (sizeof(int32_t) * ADC_ISR_N_SIGNALS)
#define SLOG_BUFF_SIZE ((size_t)(SLOG_START_FRAME_SIZE + SLOG_MOTOR_CONTROL_BUFF_SIZE + SLOG_ADC_ISR_BUFF_SIZE))

void AppTask_LowPrio(void* params) {
  const uint32_t SlogStartFrame = (uint32_t)SLOG_START_FRAME;
  uint8_t buff_signal_log[SLOG_BUFF_SIZE] = {0};
  TickType_t last_wake_time = xTaskGetTickCount();
  StreamBufferHandle_t stream_buff_motor_control = (StreamBufferHandle_t)params;
  for(;;) {

    /* Application code goes here. */
    command_update();

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
  StreamBufferHandle_t stream_buff = (StreamBufferHandle_t)params;
  MtrIf_Init();
#ifdef __SLOG__
  float signal_buff[APP_TASK_MOTOR_CONTROL_N_SIGNALS] = {0};
#endif
  uint16_t tmr = 0;
  int32_t cnt = 0;
  for(;;) {

    /* Motor control goes here. */
    Ctrl_Slow();

    signal_buff[0] = (float)MtrIf_GetPos();
    signal_buff[1] = (float)MtrIf_GetVin();
    signal_buff[2] = (float)MtrIf_GetIfbk();
    signal_buff[3] = (float)MtrIf_GetSpd();
    signal_buff[4] = (float)rtY.MtrIf_Ref;
    signal_buff[5] = (float)rtY.DBG_BUS_OUT.Status;
    signal_buff[6] = (float)rtY.DBG_BUS_OUT.Rest;
    signal_buff[7] = (float)rtY.DBG_BUS_OUT.Lest;
    signal_buff[8] = (float)rtY.DBG_BUS_OUT.KTrqEst;
    if(rtY.DBG_BUS_OUT.Status == 255) {
      signal_buff[9] = IfbkBuffer[cnt++];
      if(cnt > 999) {
        /* cnt = 0; */
        cnt = 999;
      }
    } else {
      signal_buff[9] = 0;
    }
    signal_buff[10] = (float)rtY.DBG_BUS_OUT.JEst;
    signal_buff[11] = (float)rtY.DBG_BUS_OUT.KFrcEst;
    signal_buff[12] = (float)rtY.DBG_BUS_OUT.IfbkSteady;
    signal_buff[13] = (float)rtY.DBG_BUS_OUT.IfbkMax;


#ifdef __SLOG__
    xStreamBufferSend(stream_buff,
        (void*)signal_buff,
        sizeof(signal_buff),
        0);
#endif

    vTaskDelayUntil(&last_wake_time, APP_TASK_MOTOR_CONTROL_TS); 
  }
}
