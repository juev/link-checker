# link-checker

[![Build Status](https://travis-ci.com/juev/link-checker.svg?branch=master)](https://travis-ci.com/juev/link-checker)

Trying to write network application on C++

Using libraries: curl

For compiling you need to install libraries (on MacOS):

    % brew install curl

## TODO

- [X] Check input for URL format
- [X] Get all links from webpage
- [X] Check all weblinks on existing
- [X] Format output
- [ ] Convert all internal links to full URLs

### Validate URL

Regexp:

    ^(?:http(s)?:\/\/)+[\w.-]+(?:\.[\w\.-]+)+[\w\-\._~:\/?#[\]@!\$&'\(\)\*\+,;=.]+$

### Find all links

    href\\s*=\\s*(?:[\"'](?<1>[^\"']*)[\"']|(?<1>\\S+))

### Type of links

All links ca be separated to internal and external.

External links:

    https://travis-ci.com/juev/link-checker.svg
    http://www.juev.org/
    //yandex.ru

All these links can be started with `http(s)` or `//`.

Internal links can be relative and absolute:

    /index.html
    ../../style.css

All internal links should be converted to external:

1) Get protocol and domain name from URL
1) Absolute link:
    * protocol + domain + url
1) Relative link:
    * START_URL + url

For information:
http://www.faqs.org/rfcs/rfc1808.html
