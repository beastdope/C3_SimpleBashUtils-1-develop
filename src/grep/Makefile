CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.c
	${CC} ${CFLAGS} -o s21_grep s21_grep.c

clean:
	rm -f s21_grep

rebuild: clean all

build: all
