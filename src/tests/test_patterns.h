#ifndef S21_DECIMAL_TEST_PATTERNS
#define S21_DECIMAL_TEST_PATTERNS

#include "test.h"

#define DEC_BUFF_SIZE 37

#ifdef NICE
#define NICE_OUT 1
#else
#define NICE_OUT 0
#endif

#define RESULT_2_VALS_TEST(NUM, FUNC, VAL_1, VAL_2, RES)                   \
  START_TEST(FUNC##_result_2_vals_test_##NUM) {                            \
    s21_decimal value_1 = {{0, 0, 0, 0}};                                  \
    s21_decimal value_2 = {{0, 0, 0, 0}};                                  \
    s21_decimal result = {{0, 0, 0, 0}};                                   \
    char buff[DEC_BUFF_SIZE];                                              \
                                                                           \
    convert_str_to_decimal(#VAL_1, &value_1);                              \
    convert_str_to_decimal(#VAL_2, &value_2);                              \
    FUNC(value_1, value_2, &result);                                       \
    convert_decimal_to_str(result, buff);                                  \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "Value_1:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_1); \
      printf(DARK_GREY "Value_2:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_2); \
      printf(DARK_GREY "Result:   " RESET "%*s\n", DEC_BUFF_SIZE, buff);   \
      printf(DARK_GREY "Expected: " RESET "%*s\n", DEC_BUFF_SIZE, #RES);   \
      printf(!strcmp(buff, #RES) ? GREEN "\nSUCCESS" : RED "\nFAIL");      \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_str_eq(buff, #RES);                                          \
  }                                                                        \
  END_TEST

#define RESULT_1_VAL_TEST(NUM, FUNC, VAL, RES)                             \
  START_TEST(FUNC##_result_1_val_test_##NUM) {                             \
    s21_decimal value = {{0, 0, 0, 0}};                                    \
    s21_decimal result = {{0, 0, 0, 0}};                                   \
    char buff[DEC_BUFF_SIZE];                                              \
                                                                           \
    convert_str_to_decimal(#VAL, &value);                                  \
    FUNC(value, &result);                                                  \
    convert_decimal_to_str(result, buff);                                  \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "Value:    " RESET "%*s\n", DEC_BUFF_SIZE, #VAL);   \
      printf(DARK_GREY "Result:   " RESET "%*s\n", DEC_BUFF_SIZE, buff);   \
      printf(DARK_GREY "Expected: " RESET "%*s\n", DEC_BUFF_SIZE, #RES);   \
      printf(!strcmp(buff, #RES) ? GREEN "\nSUCCESS" : RED "\nFAIL");      \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_str_eq(buff, #RES);                                          \
  }                                                                        \
  END_TEST

#define CODE_3_ARGS_TEST(NUM, FUNC, VAL_1, VAL_2, CODE)                    \
  START_TEST(FUNC##_code_3_args_test_##NUM) {                              \
    s21_decimal value_1 = {{0, 0, 0, 0}};                                  \
    s21_decimal value_2 = {{0, 0, 0, 0}};                                  \
    s21_decimal result = {{0, 0, 0, 0}};                                   \
    int code;                                                              \
                                                                           \
    convert_str_to_decimal(#VAL_1, &value_1);                              \
    convert_str_to_decimal(#VAL_2, &value_2);                              \
    code = FUNC(value_1, value_2, &result);                                \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "Value_1:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_1); \
      printf(DARK_GREY "Value_2:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_2); \
      printf(DARK_GREY "Code:     " RESET "%*d\n", DEC_BUFF_SIZE, code);   \
      printf(DARK_GREY "Expected: " RESET "%*d\n", DEC_BUFF_SIZE, CODE);   \
      printf(code == CODE ? GREEN "\nSUCCESS" : RED "\nFAIL");             \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_int_eq(code, CODE);                                          \
  }                                                                        \
  END_TEST

#define CODE_2_ARGS_TEST(NUM, FUNC, VAL_1, VAL_2, CODE)                    \
  START_TEST(FUNC##_code_2_args_test_##NUM) {                              \
    s21_decimal value_1 = {{0, 0, 0, 0}};                                  \
    s21_decimal value_2 = {{0, 0, 0, 0}};                                  \
    int code;                                                              \
                                                                           \
    convert_str_to_decimal(#VAL_1, &value_1);                              \
    convert_str_to_decimal(#VAL_2, &value_2);                              \
    code = FUNC(value_1, value_2);                                         \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "Value_1:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_1); \
      printf(DARK_GREY "Value_2:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL_2); \
      printf(DARK_GREY "Code:     " RESET "%*d\n", DEC_BUFF_SIZE, code);   \
      printf(DARK_GREY "Expected: " RESET "%*d\n", DEC_BUFF_SIZE, CODE);   \
      printf(code == CODE ? GREEN "\nSUCCESS" : RED "\nFAIL");             \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_int_eq(code, CODE);                                          \
  }                                                                        \
  END_TEST

#define CODE_1_VAL_TEST(NUM, FUNC, VAL, CODE)                              \
  START_TEST(FUNC##_code_1_val_test_##NUM) {                               \
    s21_decimal value = {{0, 0, 0, 0}};                                    \
    s21_decimal result = {{0, 0, 0, 0}};                                   \
    int code;                                                              \
                                                                           \
    convert_str_to_decimal(#VAL, &value);                                  \
    code = FUNC(value, &result);                                           \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "Value:    " RESET "%*s\n", DEC_BUFF_SIZE, #VAL);   \
      printf(DARK_GREY "Code:     " RESET "%*d\n", DEC_BUFF_SIZE, code);   \
      printf(DARK_GREY "Expected: " RESET "%*d\n", DEC_BUFF_SIZE, CODE);   \
      printf(code == CODE ? GREEN "\nSUCCESS" : RED "\nFAIL");             \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_int_eq(code, CODE);                                          \
  }                                                                        \
  END_TEST

#define FROM_INT_TO_DECIMAL_TEST(NUM, VAL)                                   \
  START_TEST(s21_from_int_to_decimal_test_##NUM) {                           \
    s21_decimal result = {{0, 0, 0, 0}};                                     \
    char buff[DEC_BUFF_SIZE];                                                \
                                                                             \
    s21_from_int_to_decimal(VAL, &result);                                   \
    convert_decimal_to_str(result, buff);                                    \
                                                                             \
    if (NICE_OUT) {                                                          \
      printf(DARK_GREY "int:      " RESET "%*d\n", DEC_BUFF_SIZE, (int)VAL); \
      printf(DARK_GREY "decimal:  " RESET "%*s\n", DEC_BUFF_SIZE, buff);     \
      printf(!strcmp(buff, #VAL) ? GREEN "\nSUCCESS" : RED "\nFAIL");        \
      printf(RESET "\n-----------------------------------------------\n");   \
    }                                                                        \
                                                                             \
    ck_assert_str_eq(buff, #VAL);                                            \
  }                                                                          \
  END_TEST

#define FROM_FLOAT_TO_DECIMAL_RES_TEST(NUM, VAL, RES)                        \
  START_TEST(s21_from_float_to_decimal_res_test_##NUM) {                     \
    float val = (float)VAL;                                                  \
    s21_decimal result = {{0, 0, 0, 0}};                                     \
    char buff_dec[DEC_BUFF_SIZE];                                            \
                                                                             \
    s21_from_float_to_decimal(val, &result);                                 \
    convert_decimal_to_str(result, buff_dec);                                \
                                                                             \
    if (NICE_OUT) {                                                          \
      printf(DARK_GREY "float:    " RESET "%*.28g\n", DEC_BUFF_SIZE, val);   \
      printf(DARK_GREY "decimal:  " RESET "%*s\n", DEC_BUFF_SIZE, buff_dec); \
      printf(DARK_GREY "Expected: " RESET "%*s\n", DEC_BUFF_SIZE, #RES);     \
      printf(!strcmp(buff_dec, #RES) ? GREEN "\nSUCCESS" : RED "\nFAIL");    \
      printf(RESET "\n-----------------------------------------------\n");   \
    }                                                                        \
                                                                             \
    ck_assert_str_eq(buff_dec, #RES);                                        \
  }                                                                          \
  END_TEST

#define FROM_FLOAT_TO_DECIMAL_CODE_TEST(NUM, VAL, CODE)                    \
  START_TEST(s21_from_float_to_decimal_code_test_##NUM) {                  \
    int code;                                                              \
    float val = (float)VAL;                                                \
    s21_decimal result = {{0, 0, 0, 0}};                                   \
                                                                           \
    code = s21_from_float_to_decimal(val, &result);                        \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "float:    " RESET "%*.29e\n", DEC_BUFF_SIZE, val); \
      printf(DARK_GREY "Code:     " RESET "%*d\n", DEC_BUFF_SIZE, code);   \
      printf(DARK_GREY "Expected: " RESET "%*d\n", DEC_BUFF_SIZE, CODE);   \
      printf(code == CODE ? GREEN "\nSUCCESS" : RED "\nFAIL");             \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_int_eq(code, CODE);                                          \
  }                                                                        \
  END_TEST

#define FROM_DECIMAL_TO_INT_RES_TEST(NUM, VAL)                             \
  START_TEST(s21_from_decimal_to_int_res_test_##NUM) {                     \
    s21_decimal value = {{0, 0, 0, 0}};                                    \
    int result;                                                            \
    char buff[DEC_BUFF_SIZE];                                              \
                                                                           \
    convert_str_to_decimal(#VAL, &value);                                  \
    s21_from_decimal_to_int(value, &result);                               \
    sprintf(buff, "%d", result);                                           \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "decimal:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL);   \
      printf(DARK_GREY "int:      " RESET "%*d\n", DEC_BUFF_SIZE, result); \
      printf(!strcmp(buff, #VAL) ? GREEN "\nSUCCESS" : RED "\nFAIL");      \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_str_eq(buff, #VAL);                                          \
  }                                                                        \
  END_TEST

#define FROM_DECIMAL_TO_INT_CODE_TEST(NUM, VAL, CODE)                      \
  START_TEST(s21_from_decimal_to_int_code_test_##NUM) {                    \
    s21_decimal value = {{0, 0, 0, 0}};                                    \
    int result, code;                                                      \
                                                                           \
    convert_str_to_decimal(#VAL, &value);                                  \
    code = s21_from_decimal_to_int(value, &result);                        \
                                                                           \
    if (NICE_OUT) {                                                        \
      printf(DARK_GREY "decimal:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL);   \
      printf(DARK_GREY "Code:     " RESET "%*d\n", DEC_BUFF_SIZE, code);   \
      printf(DARK_GREY "Expected: " RESET "%*d\n", DEC_BUFF_SIZE, CODE);   \
      printf(code == CODE ? GREEN "\nSUCCESS" : RED "\nFAIL");             \
      printf(RESET "\n-----------------------------------------------\n"); \
    }                                                                      \
                                                                           \
    ck_assert_int_eq(code, CODE);                                          \
  }                                                                        \
  END_TEST

#define FROM_DECIMAL_TO_FLOAT_TEST(NUM, VAL)                                  \
  START_TEST(s21_from_decimal_to_float_test_##NUM) {                          \
    s21_decimal value = {{0, 0, 0, 0}};                                       \
    float result, expected = (float)atof(#VAL);                               \
                                                                              \
    convert_str_to_decimal(#VAL, &value);                                     \
    s21_from_decimal_to_float(value, &result);                                \
                                                                              \
    if (NICE_OUT) {                                                           \
      printf(DARK_GREY "decimal:  " RESET "%*s\n", DEC_BUFF_SIZE, #VAL);      \
      printf(DARK_GREY "float:    " RESET "%*.28f\n", DEC_BUFF_SIZE, result); \
      printf(DARK_GREY "Expected: " RESET "%*.28f\n", DEC_BUFF_SIZE,          \
             expected);                                                       \
      printf(result == expected ? GREEN "\nSUCCESS" : RED "\nFAIL");          \
      printf(RESET "\n-----------------------------------------------\n");    \
    }                                                                         \
                                                                              \
    ck_assert_float_eq(result, expected);                                     \
  }                                                                           \
  END_TEST

#endif