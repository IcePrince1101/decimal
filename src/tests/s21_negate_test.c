#include "test.h"

RESULT_1_VAL_TEST(1, s21_negate, 4444444444444444444, -4444444444444444444)
RESULT_1_VAL_TEST(2, s21_negate, -4444444444444444444, 4444444444444444444)
RESULT_1_VAL_TEST(3, s21_negate, 0, -0)
RESULT_1_VAL_TEST(4, s21_negate, -0, 0)
CODE_1_VAL_TEST(5, s21_negate, 55555, 0)

Suite *s21_negate_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_negate\n";
#else
  suite_name = "s21_negate";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_negate_result_1_val_test_1);
  tcase_add_test(tc_core, s21_negate_result_1_val_test_2);
  tcase_add_test(tc_core, s21_negate_result_1_val_test_3);
  tcase_add_test(tc_core, s21_negate_result_1_val_test_4);
  tcase_add_test(tc_core, s21_negate_code_1_val_test_5);
  suite_add_tcase(s, tc_core);
  return s;
}