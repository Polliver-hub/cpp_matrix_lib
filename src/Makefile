.PHONY: all clean test $(SOURCENAME).a gcov_report style

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest
RFLAGS = -fprofile-arcs -ftest-coverage
SOURCENAME = s21_matrix_oop

all: $(SOURCENAME).a test

$(SOURCENAME).a: $(SOURCENAME).h
	@$(CC) $(CFLAGS) -c $(SOURCENAME).cc
	@ar rc $(SOURCENAME).a $(SOURCENAME).o
	@ranlib $(SOURCENAME).a
	@rm $(SOURCENAME).o


test: $(SOURCENAME).cc test.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(RFLAGS) $(SOURCENAME).cc test.cc -o test $(TFLAGS)
	@./test

gcov_report: test
	@rm -rf test.gc*
	@lcov -t test -o rep.info -c -d . --no-external
	@genhtml -o report rep.info
	@open ./report/index.html


clean:
	@-rm -rf *.o *.a *gcda *gcno *info report test

style:
	@clang-format -style=google -n s21_matrix_oop.cc s21_matrix_oop.h test.cc
	@clang-format -style=google -i s21_matrix_oop.cc s21_matrix_oop.h test.cc
