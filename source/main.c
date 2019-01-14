/*
 * main.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "cmd.h"
#include "curl.h"
#include <stdio.h>
#include <stdlib.h>

typedef char *string;

int main(int argc, char **argv) {
  string url = process_argc(argc, argv);
  printf("URL = %s\n", url);

  string page = get_webpage(url);
  printf("%s\n", page);
  exit(0);
}
