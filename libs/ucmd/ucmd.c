#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "ucmd.h"
#include "line.h"

#ifndef UNIT_TEST
/*
 * Unit Testing is carried on by re-defining
 * STATIC so that static functions are visible
 * to testing framework. This #define is done
 * at Makefile level so that redefinition
 * applies to the whole project.
 */
#define STATIC static
/* File ucmd_lock.h provides macro definition
 * to disable interrupts on the target.
 */
#include "ucmd_lock.h"
#else
#define STATIC
#define uCMD_LOCK()
#define uCMD_UNLOCK()
#endif

#define CHAR_SPACE 0x20
#define LAST_ARR_ELEM 0x00

const char WrdBrkCh_c = CHAR_SPACE;
STATIC uCmdTable_s _cmdtable_p_s = {0};

/*****************************************************************************/
/* Handle raw string conversion to actual numeric values. ********************/
/*****************************************************************************/
typedef ErrCode_e _strtonum_t(const char* rawstr, void* buf);

ErrCode_e _strtoi32(const char* rawstr, void* buf) {
  ErrCode_e ret = E_GENERIC;
  int32_t tmp = 0;
  if(rawstr && buf) {
    ret = strtoi32(rawstr, &tmp);
  } else {
    ret = E_NULL_PTR;
  }
  if(ret == E_OK) {
    ret = tobytes(buf, sizeof(int32_t), &tmp, sizeof(int32_t));
  }
  return ret;
}

ErrCode_e _strtou32(const char* rawstr, void* buf) {
  ErrCode_e ret = E_GENERIC;
  uint32_t tmp = 0;
  if(rawstr && buf) {
    ret = strtou32(rawstr, &tmp);
  } else {
    ret = E_NULL_PTR;
  }
  if(ret == E_OK) {
    ret = tobytes(buf, sizeof(uint32_t), &tmp, sizeof(uint32_t));
  }
  return ret;
}

ErrCode_e _strtou8(const char* rawstr, void* buf) {
  int32_t tmp;
  ErrCode_e ret = _strtou32(rawstr, &tmp);
  if((ret == E_OK) && (tmp >= 0) && (tmp <= UINT8_MAX)) {
    ret = tobytes(buf, sizeof(uint8_t), &tmp, sizeof(uint8_t));
  } else {
    ret = (ret != E_OK) ? E_OUT_OF_RANGE : ret;
  }
  return ret;
}

ErrCode_e _strtou16(const char* rawstr, void* buf) {
  int32_t tmp;
  ErrCode_e ret = _strtou32(rawstr, &tmp);
  if((ret == E_OK) && (tmp >= 0) && (tmp <= UINT16_MAX)) {
    ret = tobytes(buf, sizeof(uint16_t), &tmp, sizeof(uint16_t));
  } else {
    ret = (ret != E_OK) ? E_OUT_OF_RANGE : ret;
  }
  return ret;
}

ErrCode_e _strtoi8(const char* rawstr, void* buf) {
  int32_t tmp;
  ErrCode_e ret = _strtoi32(rawstr, &tmp);
  if((ret == E_OK) && (tmp >= INT8_MIN) && (tmp <= INT8_MAX)) {
    ret = tobytes(buf, sizeof(int8_t), &tmp, sizeof(int8_t));
  } else {
    ret = (ret != E_OK) ? E_OUT_OF_RANGE : ret;
  }
  return ret;
}

ErrCode_e _strtoi16(const char* rawstr, void* buf) {
  int32_t tmp;
  ErrCode_e ret = _strtoi32(rawstr, &tmp);
  if((ret == E_OK) && (tmp >= INT16_MIN) && (tmp <= INT16_MAX)) {
    ret = tobytes(buf, sizeof(int16_t), &tmp, sizeof(int16_t));
  } else {
    ret = (ret != E_OK) ? E_OUT_OF_RANGE : ret;
  }
  return ret;
}

static _strtonum_t* _strtonum_fp[] = {
  _strtou8,
  _strtou16,
  _strtou32,
  _strtoi8,
  _strtoi16,
  _strtoi32,
};

typedef struct _strtonum {
  _strtonum_t** _strtonum_fp;
  size_t size;
} _strtonum_s;

static _strtonum_s _strtonum_h = {
  _strtonum_fp,
  6,
};

/*****************************************************************************/

STATIC ErrCode_e _get_param(const char* rawstr, char* param, uint8_t* done) {
  int16_t i= 0;
  ErrCode_e ret = E_GENERIC;
  if(rawstr && param && done) {
    *done = 0;
    ret = findch(rawstr, WrdBrkCh_c, &i);
    if(i == -1) {
      *done = 1;
      i = (int16_t)strlen(rawstr);
    }
      /* No command found. */
      if (i == 0) {
         ret = E_INV_SIZE;
      }
      else if ((ret == E_OK) && i > 0) {
         memcpy(param, rawstr, (size_t)i);
         param[i] = '\0';
         ret = E_OK;
      }
  } else {
    ret = E_NULL_PTR;
  }
  return ret;
}

STATIC ErrCode_e _get_arg(const char* rawstr, const ArgDesc_s* argdesc_a, Arg_s* arg) {
  ErrCode_e ret = E_GENERIC;
  const char* ofs = rawstr + 1;
  char argname = rawstr[0];
  size_t i;
  if(rawstr && argdesc_a && arg) {
    ret = E_NOT_FOUND;
    for(i = 0; (i < (UCMD_ARG_MAX_SIZE)) && (ret == E_NOT_FOUND); i++) {
      if((argname == argdesc_a[i].argname) && (argdesc_a[i].argtype < (uint8_t)_strtonum_h.size)) {
        arg[i].desc = &argdesc_a[i];
        _strtonum_h._strtonum_fp[argdesc_a[i].argtype](ofs, &(arg[i].data));
            arg[i].is_valid = 1;
        ret = E_OK;
      }
    }
  } else {
    ret = E_NULL_PTR;
  }
  return ret;
}

STATIC ErrCode_e _get_cmdinfo(const char* cmdstr, const uCmdTable_s * cmd_table, const uCmdInfo_s** info) {
  ErrCode_e ret = E_GENERIC;
  uint8_t i;
  size_t table_sz;
  const uCmdInfo_s* table_sa;
  if(cmdstr && cmd_table && cmd_table->size && cmd_table->info_a && info) {
    table_sa = cmd_table->info_a;
    table_sz = cmd_table->size;
    *info = NULL;
    ret = E_OK;
    for(i = 0; i < table_sz; i++) {
      if(strcmp(cmdstr, table_sa[i].cmdname) == 0) {
        *info = &table_sa[i];
            break;
      }
    }
  } else {
    ret = (cmdstr && cmd_table && cmd_table->info_a && info) ? E_INV_SIZE : E_NULL_PTR;
  }
  return ret;
}

STATIC ErrCode_e _parse_string(const char* rawstr, const uCmdTable_s* table_sa, uCmdHandle_s* handle) {
  ErrCode_e ret = E_GENERIC;
  char buf[UCMD_RAW_STR_MAX_SIZE] = {0};
  char cmdname[UCMD_NAME_MAX_SIZE] = {0};
  uint8_t done = 0;
  const char* ofs = rawstr;
  uint8_t argidx = 0;
  const uCmdInfo_s* p_info_s;
  uint8_t i;

  if(rawstr && table_sa && table_sa->size && handle) {
    memset(handle->args, 0, sizeof(Arg_s) * (UCMD_ARG_MAX_SIZE));

    /* Get the command name from the raw string. */
    (void)_get_param(ofs, cmdname, &done);

    /* Based on command name, get Info on it */
    ret = _get_cmdinfo(cmdname, table_sa, &p_info_s);
    ofs += strlen(cmdname) + 1;
    if(!p_info_s) {
      ret = E_INTERNAL;
    }

    if(ret == E_OK) {
      /* The flag done will already be set if there are no arguments
         to pass to the command and the following logic needs not to
         be exectued. */
      while((!done) &&
        /* Get argument string from raw string. */
        ((ret = _get_param(ofs, buf, &done)) == E_OK) 
        /* Fill-in the argument structure based on command name. 
           and argument string. */
           && ((ret = _get_arg(buf, p_info_s->argdesc, handle->args)) == E_OK) 
      ) {
        /* Increase pointer to start of next argument if any. */
        ofs += strlen(buf) + 1;
        argidx++;
      }
    }

    if(ret == E_OK) {
      /* Call command based on name and argument structure. */
      // ret = _callback(table_sa, args_a);
      for(i = 0; i < table_sa->size; i++) {
        if(strcmp(table_sa->info_a[i].cmdname, cmdname) == 0) {
          handle->callback = table_sa->info_a[i].handle;
               handle->userarg = table_sa->info_a[i].userarg;
          break;
        }
      }
    }
  } else {
    ret = (rawstr && table_sa) ? E_INV_SIZE : E_NULL_PTR;
  }
  return ret;
}

ErrCode_e uCmd_InitTable(const uCmdInfo_s* cmdtable, size_t table_sz) {
   ErrCode_e ret = E_INV_ARG;
   _cmdtable_p_s.info_a = NULL;
   _cmdtable_p_s.size = 0;
   if (cmdtable && table_sz) {
      _cmdtable_p_s.info_a = cmdtable;
      _cmdtable_p_s.size = table_sz;
      ret = E_OK;
   }
   else {
      ret = cmdtable ? E_INV_SIZE : E_NULL_PTR;
   }
   return ret;
}

ErrCode_e uCmd_Run(const char* cmdstr) {
   uCmdHandle_s handle;
   ErrCode_e ret = E_GENERIC;
   if (_cmdtable_p_s.info_a && _cmdtable_p_s.size && cmdstr) {
      ret = _parse_string(cmdstr, &_cmdtable_p_s, &handle);
      if (ret == E_OK) {
         ret = handle.callback(handle.args, handle.userarg);
      }
   }
   else {
      ret = cmdstr ? E_NOT_INITIALIZED : E_NULL_PTR;
   }
   return ret;
}

ErrCode_e uCmd_Loop(void) {
  char rawcmd[LINE_BUFF_SIZE] = {0};
  ErrCode_e ret = E_OK;
  uCMD_LOCK();
  if(Line_IsCmplt()) {
    Line_GetBuff((uint8_t*)rawcmd);
    Line_FlushBuff();
    ret = uCmd_Run(rawcmd);
  }
  uCMD_UNLOCK();
  return ret;
}
