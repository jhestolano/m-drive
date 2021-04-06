#include "utils.h"
#include <assert.h>
#include <string.h>

#define _BUFOP_TO   0
#define _BUFOP_FROM 1

#define UTILS_RAW_STR_MAX_SIZE 256
#define UTILS_RAW_STR_U32_DATA_MAX_SIZE 10

#define UTILS_CHAR_ZERO 48
#define UTILS_CHAR_NINE 57

#define UTILS_STR_MAX_U32 "4294967295"
#define UTILS_STR_MIN_I32 "2147483648" // Sign is omitted.
#define UTILS_STR_MAX_I32 "2147483647"

#ifndef TEST_UTILS
#undef assert
#define assert(x)
#endif

static ErrCode_e _bufop(uint8_t* buf, size_t bufsz, void* data, size_t datasz, uint8_t toorfrom) {
  ErrCode_e ret = E_GENERIC;
  assert(buf && data && datasz && bufsz);
  assert(bufsz >= datasz);
  if(buf && data && datasz && bufsz && (bufsz >= datasz)) {
    if(toorfrom == _BUFOP_TO) {
      /* Handle storage into buffer. */
      memset(buf, 0, bufsz);
      memcpy(buf, data, datasz);
      ret = E_OK;
    } else if (toorfrom == _BUFOP_FROM) {
      /* Handle data restore from buffer. */
      memcpy(data, buf, datasz);
      ret = E_OK;	
    } else {
      ret = E_INTERNAL;
    }
  } else {
    if(!buf || !data) {
      ret = E_NULL_PTR;
    } else {
      ret = E_INV_SIZE;
    }
  }
  return ret;
}

ErrCode_e tobytes(uint8_t* buf, size_t bufsz, void* data, size_t datasz) {
  assert(buf && data);
  assert(bufsz && datasz);
  assert(bufsz >= datasz);
  return _bufop(buf, bufsz, data, datasz, _BUFOP_TO);
}

ErrCode_e frombytes(uint8_t* buf, size_t bufsz, void* data, size_t datasz) {
  assert(buf && data);
  assert(bufsz && datasz);
  assert(bufsz >= datasz);
  return _bufop(buf, bufsz, data, datasz, _BUFOP_FROM);
}

ErrCode_e findch(const char* str, uint8_t ch, int16_t* idx) {
  ErrCode_e ret = E_GENERIC;
  uint16_t i;
  if(str && idx) {
    *idx = -1;
    ret = E_OK;
    for(i = 0; (i < UTILS_RAW_STR_MAX_SIZE) && (str[i] != 0) && (*idx == -1); ++i) {
      if(str[i] == ch) {
        *idx = i;
      }
    }
  } else {
    ret = E_NULL_PTR;
  }
  return ret;
}

ErrCode_e strtoi32(const char* rawstr, int32_t* data) {
  ErrCode_e ret = E_GENERIC;
  size_t slen;
  int32_t k = 1;
  const char* ofs = rawstr;
  if((rawstr) && (data) && (slen = strlen(rawstr)))
  {
    if(rawstr[0] == '-') {
      k = -1;
      ofs = rawstr + 1;
    }
    ret = strtou32(ofs, (uint32_t*)data);
    *data *= k;
  } else {
    ret = (rawstr && data) ? E_INV_SIZE : E_NULL_PTR;
  }
  return ret;
}

ErrCode_e strtou32(const char* rawstr, uint32_t* data) {
  size_t i;
  ErrCode_e ret = E_GENERIC;
  int8_t tmp = 0;
  size_t slen;
  if((rawstr) && (data) && (slen = strlen(rawstr))) {
    ret = E_OK;
    *data = 0;
    for(i = 0; (i < slen) && ((rawstr[i] >= UTILS_CHAR_ZERO) && rawstr[i] <= UTILS_CHAR_NINE); i++) {
      tmp = rawstr[i] - (uint8_t)UTILS_CHAR_ZERO;
      *data = tmp + 10 * (*data);
    }
    if( i < slen) {
      /* For loop broke due to invalid char in string. */
      ret = E_OUT_OF_RANGE;
    }
  } else {
    ret = (rawstr && data) ? E_INV_SIZE : E_NULL_PTR;
  }
  return ret;
}

ErrCode_e strtof(const char* rawstr, float* data) {
   size_t i;
   ErrCode_e ret = E_GENERIC;
   size_t slen;
   if ((rawstr) && (data) && (slen = strlen(rawstr))) {
     ret = E_OK;
     *data = 0;
     for (i = 0; (i < slen) && ((rawstr[i] >= UTILS_CHAR_ZERO) && rawstr[i] <= UTILS_CHAR_NINE); i++) {}
     if (i < slen) {
       /* For loop broke due to invalid char in string. */
       ret = E_OUT_OF_RANGE;
     }
   }
   else {
     ret = (rawstr && data) ? E_INV_SIZE : E_NULL_PTR;
   }
   return ret;
}

