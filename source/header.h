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

struct URL {
  string fullUrl;
  string scheme;
  string domain;
  string path;
};

string getPage(string url);
bool checkUrl(string url);
set<string> extract_hyperlinks(string html);
long getResutlCode(string originUrl, string url);
URL parse_link(const string link);

#endif /* !HEADER_H */
