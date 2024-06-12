#include "test.h"

RESULT_2_VALS_TEST(1, s21_sub, 10000000000000000000000000000,
                   9999999999999999999999999999, 1)
RESULT_2_VALS_TEST(2, s21_sub, -55555555, -66666666666666666666666,
                   66666666666666611111111)
RESULT_2_VALS_TEST(3, s21_sub, 23874623781654346546, 123126541265341254,
                   23751497240389005292)
RESULT_2_VALS_TEST(4, s21_sub, 10.000000000, 7777777.00000000000000000000,
                   -7777767)
RESULT_2_VALS_TEST(5, s21_sub, 79228162514264337593543950335, 0.5,
                   79228162514264337593543950334)
RESULT_2_VALS_TEST(6, s21_sub, 79228162514264337593543950335, 0.4,
                   79228162514264337593543950335)
CODE_3_ARGS_TEST(7, s21_sub, -79228162514264337593543950335, 0.4, 0)
CODE_3_ARGS_TEST(8, s21_sub, -79228162514264337593543950335, 0.5, 2)
CODE_3_ARGS_TEST(9, s21_sub, 79228162514264337593543950335, -0.5, 1)
CODE_3_ARGS_TEST(10, s21_sub, -79228162514264337593543950334, 1.5, 2)

Suite *s21_sub_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_sub\n";
#else
  suite_name = "s21_sub";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_1);
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_2);
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_3);
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_4);
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_5);
  tcase_add_test(tc_core, s21_sub_result_2_vals_test_6);
  tcase_add_test(tc_core, s21_sub_code_3_args_test_7);
  tcase_add_test(tc_core, s21_sub_code_3_args_test_8);
  tcase_add_test(tc_core, s21_sub_code_3_args_test_9);
  tcase_add_test(tc_core, s21_sub_code_3_args_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}