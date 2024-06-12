#ifndef S21_DECIMAL_CONVERTER
#define S21_DECIMAL_CONVERTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../other/colors.h"
#include "../s21_decimal.h"

#define BUFF_SIZE 32
#define LOWEST_DIGIT_CODE 48
#define HIGHEST_DIGIT_CODE 57
#define HIGHEST_EXP 28

typedef union integer_bits {
  int num;
  struct {
    unsigned bit_00 : 1;
    unsigned bit_01 : 1;
    unsigned bit_02 : 1;
    unsigned bit_03 : 1;
    unsigned bit_04 : 1;
    unsigned bit_05 : 1;
    unsigned bit_06 : 1;
    unsigned bit_07 : 1;
    unsigned bit_10 : 1;
    unsigned bit_11 : 1;
    unsigned bit_12 : 1;
    unsigned bit_13 : 1;
    unsigned bit_14 : 1;
    unsigned bit_15 : 1;
    unsigned bit_16 : 1;
    unsigned bit_17 : 1;
    unsigned bit_20 : 1;
    unsigned bit_21 : 1;
    unsigned bit_22 : 1;
    unsigned bit_23 : 1;
    unsigned bit_24 : 1;
    unsigned bit_25 : 1;
    unsigned bit_26 : 1;
    unsigned bit_27 : 1;
    unsigned bit_30 : 1;
    unsigned bit_31 : 1;
    unsigned bit_32 : 1;
    unsigned bit_33 : 1;
    unsigned bit_34 : 1;
    unsigned bit_35 : 1;
    unsigned bit_36 : 1;
    unsigned bit_37 : 1;
  } bits;
} int_bits;

typedef union special_integer_bits {
  int num;
  struct {
    unsigned unused_bits_0 : 16;
    unsigned exponent_bits : 8;
    unsigned unused_bits_1 : 7;
    unsigned sign_bit : 1;
  } bits;
} sp_int_bits;

int convert_str_to_decimal(const char *str, s21_decimal *dec);
int convert_decimal_to_str(s21_decimal dec, char *str);
int preprocess_str(const char *src, char *res, int *sign, int *exp);
void postprocess_str(const char *src, char *res, int sign, int exp);
int set_sign_and_exp(s21_decimal *dec, int sign, int exp);
int get_sign_and_exp(s21_decimal dec, int *sign, int *exp);
int get_pow_of_two(int exp);
int div_str_by_two(const char *src, char *res, int *rem);
int mul_str_by_two(const char *src, char *res);
int add_bit_to_str(const char *src, char *res, int bit);
void print_decimal(s21_decimal dec);
int print_significant_digits(s21_decimal dec, int color_code, int len);
void print_integer(int integer, int index, int len, int color_code);
void print_integer_bits(int integer, int color_code, int is_special);

#endif