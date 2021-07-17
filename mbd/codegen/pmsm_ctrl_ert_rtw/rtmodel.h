/*
 * rtmodel.h
 *
 * Code generation for Simulink model "pmsm_ctrl".
 *
 * Simulink Coder version                : 8.14 (R2018a) 06-Feb-2018
 *
 * Note that the generated code is not dependent on this header file.
 * The file is used in cojuction with the automatic build procedure.
 * It is included by the sample main executable harness
 * MATLAB/rtw/c/src/common/rt_main.c.
 *
 */

#ifndef RTW_HEADER_rtmodel_h_
#define RTW_HEADER_rtmodel_h_
#include "pmsm_ctrl.h"

/*
 * ROOT_IO_FORMAT: 0 (Individual arguments)
 * ROOT_IO_FORMAT: 1 (Structure reference)
 * ROOT_IO_FORMAT: 2 (Part of model data structure)
 */
# define ROOT_IO_FORMAT                0

/* Macros generated for backwards compatibility  */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((void*) 0)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((void) 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif
#endif                                 /* RTW_HEADER_rtmodel_h_ */
