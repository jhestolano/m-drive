#ifndef RTW_HEADER_CalMgrSt_T_h_
#define RTW_HEADER_CalMgrSt_T_h_
#include "rtwtypes.h"

typedef enum {
  ST_FAILED = -1,                      /* Default value */
  ST_NOT_STARTED,
  ST_ENC_OFS,
  ST_RES_ID,
  ST_IND_ID,
  ST_IFBK_OFS_CAL,
  ST_DONE = 255
} CalMgrSt_T;

#endif                                 /* RTW_HEADER_CalMgrSt_T_h_ */
