/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * column.c
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef WITH_REGEX
#define WITH_REGEX
/* WITH_REGEX */
#endif

#include "./column.h"
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <locale.h>

#ifdef  WITH_GLIB
#include <glib.h>
/* WITH_GLIB */
#endif

#define ANSI_ESCSEQ "\x1b\[[0-9;]*[a-zA-Z]"

static size_t count_lines(char** const array[]);
static size_t count_cols(char** const array[]);
static int count_length(char** const array[], size_t x, size_t y, size_t** length, regex_t* reg);
static int put(char** const array[], size_t x, size_t y, size_t* length, regex_t* reg);
static int mbstrlen_with_regex(char* src, regex_t* reg);

static
size_t count_lines(char** const array[])
{
    size_t  y       = 0;

    while (*(array + y) != NULL)
        y++;

    return y;
}

static
size_t count_cols(char** const array[])
{
    size_t  x       = 0;

    while (*(*(array) + x) != NULL)
        x++;

    return x;
}

static
int count_length(char** const array[], size_t x, size_t y, size_t** length, regex_t* reg)
{
    size_t  i       = 0,
            j       = 0,
            len     = 0;

    if ((*length = (size_t*)
                malloc(sizeof(size_t) * x)) == NULL)
        return -1;

    while (i < x) {
        *(*length + i) = j = 0;
        while (j < y && *(*(array + j) + i) != NULL) {
            if ((len = mbstrlen_with_regex(*(*(array + j) + i), reg)) >
                    *(*length + i))
                *(*length + i) = len;
            j++;
        }
        i++;
    }

    return 0;
}

static
int put(char** const array[], size_t x, size_t y, size_t* length, regex_t* reg)
{
    size_t  i       = 0,
            j       = 0,
            len     = 0;

    while (i < y) {
        j = 0;
        while (j < x && *(*(array + i) + j) != NULL) {
            fprintf(stdout, "%s",
                    *(*(array + i) + j));
            len = mbstrlen_with_regex(*(*(array + i) + j), reg);
            while (len <= *(length + j) && putchar(' '))
                len++;
            j++;
        }
        putchar('\n');
        i++;
    }

    return 0;
}

int tablize(char** const array[])
{
    int     status  = 0;

    size_t  x       = 0,
            y       = 0,
        *   length  = NULL;

    regex_t reg;

    y = count_lines(array);
    x = count_cols(array);
    if (regcomp(&reg, ANSI_ESCSEQ, REG_EXTENDED) != 0) {
        status = -1; goto ERR;
    }
    if (count_length(array, x, y, &length, &reg) < 0) {
        status = -2; goto ERR;
    }
    put(array, x, y, length, &reg);
    regfree(&reg);
    free(length);

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            regfree(&reg);
            break;
    }

    return status;
}

static
int mbstrlen_with_regex(char* src, regex_t* reg)
{
    int         ch      = 0,
                len     = 0;

    char*       p       = src;

#ifdef  WITH_GLIB
    gunichar*   cpoints;
/* WITH_GLIB */
#endif

    regmatch_t  match;

    setlocale(LC_CTYPE, LOCALE);

    while (*p != '\0') {
        /* get string length */
        if ((ch = mblen(p, MB_CUR_MAX)) < 0)
            return 0;

#ifdef  WITH_GLIB
        /*
         * true : multi byte
         * false: ascii
         */
        if (ch > 1) {
            /* get unicode code point */
            cpoints = g_utf8_to_ucs4_fast(p, sizeof(*p), NULL);
            /*
             * # multi byte
             * true : hankaku kana
             * false: other
             */
            if ((*cpoints >= 0xff65 && *cpoints <= 0xff9f) ||
                    *cpoints == 0x001b) {
                len++;
            } else {
                len += 2;
            }
            g_free(cpoints);
        } else {
            len++;
        }
#else
        /*
         * true : multi byte
         * false: ascii
         */
        if (ch > 1) {
            len += 2;
        } else {
            len++;
        }
/* WITH_GLIB */
#endif
        /* seek offset */
        p += ch;
    }

    /* regex match */
    while (regexec(reg, src, 1, &match, 0) != REG_NOMATCH) {
        src += match.rm_eo;
        len -= match.rm_eo - match.rm_so;
    }

    return len;
}
