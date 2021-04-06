#ifndef __APP_H__
#define __APP_H__

#include "stdint.h"

#define APP_PARAMS_IFBK_R (330) /* Shunt resistance [mOhms]. */
#define APP_PARAMS_IFBK_R_INV (3) /*Inverse of shunt resistance [1 / Ohms]. */
#define APP_PARAMS_IFBK_GAIN (2) /* Amplifier current circuit gain. */
#define APP_PARAMS_IFBK_BIAS (1558) /* Zero current bias at ADC input [mVolts]. */
#define APP_PARAMS_IFBK_BIAS_ADC_COUNTS (1934) /* Zerro current bias in ADC counts. */
#define APP_PARAMS_IFBK_RES (1000) /* Current signal in milli-amps. */
#define APP_PARAMS_PWM_VOLTS (12000) /* PWM maximum voltage [mVolts]. */
#define APP_PARAMS_VBUS_DIV (19152) /* Resistor divider scaled by 1000. */
#define APP_PARAMS_MOTOR_R (19000) /* Motor winding resistance [mOhms]. */
#define APP_PARAMS_MOTOR_TAU (12) /* Motor electric time constant scaled by 10000. */
#define APP_PARAMS_MOTOR_L (23) /* Motor winding inductance [mH]. */
#define APP_PARAMS_ITGT_TS (200) /* Current response closed loop [ms]. */
#define APP_PARAMS_TEMP_BIAS (25000) /* Temperature bias [mdegC]. */
#define APP_PARAMS_TEMP_V_BIAS (1055) /* Temperature voltage bias [mV]. */
#define APP_PARAMS_TEMP_GAIN (43) /* Sensor gain [mdegC / mV]. */
#define APP_PARAMS_ENC_COUNTS (400) /* Encoder counts per revolution (4x mode) */
#define APP_PARAMS_ENC_RES (9) /* Encoder resolution in 0.1 deg resolution. */
#define APP_PARAMS_POS_RES (10) /* Represents 0.1 deg resolution of position signal. */
#define APP_PARAMS_MOTOR_J (110) /* Motor inertia in g/mm^2 units. Actual: 1.10127e-7 kg/m^2 */
#define APP_PARAMS_MOTOR_KEMF (103) /* Motor back emf constant in mN*m*s/rad units. Actual: 1.10127e-5 N*m*s/rad */
#define APP_PARAMS_MOTOR_KF (11012) /* Motor friction in g*mm^2*s/rad. Actual: 1.10127e-5 */
#define APP_PARAMS_DEG_TO_RAD (0.017453292519943f) /* pi / 180 constant */
#define APP_PARAMS_RADpS_TO_RPM (9.549296585513721f) /* 30 / pi scaling. */

/* Voltage over which is not possible to read shunt resistor that is powering the phase. This is due to the fact */
/* that the shunt resistor is located on the negative side of the bridge. At 100% duty-cycle, the shunt resistor */
/* is never connected to the phase, as it is being turned on 100% of the time. To allow some curren to flow */
/* through the shunt resistor, the duty cycle must not exceed this threshold. */
/* Another workaround is to read the opposite phase all the time. As it is guaranteeed for it to be connected */
/* to ground at some point. The software will use a combination of both workarounds. */
#define APP_PARAMS_RSHUNT_NOT_READABLE (11000) /* Voltage over which is not possible to read phase. */

typedef enum {
  IfbkPhA_E,
  IfbkPhB_E,
  IfbkPhC_E,
  IfbkPhMax_E,
  IfbkPhUnknown_E = 255,
} IfbkPh_E;

typedef enum {
  VAdcChPhA_E = 0,
  VAdcChPhB_E,
  VAdcChPhC_E,
  VAdcChPot_E,
  VAdcChTemp_E,
  VAdcChVBus_E,
  VAdcChMax_E,
  VAdcChUnknown_E = 255,
} VAdcCh_E;

typedef enum {
  PwmChA_E = 0,
  PwmChB_E,
  PwmChC_E,
  PwmChMax_E,
  PwmChUnknown_E = 255,
} PwmCh_E;

typedef enum {
  GpioChA_E = 0,
  GpioChB_E,
  GpioChC_E,
  GpioChBkIn2_E,
  GpioChMax_E,
  GpioChUnknown_E = 255,
} GpioCh_E;

int32_t App_GetCurrent(IfbkPh_E ifbk);

uint32_t App_GetVoltage(VAdcCh_E vch);

uint32_t App_GetBusVoltage(void);

void App_SetPwmDutyCycle(PwmCh_E pwmch, uint32_t pwmdc);

void App_SetPwmVoltage(PwmCh_E pwmch, uint32_t mvolts);

void App_SetPwmVoltageAll(uint32_t mvolts);

uint32_t App_GetPwmDutyCycle(PwmCh_E pwmch);

uint32_t App_GetPwmVoltage(PwmCh_E pwmch);

int32_t App_GetTemp(void);

int32_t App_GetPosition(void);

void App_DisarmMotor(void);

void App_ArmMotor(void);

void App_ArmPhase(GpioCh_E gpio);

void App_DisarmPhase(GpioCh_E gpio);

void App_ArmDrive(void);

void App_DisarmDrive(void);

int32_t App_GetCurrent(IfbkPh_E);

#endif // __APP_H__
