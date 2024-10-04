#include "s21_grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void e_sample(FILE *file, const char *file_name, const char *regex_pattern,
              int file_count);
void i_case_ignore(FILE *file, const char *file_name, const char *regex_pattern,
                   int file_count);
void v_inverse_search(FILE *file, const char *file_name,
                      const char *regex_pattern, int file_count);
void c_number_of_correlated_lines(FILE *file, const char *file_name,
                                  const char *regex_pattern, int file_count);
void l_file_names_if_find(FILE *file, const char *file_name,
                          const char *regex_pattern);
void n_name_numberline_line(FILE *file, const char *file_name,
                            const char *regex_pattern, int file_count);
void h_result_without_names(FILE *file, const char *regex_pattern);
void s_silent_mode(FILE *file, const char *file_name, const char *regex_pattern,
                   int file_count);
void f_file_to_file_search(FILE *file, const char *pattern_file,
                           const char *file_name, int file_count);
void o_only_coincidence(FILE *file, const char *file_name,
                        const char *regex_pattern, int file_count);

int flags_checker(int argc, char *argv[], choice *options);

int main(int argc, char *argv[]) {
  choice options = {0};
  if (flags_checker(argc, argv, &options)) {
    printf("Ошибка в аргументах командной строки\n");
    return 1;
  }
  const char *regex_pattern = argv[optind];
  int file_count = argc - optind - 1;
  if (options.e) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          e_sample(file, file_name, regex_pattern, file_count);
          fseek(file, 0, SEEK_END);
          long size = ftell(file);
          if (size > 0) {
            fseek(file, 0, SEEK_SET);
            char buffer[size + 1];
            fread(buffer, 1, size, file);
          }
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.i) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          i_case_ignore(file, file_name, regex_pattern, file_count);
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.v) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          v_inverse_search(file, file_name, regex_pattern, file_count);
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.c) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          c_number_of_correlated_lines(file, file_name, regex_pattern,
                                       file_count);
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.l) {
    if (optind < argc) {
      optind++;

      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          l_file_names_if_find(file, file_name, regex_pattern);
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.n) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          n_name_numberline_line(file, file_name, regex_pattern, file_count);
          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.h) {
    if (optind < argc) {
      optind++;

      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          h_result_without_names(file, regex_pattern);

          fclose(file);
        } else {
          printf("no such file or directory %s\n", file_name);
        }
      }
    } else {
      printf("error");
      return 1;
    }
  }
  if (options.s) {
    if (optind < argc) {
      optind++;

      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          s_silent_mode(file, file_name, regex_pattern, file_count);
          fclose(file);
        } else {
          continue;
        }
      }
    } else {
      return 1;
    }
  }
  if (options.f) {
    if (optind < argc) {
      optind++;
      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r");
        if (file) {
          f_file_to_file_search(file, regex_pattern, file_name, file_count);
          fclose(file);
        } else {
        }
      }
    } else {
      printf("error2");
    }
  }
  if (options.o) {
    if (optind < argc) {
      optind++;

      for (int i = optind; i < argc; i++) {
        const char *file_name = argv[i];
        FILE *file = fopen(file_name, "r+");
        if (file) {
          o_only_coincidence(file, file_name, regex_pattern, file_count);
          fclose(file);
        } else {
          continue;
        }
      }
    } else {
      return 1;
    }
  }
  if (optind + 1 < argc) {
    const char *file_name = argv[optind + 1];
    FILE *file = fopen(file_name, "r");

    if (file) {
      e_sample(file, regex_pattern, file_name, file_count);
      fclose(file);
    } else {
      printf("Не удалось открыть файл: %s\n", file_name);
    }
  }
  return 0;
}

void e_sample(FILE *file, const char *file_name, const char *regex_pattern,
              int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length1 = 0;
  regmatch_t match;
  int line_counter = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    line_counter++;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      if (file_count > 1) {
        printf("%s:", file_name);
      }
      size_t line_length = strlen(str);
      if (line_length > 0 && str[line_length - 1] == '\n') {
        str[line_length - 1] = '\0';
      }
      int offset = 0;
      int find_match = 0;

      while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        find_match = 1;
        int match_start = offset + match.rm_so;
        int match_end = offset + match.rm_eo;

        for (int i = offset; i < match_start; i++) {
          putchar(str[i]);
        }

        for (int i = match_start; i < match_end; i++) {
          line_counter = 1;
          putchar(str[i]);
        }

        offset = match_end;
      }
      if (find_match) {
        printf("%s\n", str + offset);
      }
    }
  }

  if (line) {
    free(line);
  }

  regfree(&regex);
}
void i_case_ignore(FILE *file, const char *file_name, const char *regex_pattern,
                   int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED | REG_ICASE);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length1 = 0;
  regmatch_t match;
  int line_counter = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    line_counter++;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      if (file_count > 1) {
        printf("%s:", file_name);
      }
      size_t line_length = strlen(str);
      if (line_length > 0 && str[line_length - 1] == '\n') {
        str[line_length - 1] = '\0';
      }
      int offset = 0;
      int find_match = 0;

      while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        find_match = 1;
        int match_start = offset + match.rm_so;
        int match_end = offset + match.rm_eo;

        for (int i = offset; i < match_start; i++) {
          putchar(str[i]);
        }

        for (int i = match_start; i < match_end; i++) {
          line_counter = 1;
          putchar(str[i]);
        }

        offset = match_end;
      }
      if (find_match) {
        printf("%s\n", str + offset);
      }
    }
  }

  if (line) {
    free(line);
  }
  regfree(&regex);
}
void v_inverse_search(FILE *file, const char *file_name,
                      const char *regex_pattern, int file_count) {
  regex_t regex;
  int reti;

  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }

  char *line = NULL;

  size_t line_length1 = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    if (regexec(&regex, str, 0, NULL, 0) != 0) {
      if (file_count > 1) {
        printf("%s:", file_name);
      }
      size_t line_length = strlen(str);
      if (line_length > 0 && str[line_length - 1] == '\n') {
        str[line_length - 1] = '\0';
      }
      printf("%s\n", str);
    }
  }
  if (line) {
    free(line);
  }
  regfree(&regex);
}
void c_number_of_correlated_lines(FILE *file, const char *file_name,
                                  const char *regex_pattern, int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length = 0;
  regmatch_t match;
  int line_number = 0;
  int number_of_lines_counter = 0;
  while (getline(&line, &line_length, file) != -1) {
    line_number++;
    char *str = line;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      int offset = 0;
      while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int match_start = offset + match.rm_so;
        int match_end = offset + match.rm_eo;

        for (int i = match_start; i < match_end; i++) {
        }

        offset = match_end;
      }
      number_of_lines_counter++;
    }
  }
  if (file_count > 1) {
    printf("%s:", file_name);
  }
  printf("%d", number_of_lines_counter);
  printf("\n");
  if (line) {
    free(line);
  }
  regfree(&regex);
}
void l_file_names_if_find(FILE *file, const char *file_name,
                          const char *regex_pattern) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length = 0;
  int found_match = 0;
  while (getline(&line, &line_length, file) != -1) {
    char *str = line;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      found_match = 1;
      break;
    }
  }
  if (found_match) {
    printf("%s\n", file_name);
  }
  if (line) {
    free(line);
  }
  regfree(&regex);
}

void n_name_numberline_line(FILE *file, const char *file_name,
                            const char *regex_pattern, int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length1 = 0;
  regmatch_t match;
  int line_number = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    line_number++;
    int find_match = 0;
    size_t line_length = strlen(str);
    if (line_length > 0 && str[line_length - 1] == '\n') {
      str[line_length - 1] = '\0';
    }
    int offset = 0;
    int match_count = 0;
    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
      find_match = 1;
      int match_start = offset + match.rm_so;
      int match_end = offset + match.rm_eo;
      if (match_count == 0) {
        if (file_count > 1) {
          printf("%s:", file_name);
        }
        printf("%d:", line_number);
        match_count++;
      }
      for (int i = offset; i < match_start; i++) {
        putchar(str[i]);
      }
      for (int i = match_start; i < match_end; i++) {
        putchar(str[i]);
      }
      offset = match_end;
    }
    if (find_match) {
      printf("%s\n", str + offset);
    }
  }
  if (line) {
    free(line);
  }
  regfree(&regex);
}

void h_result_without_names(FILE *file, const char *regex_pattern) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length1 = 0;
  regmatch_t match;
  int line_number = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    line_number++;
    int find_match = 0;
    size_t line_length = strlen(str);
    if (line_length > 0 && str[line_length - 1] == '\n') {
      str[line_length - 1] = '\0';
    }
    int offset = 0;

    while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
      find_match = 1;
      int match_start = offset + match.rm_so;
      int match_end = offset + match.rm_eo;

      for (int i = offset; i < match_start; i++) {
        putchar(str[i]);
      }
      for (int i = match_start; i < match_end; i++) {
        putchar(str[i]);
      }
      offset = match_end;
    }
    if (find_match) {
      printf("%s\n", str + offset);
    }
  }
  if (line) {
    free(line);
  }

  regfree(&regex);
}
void s_silent_mode(FILE *file, const char *file_name, const char *regex_pattern,
                   int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length1 = 0;
  regmatch_t match;
  int line_counter = 0;
  while (getline(&line, &line_length1, file) != -1) {
    char *str = line;
    line_counter++;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      if (file_count > 1) {
        printf("%s:", file_name);
      }
      size_t line_length = strlen(str);
      if (line_length > 0 && str[line_length - 1] == '\n') {
        str[line_length - 1] = '\0';
      }
      int offset = 0;
      int find_match = 0;

      while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        find_match = 1;
        int match_start = offset + match.rm_so;
        int match_end = offset + match.rm_eo;

        for (int i = offset; i < match_start; i++) {
          putchar(str[i]);
        }

        for (int i = match_start; i < match_end; i++) {
          line_counter = 1;
          putchar(str[i]);
        }
        offset = match_end;
      }
      if (find_match) {
        printf("%s\n", str + offset);
      }
    }
  }
  if (line) {
    free(line);
  }
  regfree(&regex);
}
struct RegexInfo {
  regex_t regex;
  char *pattern;
};
void f_file_to_file_search(FILE *file, const char *pattern_file,
                           const char *file_name, int file_count) {
  FILE *patterns = fopen(pattern_file, "r");
  if (patterns == NULL) {
    perror("Ошибка при открытии файла с регулярными выражениями");
    return;
  }

  char *pattern = NULL;
  size_t pattern_size = 0;

  // Массив структуры для стока регулярок
  struct RegexInfo *regex_array = NULL;
  int regex_count = 0;

  while (getline(&pattern, &pattern_size, patterns) != -1) {
    size_t len = strlen(pattern);
    if (len > 0 && pattern[len - 1] == '\n') {
      pattern[len - 1] = '\0';
    }

    struct RegexInfo regex_info;
    regex_info.pattern = strdup(pattern);

    int reti = regcomp(&regex_info.regex, pattern, REG_EXTENDED);
    if (reti) {
      printf("Could not compile regex: %s\n", pattern);
      free(pattern);
      fclose(patterns);

      for (int i = 0; i < regex_count; i++) {
        free(regex_array[i].pattern);
        regfree(&regex_array[i].regex);
      }
      free(regex_array);

      return;
    }
    struct RegexInfo *temp =
        realloc(regex_array, (regex_count + 1) * sizeof(struct RegexInfo));
    if (temp != NULL) {
      regex_array = temp;  // Обновляем указатель только в случае успеха realloc
      regex_array[regex_count] = regex_info;
      regex_count++;
    } else {
      printf("Ошибка при выделении памяти для регулярного выражения: %s\n",
             pattern);
      free(pattern);
      fclose(patterns);

      for (int i = 0; i < regex_count; i++) {
        free(regex_array[i].pattern);
        regfree(&regex_array[i].regex);
      }
      free(regex_array);

      return;
    }
  }

  free(pattern);
  fclose(patterns);

  rewind(file);
  char *line = NULL;
  size_t line_length = 0;
  int line_number = 0;
  int match_found = 0;
  while (getline(&line, &line_length, file) != -1) {
    char *str = line;
    line_number++;

    for (int i = 0; i < regex_count; i++) {
      if (regexec(&regex_array[i].regex, str, 0, NULL, 0) == 0) {
        if (file_count > 1) {
          printf("%s", file_name);
        }
        int offset = 0;
        regmatch_t match;
        while (regexec(&regex_array[i].regex, str + offset, 1, &match, 0) ==
               0) {
          int match_start = offset + match.rm_so;
          int match_end = offset + match.rm_eo;
          match_found = 1;
          for (int j = offset; j < match_start; j++) {
            putchar(str[j]);
          }
          for (int j = match_start; j < match_end; j++) {
            putchar(str[j]);
          }

          offset = match_end;
        }

        printf("%s", str + offset);
      }
    }
  }
  if (match_found) {
    printf("\n");
  }
  free(line);
  for (int i = 0; i < regex_count; i++) {
    free(regex_array[i].pattern);
    regfree(&regex_array[i].regex);
  }
  free(regex_array);
}

void o_only_coincidence(FILE *file, const char *file_name,
                        const char *regex_pattern, int file_count) {
  regex_t regex;
  int reti;
  reti = regcomp(&regex, regex_pattern, REG_EXTENDED);
  if (reti) {
    printf("Could not compile regex\n");
    return;
  }
  char *line = NULL;
  size_t line_length = 0;
  regmatch_t match;
  while (getline(&line, &line_length, file) != -1) {
    char *str = line;
    if (regexec(&regex, str, 0, NULL, 0) == 0) {
      int offset = 0;
      while (regexec(&regex, str + offset, 1, &match, 0) == 0) {
        int match_start = offset + match.rm_so;
        int match_end = offset + match.rm_eo;
        if (file_count > 1) {
          printf("%s:", file_name);
        }
        for (int i = match_start; i < match_end; i++) {
          putchar(str[i]);
        }
        printf("\n");
        offset = match_end;
      }
    }
  }
  if (line) {
    free(line);
  }
  regfree(&regex);
}

int flags_checker(int argc, char *argv[], choice *options) {
  int option_result_saver;
  int error = 0;

  while ((option_result_saver = getopt(argc, argv, "eivclnhsfo")) != -1) {
    switch (option_result_saver) {
      case 'e':
        options->e = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        break;
      case 'o':
        options->o = 1;
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
