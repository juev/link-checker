/*
 * main.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"
#include "termcolor/termcolor.hpp"

void usage() {
  cout << "Usage: link-checker [OPTION...] URL\n"
       << "Link checker\n"
       << "\n"
       << " --help                 Give this help list\n"
       << " --version              Print program version\n";
  exit(0);
}

int wmain(int argc, wchar_t **argv) {
  if (argc < 2) {
    usage();
  }
  for (int i = 1; i < argc; i++) {
    if (((wstring)argv[i]) == L"--help" || ((wstring)argv[i]) == L"--usage") {
      usage();
    }
    if ((wstring)argv[i] == L"--version") {
      puts("Link checker version 1.0");
      exit(0);
    }
  }
  wstring url = (wstring)argv[1];
  URL l = URL(url);
  /* for (const string &hlink : l.extract()) { */
  /*   cout << left; */
  /*   cout << "*  " << setw(120) << hlink << setw(5) << ' '; */
  /*   long res = getResutlCode(url, hlink); */
  /*   if (res == 200) { */
  /*     cout << termcolor::green << res << termcolor::reset << endl; */
  /*   } else { */
  /*     cout << termcolor::red << res << termcolor::reset << endl; */
  /*   } */
  /* } */
  return 0;
}
