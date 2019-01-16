/*
 * getLinks.c
 * Copyright (C) 2019 Denis Evsyukov
 *
 * Distributed under terms of the MIT license.
 */

#include "getLinks.h"
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OVECCOUNT 300 /* should be a multiple of 3 */

int *getLinks(char *page) {
  pcre *re;
  const char *error;
  char *pattern = "href\\s*=\\s*(?:[\"'](?<1>[^\"']*)[\"']|(?<1>\\S+))";
  int erroffset;

  int rc;
  static int ovector[OVECCOUNT];

  re = pcre_compile(pattern,    /* the pattern */
                    0,          /* default options */
                    &error,     /* for error message */
                    &erroffset, /* for error offset */
                    NULL);      /* use default character tables */

  /* Compilation failed: print the error message and exit */

  if (re == NULL) {
    printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
    exit(1);
  }

  rc = pcre_exec(re,           /* the compiled pattern */
                 NULL,         /* no extra data - we didn't study the pattern */
                 page,         /* the subject string */
                 strlen(page), /* the length of the subject */
                 0,            /* start at offset 0 in the subject */
                 0,            /* default options */
                 ovector,      /* output vector for substring information */
                 OVECCOUNT);   /* number of elements in the output vector */

  /* Matching failed: handle error cases */
  if (rc < 0) {
    switch (rc) {
      case PCRE_ERROR_NOMATCH:
        return ovector;
        break;
      /*
      Handle other special cases if you like
      */
      default:
        printf("Matching error %d\n", rc);
        break;
    }
    pcre_free(re); /* Release memory used for the compiled pattern */
    exit(1);
  }

  /* Match succeded */
  return ovector;
}
