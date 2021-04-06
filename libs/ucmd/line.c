#include "line.h"
#include <stdbool.h>
#include <string.h>

#ifdef UNIT_TEST
#define STATIC
#else
#define STATIC static
#endif

typedef struct _Line_S {
  uint8_t buff[LINE_BUFF_SIZE]; /* Buffer memory. */
  uint8_t iscmplt; /* Message complete flag. */
  uint16_t cnt; /* Number of elements in buffer. */
  uint8_t isovrflwn; /* Signal overflow condition. */
} Line_S;

/*-----------------------------------------------------------------------------
 *  Static global variables.
 *-----------------------------------------------------------------------------*/
static volatile Line_S _line_s;

/*-----------------------------------------------------------------------------
 * Static function prototypes. 
 *-----------------------------------------------------------------------------*/
static void _new_ch_callback (void*);
STATIC inline uint8_t _is_eol_ch(uint8_t);
static inline void _add_new_ch(uint8_t);

static inline void _add_new_ch ( uint8_t newchar )
{
  _line_s.buff[_line_s.cnt] = newchar;
  _line_s.cnt++;
  return;
}

STATIC inline uint8_t _is_eol_ch (uint8_t ch)
{
  return (ch == LINE_CHAR_LF) ||
         (ch == LINE_CHAR_CR);
}

static void _new_ch_callback (void* params)
{
  uint8_t newchar = *((uint8_t*)params);

  /* If buffer is empty and end of line character received, just ignore it and return. */
  /* If an end character is received after the message is complete, ignore it and return. */
  /* If buffer is overflown, a character cannot be normally added. Wait for recovery conditions. */
  if(!Line_BuffIsFull() &&
     !(Line_BuffIsEmpty() && (_is_eol_ch(newchar) || (newchar == LINE_CHAR_SPACE))) &&
     ! Line_BuffIsOvrFlwn()) {

    /* If buffer is not empty and end of message character received, signal a message */
    /* complete so that command can be processed. Also replace end character with */
    /* null character so that it can be processed as a null-terminated string. */
    if(!Line_BuffIsEmpty() && _is_eol_ch(newchar)) {
      _line_s.iscmplt = true;
      _add_new_ch(LINE_NULL_CHAR);
      /* Call string parser. */
    }

    /* If this is the last character that fits into buffer and no end of message caharacter */
    /* has been received, then signal overflow condition. */
    /* When an overflow condition has happened, flush the buffer and ignore all characters */
    /* until a new end of line has been received as previous command was invalid. */
    else if(Line_GetCnt() == (LINE_BUFF_SIZE - 1)) {
      _line_s.isovrflwn = true;
      Line_FlushBuff();

    } else {
      /* This is a valid char and command is not complete. Add it to buffer. */
      _add_new_ch(newchar);
    }
  } else if (Line_BuffIsOvrFlwn() && _is_eol_ch(newchar)) {
    /* Are conditions valid to recover from overflow? */
    /* Recovers from overflow event when eond of line character is received. */
    _line_s.isovrflwn = false;
    Line_FlushBuff();
  }
  return;
}

void Line_Init (void) {
  Line_FlushBuff();
  _line_s.isovrflwn = false;
  /* Connect char rx interrupt to new char handle function. */
}


uint8_t Line_BuffIsFull (void)
{
  return _line_s.cnt >= LINE_BUFF_SIZE;
}

void Line_GetBuff (uint8_t* buff)
{
  memcpy((void*)buff, (void*)_line_s.buff, sizeof(_line_s.buff));
}

uint8_t Line_BuffIsEmpty (void)
{
  return _line_s.cnt == 0;
}

uint8_t Line_GetCnt (void)
{
  return _line_s.cnt;
}

void Line_FlushBuff (void) {
  memset((void*)_line_s.buff, 0, sizeof(_line_s.buff));
  _line_s.iscmplt = false;
  _line_s.cnt = 0;
  return;
}

uint8_t Line_IsCmplt (void)
{
  return _line_s.iscmplt;
}

uint8_t Line_BuffIsOvrFlwn ( void )
{
  return _line_s.isovrflwn;
}

void Line_AddChar(char ch) {
  uint8_t tmp = ch;
  _new_ch_callback((void*)&tmp);
}
