#include "s21_decimal_mantissa.h"

int mant_is_not_zero(const int *m, int len) {
  int res = 0;

  for (int i = len - 1; i >= 0 && !res; i--) {
    res = m[i] != 0;
  }

  return res;
}

void fill_mant_with_zeros(int *m, int len) {
  for (int i = 0; i < len; i++) {
    m[i] = 0;
  }
}

void copy_mant(const int *src, int *dst, int len) {
  for (int i = 0; i < len; i++) {
    dst[i] = src[i];
  }
}

int compare_mants(const int *m_1, const int *m_2, int len) {
  int res = 0;
  long operand_1, operand_2, diff;

  for (int i = len - 1; i >= 0 && !res; i--) {
    operand_1 = (unsigned)m_1[i];
    operand_2 = (unsigned)m_2[i];
    diff = operand_1 - operand_2;

    if (diff > 0) {
      res = 1;
    } else if (diff < 0) {
      res = -1;
    }
  }

  return res;
}

int add_mants(const int *m_1, const int *m_2, int *res, int len) {
  int total_res[len];
  unsigned long operand_1, operand_2, cur_res, carry = 0;

  fill_mant_with_zeros(total_res, len);

  for (int i = 0; i < len; i++) {
    operand_1 = (unsigned)m_1[i];
    operand_2 = (unsigned)m_2[i];
    cur_res = operand_1 + operand_2 + carry;
    carry = cur_res >> INT_BITS_SHIFT;
    total_res[i] = cur_res & UINT_MAX;
  }

  if (!carry) {
    copy_mant(total_res, res, len);
  }

  return carry ? -1 : 0;
}

int sub_mants(const int *m_1, const int *m_2, int *res, int len) {
  int total_res[len];
  long cur_res;
  unsigned long operand_1, operand_2;
  int borrow = 0;

  fill_mant_with_zeros(total_res, len);

  for (int i = 0; i < len; i++) {
    operand_1 = (unsigned)m_1[i];
    operand_2 = (unsigned)m_2[i];
    cur_res = operand_1 - operand_2 - borrow;
    borrow = cur_res < 0;
    total_res[i] = cur_res & UINT_MAX;
  }

  if (!borrow) {
    copy_mant(total_res, res, len);
  }

  return borrow ? -1 : 0;
}

void mul_mants(const int *m_1, const int *m_2, int *res, int len) {
  int total_res[len * 2];
  unsigned long operand_1, operand_2, cur_res, carry;
  unsigned long temp[len * 2];

  fill_mant_with_zeros(total_res, len * 2);

  for (int i = 0, j = len * 2; i < j; i++) {
    temp[i] = 0;
  }

  for (int i = 0; i < len; i++) {
    carry = 0;
    for (int j = 0; j < len; j++) {
      operand_1 = (unsigned)m_1[j];
      operand_2 = (unsigned)m_2[i];
      cur_res = operand_1 * operand_2 + carry;
      carry = cur_res >> INT_BITS_SHIFT;
      temp[i + j] += cur_res & UINT_MAX;
    }
    temp[i + len] += carry;
  }

  carry = 0;

  for (int i = 0, j = len * 2; i < j; i++) {
    temp[i] += carry;
    carry = temp[i] >> INT_BITS_SHIFT;
    total_res[i] = temp[i] & UINT_MAX;
  }

  copy_mant(total_res, res, len * 2);
}

void i_div_mants(const int *m_1, const int *m_2, int *res, int *rem, int len) {
  int total_res[len];
  int cur_dividend[len];
  int comparison_res = 0;

  fill_mant_with_zeros(total_res, len);
  copy_mant(m_1, cur_dividend, len);

  while (compare_mants(cur_dividend, m_2, len) >= 0) {
    int cur_res[len];
    int cur_divisor[len];
    int temp[len];
    int overflow = 0;

    fill_mant_with_zeros(cur_res, len);
    copy_mant(m_2, cur_divisor, len);

    add_int_to_mant(cur_res, 1, cur_res, len);

    do {
      copy_mant(cur_divisor, temp, len);
      overflow = mul_mant_by_two(cur_divisor, cur_divisor, len);
      if (!overflow) {
        comparison_res = compare_mants(cur_dividend, cur_divisor, len);
      }
      if (!overflow && comparison_res >= 0) {
        mul_mant_by_two(cur_res, cur_res, len);
      }
    } while (comparison_res >= 0 && !overflow);

    copy_mant(temp, cur_divisor, len);
    sub_mants(cur_dividend, cur_divisor, cur_dividend, len);
    add_mants(total_res, cur_res, total_res, len);
  }

  copy_mant(total_res, res, len);
  copy_mant(cur_dividend, rem, len);
}

void f_div_mants(const int *m_1, const int *m_2, int *res, int *exp, int len) {
  int total_res[len];
  int cur_res[len];
  int rem[len];
  int temp[len];
  int fract_digits = -1;
  int overflow = 0;

  fill_mant_with_zeros(total_res, len);
  fill_mant_with_zeros(cur_res, len);
  copy_mant(m_1, rem, len);

  while (!overflow) {
    i_div_mants(rem, m_2, cur_res, rem, len);
    copy_mant(total_res, temp, len);
    overflow = mul_mant_by_int(temp, 10, temp, len);
    if (!overflow) {
      overflow = add_mants(temp, cur_res, temp, len);
    }
    if (!overflow) {
      mul_mant_by_int(rem, 10, rem, len);
      copy_mant(temp, total_res, len);
      fract_digits++;
    }
  }

  copy_mant(total_res, temp, len);
  add_int_to_mant(cur_res, 5, cur_res, len);
  div_mant_by_int(cur_res, 10, cur_res, rem, len);
  overflow = add_mants(temp, cur_res, temp, len);
  if (!overflow) {
    copy_mant(temp, total_res, len);
  }

  copy_mant(total_res, res, len);
  *exp = fract_digits;
}

int add_int_to_mant(const int *m, unsigned x, int *res, int len) {
  int total_res[len];
  unsigned long operand, cur_res, carry = x;

  fill_mant_with_zeros(total_res, len);

  for (int i = 0; i < len; i++) {
    operand = (unsigned)m[i];
    cur_res = operand + carry;
    carry = cur_res >> INT_BITS_SHIFT;
    total_res[i] = cur_res & UINT_MAX;
  }

  if (!carry) {
    copy_mant(total_res, res, len);
  }

  return carry ? -1 : 0;
}

int mul_mant_by_int(const int *m, unsigned x, int *res, int len) {
  int total_res[len];
  unsigned long operand, cur_res, carry = 0;

  fill_mant_with_zeros(total_res, len);

  for (int i = 0; i < len; i++) {
    operand = (unsigned)m[i];
    cur_res = operand * x + carry;
    carry = cur_res >> INT_BITS_SHIFT;
    total_res[i] = cur_res & UINT_MAX;
  }

  if (!carry) {
    copy_mant(total_res, res, len);
  }

  return carry ? -1 : 0;
}

int mul_mant_by_two(const int *m, int *res, int len) {
  int total_res[len];
  unsigned cur_int, carry = 0;

  fill_mant_with_zeros(total_res, len);

  for (int i = 0; i < len; i++) {
    cur_int = m[i];
    total_res[i] = carry + (cur_int << 1);
    carry = m[i] < 0;
  }

  if (!carry) {
    copy_mant(total_res, res, len);
  }

  return carry ? -1 : 0;
}

void div_mant_by_int(const int *m, unsigned x, int *res, int *rem, int len) {
  int divisor[len];

  fill_mant_with_zeros(divisor, len);
  divisor[0] += x;

  i_div_mants(m, divisor, res, rem, len);
}

int div_mant_by_two(const int *m, int *res, int len) {
  int total_res[len];
  unsigned cur_int, carry = 0;

  fill_mant_with_zeros(total_res, len);

  for (int i = len - 1; i >= 0; i--) {
    cur_int = m[i];
    total_res[i] = (carry << 31) + (cur_int >> 1);
    carry = cur_int & 1;
  }

  copy_mant(total_res, res, len);

  return carry ? -1 : 0;
}

void round_and_add_mants(const int *m_1, const int *m_2, int *res, int len) {
  int m_1_copy[len];
  int m_2_copy[len];
  int digit_1[len];
  int digit_2[len];
  int cur_res[len];
  int carry;

  copy_mant(m_1, m_1_copy, len);
  copy_mant(m_2, m_2_copy, len);

  div_mant_by_int(m_1_copy, 10, m_1_copy, digit_1, len);
  div_mant_by_int(m_2_copy, 10, m_2_copy, digit_2, len);
  carry = (digit_1[0] + digit_2[0] + 5) / 10;
  add_mants(m_1_copy, m_2_copy, cur_res, len);
  add_int_to_mant(cur_res, carry, cur_res, len);

  copy_mant(cur_res, res, len);
}

int check_and_round_too_big_mant(const int *m, int *res, int len) {
  int exp_decr = 0;
  int total_res[len];
  int too_big[len];

  copy_mant(m, total_res, len);

  too_big[0] = -5;
  for (int i = 1; i < len; i++) {
    too_big[i] = -1;
  }

  if (compare_mants(total_res, too_big, len) >= 0) {
    int temp[len];
    int the_biggest[len];
    int carry;

    for (int i = 0; i < len; i++) {
      the_biggest[i] = -1;
    }

    carry = compare_mants(total_res, the_biggest, len) == 0;

    div_mant_by_int(total_res, 10, total_res, temp, len);
    add_int_to_mant(total_res, carry, total_res, len);

    exp_decr = 1;
  }

  copy_mant(total_res, res, len);

  return exp_decr;
}

int shift_mant_to_the_rignt(const int *m, int *res, int len, int *exp) {
  int err_code = 0;
  int total_res[len];
  int temp_1[len];
  int temp_2[len];

  copy_mant(m, total_res, len);

  while (upper_ints_are_not_zeros(total_res, len) && !err_code) {
    copy_mant(total_res, temp_1, len);
    div_mant_by_int(temp_1, 10, temp_1, temp_2, len);
    if (!upper_ints_are_not_zeros(temp_1, len)) {
      add_int_to_mant(total_res, 5, total_res, len);
    }
    div_mant_by_int(total_res, 10, total_res, temp_2, len);
    (*exp)--;
    if (*exp < 0) {
      err_code = -1;
    }
  }

  if (!err_code) {
    copy_mant(total_res, res, len);
  }

  return err_code;
}

int upper_ints_are_not_zeros(const int *m, int len) {
  int res = 0;

  for (int i = len - 1, j = len / 2; i >= j && !res; i--) {
    if (m[i]) {
      res = 1;
    }
  }

  return res;
}

int process_bin_exp(const int *m, int *res, int bin_exp, int *dec_exp,
                    int len) {
  int err_code = 0;
  int cur_dec_exp = 0;
  int total_res[len];

  copy_mant(m, total_res, len);

  for (; bin_exp < 0 && mant_is_not_zero(total_res, len); bin_exp++) {
    if (bin_exp == -1) {
      add_int_to_mant(total_res, 1, total_res, len);
    }

    int rem = div_mant_by_two(total_res, total_res, len);

    if (rem && bin_exp != -1 && cur_dec_exp < MAX_EXP) {
      int overflow;
      int temp[len];

      copy_mant(total_res, temp, len);

      overflow = mul_mant_by_int(temp, 10, temp, len);

      if (!overflow) {
        overflow = add_int_to_mant(temp, 5, temp, len);
      }

      if (!overflow) {
        mul_mant_by_int(total_res, 10, total_res, len);
        add_int_to_mant(total_res, 5, total_res, len);
        cur_dec_exp++;
      }
    }
  }

  for (; bin_exp > 0 && !err_code; bin_exp--) {
    err_code = mul_mant_by_two(total_res, total_res, len);
  }

  if (!err_code) {
    copy_mant(total_res, res, len);
    *dec_exp = cur_dec_exp;
  }

  return err_code;
}

void save_seven_digits(const int *m, int *res, int *res_dec_exp, int len) {
  int seven_max_digits[len];
  int total_res[len];
  int temp_1[len];
  int temp_2[len];
  int dec_exp = *res_dec_exp;

  fill_mant_with_zeros(seven_max_digits, len);
  seven_max_digits[0] = SEVEN_MAX_DIGITS;

  copy_mant(m, total_res, len);
  copy_mant(m, temp_1, len);

  while (compare_mants(total_res, seven_max_digits, len) > 0) {
    div_mant_by_int(temp_1, 10, temp_1, temp_2, len);
    if (compare_mants(temp_1, seven_max_digits, len) <= 0) {
      add_int_to_mant(total_res, 5, total_res, len);
    }
    div_mant_by_int(total_res, 10, total_res, temp_2, len);
    dec_exp--;
  }

  while (dec_exp < 0) {
    mul_mant_by_int(total_res, 10, total_res, len);
    dec_exp++;
  }

  copy_mant(total_res, res, len);
  *res_dec_exp = dec_exp;
}