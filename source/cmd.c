/*
 * cmd.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
  puts(
      "Usage: link-checker [OPTION...] URL \n \
Link checker \n \
\n \
  --help                 Give this help list \n \
  --version              Print program version");
  exit(0);
}

char* process_argc(int argc, char **argv) {
  if (argc < 2) {
    usage();
  }
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--usage") == 0) {
      usage();
    }
    if (strcmp(argv[i], "--version") == 0) {
      puts("Link checker version 1.0");
      exit(0);
    }
  }

  return argv[1];
}
