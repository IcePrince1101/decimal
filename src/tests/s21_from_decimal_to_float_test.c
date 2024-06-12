#include "test.h"

FROM_DECIMAL_TO_FLOAT_TEST(1, -0.000000)
FROM_DECIMAL_TO_FLOAT_TEST(2, 7777777.7777777)
FROM_DECIMAL_TO_FLOAT_TEST(3, -0.000888)
FROM_DECIMAL_TO_FLOAT_TEST(4, 9.87654321)
FROM_DECIMAL_TO_FLOAT_TEST(5, -2344.23763240000004324)
FROM_DECIMAL_TO_FLOAT_TEST(6, 999.999)
FROM_DECIMAL_TO_FLOAT_TEST(7, 999.000999)
FROM_DECIMAL_TO_FLOAT_TEST(8, -0.0000152587890625)
FROM_DECIMAL_TO_FLOAT_TEST(9, 0.0000000000000000000000000001)
FROM_DECIMAL_TO_FLOAT_TEST(10, 79228162514264337593543950335)

Suite *s21_from_decimal_to_float_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_from_decimal_to_float\n";
#else
  suite_name = "s21_from_decimal_to_float";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_1);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_2);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_3);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_4);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_5);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_6);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_7);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_8);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_9);
  tcase_add_test(tc_core, s21_from_decimal_to_float_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}