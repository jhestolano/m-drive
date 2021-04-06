#include "err.h"

static const char _err_str_a[][32] = {
   "OK",
   "NULL Pointer",
   "Invalid Argument",
   "Invalid Size",
   "Too Large",
   "Too Small",
   "Out of Range",
   "Not Implemented",
   "Not Found",
   "Internal",
   "Generic",
   "Not Initialized",
   {0},
};

void print_err(char* msg, ErrCode_e err) {
   if (err < E_LAST_ELEM) {
      printf("%s: %s.\n\r", msg, _err_str_a[err]);
   }
   else {
      printf("%s: Unknown Error.\n\r", msg);
   }
}
