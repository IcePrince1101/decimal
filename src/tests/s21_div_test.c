#include "test.h"

RESULT_2_VALS_TEST(1, s21_div, 217, 7, 31)
RESULT_2_VALS_TEST(2, s21_div, 219, 7, 31.285714285714285714285714286)
RESULT_2_VALS_TEST(3, s21_div, 1, 3, 0.3333333333333333333333333333)
RESULT_2_VALS_TEST(4, s21_div, 1, 6, 0.1666666666666666666666666667)
RESULT_2_VALS_TEST(5, s21_div, 100, -50.001, -1.9999600007999840003199936001)
RESULT_2_VALS_TEST(6, s21_div, -234.567, -89.01, 2.6352881698685540950455005056)
RESULT_2_VALS_TEST(7, s21_div, 66666666666666666666666, 5555555555,
                   12000000001200.00000011988)
RESULT_2_VALS_TEST(8, s21_div, 777777777.77777777777777,
                   7777.7777777777777777777, 100000)
RESULT_2_VALS_TEST(9, s21_div, 357635863458634573.45845,
                   26452634.523642364253435, 13519858036.786209898980754217)
CODE_3_ARGS_TEST(10, s21_div, 22222222222222222222222, -0.00000000000, 3)

Suite *s21_div_suite() {
  char *suite_name;
#ifdef NICE
  suite_name = "s21_div\n";
#else
  suite_name = "s21_div";
#endif
  Suite *s = suite_create(suite_name);
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_div_result_2_vals_test_1);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_2);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_3);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_4);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_5);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_6);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_7);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_8);
  tcase_add_test(tc_core, s21_div_result_2_vals_test_9);
  tcase_add_test(tc_core, s21_div_code_3_args_test_10);
  suite_add_tcase(s, tc_core);
  return s;
}