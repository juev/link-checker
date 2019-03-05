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

string getPage(wstring url);
long getResutlCode(string originUrl, string url);

class URL {
 public:
  wstring fullUrl;
  wstring scheme;
  wstring domain;
  wstring port;
  wstring path;
  wstring query;

  URL(const string slink) {
    cout << "link: " << slink << endl;
    typedef std::wstring::const_iterator iterator_t;

    wstring link(slink.begin(), slink.end());
    iterator_t linkEnd = link.end();
    // get query start
    iterator_t queryStart = std::find(link.begin(), linkEnd, L'?');
    // protocol
    iterator_t protocolStart = link.begin();
    iterator_t protocolEnd = std::find(link.begin(), linkEnd, L'//');
    if (protocolEnd != linkEnd && protocolEnd != protocolStart) {
      protocolEnd += 2;  //      ://
      scheme = std::wstring(protocolStart, protocolEnd);
    } else if (protocolEnd == protocolStart) {
      protocolEnd += 2;
    } else
      protocolEnd = link.begin();  // no protocol

    if (scheme == L"") scheme = L"https://";

    // host
    iterator_t hostStart = protocolEnd;
    iterator_t pathStart =
        std::find(hostStart, linkEnd, L'/');  // get pathStart

    iterator_t hostEnd =
        std::find(protocolEnd, (pathStart != linkEnd) ? pathStart : queryStart,
                  L':');  // check for port

    domain = std::wstring(hostStart, hostEnd);

    // port
    if ((hostEnd != linkEnd) && ((&*(hostEnd))[0] == L':'))  // we have a port
    {
      hostEnd++;
      iterator_t portEnd = (pathStart != linkEnd) ? pathStart : queryStart;
      port = std::wstring(hostEnd, portEnd);
    }

    // path
    if (pathStart != linkEnd) path = std::wstring(pathStart, queryStart);

    // query
    if (queryStart != linkEnd) query = std::wstring(queryStart, link.end());

    // init scheme, domain and path variables
    // change links to full link
    fullUrl = scheme + domain + path;
    wcout << "scheme: " << scheme << endl;
    wcout << "domain: " << domain << endl;
    wcout << "path: " << path << endl;

    wcout << "fullUrl: " << fullUrl << endl;
  }

  // extract links from page
  set<wstring> extract() {
    static const std::regex hl_regex(R"(href=['"]?([^\'" >]+))",
                                     std::regex_constants::icase);

    string html = getPage(fullUrl);
    set<string> temp = {
        std::sregex_token_iterator(html.begin(), html.end(), hl_regex, 1),
        std::sregex_token_iterator{}};
    set<wstring> result = {};
    // TODO: add handler for internal links */
    for (auto el : temp) {
      result.insert(URL(el).fullUrl);
    }
    return (result);
  }
};

#endif /* !HEADER_H */
