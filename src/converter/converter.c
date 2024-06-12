#include "converter.h"

int convert_str_to_decimal(const char *str, s21_decimal *dec) {
  s21_decimal cur_res = {{0, 0, 0, 0}};
  int err_code;
  int stop = 0;
  int sign;
  int exponent;
  int pow_of_two = 0;
  int int_num = 0;
  char buff_0[BUFF_SIZE];
  char buff_1[BUFF_SIZE];

  err_code = strlen(str) >= BUFF_SIZE;

  if (!err_code) {
    strcpy(buff_0, str);
    err_code = preprocess_str(buff_0, buff_1, &sign, &exponent);
  }

  if (!err_code) {
    strcpy(buff_0, buff_1);
    err_code = set_sign_and_exp(&cur_res, sign, exponent);
  }

  while (!err_code && !stop && (strlen(buff_0) > 1 || buff_0[0] != '0')) {
    int bit;
    err_code = div_str_by_two(buff_0, buff_1, &bit);
    if (!err_code) {
      cur_res.bits[int_num] += bit * get_pow_of_two(pow_of_two);
      pow_of_two++;
      if (pow_of_two == 32) {
        pow_of_two = 0;
        int_num++;
      }
      stop = int_num == 3;
      strcpy(buff_0, buff_1);
    }
  }

  if (!err_code && stop && (strlen(buff_0) > 1 || buff_0[0] != '0')) {
    err_code = sign ? 2 : 3;
  }

  if (!err_code) {
    *dec = cur_res;
  }

  return err_code;
}

int convert_decimal_to_str(s21_decimal dec, char *str) {
  int err_code;
  int sign;
  int exponent;
  int int_num = 2;
  int exp_of_two = 31;
  char buff_0[BUFF_SIZE] = "0";
  char buff_1[BUFF_SIZE];

  err_code = get_sign_and_exp(dec, &sign, &exponent);

  while (!err_code && int_num >= 0) {
    err_code = mul_str_by_two(buff_0, buff_1);
    if (!err_code) {
      strcpy(buff_0, buff_1);
      unsigned bit = dec.bits[int_num];
      unsigned pow_of_two = get_pow_of_two(exp_of_two);
      bit &= pow_of_two;
      bit = bit > 0 ? 1 : 0;
      err_code = add_bit_to_str(buff_0, buff_1, bit);
    }
    if (!err_code) {
      strcpy(buff_0, buff_1);
      exp_of_two--;
      if (exp_of_two < 0) {
        exp_of_two = 31;
        int_num--;
      }
    }
  }

  if (!err_code) {
    postprocess_str(buff_0, str, sign, exponent);
  }

  return err_code;
}

int preprocess_str(const char *src, char *res, int *sign, int *exp) {
  int err_code = 0;
  char buff[BUFF_SIZE];
  int index = 0;
  int point_found = 0;
  int exponent = 0;
  int negative = *src == '-';

  if (*src == '-' || *src == '+') {
    src++;
  };

  while (!err_code && *src) {
    if (*src >= LOWEST_DIGIT_CODE && *src <= HIGHEST_DIGIT_CODE) {
      if (point_found) {
        exponent++;
      }
      buff[index] = *src;
      index++;
      src++;
    } else if (*src == '.') {
      if (point_found) {
        err_code = 1;
      } else {
        point_found = 1;
        src++;
      }
    } else {
      err_code = 1;
    }
  }

  if (!err_code) {
    buff[index] = '\0';
    strcpy(res, buff);
    *sign = negative;
    *exp = exponent;
  }

  return err_code;
}

void postprocess_str(const char *src, char *res, int sign, int exp) {
  int len = strlen(src);
  int dot_index;

  if (sign) {
    *res = '-';
    res++;
  }

  if (!exp) {
    dot_index = -1;
  } else if (exp < len) {
    dot_index = len - 1 - exp;
  } else {
    dot_index = -1;
    *res = '0';
    res++;
    *res = '.';
    res++;

    while (exp > len) {
      *res = '0';
      res++;
      exp--;
    }
  }

  for (int i = 0; i < len; i++) {
    *res = src[i];
    res++;
    if (i == dot_index) {
      *res = '.';
      res++;
    }
  }

  *res = '\0';
}

int set_sign_and_exp(s21_decimal *dec, int sign, int exp) {
  int err_code = (sign != 0 && sign != 1) || exp < 0 || exp > HIGHEST_EXP;

  if (!err_code) {
    sp_int_bits sp_int;
    sp_int.bits.unused_bits_0 = 0;
    sp_int.bits.exponent_bits = exp;
    sp_int.bits.unused_bits_1 = 0;
    sp_int.bits.sign_bit = sign;
    dec->bits[3] = sp_int.num;
  }

  return err_code;
}

int get_sign_and_exp(s21_decimal dec, int *sign, int *exp) {
  sp_int_bits sp_int;
  sp_int.num = dec.bits[3];

  int err_code = sp_int.bits.unused_bits_0 || sp_int.bits.unused_bits_1;

  if (!err_code) {
    *sign = sp_int.bits.sign_bit;
    *exp = sp_int.bits.exponent_bits;
  }

  return err_code;
}

int get_pow_of_two(int exp) {
  int res = 1;

  for (int i = 0; i < exp; i++) {
    res *= 2;
  }

  return res;
}

int div_str_by_two(const char *src, char *res, int *rem) {
  int err_code = 0;
  char buff[BUFF_SIZE];
  int index = 0;
  int remainder = 0;
  int flag = 0; /* significant digits detected */

  while (!err_code && *src) {
    int digit = *src - LOWEST_DIGIT_CODE;
    err_code = digit < 0 || digit > 9;
    if (!err_code) {
      int dividend = remainder * 10 + digit;
      int quotient = dividend / 2;
      if (flag || quotient > 0) {
        flag = 1;
        buff[index] = quotient + LOWEST_DIGIT_CODE;
        index++;
      }
      remainder = dividend % 2;
      src++;
    }
  }

  if (!err_code) {
    if (!flag) {
      buff[index] = '0';
      index++;
    }
    buff[index] = '\0';
    strcpy(res, buff);
    *rem = remainder;
  }

  return err_code;
}

int mul_str_by_two(const char *src, char *res) {
  int err_code = 0;
  int len = strlen(src);
  int buff_len = len + 1;
  char buff[buff_len];
  int index = len;
  int carry = 0;

  for (int i = len - 1; !err_code && i >= 0; i--) {
    int digit = src[i] - LOWEST_DIGIT_CODE;
    err_code = digit < 0 || digit > 9;
    if (!err_code) {
      int cur_res = digit * 2 + carry;
      int new_carry = 0;
      if (cur_res >= 10) {
        new_carry = cur_res / 10;
        cur_res %= 10;
      }
      buff[index] = cur_res + LOWEST_DIGIT_CODE;
      index--;
      carry = new_carry;
    }
  }

  if (!err_code) {
    if (carry) {
      buff[index] = carry + LOWEST_DIGIT_CODE;
      index--;
    }

    while (index >= 0) {
      buff[index] = '\0';
      index--;
    }

    for (int i = 0; i < buff_len; i++) {
      if (buff[i]) {
        *res = buff[i];
        res++;
      }
    }

    *res = '\0';
  }

  return err_code;
}

int add_bit_to_str(const char *src, char *res, int bit) {
  int err_code = 0;
  int len = strlen(src);
  int buff_len = len + 1;
  char buff[buff_len];
  int index = len;
  int carry = bit;

  for (int i = len - 1; !err_code && i >= 0; i--) {
    int digit = src[i] - LOWEST_DIGIT_CODE;
    err_code = digit < 0 || digit > 9;
    if (!err_code) {
      int cur_res = digit + carry;
      int new_carry = 0;
      if (cur_res >= 10) {
        new_carry = cur_res / 10;
        cur_res %= 10;
      }
      buff[index] = cur_res + LOWEST_DIGIT_CODE;
      index--;
      carry = new_carry;
    }
  }

  if (!err_code) {
    if (carry) {
      buff[index] = carry + LOWEST_DIGIT_CODE;
      index--;
    }

    while (index >= 0) {
      buff[index] = '\0';
      index--;
    }

    for (int i = 0; i < buff_len; i++) {
      if (buff[i]) {
        *res = buff[i];
        res++;
      }
    }

    *res = '\0';
  }

  return err_code;
}

void print_decimal(s21_decimal dec) {
  int len;

  printf("\n");
  printf(DARK_PURPLE "Significant digits:   ");
  len = print_significant_digits(dec, PURPLE_CODE, 0);
  printf(DARK_BLUE "bits[2]:              ");
  print_integer(dec.bits[2], 2, len, BLUE_CODE);
  printf(DARK_GREEN "bits[1]:              ");
  print_integer(dec.bits[1], 1, len, GREEN_CODE);
  printf(DARK_YELLOW "bits[0]:              ");
  print_integer(dec.bits[0], 0, len, YELLOW_CODE);
  printf("\n\n");
  printf(DARK_PURPLE "____________________________bits[3]");
  printf("   ");
  printf(DARK_BLUE "____________________________bits[2]");
  printf("   ");
  printf(DARK_GREEN "____________________________bits[1]");
  printf("   ");
  printf(DARK_YELLOW "____________________________bits[0]");
  printf(RESET "\n");
  printf(DARK_GREY "%35u   %35u   %35u   %35u\n", (unsigned)dec.bits[3],
         (unsigned)dec.bits[2], (unsigned)dec.bits[1], (unsigned)dec.bits[0]);
  print_integer_bits(dec.bits[3], PURPLE_CODE, 1);
  printf("   ");
  print_integer_bits(dec.bits[2], BLUE_CODE, 0);
  printf("   ");
  print_integer_bits(dec.bits[1], GREEN_CODE, 0);
  printf("   ");
  print_integer_bits(dec.bits[0], YELLOW_CODE, 0);
  printf("\n\n");
}

int print_significant_digits(s21_decimal dec, int color_code, int len) {
  int int_num = 2;
  int exp_of_two = 31;
  char buff_0[BUFF_SIZE] = "0";
  char buff_1[BUFF_SIZE];

  while (int_num >= 0) {
    mul_str_by_two(buff_0, buff_1);
    strcpy(buff_0, buff_1);
    unsigned bit = dec.bits[int_num];
    unsigned pow_of_two = get_pow_of_two(exp_of_two);
    bit &= pow_of_two;
    bit = bit > 0;
    add_bit_to_str(buff_0, buff_1, bit);
    strcpy(buff_0, buff_1);
    exp_of_two--;
    if (exp_of_two < 0) {
      exp_of_two = 31;
      int_num--;
    }
  }

  printf("\033[0;%dm%*s\n" RESET, color_code, len, buff_0);

  return strlen(buff_0);
}

void print_integer(int integer, int index, int len, int color_code) {
  char buff_0[BUFF_SIZE];
  char buff_1[BUFF_SIZE];

  sprintf(buff_0, "%u", (unsigned)integer);

  for (int i = index * 32; i > 0; i--) {
    mul_str_by_two(buff_0, buff_1);
    strcpy(buff_0, buff_1);
  }

  printf("\033[0;%dm%*s\n" RESET, color_code, len, buff_0);
}

void print_integer_bits(int integer, int color_code, int is_special) {
#ifndef NICE
  is_special = 0;
#endif
  int_bits num;
  num.num = integer;
  printf("\033[0;%dm", color_code);
  printf("%u", num.bits.bit_37);
  printf("\033[%d;%dm", is_special ? 2 : 0, color_code);
  printf("%u", num.bits.bit_36);
  printf("%u", num.bits.bit_35);
  printf("%u", num.bits.bit_34);
  printf("%u", num.bits.bit_33);
  printf("%u", num.bits.bit_32);
  printf("%u", num.bits.bit_31);
  printf("%u", num.bits.bit_30);
  printf(" ");
  printf("\033[0;%dm", color_code);
  printf("%u", num.bits.bit_27);
  printf("%u", num.bits.bit_26);
  printf("%u", num.bits.bit_25);
  printf("%u", num.bits.bit_24);
  printf("%u", num.bits.bit_23);
  printf("%u", num.bits.bit_22);
  printf("%u", num.bits.bit_21);
  printf("%u", num.bits.bit_20);
  printf(" ");
  printf("\033[%d;%dm", is_special ? 2 : 0, color_code);
  printf("%u", num.bits.bit_17);
  printf("%u", num.bits.bit_16);
  printf("%u", num.bits.bit_15);
  printf("%u", num.bits.bit_14);
  printf("%u", num.bits.bit_13);
  printf("%u", num.bits.bit_12);
  printf("%u", num.bits.bit_11);
  printf("%u", num.bits.bit_10);
  printf(" ");
  printf("%u", num.bits.bit_07);
  printf("%u", num.bits.bit_06);
  printf("%u", num.bits.bit_05);
  printf("%u", num.bits.bit_04);
  printf("%u", num.bits.bit_03);
  printf("%u", num.bits.bit_02);
  printf("%u", num.bits.bit_01);
  printf("%u", num.bits.bit_00);
  printf(RESET);
}