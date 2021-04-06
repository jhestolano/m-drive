#include "unity.h"
#include "utils.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define MODUDLE_NAME "utils"

void test_utils_findch(void) {
  /*************************************************************************/
  /* TEST SETUP ************************************************************/
  /*************************************************************************/
  char test_str[] = "This is a test string";
  ErrCode_e res;
  int16_t idx;
  char dch = 'a';

  /*************************************************************************/
  /* TEST ARGUMENT VALIDATION **********************************************/
  /*************************************************************************/
  res = findch(NULL, 0, &idx);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)res);

  res = findch(test_str, 0, NULL);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)res);

  /*************************************************************************/
  /* TEST BODY AND VALIDATION **********************************************/
  /*************************************************************************/
  res = findch(test_str, dch, &idx);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
  TEST_ASSERT_EQUAL_INT32((int32_t)8, (int32_t)idx);

  res = findch(test_str, 'z', &idx);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
  TEST_ASSERT_EQUAL_INT32((int32_t)-1, (int32_t)idx);

  res = findch(test_str, 'T', &idx);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
  TEST_ASSERT_EQUAL_INT32((int32_t)0, (int32_t)idx);
}

void test_utils_asbytes(void) {
  /*************************************************************************/
  /* TEST SETUP ************************************************************/
  /*************************************************************************/

  // TEST VARS.
  float fval[] = {-23.44f, 0.0f, 2444.23f};
  int8_t i8val[] = {-12, 0, 240};
  int16_t i16val[] = {-400, 0, 500};
  int32_t i32val[] = {-80000, 0, 90123};

  // TEMP VARS.
  uint8_t i;
  uint8_t buf[8];
  ErrCode_e res;

  // RESULT VARS.
  float fres = 0.f;
  int8_t i8res = 0;
  int16_t i16res = 0;
  int32_t i32res = 0;


  /*************************************************************************/
  /* TEST ARGUMENT VALIDATION **********************************************/
  /*************************************************************************/

  // Null pointers.
  res = frombytes(NULL, sizeof(buf), (void*)&fval[0], sizeof(float)); 
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)res);

  res = frombytes(buf, sizeof(buf), NULL, sizeof(float)); 
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)res);

  // Invalid buffer size as 0.
  res = frombytes(buf, 0, (void*)&fval[0], sizeof(float));
  TEST_ASSERT_EQUAL_INT32((int32_t)E_INV_SIZE, (int32_t)res);

  // Invalid buffer size as smaller than data.
  res = frombytes(buf, 1, (void*)&fval[0], sizeof(float));
  TEST_ASSERT_EQUAL_INT32((int32_t)E_INV_SIZE, (int32_t)res);

  // Invalid data size as 0.
  res = frombytes(buf, sizeof(buf), (void*)&fval[0], 0);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_INV_SIZE, res);

  /*************************************************************************/
  /* TEST BODY AND VALIDATION **********************************************/
  /*************************************************************************/


  // FLOAT VALUES
  for(i = 0; i < sizeof(fval) / sizeof(float); i++) {
    res = tobytes(buf, sizeof(buf), (void*)&fval[i], sizeof(float));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    res = frombytes(buf, sizeof(buf), (void*)&fres, sizeof(float));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4, fval[i], fres);
  }

  // INT8 VALUES
  for(i = 0; i < sizeof(i8val) / sizeof(int8_t); i++) {
    res = tobytes(buf, sizeof(buf), (void*)&i8val[i], sizeof(int8_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    res = frombytes(buf, sizeof(buf), (void*)&i8res, sizeof(int8_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    TEST_ASSERT_EQUAL_INT8(i8val[i], i8res);
  }

  // INT16 VALUES
  for(i = 0; i < sizeof(i16val) / sizeof(int16_t); i++) {
    res = tobytes(buf, sizeof(buf), (void*)&i16val[i], sizeof(int16_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    res = frombytes(buf, sizeof(buf), (void*)&i16res, sizeof(int16_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    TEST_ASSERT_EQUAL_INT16(i16val[i], i16res);
  }

  // INT32 VALUES
  for(i = 0; i < sizeof(i32val) / sizeof(int32_t); i++) {
    res = tobytes(buf, sizeof(buf), (void*)&i32val[i], sizeof(int32_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    res = frombytes(buf, sizeof(buf), (void*)&i32res, sizeof(int32_t));
    TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)res);
    TEST_ASSERT_EQUAL_INT32(i32val[i], i32res);
  }
}

void test_strtou32(void) {
  /*************************************************************************/
  /* TEST SETUP ************************************************************/
  /*************************************************************************/
  uint32_t num;
  ErrCode_e ret;

  /*************************************************************************/
  /* TEST ARGUMENT VALIDATION **********************************************/
  /*************************************************************************/
  ret = strtou32(NULL, NULL);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, ret);

  ret = strtou32("230", NULL);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, ret);

  ret = strtou32("", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_INV_SIZE, ret);
  /*************************************************************************/
  /* TEST BODY AND VALIDATION **********************************************/
  /*************************************************************************/

  ret = strtou32("4294967295", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_UINT32((int32_t)4294967295, (uint32_t)num);

  ret = strtou32("0", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_UINT32((uint32_t)0, (uint32_t)num);

  ret = strtou32("12--23", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OUT_OF_RANGE, (int32_t)ret);
}

void test_strtoi32(void) {
  /*************************************************************************/
  /* TEST SETUP ************************************************************/
  /*************************************************************************/
  int32_t num;
  ErrCode_e ret;

  /*************************************************************************/
  /* TEST ARGUMENT VALIDATION **********************************************/
  /*************************************************************************/
  ret = strtoi32(NULL, NULL);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)ret);

  ret = strtoi32("230", NULL);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_NULL_PTR, (int32_t)ret);

  ret = strtoi32("", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_INV_SIZE, (int32_t)ret);
  /*************************************************************************/
  /* TEST BODY AND VALIDATION **********************************************/
  /*************************************************************************/
  /* TODO: Test positive and negative extreme values. */

  ret = strtoi32("230", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_INT32((int32_t)num, (int32_t)230);


  ret = strtoi32("0", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_INT32((int32_t)num, (int32_t)0);

  ret = strtoi32("-0", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_INT32((int32_t)num, (int32_t)0);

  ret = strtoi32("-123", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OK, (int32_t)ret);
  TEST_ASSERT_EQUAL_INT32((int32_t)num, (int32_t)-123);

  ret = strtoi32("12--23", &num);
  TEST_ASSERT_EQUAL_INT32((int32_t)E_OUT_OF_RANGE, (int32_t)ret);
}
