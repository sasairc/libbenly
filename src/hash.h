/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * hash.h
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef BENLY_HASH_H
#define BENLY_HASH_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <stddef.h>

#ifndef DEFAULT_ELEM_SIZE
#define DEFAULT_ELEM_SIZE   32
/* DEFAULT_ELEM_SIZE */
#endif

typedef struct SHASH {
    int     elemc;
    char*** elem;
    int     (*put)(struct SHASH** shash, const char* key, const char* value);
    char*   (*get)(struct SHASH* shash, const char* key);
    int     (*exists)(struct SHASH* shash, const char* key);
    void    (*remove)(struct SHASH** shash, const char* key);
    void    (*release)(struct SHASH* shash);
    size_t  size;
} SHASH;

extern int init_shash(SHASH** shash);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* BENLY_HASH_H */
#endif
