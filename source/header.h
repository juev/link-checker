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

#include <algorithm>
#include <cctype>
#include <functional>

#include <wchar.h>

using namespace std;

string getPage(string url);
long getResutlCode(string originUrl, string url);

class URL
{
public:
  URL(const string link)
  {
    auto linkEnd = link.length();
    // get query start
    auto queryStart = link.find("?");
    // protocol
    auto protocolStart = 0;
    auto protocolEnd = link.find("//");

    if (protocolEnd != linkEnd && protocolEnd != protocolStart)
    {
      protocolEnd += 2; //      ://
      scheme = link.substr(protocolStart, protocolEnd - protocolStart);
    }
    else if (protocolEnd == protocolStart)
    {
      protocolEnd += 2;
    }
    else
      protocolEnd = 0; // no protocol
    if (scheme == "")
      scheme = "https://";
    // host
    auto hostStart = protocolEnd;
    auto pathStart = link.find("/", hostStart);
    auto hostEnd = link.find(":", protocolEnd);
    if (static_cast<int>(hostEnd) == -1)
      hostEnd = pathStart;

    domain = link.substr(hostStart, hostEnd - hostStart);

    // path
    if (pathStart != linkEnd && static_cast<int>(pathStart) != -1)
    {
      if (queryStart != -1)
      {
        path = link.substr(pathStart, queryStart - pathStart);
      }
      else
      {
        path = link.substr(pathStart, linkEnd - pathStart);
      }
    }
    // query
    if (queryStart != -1 && queryStart != linkEnd)
      query = link.substr(queryStart, link.length() - queryStart);
    // change links to full link
    fullUrl = scheme + domain + path;
    print();
  }

  string to_string()
  {
    return fullUrl;
  }

  void print()
  {
    cout << "fullUrl: " << fullUrl << endl;
    cout << "scheme: " << scheme << endl;
    cout << "domain: " << domain << endl;
    cout << "path: " << query << endl;
    cout << "query: " << query << endl;
  }
  // extract links from page
  set<string> extract()
  {
    static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                     std::regex_constants::icase);

    string html = getPage(fullUrl);
    set<string> temp = {
        std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
        std::sregex_token_iterator{}};
    set<string> result = {};
    // TODO: add handler for internal links */
    for (auto el : temp)
    {
      result.insert(URL(el).fullUrl);
    }
    return (result);
  }

private:
  string fullUrl = "";
  string scheme = "";
  string domain = "";
  string port = "";
  string path = "";
  string query = "";
};

#endif /* !HEADER_H */
