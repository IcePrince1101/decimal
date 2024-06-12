#include "test.h"

FROM_FLOAT_TO_DECIMAL_RES_TEST(1, -0.0F, -0)
FROM_FLOAT_TO_DECIMAL_RES_TEST(2, 0.00000000555555555000000F, 0.000000005555556)
FROM_FLOAT_TO_DECIMAL_RES_TEST(3, 999.000999F, 999.001)
FROM_FLOAT_TO_DECIMAL_RES_TEST(4, -7654321.1234567F, -7654321)
FROM_FLOAT_TO_DECIMAL_RES_TEST(5, -1.0e-28F, -0.0000000000000000000000000001)
FROM_FLOAT_TO_DECIMAL_RES_TEST(6, 7.99999954e-28F,
                               0.0000000000000000000000000008)
FROM_FLOAT_TO_DECIMAL_RES_TEST(7, 7.92281625142643375935439503360e+27F,
                               7922816000000000000000000000)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(8, 7.92281625142643375935439503360e+27F, 0)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(9, 7.92281625142643375935439503360e+28F, 1)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(10, 1e-28F, 0)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(11, 1e-29F, 1)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(12, INFINITY, 1)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(13, -INFINITY, 1)
FROM_FLOAT_TO_DECIMAL_CODE_TEST(14, NAN, 1)

Suite *s21_from_float_to_decimal_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_from_float_to_decimal\n";
#else
  suite_name = "s21_from_float_to_decimal";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_1);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_2);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_3);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_4);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_5);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_6);
  tcase_add_test(tc_core, s21_from_float_to_decimal_res_test_7);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_8);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_9);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_10);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_11);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_12);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_13);
  tcase_add_test(tc_core, s21_from_float_to_decimal_code_test_14);
  suite_add_tcase(s, tc_core);
  return s;
}