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
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <stdio.h>      /* FILE */
#include <stddef.h>     /* size_t */
#include <stdint.h>     /* uint32_t */
#include <stdarg.h>

#ifdef  WITH_GLIB
#include <glib.h>
/* WITH_GLIB */
#endif

#ifndef T_STRING_DEFAULT_ALLOC_SIZE
#define T_STRING_DEFAULT_ALLOC_SIZE 1024
/* T_STRING_DEFAULT_ALLOC_SIZE */
#endif

#ifndef T_STRING_LOCALE_VALUE
#define T_STRING_LOCALE_VALUE   ""
/* T_STRING_DEFAULT_LOCALE_VALUE */
#endif

/*
 * typestring_errno
 */
#define EOUTOFRANGE         -1
#define EINVALIDCHAR        -2
#define EMEMORYALLOC        -3
#define ESTRISEMPTY         -4
#define EARGISNULPTR        -5
#define ESTRNOTFOUND        -6

/*
 * string_errno check macros
 */
#define WOUTOFRANGE(x)      ((x) == EOUTOFRANGE)
#define WINVALIDCHAR(x)     ((x) == EINVALIDCHAR)
#define WMEORYALLOC(x)      ((x) == EMEMORYALLOC)
#define WSTRISEMPTY(x)      ((x) == ESTRISEMPTY)
#define WEARGISNULPTR(x)    ((x) == EARGISNULPTR)
#define WSTRNOTFOUND(x)     ((x) == ESTRNOTFOUND)

extern int* wrap_type_string_errno(void);
#define string_errno    (*wrap_type_string_errno())

typedef struct STRING STRING;

typedef struct STRING {
    size_t  alloc_size;
    size_t  length;
    char*   string;
    size_t  (*size)(STRING* self);
    size_t  (*mblen)(STRING* self);
    size_t  (*capacity)(STRING* self);
    size_t  (*count)(STRING* self, char* const str);
    size_t  (*reconf)(STRING** self, size_t n);
    int     (*reserve)(STRING** self, size_t s);
    int     (*shrink_to_fit)(STRING** self);
    int     (*resize)(STRING** self, size_t n, char const c);
    int     (*assign)(STRING** self, char* const str);
    int     (*prepend)(STRING** self, char* const str);
    int     (*append)(STRING** self, char* const str);
    int     (*push_back)(STRING** self, char const c);
    void    (*pop_back)(STRING** self);
    void    (*swap)(STRING** s1, STRING** s2);
    int     (*insert)(STRING** self, size_t pos, char* const str);
    int     (*erase)(STRING** self, size_t pos, size_t n);
    int     (*replace)(STRING** self, size_t pos, size_t n, char* const str);
    int     (*empty)(STRING* self);
    char    (*at)(STRING* self, size_t pos);
    char*   (*front)(STRING* self);
    char*   (*back)(STRING* self);
    char*   (*data)(STRING* self);
    char*   (*c_str)(STRING* self);
    int     (*copy)(STRING* self, STRING** dest);
    size_t  (*c_copy)(STRING* self, char** dest);
    int     (*substr)(STRING* self, size_t pos, size_t n, STRING** dest);
    int     (*c_substr)(STRING* self, size_t pos, size_t n, char** dest);
    int     (*partition)(STRING* self, char* const str, STRING*** dest);
    int     (*c_partition)(STRING* self, char* const str, char*** dest);
    size_t  (*split)(STRING* self, char* const delim, STRING*** dest);
    size_t  (*c_split)(STRING* self, char* const delim, char*** dest);
    int     (*to_char_arr)(STRING* self, char*** dest);
    int     (*compare)(STRING* self, STRING* opp);
    int     (*c_compare)(STRING* self, const char* s);
    int     (*casecmp)(STRING* self, STRING* opp);
    int     (*c_casecmp)(STRING* self, char* const s);
    int     (*concat)(STRING** self, STRING* opp, ...);
    int     (*c_concat)(STRING** self, char* const s, ...);
    size_t  (*chomp)(STRING** self);
    size_t  (*lstrip)(STRING** self);
    size_t  (*rstrip)(STRING** self);
    int     (*rjust)(STRING** self, size_t s, char c);
    int     (*ljust)(STRING** self, size_t s, char c);
    int     (*center)(STRING** self, size_t s, char c);
    int     (*mbrjust)(STRING** self, size_t s, char c);
    int     (*mbljust)(STRING** self, size_t s, char c);
    int     (*mbcenter)(STRING** self, size_t s, char c);
    int     (*downcase)(STRING** self);
    int     (*upcase)(STRING** self);
    int     (*swapcase)(STRING** self);
    int     (*capitalize)(STRING** self);
    int     (*include)(STRING* self, char* const str);
    int     (*index)(STRING* self, char* const str, size_t pos, size_t* idx);
    int     (*rindex)(STRING* self, char* const str, size_t pos, size_t* idx);
    int     (*mbindex)(STRING* self, char* const str, size_t pos, size_t* idx);
    int     (*mbrindex)(STRING* self, char* const str, size_t pos, size_t* idx);
    int     (*slice)(STRING** self, char* const str);
    int     (*delete_prefix)(STRING** self, char* const str);
    int     (*delete_suffix)(STRING** self, char* const str);
    int     (*sub)(STRING** self, char* const src, char* const dest);
    int     (*gsub)(STRING** self, char* const src, char* const dest);
    int     (*to_i)(STRING* self, int base);
    long    (*to_l)(STRING* self, int base);
    float   (*to_f)(STRING* self);
    int     (*reverse)(STRING** self);
    int     (*ascii_only)(STRING* self);
    int     (*digit_only)(STRING* self);
    int     (*each_line)(STRING* self, char* const delim, void (*fn)(STRING*));
    int     (*each_byte)(STRING* self, void (*fn)(char));
    int     (*each_char)(STRING* self, void (*fn)(char*));
    int     (*each_codepoint)(STRING* self, void (*fn)(uint32_t));
    char*   (*crypt)(STRING* self, char* const salt);
    int     (*crypt2)(STRING* self, char* const salt, char** dest);
    void    (*clear)(STRING** self);
    void    (*release)(STRING* self);

    /*
     * おまけ
     */
    size_t  (*mbstrlen)(char* const str);
} STRING;

extern STRING* new_string(char* const str);
extern int fgetline(FILE* fp, STRING** s);
extern int fputline(FILE* fp, STRING* s);
extern void release_char_arr(STRING* self, size_t n, char** arr);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* T_STRING_H */
#endif
