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

string getPage(string url);
long getResutlCode(string originUrl, string url);

class URL {
 public:
  bool isValid = false;
  set<string> links;

  URL(const string link) {
    static const std::regex scheme_regex(R"((.*):\/\/(?:.*))",
                                         std::regex_constants::icase);
    std::cmatch m;
    char l[link.size() + 1];
    strcpy(l, link.c_str());
    if (std::regex_match(l, m, scheme_regex)) {
      scheme = m[1];
    } else {
      cout << "Scheme not found, using default https" << endl;
      scheme = "https";
    }
    static const std::regex domain_regex(
        R"((?:.*):\/\/([^\/:]*)(?:\/){0,1}(?:.*))",
        std::regex_constants::icase);
    if (std::regex_match(l, m, domain_regex)) {
      domain = m[1];
    } else {
      cout << "Domain not found" << endl;
    }
    static const std::regex path_regex(
        R"((?:.*):\/\/(?:[^\/]*)(?:\/){0,1}(.*))", std::regex_constants::icase);
    if (std::regex_match(l, m, path_regex)) {
      path = m[1];
    } else {
      cout << "Path not found" << endl;
    }
    regex rgx(
        "^(?:http(s)?:\\/\\/)[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/"
        "?#[\\]@!\\$&'\\(\\)\\*\\+,;=.]+$");
    smatch match;

    isValid = std::regex_search(link, rgx);
    static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                     std::regex_constants::icase);

    string html = getPage(link);
    links = {std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
             std::sregex_token_iterator{}};
  }

 private:
  string fullUrl;
  string scheme;
  string domain;
  string path;
};

#endif /* !HEADER_H */
