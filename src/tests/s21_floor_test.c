#include "test.h"

RESULT_1_VAL_TEST(1, s21_floor, 4444444444444444444, 4444444444444444444)
RESULT_1_VAL_TEST(2, s21_floor, -4444444444444444444, -4444444444444444444)
RESULT_1_VAL_TEST(3, s21_floor, 4444444444.444444444, 4444444444)
RESULT_1_VAL_TEST(4, s21_floor, -4444444444.444444444, -4444444445)
RESULT_1_VAL_TEST(5, s21_floor, 4444444444.000000000, 4444444444)
RESULT_1_VAL_TEST(6, s21_floor, -4444444444.000000000, -4444444444)
RESULT_1_VAL_TEST(7, s21_floor, 0.0000000000000000001, 0)
RESULT_1_VAL_TEST(8, s21_floor, -0.0000000000000000001, -1)
CODE_1_VAL_TEST(9, s21_floor, -55555555.55555555, 0)

Suite *s21_floor_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_floor\n";
#else
  suite_name = "s21_floor";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_floor_result_1_val_test_1);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_2);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_3);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_4);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_5);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_6);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_7);
  tcase_add_test(tc_core, s21_floor_result_1_val_test_8);
  tcase_add_test(tc_core, s21_floor_code_1_val_test_9);
  suite_add_tcase(s, tc_core);
  return s;
}