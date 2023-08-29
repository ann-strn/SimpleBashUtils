#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    options *config = NULL;
    config = calloc(1, sizeof(options));
    if (config != NULL) {
      int counter_file = scan_options(argc, argv, config);
      for (; counter_file < argc; counter_file++) {
        use_grep(argv[counter_file], config);
      }
      if (config->patterns != NULL) {
        free(config->patterns);
      }
      free(config);
    } else {
      fprintf(stderr, "memory not alloc");
    }
  } else {
    printf("didn't have argument command line");
  }
  return 0;
}

void print_l_c_option(options *config, char *file_name) {
  if (config->count_files > 1 && (!(config->h))) {
    printf("%s:", file_name);
  }
  if (config->suc_match > 0) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  print_l_option(config, file_name);
}

void print_l_option(options *config, char *file_name) {
  if (config->suc_match) {
    printf("%s\n", file_name);
  }
}

void print_c_option(options *config, char *file_name) {
  if (config->count_files > 1 && (!(config->h))) {
    printf("%s:", file_name);
  }
  printf("%d\n", config->suc_match);
}

void use_grep(char *file_name, options *config) {
  FILE *fp = NULL;
  fp = fopen(file_name, "r");
  char *array_ch = NULL;
  size_t len = 0;
  int len_array_ch;

  if (fp != NULL) {
    config->number_line = 0;
    while ((len_array_ch = getline(&array_ch, &len, fp)) != -1) {
      config->number_line += 1;
      print_string(array_ch, config, file_name, len_array_ch);
    }
    free(array_ch);

    if (fp != NULL) {
      fclose(fp);
    }
    if (config->c && config->l) {
      print_l_c_option(config, file_name);
      config->suc_match = 0;
    } else if (config->c) {
      print_c_option(config, file_name);
      config->suc_match = 0;
    } else if (config->l) {
      print_l_option(config, file_name);
      config->suc_match = 0;
    }

  } else if (config->s == 0) {
    fprintf(stderr, "grep: %s: No such file or directory\n", file_name);
  }
}

void print_string(char *array_ch, options *config, char *file_name,
                  int len_array_ch) {
  regex_t regex;
  regmatch_t rm[1];
  char *end = array_ch;
  int flag = REG_EXTENDED;
  if (config->i) {
    flag = REG_ICASE;
  }

  if (regcomp(&regex, config->patterns, flag) == 0) {
    if (regexec(&regex, end, 1, rm, 0) == config->v) {
      config->suc_match += 1;

      if ((config->c || config->l) == 0) {
        if (config->count_files > 1 && (!(config->h))) {
          printf("%s:", file_name);
        }

        if (config->n) {
          printf("%i:", config->number_line);
        }
        if (config->v || !(config->o)) {
          printf("%s", array_ch);
          if (array_ch[len_array_ch - 1] != '\n') {
            printf("\n");
          }
        } else if (config->o && (config->v == 0)) {
          do {
            printf("%.*s\n", (int)(rm[0].rm_eo - rm[0].rm_so),
                   end + rm[0].rm_so);
            end = end + (int)rm[0].rm_eo;
          } while (regexec(&regex, end, 1, rm, 0) == 0);
        }
      }
    }
    regfree(&regex);
  }
}

int scan_options(int argc, char **argv, options *config) {
  int sym = 0;
  opterr = 0;
  const char *short_options = "e:ivclnhsf:o";
  while ((sym = getopt_long(argc, argv, short_options, NULL, NULL)) != (-1)) {
    switch (sym) {
      case 'i':
        config->i = 1;
        break;
      case 'v':
        config->v = 1;
        break;
      case 'c':
        config->c = 1;
        break;
      case 'l':
        config->l = 1;
        break;
      case 'n':
        config->n = 1;
        break;
      case 'h':
        config->h = 1;
        break;
      case 's':
        config->s = 1;
        break;
      case 'o':
        config->o = 1;
        break;
      case 'e':
        set_config(config, optarg);
        config->e += 1;
        break;
      case 'f':
        set_config_f(config, optarg);
        break;
    }
  }

  if (config->patterns == NULL) {
    add_first_pattern(config, argv[optind]);
    optind++;
  }

  config->count_files = argc - optind;

  return optind;
}

void set_config(options *config, char *optarg) {
  if (!(config->e || config->f)) {
    add_first_pattern(config, optarg);
  } else {
    add_patterns(config, optarg);
  }
}

void set_config_f(options *config, char *optarg) {
  FILE *fp = NULL;
  char *array_ch = NULL;
  size_t len = 0;
  fp = fopen(optarg, "r");

  if (fp != NULL) {
    int lenght = 0;
    while ((lenght = getline(&array_ch, &len, fp)) != -1) {
      if (array_ch[lenght - 1] == '\n') {
        array_ch[lenght - 1] = '\0';
      }

      set_config(config, array_ch);
      config->f += 1;
    }
    free(array_ch);

  } else if (config->s == 0) {
    printf("grep: %s: No such file or directory\n", optarg);
  }

  if (fp != NULL) {
    fclose(fp);
  }
}

void add_first_pattern(options *config, char *optarg) {
  config->patterns = malloc(sizeof(char) * (strlen(optarg) + 1));
  if (config->patterns == NULL) {
    printf("ERROR1");
    exit(EXIT_FAILURE);
  }
  strcpy(config->patterns, optarg);
}

void add_patterns(options *config, char *optarg) {
  int len = strlen(config->patterns) + strlen(optarg) + 2;
  config->patterns = realloc(config->patterns, len);
  if (config->patterns == NULL) {
    printf("ERROR2");
    exit(EXIT_FAILURE);
  }
  strcat(config->patterns, "|");
  strcat(config->patterns, optarg);
}