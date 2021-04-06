#ifndef ERR_H
#define ERR_H

#include <stdio.h>

typedef enum ErrCode {
  E_OK = 0,
  E_NULL_PTR,
  E_INV_ARG,
  E_INV_SIZE,
  E_TOO_LARGE,
  E_TOO_SMALL,
  E_OUT_OF_RANGE,
  E_NOT_IMPLEMENTED,
  E_NOT_FOUND,
  E_INTERNAL,
  E_GENERIC,
  E_NOT_INITIALIZED,
  E_LAST_ELEM,
} ErrCode_e;

void print_err(char* msg, ErrCode_e err);

#endif
