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

class URL {
 public:
  string fullUrl = "";
  string scheme = "";
  string domain = "";
  string port = "";
  string path = "";
  string query = "";

  URL(const string link) {
    cout << "link: " << link << endl;
    // typedef std::wstring::const_iterator iterator_t;

    // wstring link(slink.begin(), slink.end());
    // iterator_t linkEnd = link.end();
    auto linkEnd = link.length();
    cout << "linkEnd: " << linkEnd << endl;
    // get query start
    auto queryStart = link.find("?");
    cout << "queryStart: " << static_cast<int>(queryStart) << endl;
    // iterator_t queryStart = std::find(link.begin(), linkEnd, L'?');
    // protocol
    // iterator_t protocolStart = link.begin();
    auto protocolStart = 0;
    // iterator_t protocolEnd = std::find(link.begin(), linkEnd, L'//');
    auto protocolEnd = link.find("//");
    cout << "protocolEnd: " << static_cast<int>(protocolEnd) << endl;

    if (protocolEnd != linkEnd && protocolEnd != protocolStart) {
      protocolEnd += 2;  //      ://
      // scheme = std::wstring(protocolStart, protocolEnd);
      scheme = link.substr(protocolStart, protocolEnd-protocolStart);
    } else if (protocolEnd == protocolStart) {
      protocolEnd += 2;
    } else
      // protocolEnd = link.begin();  // no protocol
      protocolEnd = 0;  // no protocol
    cout << "protocolEnd: " << static_cast<int>(protocolEnd) << endl;
    if (scheme == "") scheme = "https://";
    cout << "scheme: " << scheme << endl;
    // host
    // iterator_t hostStart = protocolEnd;
    auto hostStart = protocolEnd;
    cout << "hostStart: " << hostStart << endl;
    // iterator_t pathStart =
    //     std::find(hostStart, linkEnd, L'/');  // get pathStart
    auto pathStart = link.find("/", hostStart);
    cout << "pathStart: " << static_cast<int>(pathStart) << endl;
    // iterator_t hostEnd =
    //     std::find(protocolEnd, (pathStart != linkEnd) ? pathStart : queryStart,
    //               L':');  // check for port

    auto hostEnd = link.find(":", protocolEnd);
    if (static_cast<int>(hostEnd) == -1) hostEnd = pathStart;
    cout << "hostEnd: " << static_cast<int>(hostEnd) << endl;
    // domain = std::wstring(hostStart, hostEnd);
    domain = link.substr(hostStart, hostEnd-hostStart);
    cout << "domain: " << domain << endl;
    // path
    // if (pathStart != linkEnd) path = std::wstring(pathStart, queryStart);
    if (pathStart != linkEnd) {
      if (queryStart != -1) {
        path = link.substr(pathStart, queryStart-pathStart);
      } else {
        path = link.substr(pathStart, linkEnd-pathStart);
      }
    }
    cout << "path: " << path << endl;
    // query
    // if (queryStart != linkEnd) query = std::wstring(queryStart, link.length());
    if (queryStart!= -1 && queryStart != linkEnd) query = link.substr(queryStart, link.length()-queryStart);
    cout << "query: " << query << endl;
    // init scheme, domain and path variables
    // change links to full link
    fullUrl = scheme + domain + path;
    // cout << "scheme: " << scheme << endl;
    // cout << "domain: " << domain << endl;
    // cout << "path: " << path << endl;

    cout << "fullUrl: " << fullUrl << endl;
  }

  // extract links from page
  set<string> extract() {
    static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                     std::regex_constants::icase);

    string html = getPage(fullUrl);
    set<string> temp = {
        std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
        std::sregex_token_iterator{}};
    set<string> result = {};
    // TODO: add handler for internal links */
    for (auto el : temp) {
      result.insert(URL(el).fullUrl);
    }
    return (result);
  }
};

#endif /* !HEADER_H */
