#include "test.h"

RESULT_2_VALS_TEST(1, s21_add, 77777777777777777777777,
                   -66666666666666666666666, 11111111111111111111111)
RESULT_2_VALS_TEST(2, s21_add, -55555555, 66666666666666666666666,
                   66666666666666611111111)
RESULT_2_VALS_TEST(3, s21_add, 10.000000000, 7777777.00000000000000000000,
                   7777787)
RESULT_2_VALS_TEST(4, s21_add, 79228162514264337593543950334, 0.6,
                   79228162514264337593543950335)
RESULT_2_VALS_TEST(5, s21_add, 7922816251426433759354395033.5,
                   7922816251426433759354395033.5,
                   15845632502852867518708790067)
RESULT_2_VALS_TEST(6, s21_add, 0.0000000000000000000000000001,
                   0.9999999999999999999999999999, 1)
RESULT_2_VALS_TEST(7, s21_add, 792281625.14264337593543950335,
                   79228162514264337593543.950335,
                   79228162514265129875169.09298)
CODE_3_ARGS_TEST(8, s21_add, 79228162514264337593543950334, 1.5, 1)
CODE_3_ARGS_TEST(9, s21_add, -79228162514264337593543950334, -1.5, 2)
CODE_3_ARGS_TEST(10, s21_add, 7922816251426433759354395033.5,
                 7922816251426433759354395033.5, 0)

Suite *s21_add_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_add\n";
#else
  suite_name = "s21_add";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_add_result_2_vals_test_1);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_2);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_3);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_4);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_5);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_6);
  tcase_add_test(tc_core, s21_add_result_2_vals_test_7);
  tcase_add_test(tc_core, s21_add_code_3_args_test_8);
  tcase_add_test(tc_core, s21_add_code_3_args_test_9);
  tcase_add_test(tc_core, s21_add_code_3_args_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}