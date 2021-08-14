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

#ifdef __SLOG__
  MtrParams_S mtr_params;
  MtrDbg_S mtr_dbg;
  MtrStats_S mtr_stats;
  float ifbk_dq[2];
  float pwm_dq[2];
  StreamBufferHandle_t stream_buff = (StreamBufferHandle_t)params;
  float signal_buff[APP_TASK_MOTOR_CONTROL_N_SIGNALS] = {0};
#endif

  MtrIf_Init();

  for(;;) {

    /* Motor control goes here. */
    MtrIf_CtrlSlow();

    /* Get data from control layer. */
#ifdef __SLOG__

    MtrIf_GetMtrParams(&mtr_params);
    MtrIf_GetDbg(&mtr_dbg);
    MtrIf_GetIfbkDq(ifbk_dq);
    MtrIf_GetPwmDq(pwm_dq);
    MtrIf_GetStats(&mtr_stats);

    signal_buff[0] = (float)mtr_dbg.mtr_if_enc_cnts;
    signal_buff[1] = (float)MtrIf_GetSpd();
    signal_buff[2] = (float)mtr_dbg.mtrif_ifbk_act[0];
    signal_buff[3] = (float)mtr_dbg.mtrif_ifbk_act[1];
    signal_buff[4] = (float)mtr_dbg.mtrif_ifbk_act[2];
    signal_buff[5] = (float)MtrIf_GetPwmDcCh(PwmChA_E);
    signal_buff[6] = (float)MtrIf_GetPwmDcCh(PwmChB_E);
    signal_buff[7] = (float)MtrIf_GetPwmDcCh(PwmChC_E);
    signal_buff[8] = mtr_dbg.e_angl; /* Electrical angle. */
    signal_buff[9] = mtr_dbg.i_abc_lpf[0];
    signal_buff[10] = mtr_dbg.i_abc_lpf[1];
    signal_buff[11] = mtr_dbg.i_abc_lpf[2];
    signal_buff[12] = mtr_dbg.i_dq0[0]; /* D-component. */
    signal_buff[13] = mtr_dbg.i_dq0[1]; /* Q-component. */
    signal_buff[14] = (float)MtrIf_GetVBus();
    signal_buff[15] = mtr_dbg.mtrif_v_bus;
    signal_buff[16] = (float)MtrIf_GetTemp();
    signal_buff[17] = mtr_dbg.ifbk_q_tgt;
    signal_buff[18] = (float)mtr_dbg.obs_enc_cnts;
    signal_buff[19] = (float)mtr_dbg.mtr_load_obs;
    signal_buff[20] = (float)pwm_dq[1];
    signal_buff[21] = (float)mtr_dbg.motn_ctrl_cmd;
    /* signal_buff[22] = (float)mtr_dbg.motn_ctrl_cmd_trq_tgt; */
    signal_buff[23] = (float)mtr_dbg.mtr_spd_tgt;
    /* signal_buff[24] = (float)((int32_t)mtr_dbg.ctrl_md_act); */
    /* signal_buff[25] = (float)mtr_dbg.ctrl_mgr_ctrl_tgt[0]; */
    signal_buff[26] = (float)mtr_dbg.ifbk_ctrl_v_dq0[0];
    signal_buff[27] = (float)mtr_dbg.ifbk_ctrl_v_dq0[1];
    signal_buff[28] = (float)mtr_stats.ctrl_fast_cnt;
    signal_buff[29] = (float)mtr_dbg.mtr_spd_obs;
    signal_buff[30] = (float)mtr_dbg.mtr_spd_pll;
    signal_buff[31] = (float)mtr_dbg.mtr_cnts_ref;
    signal_buff[32] = (float)mtr_dbg.mtr_cnts_tgt;

    xStreamBufferSend(stream_buff,
        (void*)signal_buff,
        sizeof(signal_buff),
        0);
#endif

    vTaskDelayUntil(&last_wake_time, APP_TASK_MOTOR_CONTROL_TS); 
  }
}
