/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * typestring.c
 *
 * Copyright (c) 2018 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef T_STRING_H
#define T_STRING_H

#include <stddef.h>

#ifndef T_STRING_DEFAULT_ALLOC_SIZE
#define T_STRING_DEFAULT_ALLOC_SIZE 1024
/* T_STRING_DEFAULT_ALLOC_SIZE */
#endif

typedef struct STRING STRING;

typedef struct STRING {
    size_t  alloc_size;
    size_t  length;
    char*   string;
    size_t  (*size)(STRING* self);
    size_t  (*capacity)(STRING* self);
    int     (*resize)(STRING** self, size_t size, char const c);
    int     (*assign)(STRING** self, char* const str);
    int     (*append)(STRING** self, char* const str);
    int     (*push_back)(STRING** self, char const c);
    void    (*pop_back)(STRING** self);
    int     (*insert)(STRING** self, size_t pos, char* const str);
    int     (*empty)(STRING* self);
    char    (*at)(STRING* self, size_t pos);
    char    (*front)(STRING* self);
    char    (*back)(STRING* self);
    char*   (*c_str)(STRING* self);
    size_t  (*copy)(STRING* self, char** dest);
    STRING* (*substr)(STRING* self, size_t pos, size_t n);
    int     (*c_substr)(STRING* self, size_t pos, size_t n, char** dest);
    int     (*compare)(STRING* self, struct STRING* opp);
    int     (*c_compare)(STRING* self, const char* s);
    void    (*clear)(STRING** self);
    void    (*release)(STRING* self);
} STRING;

STRING* new_string(char* const str);

/* T_STRING_H */
#endif
