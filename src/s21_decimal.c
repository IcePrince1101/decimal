#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal cur_res = {{0, 0, 0, 0}};
  int err_code = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);
  int exp;

  check_exp_len(&value_1);
  check_exp_len(&value_2);

  trunc_empty_exp(&value_1);
  trunc_empty_exp(&value_2);

  compare_and_align_exps(&value_1, &value_2);
  exp = get_exp(value_1);

  if (sign_1 == 0 && sign_2 == 1) {
    set_sign(&value_2, 0);
    s21_sub(value_1, value_2, &cur_res);
  } else if (sign_1 == 1 && sign_2 == 0) {
    set_sign(&value_1, 0);
    s21_sub(value_2, value_1, &cur_res);
  } else {
    err_code = add_mants(value_1.bits, value_2.bits, cur_res.bits, MANT_LEN);
    if (err_code && exp) {
      round_and_add_mants(value_1.bits, value_2.bits, cur_res.bits, MANT_LEN);
      exp--;
      err_code = 0;
    }
    if (!err_code) {
      set_sign(&cur_res, sign_1);
      set_exp(&cur_res, exp);
      check_exp_len(&cur_res);
      trunc_empty_exp(&cur_res);
    } else if (sign_1 == 0) {
      err_code = 1;
    } else {
      err_code = 2;
    }
  }

  if (!err_code) {
    *result = cur_res;
  }

  return err_code;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal cur_res = {{0, 0, 0, 0}};
  int err_code = 0;
  int sign_1 = get_sign(value_1);
  int sign_2 = get_sign(value_2);

  check_exp_len(&value_1);
  check_exp_len(&value_2);

  trunc_empty_exp(&value_1);
  trunc_empty_exp(&value_2);

  compare_and_align_exps(&value_1, &value_2);

  if (sign_1 == 0 && sign_2 == 1) {
    set_sign(&value_2, 0);
    err_code = s21_add(value_1, value_2, &cur_res);
  } else if (sign_1 == 1 && sign_2 == 0) {
    set_sign(&value_2, 1);
    err_code = s21_add(value_1, value_2, &cur_res);
  } else if (sign_1 == 1 && sign_2 == 1) {
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    s21_sub(value_2, value_1, &cur_res);
  } else {
    int comparison_res = compare_mants(value_1.bits, value_2.bits, MANT_LEN);
    if (comparison_res >= 0) {
      sub_mants(value_1.bits, value_2.bits, cur_res.bits, MANT_LEN);
      set_sign(&cur_res, sign_1);
    } else {
      sub_mants(value_2.bits, value_1.bits, cur_res.bits, MANT_LEN);
      set_sign(&cur_res, !sign_1);
    }
    set_exp(&cur_res, get_exp(value_1));
    check_exp_len(&cur_res);
    trunc_empty_exp(&cur_res);
  }

  if (!err_code) {
    *result = cur_res;
  }

  return err_code;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal cur_res = {{0, 0, 0, 0}};
  int err_code = 0;
  int sign;
  int exp;
  int extd_mant[DBL_MANT_LEN];

  check_exp_len(&value_1);
  check_exp_len(&value_2);

  trunc_empty_exp(&value_1);
  trunc_empty_exp(&value_2);

  sign = get_sign(value_1) == get_sign(value_2) ? 0 : 1;
  exp = get_exp(value_1) + get_exp(value_2);

  mul_mants(value_1.bits, value_2.bits, extd_mant, MANT_LEN);

  err_code = shift_mant_to_the_rignt(extd_mant, extd_mant, DBL_MANT_LEN, &exp);

  if (!err_code) {
    copy_mant(extd_mant, cur_res.bits, MANT_LEN);
    set_sign(&cur_res, sign);
    set_exp(&cur_res, exp);
    check_exp_len(&cur_res);
    trunc_empty_exp(&cur_res);
    *result = cur_res;
  } else if (sign == 0) {
    err_code = 1;
  } else {
    err_code = 2;
  }

  return err_code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err_code = !mant_is_not_zero(value_2.bits, MANT_LEN) ? 3 : 0;

  if (!err_code) {
    s21_decimal int_res = {{0, 0, 0, 0}};
    s21_decimal fract_res = {{0, 0, 0, 0}};
    s21_decimal cur_res = {{0, 0, 0, 0}};
    int sign = get_sign(value_1) == get_sign(value_2) ? 0 : 1;
    int dividend_exp;
    int divisor_exp;
    int fract_exp;

    check_exp_len(&value_1);
    check_exp_len(&value_2);

    trunc_empty_exp(&value_1);
    trunc_empty_exp(&value_2);

    dividend_exp = get_exp(value_1);
    divisor_exp = get_exp(value_2);

    if (compare_mants(value_1.bits, value_2.bits, MANT_LEN) >= 0) {
      i_div_mants(value_1.bits, value_2.bits, int_res.bits, value_1.bits,
                  MANT_LEN);
      set_exp(&int_res, dividend_exp - divisor_exp);
      check_exp_len(&int_res);
    }

    if (mant_is_not_zero(value_1.bits, MANT_LEN)) {
      f_div_mants(value_1.bits, value_2.bits, fract_res.bits, &fract_exp,
                  MANT_LEN);
      set_exp(&fract_res, fract_exp + dividend_exp - divisor_exp);
      check_exp_len(&fract_res);
    }

    s21_add(int_res, fract_res, &cur_res);

    set_sign(&cur_res, sign);
    *result = cur_res;
  }

  return err_code;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) < 0;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) <= 0;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) > 0;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) >= 0;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) == 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return compare(value_1, value_2) != 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_decimal res = {{0, 0, 0, 0}};
  int sign = src < 0;

  if (sign) {
    src *= -1;
  }

  res.bits[0] = src;
  set_sign(&res, sign);

  *dst = res;

  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_decimal res = {{0, 0, 0, 0}};
  int err_code = 0;
  int sign, bin_exp, dec_exp;
  f_conv conv;

  conv.num = src;
  sign = conv.bits.sign_bit;
  conv.bits.sign_bit = 0;

  if (conv.num < FLOAT_MIN && conv.num > 0) {
    *dst = res;
    err_code = 1;
  }

  if (!err_code) {
    res.bits[0] = conv.bits.mant_bits + FLOAT_MANT_IMPLICIT_BIT;
    bin_exp = conv.bits.exp_bits - FLOAT_EXP_SHIFT - FLOAT_MANT_LEN;
    err_code = process_bin_exp(res.bits, res.bits, bin_exp, &dec_exp, MANT_LEN);
  }

  if (!err_code) {
    save_seven_digits(res.bits, res.bits, &dec_exp, MANT_LEN);
    set_exp(&res, dec_exp);
    set_sign(&res, sign);
    trunc_empty_exp(&res);
    *dst = res;
  }

  return err_code ? 1 : 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  s21_truncate(src, &src);

  int err_code = 0;
  int sign = get_sign(src);

  if (src.bits[2] || src.bits[1]) {
    err_code = 1;
  }

  if (!err_code) {
    unsigned value = (unsigned)src.bits[0];

    if ((value > INT_MAX && !sign) || value > (unsigned)INT_MAX + 1) {
      err_code = 1;
    } else if (sign) {
      src.bits[0] *= -1;
    }

    *dst = src.bits[0];
  }

  return err_code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  f_conv conv;
  int sign = get_sign(src);

  if (mant_is_not_zero(src.bits, MANT_LEN)) {
    check_exp_len(&src);
    trunc_empty_exp(&src);

    int bin_exp = 0;
    int dec_exp = get_exp(src);

    if (dec_exp) {
      fract_dec_to_bin(&src);
    }

    shift_float_bits(&src);

    bin_exp = get_exp(src);

    conv.bits.exp_bits = FLOAT_EXP_SHIFT + FLOAT_MANT_LEN - bin_exp;
    conv.bits.mant_bits = src.bits[0] & (FLOAT_MANT_IMPLICIT_BIT - 1);
  } else {
    conv.bits.exp_bits = 0;
    conv.bits.mant_bits = 0;
  }

  conv.bits.sign_bit = sign;
  *dst = conv.num;

  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  trunc_empty_exp(&value);

  int exp = get_exp(value);

  if (exp) {
    int sign = get_sign(value);
    int temp[MANT_LEN];

    for (; exp > 0; exp--) {
      div_mant_by_int(value.bits, 10, value.bits, temp, MANT_LEN);
    }

    if (sign) {
      add_int_to_mant(value.bits, sign, value.bits, MANT_LEN);
      set_sign(&value, sign);
    }

    set_exp(&value, 0);
  }

  *result = value;

  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int exp = get_exp(value);

  if (exp) {
    int sign = get_sign(value);
    int temp[MANT_LEN];

    if (exp == 1) {
      exp -= check_and_round_too_big_mant(value.bits, value.bits, MANT_LEN);
    }

    for (; exp > 0; exp--) {
      if (exp == 1) {
        add_int_to_mant(value.bits, 5, value.bits, MANT_LEN);
      }
      div_mant_by_int(value.bits, 10, value.bits, temp, MANT_LEN);
    }

    if (sign) {
      set_sign(&value, sign);
    }

    set_exp(&value, 0);
  }

  *result = value;

  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int exp = get_exp(value);

  if (exp) {
    int sign = get_sign(value);
    int temp[MANT_LEN];

    for (; exp > 0; exp--) {
      div_mant_by_int(value.bits, 10, value.bits, temp, MANT_LEN);
    }

    if (sign) {
      set_sign(&value, sign);
    }

    set_exp(&value, 0);
  }

  *result = value;

  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  set_sign(&value, !get_sign(value));
  *result = value;

  return 0;
}