/*
 * main.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"
#include "../termcolor/termcolor.hpp"

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
    if (((string)argv[i]) == "--help" || ((string)argv[i]) == "--usage") {
      usage();
    }
    if ((string)argv[i] == "--version") {
      puts("Link checker version 1.0");
      exit(0);
    }
  }
  string url = argv[1];
  if (checkUrl(url)) {
    for (const string &hlink : extract_hyperlinks(getPage(url))) {
      cout << left;
      cout << "*  " << setw(120) << hlink << setw(5) << ' ';
      long res = getResutlCode(url, hlink);
      if (res == 200) {
        cout << termcolor::green << res << termcolor::reset << endl;
      } else {
        cout << termcolor::red << res << termcolor::reset << endl;
      }
    }
  } else {
    usage();
  }
  return 0;
}
