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

typedef struct STRING {
    size_t  alloc_size;
    size_t  length;
    char*   string;
    size_t  (*size)(struct STRING* self);
    int     (*assign)(struct STRING** self, char* const str);
    int     (*append)(struct STRING** self, char* const str);
    int     (*push_back)(struct STRING** self, char const c);
    void    (*pop_back)(struct STRING** self);
    int     (*insert)(struct STRING** self, size_t pos, char* const str);
    int     (*empty)(struct STRING* self);
    char*   (*c_str)(struct STRING* self);
    int     (*compare)(struct STRING* self, struct STRING* opp);
    void    (*clear)(struct STRING** self);
    void    (*release)(struct STRING* self);
} STRING;

STRING* new_string(char* const str);

/* T_STRING_H */
#endif
