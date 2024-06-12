#include "test.h"

FROM_DECIMAL_TO_INT_RES_TEST(1, 0)
FROM_DECIMAL_TO_INT_RES_TEST(2, -1)
FROM_DECIMAL_TO_INT_RES_TEST(3, 2147483647)
FROM_DECIMAL_TO_INT_RES_TEST(4, -2147483648)
FROM_DECIMAL_TO_INT_CODE_TEST(5, 2147483648, 1)
FROM_DECIMAL_TO_INT_CODE_TEST(6, -2147483649, 1)
FROM_DECIMAL_TO_INT_CODE_TEST(7, 9999999999999999999999999999, 1)
FROM_DECIMAL_TO_INT_CODE_TEST(8, -9999999999999999999999999999, 1)

Suite *s21_from_decimal_to_int_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_from_decimal_to_int\n";
#else
  suite_name = "s21_from_decimal_to_int";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_decimal_to_int_res_test_1);
  tcase_add_test(tc_core, s21_from_decimal_to_int_res_test_2);
  tcase_add_test(tc_core, s21_from_decimal_to_int_res_test_3);
  tcase_add_test(tc_core, s21_from_decimal_to_int_res_test_4);
  tcase_add_test(tc_core, s21_from_decimal_to_int_code_test_5);
  tcase_add_test(tc_core, s21_from_decimal_to_int_code_test_6);
  tcase_add_test(tc_core, s21_from_decimal_to_int_code_test_7);
  tcase_add_test(tc_core, s21_from_decimal_to_int_code_test_8);
  suite_add_tcase(s, tc_core);
  return s;
}