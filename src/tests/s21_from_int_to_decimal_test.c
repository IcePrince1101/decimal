#include "test.h"

FROM_INT_TO_DECIMAL_TEST(1, 0)
FROM_INT_TO_DECIMAL_TEST(2, -1)
FROM_INT_TO_DECIMAL_TEST(3, 2147483647)
FROM_INT_TO_DECIMAL_TEST(4, -2147483648)

Suite *s21_from_int_to_decimal_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_from_int_to_decimal\n";
#else
  suite_name = "s21_from_int_to_decimal";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_1);
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_2);
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_3);
  tcase_add_test(tc_core, s21_from_int_to_decimal_test_4);
  suite_add_tcase(s, tc_core);
  return s;
}