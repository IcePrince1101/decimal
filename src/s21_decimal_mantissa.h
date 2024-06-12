#ifndef S21_DECIMAL_MANTISSA
#define S21_DECIMAL_MANTISSA

#include <limits.h>

#include "s21_decimal_data.h"

int mant_is_not_zero(const int *m, int len);
void fill_mant_with_zeros(int *m, int len);
void copy_mant(const int *src, int *dst, int len);
int compare_mants(const int *m_1, const int *m_2, int len);
int add_mants(const int *m_1, const int *m_2, int *res, int len);
int sub_mants(const int *m_1, const int *m_2, int *res, int len);
void mul_mants(const int *m_1, const int *m_2, int *res, int len);
void i_div_mants(const int *m_1, const int *m_2, int *res, int *rem, int len);
void f_div_mants(const int *m_1, const int *m_2, int *res, int *exp, int len);
int add_int_to_mant(const int *m, unsigned x, int *res, int len);
int mul_mant_by_int(const int *m, unsigned x, int *res, int len);
int mul_mant_by_two(const int *m, int *res, int len);
void div_mant_by_int(const int *m, unsigned x, int *res, int *rem, int len);
int div_mant_by_two(const int *m, int *res, int len);
void round_and_add_mants(const int *m_1, const int *m_2, int *res, int len);
int check_and_round_too_big_mant(const int *m, int *res, int len);
int shift_mant_to_the_rignt(const int *m, int *res, int len, int *exp);
int upper_ints_are_not_zeros(const int *m, int len);
int process_bin_exp(const int *m, int *res, int bin_exp, int *dec_exp, int len);
void save_seven_digits(const int *m, int *res, int *res_dec_exp, int len);

#endif