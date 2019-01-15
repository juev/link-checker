/*
 * validate.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "validate.h"
#include <pcre.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVECCOUNT 30 /* should be a multiple of 3 */

bool isUrl(char *url) {
  pcre *re;
  const char *error;
  char *pattern =
      /* "^(?:http(s)?:\\/\\/" */
      /* ")+[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/?#[\\]@!\\$&" */
      "[\\w.-]+(?:\\.[\\w\\.-]+)+[\\w\\-\\._~:\\/?#[\\]@!\\$&"
      "'\(\\)\\*\\+,;=.]+$";
  int erroffset;

  int rc;
  int ovector[OVECCOUNT];

  re = pcre_compile(pattern,    /* the pattern */
                    0,          /* default options */
                    &error,     /* for error message */
                    &erroffset, /* for error offset */
                    NULL);      /* use default character tables */

  /* Compilation failed: print the error message and exit */

  if (re == NULL) {
    printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
    return 1;
  }

  rc = pcre_exec(re,          /* the compiled pattern */
                 NULL,        /* no extra data - we didn't study the pattern */
                 url,         /* the subject string */
                 strlen(url), /* the length of the subject */
                 0,           /* start at offset 0 in the subject */
                 0,           /* default options */
                 ovector,     /* output vector for substring information */
                 OVECCOUNT);  /* number of elements in the output vector */

  /* Matching failed: handle error cases */
  if (rc < 0) {
    switch (rc) {
      case PCRE_ERROR_NOMATCH:
        return false;
        break;
      /*
      Handle other special cases if you like
      */
      default:
        printf("Matching error %d\n", rc);
        break;
    }
    pcre_free(re); /* Release memory used for the compiled pattern */
    return 1;
  }

  /* Match succeded */
  return true;
}
