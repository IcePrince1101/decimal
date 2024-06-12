#ifndef S21_DECIMAL_UTTILITIES
#define S21_DECIMAL_UTTILITIES

#include "s21_decimal.h"
#include "s21_decimal_data.h"
#include "s21_decimal_mantissa.h"

int compare(s21_decimal value_1, s21_decimal value_2);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_exp(s21_decimal value);
void set_exp(s21_decimal *value, int exp);
void trunc_empty_exp(s21_decimal *value);
void check_exp_len(s21_decimal *value);
void compare_and_align_exps(s21_decimal *value_1, s21_decimal *value_2);
void align_exps(s21_decimal *lower, s21_decimal *higner);
void fract_dec_to_bin(s21_decimal *value);
void shift_float_bits(s21_decimal *value);

#endif