#include "test.h"

CODE_2_ARGS_TEST(1, s21_is_less, -999999999999999999999999,
                 999999999999999999999999, 1)
CODE_2_ARGS_TEST(2, s21_is_less, 33333333.333333, 333333.33333333, 0)
CODE_2_ARGS_TEST(3, s21_is_less, -33333333.333333, 333333.33333333, 1)
CODE_2_ARGS_TEST(4, s21_is_less, 1.00000000000000, 1, 0)
CODE_2_ARGS_TEST(5, s21_is_less, 0.00000000000001, 0.0000000001, 1)
CODE_2_ARGS_TEST(6, s21_is_less, 0, -0, 0)

Suite *s21_is_less_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_is_less\n";
#else
  suite_name = "s21_is_less";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_1);
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_2);
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_3);
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_4);
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_5);
  tcase_add_test(tc_core, s21_is_less_code_2_args_test_6);
  suite_add_tcase(s, tc_core);
  return s;
}