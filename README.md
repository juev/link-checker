# link-checker

[![Build Status](https://travis-ci.com/juev/link-checker.svg?branch=master)](https://travis-ci.com/juev/link-checker)

Trying to write network application on C.

Used this libraries: curl

For compiling you need to install libraries (on MacOS):

    % brew install curl

## TODO

- [X] Check input for URL format
- [X] Get all links from webpage
- [X] Convert all internal links to full URLs
- [X] Check all weblinks on existing
- [ ] Format output

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

Internal links can relative and absolute:

    /index.html
    ../../style.css

All internal links should be converted to external.

For information:
http://www.faqs.org/rfcs/rfc1808.html

**libcurl** can handle relative url with `curl_url_set`:

> curl_url_set() can also update the full URL, which also accepts a relative URL in case an existing one was already set. It will then apply the relative URL onto the former one and “transition” to the new absolute URL. Like this:

    /* first an absolute URL */
    curl_url_set(h, CURLUPART_URL,
        "https://example.org:88/path/html", 0);
   
    /* .. then we set a relative URL "on top" */
    curl_url_set(h, CURLUPART_URL,
        "../new/place", 0); 