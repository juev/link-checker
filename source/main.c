/*
 * main.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include "cmd.h"
#include "curl.h"
#include "getLinks.h"
#include "validate.h"

int main(int argc, char **argv) {
  char *url = process_argc(argc, argv);
  printf("URL = %s\n", url);

  bool res = isUrl(url);
  printf("%s is URL: %i\n", url, res);
  if (res) {
    char *page = get_webpage(url);
    printf("%s\n", page);
  }

  exit(0);
}
