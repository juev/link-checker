/*
 * header.h
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HEADER_H
#define HEADER_H

#include <curl/curl.h>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>

using namespace std;

struct link {
  string scheme;
  string domain;
  string path;
};

string getPage(string url);
bool checkUrl(string url);
set<string> extract_hyperlinks(string html);
long getResutlCode(string originUrl, string url);

#endif /* !HEADER_H */
