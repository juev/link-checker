/*
 * header.h
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#ifndef HEADER_H
#define HEADER_H

#include <curl/curl.h>
#include <iostream>
#include <iterator>
#include <regex>
#include <set>
#include <string>

using namespace std;

string getPage(string url);
bool checkUrl(string url);
set<string> extract_hyperlinks(string html);

#endif /* !HEADER_H */
