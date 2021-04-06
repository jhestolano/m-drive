#include "unity.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "line.h"
#include "ucmd.h"

uint8_t simple_cmd_callback_is_called = 0;
uint8_t cmd_no_args_callback_is_called = 0;
uint8_t cmd_one_arg_callback_is_called = 0;
uint8_t cmd_one_arg_is_valid = 0;
uint8_t cmd_max_arg_callback_is_called = 0;

struct MaxArgs {
  uint8_t q;
  int8_t r;
  int32_t s;
  int16_t z;
};

static ErrCode_e simple_cmd_callback(Arg_s* args, void* usrargs) {
  (void)args;
  (void)usrargs;
  simple_cmd_callback_is_called = 1;
  return E_OK;
}

static ErrCode_e cmd_no_args_callback(Arg_s* args, void* usrargs) {
  (void)args;
  (void)usrargs;
  cmd_no_args_callback_is_called = 1;
  return E_OK;
}

static struct MaxArgs max_args_s = {0};

static ErrCode_e cmd_max_arg_callback(Arg_s* args, void* usrargs) {
  (void)usrargs;
  max_args_s.q = UCMD_ARG(args, 0, uint8_t);
  max_args_s.r = UCMD_ARG(args, 1, int8_t);
  max_args_s.s = UCMD_ARG(args, 2, int32_t);
  max_args_s.z = UCMD_ARG(args, 3, uint16_t);
  cmd_max_arg_callback_is_called = 1;
  return E_OK;
}

static ErrCode_e cmd_one_arg_callback(Arg_s* args, void* usrargs) {
  (void)usrargs;
  cmd_one_arg_is_valid = UCMD_ARG_IS_VALID(args, 0);
  if(cmd_one_arg_is_valid) {
    cmd_one_arg_callback_is_called = UCMD_ARG(args, 0, uint8_t); 
  }
  return E_OK;
}

const uCmdInfo_s info_a[] = {
  {"a", simple_cmd_callback, UCMD_ARG_NONE, UCMD_ARG_USER_NONE},
  {"cmd_no_args", cmd_no_args_callback, UCMD_ARG_NONE, UCMD_ARG_USER_NONE},
  {"cmd_one_arg", cmd_one_arg_callback, {{E_ARG_U8, 'q'}}, UCMD_ARG_USER_NONE},
  {"cmd_max_arg", cmd_max_arg_callback, {{E_ARG_U8, 'q'}, {E_ARG_I8, 'r'}, {E_ARG_I32, 's'}, {E_ARG_I16, 'z'}}, UCMD_ARG_USER_NONE},
  /* Keep this element last. Denotes end of table. */
  UCMD_TABLE_END,
};

static void helper_setup(void) {
  simple_cmd_callback_is_called = 0;
  cmd_no_args_callback_is_called = 0;
  uCmd_InitTable(info_a, UCMD_GET_TABLE_SIZE(info_a));
  Line_Init();
}

static void helper_fill_buff(const char* str) {
  while(*str != '\0') {
    Line_AddChar(*str++);
  }
  if(Line_BuffIsOvrFlwn()) {
    TEST_MESSAGE("Line buffer has been overflown!");
  }
  Line_AddChar('\n');
}

void test_single_char_command(void) {
  helper_setup();
  Line_AddChar('a');
  uCmd_Loop();
  TEST_ASSERT_EQUAL_UINT8(false, simple_cmd_callback_is_called);
  Line_AddChar('\n');
  uCmd_Loop();
  TEST_ASSERT_EQUAL_UINT8(true, simple_cmd_callback_is_called);
  /* When a command is complete and executed, the buffer shall be cleared. */
  TEST_ASSERT_TRUE(Line_BuffIsEmpty());
}

void test_multiple_char_command_no_arguments(void) {
  helper_setup();
  helper_fill_buff("cmd_no_args");
  uCmd_Loop();
  TEST_ASSERT_EQUAL_UINT8(true, cmd_no_args_callback_is_called);
  TEST_ASSERT_TRUE(Line_BuffIsEmpty());
}

void test_char_command_one_argument(void) {
  helper_setup();
  TEST_ASSERT_EQUAL_UINT8(0, cmd_one_arg_callback_is_called);
  /* Make it true, to make sure uCmd changes it to false */
  /* when the command with no args is received. */
  cmd_one_arg_is_valid = 1;
  helper_fill_buff("cmd_one_arg");
  uCmd_Loop();
  /* uCmd must set it to false, since no arguemnt was provided. */
  TEST_ASSERT_FALSE(cmd_one_arg_is_valid);
  helper_fill_buff("cmd_one_arg q12");
  uCmd_Loop();
  TEST_ASSERT_TRUE(cmd_one_arg_is_valid);
  TEST_ASSERT_EQUAL_UINT8(12, cmd_one_arg_callback_is_called);
  TEST_ASSERT_TRUE(Line_BuffIsEmpty());
}

void test_char_command_max_arguments(void) {
  helper_setup();
  cmd_max_arg_callback_is_called = 0;
  memset((void*)&max_args_s, 0, sizeof(struct MaxArgs));
  helper_fill_buff("cmd_max_arg q255 r-128 s2300 z-32000");
  TEST_ASSERT_TRUE(Line_IsCmplt());
  uCmd_Loop();
  TEST_ASSERT_TRUE(cmd_max_arg_callback_is_called);
  TEST_ASSERT_EQUAL_UINT8(max_args_s.q, 255);
  TEST_ASSERT_EQUAL_INT8(max_args_s.r, -128);
  TEST_ASSERT_EQUAL_INT32(max_args_s.s, 2300);
  TEST_ASSERT_EQUAL_INT16(max_args_s.z, -32000);
}

void test_char_command_max_diff_positions(void) {
  helper_setup();
  cmd_max_arg_callback_is_called = 0;
  memset((void*)&max_args_s, 0, sizeof(struct MaxArgs));
  helper_fill_buff("cmd_max_arg r-128 s2300 z-32000 q255");
  TEST_ASSERT_TRUE(Line_IsCmplt());
  uCmd_Loop();
  TEST_ASSERT_TRUE(cmd_max_arg_callback_is_called);
  TEST_ASSERT_EQUAL_UINT8(max_args_s.q, 255);
  TEST_ASSERT_EQUAL_INT8(max_args_s.r, -128);
  TEST_ASSERT_EQUAL_INT32(max_args_s.s, 2300);
  TEST_ASSERT_EQUAL_INT16(max_args_s.z, -32000);
}

void test_integration_all_tests(void) {
  RUN_TEST(test_single_char_command);
  RUN_TEST(test_multiple_char_command_no_arguments);
  RUN_TEST(test_char_command_one_argument);
  RUN_TEST(test_char_command_max_arguments);
  RUN_TEST(test_char_command_max_diff_positions);
}
