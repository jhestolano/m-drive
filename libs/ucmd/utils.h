#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "err.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

ErrCode_e tobytes(uint8_t* buf, size_t bufsz, void* data, size_t datasz);
ErrCode_e frombytes(uint8_t* buf, size_t bufsz, void* data, size_t datasz);
ErrCode_e findch(const char* str, uint8_t ch, int16_t* idx);
ErrCode_e strtou32(const char* rawstr, uint32_t* data);
ErrCode_e strtoi32(const char* rawstr, int32_t* data);

#endif
