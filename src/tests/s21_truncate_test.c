#include "test.h"

RESULT_1_VAL_TEST(1, s21_truncate, 444444444.4444444444, 444444444)
RESULT_1_VAL_TEST(2, s21_truncate, -444444444.4444444444, -444444444)
RESULT_1_VAL_TEST(3, s21_truncate, 555555555.555555555, 555555555)
RESULT_1_VAL_TEST(4, s21_truncate, 555555555.000000000, 555555555)
RESULT_1_VAL_TEST(5, s21_truncate, 0.0000000000000000001, 0)
RESULT_1_VAL_TEST(6, s21_truncate, -0.0000000000000000001, -0)
RESULT_1_VAL_TEST(7, s21_truncate, 0.9999999999999999999, 0)
RESULT_1_VAL_TEST(8, s21_truncate, 7922816251426433759354395033.5,
                  7922816251426433759354395033)
RESULT_1_VAL_TEST(9, s21_truncate, 7.9228162514264337593543950335, 7)
CODE_1_VAL_TEST(10, s21_truncate, 7922816251426433759354395033.5, 0)

Suite *s21_truncate_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_truncate\n";
#else
  suite_name = "s21_truncate";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_1);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_2);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_3);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_4);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_5);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_6);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_7);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_8);
  tcase_add_test(tc_core, s21_truncate_result_1_val_test_9);
  tcase_add_test(tc_core, s21_truncate_code_1_val_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}