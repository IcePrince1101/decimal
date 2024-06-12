#ifndef S21_DECIMAL_MAN_TESTS
#define S21_DECIMAL_MAN_TESTS

#include <stdlib.h>
#include <string.h>

#include "../converter/converter.h"
#include "../other/colors.h"
#include "../s21_decimal.h"

#define ARITMETIC_FUNC_TEST(FUNC)                                 \
  int man_test_##FUNC(const char *value_1, const char *value_2) { \
    int err_code = 0;                                             \
    s21_decimal dec_1 = {{0, 0, 0, 0}};                           \
    s21_decimal dec_2 = {{0, 0, 0, 0}};                           \
    s21_decimal res = {{0, 0, 0, 0}};                             \
    char dec_1_str[BUFF_SIZE] = "0";                              \
    char dec_2_str[BUFF_SIZE] = "0";                              \
    char res_str[BUFF_SIZE] = "0";                                \
                                                                  \
    err_code = convert_str_to_decimal(value_1, &dec_1);           \
    if (!err_code) {                                              \
      convert_decimal_to_str(dec_1, dec_1_str);                   \
      printf(DARK_GREY "\nVALUE_1: %s\n" RESET, dec_1_str);       \
      print_decimal(dec_1);                                       \
      err_code = convert_str_to_decimal(value_2, &dec_2);         \
    }                                                             \
    if (!err_code) {                                              \
      convert_decimal_to_str(dec_2, dec_2_str);                   \
      printf(DARK_GREY "\nVALUE_2: %s\n" RESET, dec_2_str);       \
      print_decimal(dec_2);                                       \
      err_code = s21_##FUNC(dec_1, dec_2, &res);                  \
    }                                                             \
    if (!err_code) {                                              \
      convert_decimal_to_str(res, res_str);                       \
      printf(DARK_GREY "\nRESULT: %s\n" RESET, res_str);          \
      print_decimal(res);                                         \
    }                                                             \
                                                                  \
    return err_code;                                              \
  }

#define COMPARISON_FUNC_TEST(FUNC)                                \
  int man_test_##FUNC(const char *value_1, const char *value_2) { \
    int err_code = 0;                                             \
    s21_decimal dec_1 = {{0, 0, 0, 0}};                           \
    s21_decimal dec_2 = {{0, 0, 0, 0}};                           \
    char dec_1_str[BUFF_SIZE] = "0";                              \
    char dec_2_str[BUFF_SIZE] = "0";                              \
    int res;                                                      \
                                                                  \
    err_code = convert_str_to_decimal(value_1, &dec_1);           \
    if (!err_code) {                                              \
      convert_decimal_to_str(dec_1, dec_1_str);                   \
      printf(DARK_GREY "\nVALUE_1: %s\n" RESET, dec_1_str);       \
      print_decimal(dec_1);                                       \
      err_code = convert_str_to_decimal(value_2, &dec_2);         \
    }                                                             \
    if (!err_code) {                                              \
      convert_decimal_to_str(dec_2, dec_2_str);                   \
      printf(DARK_GREY "\nVALUE_2: %s\n" RESET, dec_2_str);       \
      print_decimal(dec_2);                                       \
      res = s21_##FUNC(dec_1, dec_2);                             \
      printf(DARK_GREY "\nRESULT: %d\n\n" RESET, res);            \
    }                                                             \
                                                                  \
    return err_code;                                              \
  }

#define ANOTHER_FUNC_TEST(FUNC)                          \
  int man_test_##FUNC(const char *value) {               \
    int err_code = 0;                                    \
    s21_decimal dec = {{0, 0, 0, 0}};                    \
    s21_decimal res = {{0, 0, 0, 0}};                    \
    char dec_str[BUFF_SIZE] = "0";                       \
    char res_str[BUFF_SIZE] = "0";                       \
                                                         \
    err_code = convert_str_to_decimal(value, &dec);      \
    if (!err_code) {                                     \
      convert_decimal_to_str(dec, dec_str);              \
      printf(DARK_GREY "\nVALUE: %s\n" RESET, dec_str);  \
      print_decimal(dec);                                \
      err_code = s21_##FUNC(dec, &res);                  \
    }                                                    \
    if (!err_code) {                                     \
      convert_decimal_to_str(res, res_str);              \
      printf(DARK_GREY "\nRESULT: %s\n" RESET, res_str); \
      print_decimal(res);                                \
    }                                                    \
                                                         \
    return err_code;                                     \
  }

enum {
  t_add,
  t_sub,
  t_mul,
  t_div,
  t_is_less,
  t_is_less_or_equal,
  t_is_greater,
  t_is_greater_or_equal,
  t_is_equal,
  t_is_not_equal,
  t_from_int_to_decimal,
  t_from_float_to_decimal,
  t_from_decimal_to_int,
  t_from_decimal_to_float,
  t_floor,
  t_round,
  t_truncate,
  t_negate,
};

int get_token(const char *str);
int check_token(int token, int argc);
int use_token(int token, char **argv);
int man_test_add(const char *value_1, const char *value_2);
int man_test_sub(const char *value_1, const char *value_2);
int man_test_mul(const char *value_1, const char *value_2);
int man_test_div(const char *value_1, const char *value_2);
int man_test_is_less(const char *value_1, const char *value_2);
int man_test_is_less_or_equal(const char *value_1, const char *value_2);
int man_test_is_greater(const char *value_1, const char *value_2);
int man_test_is_greater_or_equal(const char *value_1, const char *value_2);
int man_test_is_equal(const char *value_1, const char *value_2);
int man_test_is_not_equal(const char *value_1, const char *value_2);
int man_test_from_int_to_decimal(const char *value);
int man_test_from_float_to_decimal(const char *value);
int man_test_from_decimal_to_int(const char *value);
int man_test_from_decimal_to_float(const char *value);
int man_test_floor(const char *value);
int man_test_round(const char *value);
int man_test_truncate(const char *value);
int man_test_negate(const char *value);

#endif