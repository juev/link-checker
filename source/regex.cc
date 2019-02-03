/*
 * regex.cc
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"

bool checkUrl(const string link) {
  regex rgx(
      "^(?:http(s)?:\\/\\/)[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/"
      "?#[\\]@!\\$&'\\(\\)\\*\\+,;=.]+$");
  smatch match;

  return std::regex_search(link, rgx);
}

set<string> extract_hyperlinks(string html) {
  static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                   std::regex_constants::icase);

  return {std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
          std::sregex_token_iterator{}};
}

URL parse_link(const string link) {
  URL result;
  static const std::regex scheme_regex(R"((.*):\/\/(?:.*))",
                                       std::regex_constants::icase);
  std::cmatch m;
  char l[link.size() + 1];
  strcpy(l, link.c_str());
  if (std::regex_match(l, m, scheme_regex)) {
    result.scheme = m[1];
  } else {
    cout << "Scheme not found, using default https" << endl;
    result.scheme = "https";
  }
  static const std::regex domain_regex(
      R"((?:.*):\/\/([^\/:]*)(?:\/){0,1}(?:.*))", std::regex_constants::icase);
  if (std::regex_match(l, m, domain_regex)) {
    result.domain = m[1];
  } else {
    cout << "Domain not found" << endl;
  }
  static const std::regex path_regex(R"((?:.*):\/\/(?:[^\/]*)(?:\/){0,1}(.*))",
                                     std::regex_constants::icase);
  if (std::regex_match(l, m, path_regex)) {
    result.path = m[1];
  } else {
    cout << "Path not found" << endl;
  }
  return result;
}
