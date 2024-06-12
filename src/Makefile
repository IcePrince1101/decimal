CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = 
CHECK_FLAGS = -lcheck -lpthread
SRCMODULES = s21_decimal.c s21_decimal_utilities.c s21_decimal_mantissa.c
OBJMODULES = $(SRCMODULES:.c=.o)

ifeq ($(shell uname), Darwin)
# MacOS
    FLAGS += -I /usr/local/include
    OPEN_HTML = open
else
# Linux
    CHECK_FLAGS += -lrt -lsubunit -lm
    OPEN_HTML = xdg-open
endif

ifeq ($(MAKECMDGOALS), $ )
    TEST_FLAGS += -fprofile-arcs -ftest-coverage
else ifeq ($(MAKECMDGOALS), all)
    TEST_FLAGS += -fprofile-arcs -ftest-coverage
else ifeq ($(MAKECMDGOALS), test)
    TEST_FLAGS += -fprofile-arcs -ftest-coverage
else ifeq ($(MAKECMDGOALS), gcov_report)
    TEST_FLAGS += -fprofile-arcs -ftest-coverage
endif

ifeq ($(MAKECMDGOALS), nice_test)
    FLAGS += -D NICE
else ifeq ($(MAKECMDGOALS), nice_man_test)
    FLAGS += -D NICE
else ifeq ($(MAKECMDGOALS), nice_converter_test)
    FLAGS += -D NICE
endif

%.o: %.c %.h s21_decimal_data.h
	$(CC) $(FLAGS) $(TEST_FLAGS) -c $< -o $@

all: clean s21_decimal.a test gcov_report

s21_decimal.a: $(OBJMODULES)
	ar -rcs $@ $(OBJMODULES)

test: clean s21_decimal.a converter.a tests/*.c tests/*.h
	$(CC) $(FLAGS) -c tests/*.c
	$(CC) $(FLAGS) $(TEST_FLAGS) -L. converter.a -L. s21_decimal.a *.o -o $@ $(CHECK_FLAGS)
	./test

gcov_report: clean test
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(OPEN_HTML) report/index.html

# converter
converter.a: clean converter/converter.c converter/converter.h
	$(CC) $(FLAGS) -c converter/converter.c
	ar -rcs $@ converter.o

# converter test
converter_test: clean converter/converter_test.c converter.a 
	$(CC) $(FLAGS) -c converter/converter_test.c
	$(CC) $(FLAGS) converter_test.o -L. converter.a -o $@ 

# manual test
man_test: clean man_tests/man_test.c man_tests/man_test.h converter.a s21_decimal.a
	$(CC) $(FLAGS) -c man_tests/man_test.c
	$(CC) $(FLAGS) man_test.o -L. converter.a -L. s21_decimal.a -o $@

# nice versions of tests
nice_test: clean test
nice_man_test: clean man_test
nice_converter_test: clean converter_test

#other
clean:
	rm -f *.o *.a *.gcno *.gcda *.info converter_test man_test test .clang-format
	rm -rf report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h */*.c */*.h 
	rm -f .clang-format

clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h */*.c */*.h
	rm -f .clang-format

.PHONY: all clean clang clang_check
