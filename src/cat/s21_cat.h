#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int option_b;
  int option_e;
  int option_n;
  int option_s;
  int option_t;
  int option_v;
  int number_files;
} options;

void scan_options(int argc, char **argv, options *config, int *flag_error);
FILE *check_options(FILE *file, options *config);
void show_character(char character, int *change_character);
void count_empty_strings(char *array_ch, int *flag_empty_strings);

void show_flag_b_or_n(options *config, int *counter_line, char *array_ch);
void show_flag_e(char array_ch, int *change_character);
void show_flag_t(char array_ch, int *change_character);
void print_character(int len_str, options *config, char *array_ch);

#endif  // SRC_S21_CAT_H_