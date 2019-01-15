# link-checker

[![Build Status](https://travis-ci.com/juev/link-checker.svg?branch=master)](https://travis-ci.com/juev/link-checker)

Trying to write network application on C.

Used this libraries: curl

For compiling you need to install libraries (on MacOS):

    % brew install curl

## TODO

- [X] Check input for URL format
- [ ] Get all links from webpage
- [ ] Convert all internal links to full URLs
- [ ] Check all weblinks on existing

### Validate URL

Regexp:

    ^(?:http(s)?:\/\/)+[\w.-]+(?:\.[\w\.-]+)+[\w\-\._~:\/?#[\]@!\$&'\(\)\*\+,;=.]+$

### Find all links

    href\\s*=\\s*(?:[\"'](?<1>[^\"']*)[\"']|(?<1>\\S+))
