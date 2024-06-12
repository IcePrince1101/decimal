#include "man_test.h"

int main(int argc, char **argv) {
  int err_code = 0;
  int token;

  if (argc < 2) {
    err_code = -1;
  } else {
    token = get_token(argv[1]);
    err_code = check_token(token, argc);
  }

  if (!err_code) {
    err_code = use_token(token, argv);
  }

  return err_code;
}

int get_token(const char *str) {
  int token;

  if (!strcmp(str, "s21_add")) {
    token = t_add;
  } else if (!strcmp(str, "s21_sub")) {
    token = t_sub;
  } else if (!strcmp(str, "s21_mul")) {
    token = t_mul;
  } else if (!strcmp(str, "s21_div")) {
    token = t_div;
  } else if (!strcmp(str, "s21_is_less")) {
    token = t_is_less;
  } else if (!strcmp(str, "s21_is_less_or_equal")) {
    token = t_is_less_or_equal;
  } else if (!strcmp(str, "s21_is_greater")) {
    token = t_is_greater;
  } else if (!strcmp(str, "s21_is_greater_or_equal")) {
    token = t_is_greater_or_equal;
  } else if (!strcmp(str, "s21_is_equal")) {
    token = t_is_equal;
  } else if (!strcmp(str, "s21_is_not_equal")) {
    token = t_is_not_equal;
  } else if (!strcmp(str, "s21_from_int_to_decimal")) {
    token = t_from_int_to_decimal;
  } else if (!strcmp(str, "s21_from_float_to_decimal")) {
    token = t_from_float_to_decimal;
  } else if (!strcmp(str, "s21_from_decimal_to_int")) {
    token = t_from_decimal_to_int;
  } else if (!strcmp(str, "s21_from_decimal_to_float")) {
    token = t_from_decimal_to_float;
  } else if (!strcmp(str, "s21_floor")) {
    token = t_floor;
  } else if (!strcmp(str, "s21_round")) {
    token = t_round;
  } else if (!strcmp(str, "s21_truncate")) {
    token = t_truncate;
  } else if (!strcmp(str, "s21_negate")) {
    token = t_negate;
  } else {
    token = -1;
  }

  return token;
}

int check_token(int token, int argc) {
  int err_code;

  switch (token) {
    case t_add:
    case t_sub:
    case t_mul:
    case t_div:
    case t_is_less:
    case t_is_less_or_equal:
    case t_is_greater:
    case t_is_greater_or_equal:
    case t_is_equal:
    case t_is_not_equal:
      err_code = argc != 4 ? -1 : 0;
      break;
    case t_from_int_to_decimal:
    case t_from_float_to_decimal:
    case t_from_decimal_to_int:
    case t_from_decimal_to_float:
    case t_floor:
    case t_round:
    case t_truncate:
    case t_negate:
      err_code = argc != 3 ? -1 : 0;
      break;
    default:
      err_code = token;
  }

  return err_code;
}

int use_token(int token, char **argv) {
  int err_code;

  switch (token) {
    case t_add:
      err_code = man_test_add(argv[2], argv[3]);
      break;
    case t_sub:
      err_code = man_test_sub(argv[2], argv[3]);
      break;
    case t_mul:
      err_code = man_test_mul(argv[2], argv[3]);
      break;
    case t_div:
      err_code = man_test_div(argv[2], argv[3]);
      break;
    case t_is_less:
      err_code = man_test_is_less(argv[2], argv[3]);
      break;
    case t_is_less_or_equal:
      err_code = man_test_is_less_or_equal(argv[2], argv[3]);
      break;
    case t_is_greater:
      err_code = man_test_is_greater(argv[2], argv[3]);
      break;
    case t_is_greater_or_equal:
      err_code = man_test_is_greater_or_equal(argv[2], argv[3]);
      break;
    case t_is_equal:
      err_code = man_test_is_equal(argv[2], argv[3]);
      break;
    case t_is_not_equal:
      err_code = man_test_is_not_equal(argv[2], argv[3]);
      break;
    case t_from_int_to_decimal:
      err_code = man_test_from_int_to_decimal(argv[2]);
      break;
    case t_from_float_to_decimal:
      err_code = man_test_from_float_to_decimal(argv[2]);
      break;
    case t_from_decimal_to_int:
      err_code = man_test_from_decimal_to_int(argv[2]);
      break;
    case t_from_decimal_to_float:
      err_code = man_test_from_decimal_to_float(argv[2]);
      break;
    case t_floor:
      err_code = man_test_floor(argv[2]);
      break;
    case t_round:
      err_code = man_test_round(argv[2]);
      break;
    case t_truncate:
      err_code = man_test_truncate(argv[2]);
      break;
    case t_negate:
      err_code = man_test_negate(argv[2]);
      break;
  }

  return err_code;
}

int man_test_from_int_to_decimal(const char *value) {
  int err_code = 0;
  int x;
  s21_decimal res = {{0, 0, 0, 0}};

  x = atoi(value);

  printf(DARK_GREY "\nINTEGER: %d\n" RESET, x);
  err_code = s21_from_int_to_decimal(x, &res);

  if (!err_code) {
    char res_str[BUFF_SIZE] = "0";
    convert_decimal_to_str(res, res_str);
    printf(DARK_GREY "\nDECIMAL: %s\n" RESET, res_str);
    print_decimal(res);
  }

  return err_code;
}

int man_test_from_float_to_decimal(const char *value) {
  int err_code = 0;
  float x;
  s21_decimal res = {{0, 0, 0, 0}};

  x = (float)atof(value);

  printf(DARK_GREY "\nFLOAT:   %.28f\n" RESET, x);
  err_code = s21_from_float_to_decimal(x, &res);

  if (!err_code) {
    char res_str[BUFF_SIZE] = "0";
    convert_decimal_to_str(res, res_str);
    printf(DARK_GREY "\nDECIMAL: %s\n" RESET, res_str);
    print_decimal(res);
  }

  return err_code;
}

int man_test_from_decimal_to_int(const char *value) {
  int err_code = 0;
  int res;
  s21_decimal dec = {{0, 0, 0, 0}};

  err_code = convert_str_to_decimal(value, &dec);

  if (!err_code) {
    char dec_str[BUFF_SIZE] = "0";
    convert_decimal_to_str(dec, dec_str);
    printf(DARK_GREY "\nDECIMAL: %s\n" RESET, dec_str);
    print_decimal(dec);
    err_code = s21_from_decimal_to_int(dec, &res);
  }

  if (!err_code) {
    printf(DARK_GREY "\nINTEGER: %d\n\n" RESET, res);
  }

  return err_code;
}

int man_test_from_decimal_to_float(const char *value) {
  int err_code = 0;
  float res;
  s21_decimal dec = {{0, 0, 0, 0}};

  err_code = convert_str_to_decimal(value, &dec);

  if (!err_code) {
    char dec_str[BUFF_SIZE] = "0";
    convert_decimal_to_str(dec, dec_str);
    printf(DARK_GREY "\nDECIMAL: %s\n" RESET, dec_str);
    print_decimal(dec);
    err_code = s21_from_decimal_to_float(dec, &res);
  }

  if (!err_code) {
    printf(DARK_GREY "\nFLOAT: %.28f\n\n" RESET, res);
  }

  return err_code;
}

ARITMETIC_FUNC_TEST(add)

ARITMETIC_FUNC_TEST(sub)

ARITMETIC_FUNC_TEST(mul)

ARITMETIC_FUNC_TEST(div)

COMPARISON_FUNC_TEST(is_less)

COMPARISON_FUNC_TEST(is_less_or_equal)

COMPARISON_FUNC_TEST(is_greater)

COMPARISON_FUNC_TEST(is_greater_or_equal)

COMPARISON_FUNC_TEST(is_equal)

COMPARISON_FUNC_TEST(is_not_equal)

ANOTHER_FUNC_TEST(floor)

ANOTHER_FUNC_TEST(round)

ANOTHER_FUNC_TEST(truncate)

ANOTHER_FUNC_TEST(negate)