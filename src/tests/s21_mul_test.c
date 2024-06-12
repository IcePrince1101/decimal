#include "test.h"

RESULT_2_VALS_TEST(1, s21_mul, 11111111111111, 55555555555555,
                   617283950617271604938271605)
RESULT_2_VALS_TEST(2, s21_mul, -6767676767676, -2323232323232,
                   15722885419851145801448832)
RESULT_2_VALS_TEST(3, s21_mul, 666666.00000000, 222222.00000000000000,
                   148147851852)
RESULT_2_VALS_TEST(4, s21_mul, -0.00000077777777777, -0.0000000000007777777777,
                   0.0000000000000000006049382715)
RESULT_2_VALS_TEST(5, s21_mul, 7.9228162514264337593543950335,
                   7.9228162514264337593543950335,
                   62.77101735386680763835789423)
RESULT_2_VALS_TEST(6, s21_mul, 6.6666666666666666666666666666,
                   7.7777777777777777777777777777,
                   51.851851851851851851851851851)
RESULT_2_VALS_TEST(7, s21_mul, 929292929292929292929292, -0, -0)
CODE_3_ARGS_TEST(8, s21_mul, 79228162514264337593543950335, 1.1, 1)
CODE_3_ARGS_TEST(9, s21_mul, 79228162514264337593543950335, -1.1, 2)
CODE_3_ARGS_TEST(10, s21_mul, 7.9228162514264337593543950335,
                 7.9228162514264337593543950335, 0)

Suite *s21_mul_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_mul\n";
#else
  suite_name = "s21_mul";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_1);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_2);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_3);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_4);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_5);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_6);
  tcase_add_test(tc_core, s21_mul_result_2_vals_test_7);
  tcase_add_test(tc_core, s21_mul_code_3_args_test_8);
  tcase_add_test(tc_core, s21_mul_code_3_args_test_9);
  tcase_add_test(tc_core, s21_mul_code_3_args_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}