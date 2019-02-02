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

link parse_link(const string url) {
  link result;
  static const std::regex hl_regex(R"((.*):\/\/(.*)\/)",
                                   std::regex_constants::icase);
  return result;
}
