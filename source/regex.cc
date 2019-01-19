/*
 * regex.cc
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "header.h"

bool checkUrl(string url) {
  regex rgx(
      "^(?:http(s)?:\\/\\/)[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/"
      "?#[\\]@!\\$&'\(\\)\\*\\+,;=.]+$");
  smatch match;

  const string uri = url;
  if (std::regex_search(uri.begin(), uri.end(), match, rgx)) {
    return true;
  } else {
    return false;
  }
}

set<string> extract_hyperlinks(string html) {
  static const std::regex hl_regex("href=[\'\"]?([^\\'\" >]+)",
                                   std::regex_constants::icase);

  return {std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
          std::sregex_token_iterator{}};
}
