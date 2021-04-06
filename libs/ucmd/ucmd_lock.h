#include "cmsis_gcc.h"

#define uCMD_LOCK() __disable_irq()
#define uCMD_UNLOCK() __enable_irq()
