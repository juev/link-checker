/*
 * regex.cc
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"

bool checkUrl(const string url) {
  regex rgx(
      "^(?:http(s)?:\\/\\/)[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/"
      "?#[\\]@!\\$&'\\(\\)\\*\\+,;=.]+$");
  smatch match;

  return std::regex_search(url, rgx);
}

set<string> extract_hyperlinks(string html) {
  static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                   std::regex_constants::icase);

  return {std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
          std::sregex_token_iterator{}};
}

urlDef parse_link(const string url) {
  urlDef result;
  static const std::regex hl_regex(R"((?:(.*):\/\/)*([^\/\:]*)\/(.*))",
                                   std::regex_constants::icase);
  std::smatch matches;
  if (std::regex_search(url, matches, hl_regex)) {
    result.scheme = matches[1];
    result.domain = matches[2];
    result.path = matches[3];
  } else {
    std::cout << "Match not found\n";
  }
  return result;
}
