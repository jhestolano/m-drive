#ifndef UCMD_H
#define UCMD_H

#include "err.h"
#include <stdint.h>

#define UCMD_ARG_BYTES_MAX_SIZE (4) // Maximum number of bytes that arguments take.
#define UCMD_DATA_TYPE_BYTES_MAX_SIZE (UCMD_ARG_BYTES_MAX_SIZE)
#define UCMD_TABLE_MAX_SIZE (8) // Maximum number of callbacks.
#define UCMD_ARG_MAX_SIZE (4) // Maximum number of arguments per command.
#define UCMD_NAME_MAX_SIZE (16) // Maximum string length of callback name.
#define UCMD_RAW_STR_MAX_SIZE (64) // Max. size of buffer that holds raw data.

#define UCMD_ARG(_args, _idx, _type) (_type)(*(((_type*)(&(_args)[(_idx)].data))))
#define UCMD_ARG_IS_VALID(_args, _idx) ((_args)[(_idx)].is_valid)
#define UCMD_ARG_NONE {{E_ARG_NONE_TYPE, 0}}
#define UCMD_ARG_USER_NONE NULL
#define UCMD_CALLBACK_NONE NULL
#define UCMD_TABLE_END {"", UCMD_CALLBACK_NONE, UCMD_ARG_NONE, UCMD_ARG_USER_NONE}

#define UCMD_GET_TABLE_SIZE(x) (sizeof((x)) / sizeof(uCmdInfo_s))

typedef enum ArgType {
  E_ARG_U8 = 0,
  E_ARG_U16,
  E_ARG_U32,
  E_ARG_I8,
  E_ARG_I16,
  E_ARG_I32,
  E_ARG_STR,
  E_ARG_NONE_TYPE = 254,
  E_ARG_INV_TYPE = 255,
} ArgType_e;

typedef struct ArgDesc {
  ArgType_e argtype;
  char argname;
} ArgDesc_s;

typedef struct Arg {
  const ArgDesc_s* desc;
  uint8_t data[UCMD_ARG_BYTES_MAX_SIZE];
  uint8_t is_valid;
} Arg_s;

typedef ErrCode_e Callback_t(Arg_s* args, void* usrargs);

typedef Callback_t* CallbackPtr_t;

typedef struct uCmdInfo {
  const char cmdname[UCMD_NAME_MAX_SIZE];
  const CallbackPtr_t handle;
  const ArgDesc_s argdesc[UCMD_ARG_MAX_SIZE];
  void* userarg;
} uCmdInfo_s;

typedef struct uCmdTable {
  const uCmdInfo_s* info_a;
  size_t size;
} uCmdTable_s;

typedef struct uCmdHandle {
   CallbackPtr_t callback;
   Arg_s args[UCMD_ARG_MAX_SIZE];
   void* userarg;
} uCmdHandle_s;

ErrCode_e uCmd_InitTable(const uCmdInfo_s* cmdtable, size_t table_sz);

ErrCode_e uCmd_Run(const char* cmdstr);

ErrCode_e uCmd_Loop(void);

#endif
