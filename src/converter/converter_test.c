#include "converter.h"

int str2dec(const char *str);
int dec2str(const char *sign, const char *exp, const char *b_2, const char *b_1,
            const char *b_0);

int main(int argc, char **argv) {
  int err_code = 0;

  if (argc == 3 && !strcmp(argv[1], "str2dec")) {
    err_code = str2dec(argv[2]);
  } else if (argc == 7 && !strcmp(argv[1], "dec2str")) {
    err_code = dec2str(argv[2], argv[3], argv[4], argv[5], argv[6]);
  } else {
    printf(RED
           "USAGE:\n./converter_test <str2dec|dec2str> <str|sign exp bit_2 "
           "bit_1 bit_0>\n" RESET);
    err_code = -1;
  }

  return err_code;
}

int str2dec(const char *str) {
  s21_decimal dec = {{0, 0, 0, 0}};
  int err_code = convert_str_to_decimal(str, &dec);

  if (!err_code) {
    printf(DARK_GREY "\nINPUT: %s\n\n" RESET, str);
    print_decimal(dec);
  } else {
    printf(RED);
    switch (err_code) {
      case 1:
        printf("INVALID DECIMAL STRING!\n");
        break;
      case 2:
        printf("UNDERFLOW!\n");
        break;
      case 3:
        printf("OVERFLOW!\n");
    }
    printf(RESET);
  }

  return err_code;
}

int dec2str(const char *sign, const char *exp, const char *b_2, const char *b_1,
            const char *b_0) {
  s21_decimal dec = {{0, 0, 0, 0}};
  char str[BUFF_SIZE] = "0";
  int err_code = set_sign_and_exp(&dec, atoi(sign), atoi(exp));

  if (!err_code) {
    dec.bits[2] = atoi(b_2);
    dec.bits[1] = atoi(b_1);
    dec.bits[0] = atoi(b_0);
    err_code = convert_decimal_to_str(dec, str);
  }

  if (!err_code) {
    printf(CYAN "%s\n" RESET, str);
  } else {
    err_code = 4;
    printf(RED "INVALID DECIMAL-TO-STRING CONVERSION\n" RESET);
  }

  return err_code;
}
