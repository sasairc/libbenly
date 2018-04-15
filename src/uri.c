/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * uri.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifndef DEFAULT_BUFSIZE
#define DEFAULT_BUFSIZE 1024
/* DEFAULT_BUFSIZE */
#endif

int encode_uri(char* const src, char** dest)
{
    int     status  = 0;

    size_t  bufsiz  = DEFAULT_BUFSIZE,
            current = 0;

    char*   p       = src;

    if ((*dest = (char*)
                malloc(sizeof(char) * bufsiz)) == NULL) {
        status = -1; goto ERR;
    } else {
        memset(*dest, '\0', bufsiz);
    }

    while (*p != '\0') {
        if ((current + 3) >= bufsiz) {
            bufsiz += DEFAULT_BUFSIZE;
            if ((*dest = (char*)
                        realloc(*dest, sizeof(char) * bufsiz)) == NULL) {
                status = -2; goto ERR;
            } else {
                memset(*dest + current, '\0', DEFAULT_BUFSIZE);
            }
        }
        if (
                (*p >= 0x20 && *p <= 0x39)  ||  /* [0-9] */
                (*p >= 0x41 && *p <= 0x5A)  ||  /* [A-Z] */
                (*p >= 0x61 && *p <= 0x7A)  ||  /* [a-z] */
                (*p == 0x2E)                ||  /* . */
                (*p == 0x2F)                ||  /* / */
                (*p == 0x3A)                    /* : */
           ) {
            *(*(dest) + current) = *p;
            current++;
        } else {
            current += sprintf(*dest + current, "%%%02X",
                    *p & 0x000000FF);
        }
        p++;
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
        case    -2:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}
