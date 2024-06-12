#include "s21_decimal_utilities.h"

int compare(s21_decimal value_1, s21_decimal value_2) {
  int res;

  if (!mant_is_not_zero(value_1.bits, MANT_LEN) &&
      !mant_is_not_zero(value_2.bits, MANT_LEN)) {
    res = 0;
  } else {
    int sign_1 = get_sign(value_1);
    int sign_2 = get_sign(value_2);

    if (sign_1 != sign_2) {
      res = sign_2 - sign_1;
    } else {
      check_exp_len(&value_1);
      check_exp_len(&value_2);

      trunc_empty_exp(&value_1);
      trunc_empty_exp(&value_2);

      compare_and_align_exps(&value_1, &value_2);

      res = compare_mants(value_1.bits, value_2.bits, MANT_LEN);

      if (sign_1 == 1) {
        res *= -1;
      }
    }
  }

  return res;
}

int get_sign(s21_decimal value) {
  s_handler s_h;
  s_h.num = value.bits[MANT_LEN];

  return s_h.bits.sign_bit;
}

void set_sign(s21_decimal *value, int sign) {
  s_handler s_h;
  s_h.num = value->bits[MANT_LEN];
  s_h.bits.sign_bit = sign;
  value->bits[MANT_LEN] = s_h.num;
}

int get_exp(s21_decimal value) {
  e_handler e_h;
  e_h.num = value.bits[MANT_LEN];

  return e_h.bits.exp_bits;
}

void set_exp(s21_decimal *value, int exp) {
  e_handler e_h;
  e_h.num = value->bits[MANT_LEN];
  e_h.bits.exp_bits = exp;
  value->bits[MANT_LEN] = e_h.num;
}

void trunc_empty_exp(s21_decimal *value) {
  s21_decimal cur_res = *value;

  if (!mant_is_not_zero(cur_res.bits, MANT_LEN)) {
    set_exp(&cur_res, 0);
  } else {
    int exp = get_exp(cur_res);
    int dividend[MANT_LEN];
    int rem[MANT_LEN];
    int temp[MANT_LEN];

    copy_mant(cur_res.bits, dividend, MANT_LEN);

    do {
      div_mant_by_int(dividend, 10, temp, rem, MANT_LEN);
      if (exp && !mant_is_not_zero(rem, MANT_LEN)) {
        exp--;
        copy_mant(temp, dividend, MANT_LEN);
      }
    } while (exp && !mant_is_not_zero(rem, MANT_LEN));

    set_exp(&cur_res, exp);
    copy_mant(dividend, cur_res.bits, MANT_LEN);
  }

  *value = cur_res;
}

void check_exp_len(s21_decimal *value) {
  s21_decimal cur_res = *value;
  int exp = get_exp(cur_res);

  for (; exp < 0; exp++) {
    mul_mant_by_int(cur_res.bits, 10, cur_res.bits, MANT_LEN);
  }

  for (; exp > MAX_EXP; exp--) {
    int temp[MANT_LEN];

    if (exp == MAX_EXP + 1) {
      add_int_to_mant(cur_res.bits, 5, cur_res.bits, MANT_LEN);
    }
    div_mant_by_int(cur_res.bits, 10, cur_res.bits, temp, MANT_LEN);
  }

  set_exp(&cur_res, exp);

  *value = cur_res;
}

void compare_and_align_exps(s21_decimal *value_1, s21_decimal *value_2) {
  int diff = get_exp(*value_1) - get_exp(*value_2);

  if (diff > 0) {
    align_exps(value_2, value_1);
  } else if (diff < 0) {
    align_exps(value_1, value_2);
  }
}

void align_exps(s21_decimal *lower, s21_decimal *higher) {
  int lower_mant[MANT_LEN];
  int higher_mant[MANT_LEN];
  int temp[MANT_LEN];
  int exp_0 = get_exp(*lower);
  int exp_1 = get_exp(*higher);
  int overflow = 0;

  copy_mant(lower->bits, lower_mant, MANT_LEN);
  copy_mant(higher->bits, higher_mant, MANT_LEN);

  while (exp_0 < exp_1 && !overflow) {
    copy_mant(lower_mant, temp, MANT_LEN);
    overflow = mul_mant_by_int(temp, 10, temp, MANT_LEN);
    if (!overflow) {
      copy_mant(temp, lower_mant, MANT_LEN);
      exp_0++;
    }
  }

  while (exp_0 < exp_1) {
    if (exp_0 == exp_1 - 1) {
      add_int_to_mant(higher_mant, 5, higher_mant, MANT_LEN);
    }
    div_mant_by_int(higher_mant, 10, higher_mant, temp, MANT_LEN);
    exp_1--;
  }

  set_exp(lower, exp_0);
  set_exp(higher, exp_1);
  copy_mant(lower_mant, lower->bits, MANT_LEN);
  copy_mant(higher_mant, higher->bits, MANT_LEN);
}

void fract_dec_to_bin(s21_decimal *value) {
  s21_decimal cur_res = *value;
  s21_decimal temp = {{0, 0, 0, 0}};
  s21_decimal fract = {{0, 0, 0, 0}};
  int divisor[MANT_LEN] = {1, 0, 0};
  int dec_exp = get_exp(cur_res);
  int bin_exp = 0;
  int comparison_res;
  int overflow = 0;

  s21_truncate(cur_res, &temp);
  s21_sub(cur_res, temp, &fract);
  cur_res = temp;

  for (; dec_exp > 0; dec_exp--) {
    mul_mant_by_int(divisor, 10, divisor, MANT_LEN);
  }

  while (mant_is_not_zero(fract.bits, MANT_LEN) && !overflow) {
    do {
      mul_mant_by_two(fract.bits, fract.bits, MANT_LEN);
      temp = cur_res;
      overflow = mul_mant_by_two(temp.bits, temp.bits, MANT_LEN);
      if (!overflow) {
        comparison_res = compare_mants(fract.bits, divisor, MANT_LEN);
      }
      if (!overflow && comparison_res >= 0) {
        overflow = add_int_to_mant(temp.bits, 1, temp.bits, MANT_LEN);
      }
      if (!overflow) {
        cur_res = temp;
        bin_exp++;
      }
    } while (comparison_res < 0 && !overflow);

    if (mant_is_not_zero(fract.bits, MANT_LEN) && !overflow) {
      sub_mants(fract.bits, divisor, fract.bits, MANT_LEN);
    }
  }

  set_exp(&cur_res, bin_exp);
  *value = cur_res;
}

void shift_float_bits(s21_decimal *value) {
  s21_decimal cur_res = *value;
  const int twenty_four_bits[MANT_LEN] = {FLOAT_MANT_MAX, 0, 0};
  const int float_implicit_bit[MANT_LEN] = {FLOAT_MANT_IMPLICIT_BIT, 0, 0};
  int bin_exp = get_exp(cur_res);

  while (compare_mants(cur_res.bits, float_implicit_bit, MANT_LEN) < 0) {
    mul_mant_by_two(cur_res.bits, cur_res.bits, MANT_LEN);
    bin_exp++;
  }

  while (compare_mants(cur_res.bits, twenty_four_bits, MANT_LEN) > 0) {
    if (!cur_res.bits[2] && !cur_res.bits[1] &&
        cur_res.bits[0] < (FLOAT_MANT_IMPLICIT_BIT << 2)) {
      add_int_to_mant(cur_res.bits, 1, cur_res.bits, MANT_LEN);
    }
    div_mant_by_two(cur_res.bits, cur_res.bits, MANT_LEN);
    bin_exp--;
  }

  set_exp(&cur_res, bin_exp);
  *value = cur_res;
}