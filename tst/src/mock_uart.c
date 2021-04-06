#include "ucmd.h"

uCmd_CharRxCallback MockUART_ChrRxCallback;

void MockUART_SendChar(uint8_t ch) {
  uint8_t buff = ch;
  MockUART_ChrRxCallback((void*)&buff);
}

void MockUART_SendCharArray(char* chrarr, uint8_t sz) {
  uint8_t idx = 0;
  for(; idx < sz; idx++) {
    MockUART_SendChar((uint8_t)chrarr[idx]);
  }
}
