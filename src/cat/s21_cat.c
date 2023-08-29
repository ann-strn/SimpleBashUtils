#include "s21_cat.h"

int main(int argc, char **argv) {
  options config = {0};
  int flag_error = 0;
  if (argc > 1) {
    scan_options(argc, argv, &config, &flag_error);

    if (!flag_error) {
      while ((config.number_files) < argc) {
        FILE *fp = fopen(argv[config.number_files], "r");
        if (fp != NULL) {
          fclose(check_options(fp, &config));
        } else {
          fprintf(stderr, "%s: No such file or directory\n",
                  argv[config.number_files]);
        }

        config.number_files += 1;
      }
    }
  } else {
    fprintf(stderr, "argument command line not found\n");
  }

  return 0;
}

void scan_options(int argc, char **argv, options *config, int *flag_error) {
  int option;
  const char *short_options = "+beEnstTv";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((option = getopt_long(argc, argv, short_options, long_options,
                               NULL)) != -1) {
    switch (option) {
      case 'n':
        config->option_n = 1;
        break;
      case 'b':
        config->option_b = 1;
        break;
      case 'e':
        config->option_e = 1;
        config->option_v = 1;
        break;
      case 'E':
        config->option_e = 1;
        break;
      case 's':
        config->option_s = 1;
        break;
      case 't':
        config->option_t = 1;
        config->option_v = 1;
        break;
      case 'T':
        config->option_t = 1;
        break;
      case 'v':
        config->option_v = 1;
        break;
      case '?':
        *flag_error = 1;
    }
  }
  if (config->option_b == 1 && config->option_n == 1) {
    config->option_n = 0;
  }
  config->number_files = optind;
}

FILE *check_options(FILE *fp, options *config) {
  char *array_ch = NULL;
  int len_str = 0;
  int flag_empty_strings = 0;
  int counter_line = 1;
  int no_output_string = 0;
  size_t len = 0;

  while ((len_str = getline(&array_ch, &len, fp)) != -1) {
    if (config->option_s || config->option_b) {
      count_empty_strings(array_ch, &flag_empty_strings);

      if (flag_empty_strings > 1 && config->option_s) {
        no_output_string = 1;
      } else {
        no_output_string = 0;
      }
    }
    if (!no_output_string) {
      show_flag_b_or_n(config, &counter_line, array_ch);
      print_character(len_str, config, array_ch);
    }
  }
  if (array_ch != NULL) {
    free(array_ch);
  }

  return fp;
}

void print_character(int len_str, options *config, char *array_ch) {
  for (int i = 0; i < len_str; i++) {
    int change_character = 0;

    if (config->option_v) {
      show_character(array_ch[i], &change_character);
    }

    if (config->option_e) {
      show_flag_e(array_ch[i], &change_character);
    }
    if (config->option_t) {
      show_flag_t(array_ch[i], &change_character);
    }

    if (!change_character) {
      printf("%c", array_ch[i]);
    }
  }
}

void show_flag_t(char array_ch, int *change_character) {
  if (array_ch == 9) {
    putchar('^');
    putchar('I');
    *change_character += 1;
  }
}

void show_flag_e(char array_ch, int *change_character) {
  if (array_ch == 10) {
    putchar('$');
    putchar('\n');
    *change_character += 1;
  }
}

void show_flag_b_or_n(options *config, int *counter_line, char *array_ch) {
  if (config->option_n) {
    printf("%6d\t", *counter_line);
    *counter_line += 1;
  } else if (config->option_b) {
    if (array_ch[0] != '\n') {
      printf("%6d\t", *counter_line);
      *counter_line += 1;
    }
  }
}

void show_character(char character, int *change_character) {
  if (character < -96) {
    printf("M-^%c", character + 192);
    *change_character += 1;
  } else if (character < 0) {
    printf("M-%c", character + 128);
    *change_character += 1;
  } else if ((0 <= character && character <= 31) && (character != 10) &&
             (character != 9)) {
    putchar('^');
    putchar(character + 64);
    *change_character += 1;
  } else if (character == 127) {
    putchar('^');
    putchar('?');
    *change_character += 1;
  }
}

void count_empty_strings(char *array_ch, int *flag_empty_strings) {
  if (array_ch[0] == '\n') {
    *flag_empty_strings += 1;
  } else {
    *flag_empty_strings = 0;
  }
}