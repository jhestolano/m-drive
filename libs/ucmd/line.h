#include <stdint.h>

/*-----------------------------------------------------------------------------
 *  Macro detiniftions.
 *-----------------------------------------------------------------------------*/
#define LINE_CHAR_LF (10)
#define LINE_CHAR_CR (13)
#define LINE_CHAR_SPACE (32)
#define LINE_CHAR_BRK (LINE_CHAR_SPACE)
#define LINE_NULL_CHAR (0)
#define LINE_MAX_CMD_SIZE (8)
#define LINE_MAX_ARG_SIZE (8)
#define LINE_CHAR_0 (48)
#define LINE_CHAR_9 (57)
#define LINE_CHAR_A (65)
#define LINE_CHAR_Z (90)
#define LINE_CHAR_a (97)
#define LINE_CHAR_z (122)
#define LINE_MAX_STR_LEN (64)
#define LINE_BUFF_SIZE (LINE_MAX_STR_LEN + 1)


/*-----------------------------------------------------------------------------
 * Global variable definitions. 
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Type definitions. 
 *-----------------------------------------------------------------------------*/
typedef void (*Line_Callback)(void* arg);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_Init
 *  Description:  Initialize Line module.
 * =====================================================================================
 */
void Line_Init(void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_AddChar
 *  Description:  Add a new character to the buffer..
 * =====================================================================================
 */
void Line_AddChar(char ch);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_BuffIsEmpty
 *  Description:  Buffer is empty flag.
 * =====================================================================================
 */
uint8_t Line_BuffIsEmpty (void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_GetCnt
 *  Description:  Get the current number of bytes in buffer.
 * =====================================================================================
 */
uint8_t Line_GetCnt (void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_BuffIsFull
 *  Description:  Buffer is full flag is set.
 * =====================================================================================
 */
uint8_t Line_BuffIsFull (void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_GetBuff
 *  Description:  Copy raw buffer, whatever is in there. This function assumes there is
                  enough space in the target buffer to copy all data.
 * =====================================================================================
 */
void Line_GetBuff (uint8_t* buff);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_FlushBuff
 *  Description:  Set contents of buffer to zero and reset counter.
 * =====================================================================================
 */
void Line_FlushBuff (void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_IsCmplt
 *  Description:  Signals that the raw command is ready to be processed.
 * =====================================================================================
 */
uint8_t Line_IsCmplt (void);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Line_BuffIsOvrFlwn
 *  Description:  Signals that buffer has been overflown.
 * =====================================================================================
 */
uint8_t Line_BuffIsOvrFlwn ( void );
