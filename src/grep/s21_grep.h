#ifndef S21_GREP
#define S21_GREP

typedef struct choices {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char *reg_e;
  char *reg_f;
  char *regex;
  char *file;
  int file_count[1000];
  int if_reg_found;

} choice;

#endif