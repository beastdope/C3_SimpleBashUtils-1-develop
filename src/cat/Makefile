CC = gcc
CFLAGS = -Wall -Werror -Wextra 

all: s21_cat

s21_cat: s21_cat.c 
	${CC} ${CFLAGS} -o s21_cat s21_cat.c

clean:
	rm -f s21_cat

rebuild: clean all

build: all