#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
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
  int count_files;
  int number_line;
  int count_matches;
  char *patterns;
  int suc_match;
  int print_name_file;

} options;

int scan_options(int argc, char **argv, options *p_config);
void set_config(options *config, char *optarg);
void set_config_f(options *config, char *optarg);
void add_first_pattern(options *config, char *optarg);
void add_patterns(options *config, char *optarg);

void use_grep(char *file_name, options *config);

void print_string(char *array_ch, options *config, char *file_name,
                  int len_array_ch);
void print_c_option(options *config, char *file_name);
void print_l_option(options *config, char *file_name);
void print_l_c_option(options *config, char *file_name);

#endif  // SRC_GREP_S21_GREP_H_