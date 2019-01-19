/*
 * main.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"

void usage() {
  cout << "Usage: link-checker [OPTION...] URL\n"
       << "Link checker\n"
       << "\n"
       << " --help                 Give this help list\n"
       << " --version              Print program version\nn";
  exit(0);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    usage();
  }
  for (int i = 1; i < argc; i++) {
    if (((string)argv[i]).compare("--help") == 0 ||
        ((string)argv[i]).compare("--usage") == 0) {
      usage();
    }
    if (((string)argv[i]).compare("--version") == 0) {
      puts("Link checker version 1.0");
      exit(0);
    }
  }
  string url = argv[1];
  if (checkUrl(url)) {
    /* cout << getPage(url) << endl; */
    for (string hlink : extract_hyperlinks(getPage(url))) cout << hlink << '\n';
  } else {
    usage();
  }
  return 0;
}
