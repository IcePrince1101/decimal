#ifndef S21_DECIMAL_COLORS
#define S21_DECIMAL_COLORS

#ifdef NICE
#define RESET "\033[0m"
#define RED "\033[0;91m"
#define GREEN "\033[0;92m"
#define YELLOW "\033[0;93m"
#define BLUE "\033[0;94m"
#define PURPLE "\033[0;95m"
#define CYAN "\033[0;96m"
#define DARK_GREEN "\033[2;92m"
#define DARK_YELLOW "\033[2;93m"
#define DARK_BLUE "\033[2;94m"
#define DARK_PURPLE "\033[2;95m"
#define DARK_GREY "\033[2;37m"
#define RESET_CODE 0
#define RED_CODE 91
#define GREEN_CODE 92
#define YELLOW_CODE 93
#define BLUE_CODE 94
#define PURPLE_CODE 95
#define CYAN_CODE 96
#define GREY_CODE 97
#else
#define RESET "\033[0m"
#define RED "\033[0m"
#define GREEN "\033[0m"
#define YELLOW "\033[0m"
#define BLUE "\033[0m"
#define PURPLE "\033[0m"
#define CYAN "\033[0m"
#define DARK_GREEN "\033[0m"
#define DARK_YELLOW "\033[0m"
#define DARK_BLUE "\033[0m"
#define DARK_PURPLE "\033[0m"
#define DARK_GREY "\033[0m"
#define RESET_CODE 0
#define RED_CODE 97
#define GREEN_CODE 97
#define YELLOW_CODE 97
#define BLUE_CODE 97
#define PURPLE_CODE 97
#define CYAN_CODE 97
#define GREY_CODE 97
#endif

#endif