#ifndef S21_DECIMAL_TESTS
#define S21_DECIMAL_TESTS

#include <check.h>
#include <stdio.h>
#include <string.h>

#include "../converter/converter.h"
#include "../s21_decimal.h"
#include "test_patterns.h"

void run_test(Suite *test);
Suite *s21_add_suite();
Suite *s21_sub_suite();
Suite *s21_mul_suite();
Suite *s21_div_suite();
Suite *s21_is_less_suite();
Suite *s21_is_less_or_equal_suite();
Suite *s21_is_greater_suite();
Suite *s21_is_greater_or_equal_suite();
Suite *s21_is_equal_suite();
Suite *s21_is_not_equal_suite();
Suite *s21_from_int_to_decimal_suite();
Suite *s21_from_float_to_decimal_suite();
Suite *s21_from_decimal_to_int_suite();
Suite *s21_from_decimal_to_float_suite();
Suite *s21_floor_suite();
Suite *s21_round_suite();
Suite *s21_truncate_suite();
Suite *s21_negate_suite();

#endif