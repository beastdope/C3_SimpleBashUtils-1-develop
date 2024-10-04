#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "cat.h"

void number_non_blank_lines(FILE *file);
void default_cat_action(FILE *file);
void dollar_end_line(FILE *file);
void number_all_lines(FILE *file);
void squeeze_double_blank_lines(FILE *file);
void list_tabs(FILE *file);
int flags_checker(int argc, char *argv[], opt *option);

int main(int argc, char *argv[]) {
  opt options = {0};
  flags_checker(argc, argv, &options);

  if (options.b) {
    if (optind < argc) {
      const char *file_name = argv[optind];
      FILE *file = fopen(file_name, "r+");
      number_non_blank_lines(file);
      fclose(file);
    } else {
      printf("Имя файла для проверки не указано\n");
    }
  } else if (options.e) {
    if (optind < argc) {
      const char *file_name = argv[optind];
      FILE *file = fopen(file_name, "r+");
      if (file) {
        dollar_end_line(file);
        fclose(file);
      } else {
        fprintf(stderr, "Файла не существует, попробуйте снова.\n");
        return 1;
      }
    } else {
      printf("error mafa\n");
      return 0;
    }
  } else if (options.n) {
    if (optind < argc) {
      const char *file_name = argv[optind];
      FILE *file = fopen(file_name, "r+");
      number_all_lines(file);
      fclose(file);
    } else {
      printf("no file bro\n");
    }
  } else if (options.s) {
    if (optind < argc) {
      const char *file_name = argv[optind];
      FILE *file = fopen(file_name, "r+");
      squeeze_double_blank_lines(file);
      fclose(file);
    } else {
      printf("no file bro\n");
    }
  } else if (options.t) {
    if (optind < argc) {
      const char *file_name = argv[optind];
      FILE *file = fopen(file_name, "r+");
      list_tabs(file);
      fclose(file);
    } else {
      printf("no file bro\n");
    }
  } else {
    char *file_name = argv[optind];
    FILE *file = fopen(file_name, "r+");
    default_cat_action(file);
    fclose(file);
    return 1;
  }
  return 0;
}

void number_non_blank_lines(FILE *file) {
  int savechar = fgetc(file);
  int counter = 1;
  char choice_saver = savechar;

  if (savechar != EOF && savechar != '\n') {
    printf("%6d\t", counter);
    counter += 1;
  }
  while (savechar != EOF) {
    if (savechar != '\n' && choice_saver == '\n') {
      printf("%6d\t", counter);
      counter += 1;
    }
    printf("%c", savechar);
    choice_saver = savechar;
    savechar = fgetc(file);
  }
}

void default_cat_action(FILE *file) {
  char line_char = fgetc(file);
  while (!feof(file)) {
    printf("%c", line_char);
    line_char = fgetc(file);
  }
}

void dollar_end_line(FILE *file) {
  char line_char = fgetc(file);
  while (!feof(file)) {
    if (line_char == '\n') {
      printf("$");
    }
    printf("%c", line_char);
    line_char = fgetc(file);
  }
}

void number_all_lines(FILE *file) {
  char char_saver;
  int line_number = 1;
  int isStartOfLine = 1;

  while ((char_saver = fgetc(file)) != EOF) {
    if (isStartOfLine) {  // Если это начало строки
      printf("%6d\t", line_number++);
      isStartOfLine = 0;
    }
    putchar(char_saver);
    if (char_saver == '\n') isStartOfLine = 1;
  }
}

void squeeze_double_blank_lines(FILE *file) {
  int current_char, prev_char = '\n';
  int empty_line_count = 0;

  while ((current_char = fgetc(file)) != EOF) {
    if (current_char == '\n') {
      if (prev_char == '\n') {
        if (empty_line_count == 0) {
          putchar('\n');  // Вывести только одну пустую строку
          empty_line_count++;
        }
      } else {
        empty_line_count = 0;
        putchar(current_char);
      }
    } else {
      putchar(current_char);  // Вывести текстовый символ
    }
    prev_char = current_char;
  }
}

void list_tabs(FILE *file) {
  int current_char;
  while ((current_char = fgetc(file)) != EOF) {
    if (current_char == '\t') {
      putchar('^');
      putchar('I');
    } else if ((current_char >= 0 && current_char <= 31 &&
                current_char != '\n') ||
               current_char == 127) {
      putchar('^');
      putchar(current_char + 64);
    } else if ((current_char >= 128 && current_char <= 256) ||
               (current_char >= -128 && current_char <= -1)) {
      printf("M-");
      putchar(current_char + 128);
    } else {
      putchar(current_char);
    }
  }
}

int flags_checker(int argc, char *argv[], opt *options) {
  int option_result_saver;
  int error = 0;
  const struct option long_option[] = {{"number", 0, 0, 'n'},
                                       {"number-nonblank", 0, 0, 'b'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};
  while ((option_result_saver =
              getopt_long(argc, argv, "benvstET", long_option, 0)) != -1) {
    switch (option_result_saver) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        break;
      case 'T':
        options->t = 1;
        break;
      case 'E':
        options->e = 1;
        break;
      case '?':
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }
  if (error) {
    return 1;
  }
  return 0;
}