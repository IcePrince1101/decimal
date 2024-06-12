#ifndef S21_DECIMAL_DATA
#define S21_DECIMAL_DATA

#define INT_BITS_SHIFT 32
#define MANT_LEN 3
#define DBL_MANT_LEN 6
#define MAX_EXP 28
#define FLOAT_EXP_SHIFT 127
#define FLOAT_MANT_LEN 23
#define FLOAT_MANT_MAX 16777215
#define FLOAT_MANT_IMPLICIT_BIT 8388608
#define FLOAT_MIN 1e-28F
#define SEVEN_MAX_DIGITS 9999999

typedef struct {
  int bits[4];
} s21_decimal;

typedef union float_converter {
  float num;
  struct {
    unsigned mant_bits : 23;
    unsigned exp_bits : 8;
    unsigned sign_bit : 1;
  } bits;
} f_conv;

typedef union sign_handler {
  int num;
  struct {
    unsigned other_bits : 31;
    unsigned sign_bit : 1;
  } bits;
} s_handler;

typedef union exponent_handler {
  int num;
  struct {
    int other_bits_0 : 16;
    int exp_bits : 8;
    int other_bits_1 : 8;
  } bits;
} e_handler;

#endif