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

#include "./typestring.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <errno.h>

#ifdef  WITH_GLIB
#include <glib.h>
/* WITH_GLIB */
#endif

/*
 * @ LIBRARY_LIBRARY_VERBOSE
 * displaying system call errors
 */
#ifdef  LIBRARY_VERBOSE
#define print_error()   fprintf(stderr, "%s: %d: %s\n",\
        __FILE__, __LINE__, strerror(errno))
/* LIBRARY_VERBOSE */
#endif

static size_t size(STRING* self);
static size_t t_string_mblen(STRING* self);
static size_t capacity(STRING* self);
static size_t count(STRING* self, char* const str);
static size_t reconf(STRING** self, size_t n);
static int resize(STRING** self, size_t n, char const c);
static int reserve(STRING** self, size_t s);
static int shrink_to_fit(STRING** self);
static int assign(STRING** self, char* const str);
static int append(STRING** self, char* const str);
static int insert(STRING** self, size_t pos, char* const str);
static int erase(STRING** self, size_t pos, size_t n);
static int push_back(STRING** self, char const c);
static void pop_back(STRING** self);
static void swap(STRING** s1, STRING** s2);
static int empty(STRING* self);
static char at(STRING* self, size_t pos);
static char front(STRING* self);
static char back(STRING* self);
static char* c_str(STRING* self);
static int copy(STRING* self, STRING** dest);
static size_t c_copy(STRING* self, char** dest);
static int substr(STRING* self, size_t pos, size_t n, STRING** dest);
static int c_substr(STRING* self, size_t pos, size_t n, char** dest);
static size_t split(STRING* self, char* const delim, STRING*** dest);
static size_t c_split(STRING* self, char* const delim, char*** dest);
static int to_char_arr(STRING* self, char*** dest);
static int compare(STRING* self, STRING* opp);
static int c_compare(STRING* self, const char* s);
static int casecmp(STRING* self, STRING* opp);
static int c_casecmp(STRING* self, char* const s);
static int concat(STRING** self, STRING* opp, ...);
static int c_concat(STRING** self, char* const s, ...);
static size_t chomp(STRING** self);
static size_t lstrip(STRING** self);
static size_t rstrip(STRING** self);
static int rjust(STRING** self, size_t s, char c);
static int ljust(STRING** self, size_t s, char c);
static int center(STRING** self, size_t s, char c);
static int mbrjust(STRING** self, size_t s, char c);
static int mbljust(STRING** self, size_t s, char c);
static int mbcenter(STRING** self, size_t s, char c);
static int downcase(STRING** self);
static int upcase(STRING** self);
static int swapcase(STRING** self);
static int capitalize(STRING** self);
static int include(STRING* self, char* const str);
static int slice(STRING** self, char* const str);
static int delete_prefix(STRING** self, char* const str);
static int delete_suffix(STRING** self, char* const str);
static int to_i(STRING* self, int base);
static long to_l(STRING* self, int base);
static float to_f(STRING* self);
static int reverse(STRING** self);
static int ascii_only(STRING* self);
static int each_line(STRING* self, char* const delim, void (*fn)(STRING*));
static int each_byte(STRING* self, void (*fn)(char));
static int each_char(STRING* self, void (*fn)(char*));
#ifdef  WITH_GLIB
static int each_codepoint(STRING* self, void (*fn)(uint32_t));
/* WITH_GLIB */
#endif
static char* mbstrtok(char* str, char* delim);
static void clear(STRING** self);
static void release(STRING* self);

static int is_in_range(STRING* self, size_t pos);
static int count_mb_witdh(STRING* self, size_t* s);
static int allocate_memory(STRING** self, size_t size);
static int reallocate_memory(STRING** self, size_t size);

int status;

STRING* new_string(char* const str)
{
    STRING* string  = NULL;

    if ((string = (STRING*)
                malloc(sizeof(STRING))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        string->alloc_size      = 0;
        string->length          = 0;
        string->string          = NULL;
        string->size            = size;
        string->mblen           = t_string_mblen;
        string->reconf          = reconf;
        string->resize          = resize;
        string->reserve         = reserve;
        string->shrink_to_fit   = shrink_to_fit;
        string->capacity        = capacity;
        string->count           = count;
        string->assign          = assign;
        string->append          = append;
        string->push_back       = push_back;
        string->pop_back        = pop_back;
        string->swap            = swap;
        string->insert          = insert;
        string->erase           = erase;
        string->at              = at;
        string->empty           = empty;
        string->front           = front;
        string->back            = back;
        string->c_str           = c_str;
        string->substr          = substr;
        string->c_substr        = c_substr;
        string->split           = split;
        string->c_split         = c_split;
        string->to_char_arr     = to_char_arr;
        string->copy            = copy;
        string->c_copy          = c_copy;
        string->compare         = compare;
        string->c_compare       = c_compare;
        string->casecmp         = casecmp;
        string->c_casecmp       = c_casecmp;
        string->concat          = concat;
        string->c_concat        = c_concat;
        string->chomp           = chomp;
        string->lstrip          = lstrip;
        string->rstrip          = rstrip;
        string->rjust           = rjust;
        string->ljust           = ljust;
        string->center          = center;
        string->mbrjust         = mbrjust;
        string->mbljust         = mbljust;
        string->mbcenter        = mbcenter;
        string->downcase        = downcase;
        string->swapcase        = swapcase;
        string->upcase          = upcase;
        string->capitalize      = capitalize;
        string->include         = include;
        string->slice           = slice;
        string->delete_prefix   = delete_prefix;
        string->delete_suffix   = delete_suffix;
        string->to_i            = to_i;
        string->to_l            = to_l;
        string->to_f            = to_f;
        string->reverse         = reverse;
        string->ascii_only      = ascii_only;
        string->each_line       = each_line;
        string->each_byte       = each_byte;
        string->each_char       = each_char;
#ifdef  WITH_GLIB
        string->each_codepoint  = each_codepoint;
#else
        string->each_codepoint  = NULL;
/* WITH_GLIB */
#endif
        string->clear           = clear;
        string->release         = release;
    }
    if (str != NULL) {
        if (string->assign(&string, str) < 0) {
            status = EMEMORYALLOC; goto ERR;
        }
    }

    return string;

ERR:
    switch (status) {
        case    EMEMORYALLOC:
            if (string != NULL) {
                free(string);
                string = NULL;
            }
        break;
    }

    return NULL;
}

int
fgetline(FILE* fp, STRING** s)
{
    int     c       = 0;

    size_t  length  = 0,
            bufsiz  = T_STRING_DEFAULT_ALLOC_SIZE + 1;

    char*   buf     = NULL;

    if ((buf = (char*)
                malloc(sizeof(char) * bufsiz)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memset(buf, '\0', bufsiz);
    }
    while ((c = fgetc(fp)) != EOF) {
        if (length >= (bufsiz - 1)) {
            bufsiz += T_STRING_DEFAULT_ALLOC_SIZE;
            if ((buf = (char*)
                        realloc(buf, sizeof(char) * bufsiz)) == NULL) {
#ifdef  LIBRARY_VERBOSE
                print_error();
/* LIBRARY_VERBOSE */
#endif
                status = EMEMORYALLOC; goto ERR;
            } else {
                memset(buf + length, '\0', bufsiz - length);
            }
        }
        *(buf + length) = c;
        length++;
        if (c == '\n') {
            *(buf + length) = '\0';
            break;
        }
    }
    if (!length && c == EOF) {
        status = EOF; goto IS_EOF;
    }
    if ((*s = new_string(buf)) == NULL)
        goto ERR;
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    return 0;

ERR:
IS_EOF:
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    return status;
}

int 
fputline(FILE* fp, STRING* s)
{
    if (fp == NULL || s == NULL) {
        status = EARGISNULPTR; goto ERR;
    }

    return fputs(s->c_str(s), fp);

ERR:
    return status;
}

void
release_char_arr(STRING* self, size_t n, char** arr)
{
    size_t  y   = 0;

    if (self != NULL)
        n = self->mblen(self);

    if (arr != NULL) {
        while (y < n) {
            if (*(arr + y) != NULL) {
                free(*(arr + y));
                *(arr + y) = NULL;
            }
            y++;
        }
        free(arr);
        arr = NULL;
    }

    return;
}

static
size_t size(STRING* self)
{
    return self->length;
}

static
size_t t_string_mblen(STRING* self)
{
    int     ch  = 0;

    size_t  c   = 0;

    char*   p   = NULL;

    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    p = self->c_str(self);
    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    while (*p != '\0') {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EINVALIDCHAR; goto ERR;
        } else {
            p += ch;
            c++;
        }
    }

    return c;

ERR:
    return 0;
}

static
size_t reconf(STRING** self, size_t n)
{
    if (n)
        (*self)->alloc_size = n;

    (*self)->length = strlen((*self)->c_str(*self));

    return (*self)->size(*self);
}

static
int resize(STRING** self, size_t n, char const c)
{
    if (n == (*self)->size(*self))
        return 0;

    if (n < (*self)->size(*self)) {
        memset((*self)->string + n, '\0', (*self)->size(*self) - n);
        (*self)->length = strlen((*self)->string);
    } else {
        if (reallocate_memory(self, n + 1) < 0) {
            status = EMEMORYALLOC; goto ERR;
        } else {
            memset((*self)->string + (*self)->size(*self), c, n - (*self)->size(*self));
            *((*self)->string + n) = '\0';
            (*self)->length = strlen((*self)->string);
        }
    }

    return 0;

ERR:
    return status;
}

static
int reserve(STRING** self, size_t s)
{
    if (!s) {
        status = EOUTOFRANGE; goto ERR;
    }

    (*self)->alloc_size = s + 1;
    if (((*self)->string = (char*)
                realloc((*self)->string, sizeof(char) * (*self)->alloc_size)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    }

    if ((*self)->empty(*self)) {
        memset((*self)->string, '\0', (*self)->alloc_size);
    } else {
        (*self)->length = s;
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    return status;
}

static
int shrink_to_fit(STRING** self)
{
    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    } else {
        (*self)->alloc_size = (*self)->length + 1;
        if (((*self)->string = (char*)
                    realloc((*self)->string,
                        sizeof(char) * (*self)->alloc_size)) == NULL) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EMEMORYALLOC; goto ERR;
        } else {
            *((*self)->string + (*self)->length) = '\0';
        }
    }

    return 0;

ERR:
    return status;
}

static
size_t capacity(STRING* self)
{
    return self->alloc_size;
}

static
size_t count(STRING* self, char* const str)
{
    size_t  n       = 0,
            len     = 0;

    char*   p       = NULL;

    if (str == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if (self->size(self) < (len = strlen(str)) ||
            !len)
        return 0;

    p = self->c_str(self);
    while (*p != '\0') {
        if (memcmp(p, str, len) == 0) {
            n++;
            p += len;
        } else {
            p++;
        }
    }

    return n;

ERR:
    return status;
}

static
int assign(STRING** self, char* const str)
{
    if (str == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if ((*self)->string != NULL) {
        free((*self)->string);
        (*self)->string = NULL;
    }
    (*self)->length = strlen(str);
    if (allocate_memory(self, (*self)->length + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy((*self)->string, str, (*self)->length);
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    EARGISNULPTR:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
int append(STRING** self, char* const str)
{
    if (str == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if (reallocate_memory(self, strlen(str) + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy((*self)->string + (*self)->length, str, strlen(str));
        (*self)->length += strlen(str);
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    EARGISNULPTR:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
int insert(STRING** self, size_t pos, char* const str)
{
    if (str == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if (!is_in_range(*self, pos)) {
        status = EOUTOFRANGE; goto ERR;
    }
    if (reallocate_memory(self, strlen(str) + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memmove((*self)->string + strlen(str) + pos,
                (*self)->string + pos,
                strlen((*self)->string + pos));
        memcpy((*self)->string + pos, str, strlen(str));
        (*self)->length = strlen((*self)->string);
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    EARGISNULPTR:
        case    EOUTOFRANGE:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
int erase(STRING** self, size_t pos, size_t n)
{
    if (!is_in_range(*self, pos) ||
            !is_in_range(*self, pos + n)) {
        status = EOUTOFRANGE; goto ERR;
    }

    if (n == 0)
        n = (*self)->size(*self) - pos;

    memmove((*self)->string + pos,
            (*self)->string + pos + n,
            strlen((*self)->string + pos + n));
    memset((*self)->string + (*self)->length - n, '\0', n);
    (*self)->length = strlen((*self)->c_str(*self));

    return 0;

ERR:
    switch (status) {
        case    EOUTOFRANGE:
            break;
    }

    return status;
}

static
int push_back(STRING** self, char const c)
{
    if (c == '\0')
        return 0;

    if (reallocate_memory(self, sizeof(c) + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        *((*self)->string + (*self)->length) = c;
        *((*self)->string + (*self)->length + 1) = '\0';
        (*self)->length += 1;
    }

    return 0;

ERR:
    switch (status) {
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
void pop_back(STRING** self)
{
    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY;
    } else {
        (*self)->length -= 1;
        *((*self)->string + (*self)->length) = '\0';
    }

    return;
}

static
void swap(STRING** s1, STRING** s2)
{
    STRING*     s3  = NULL;

    s3 = *s1;
    *s1 = *s2;
    *s2 = s3;

    return;
}

static
int empty(STRING* self)
{
    return !self->size(self);
}

static
char at(STRING* self, size_t pos)
{
    char    c   =   '\0';

    if (!is_in_range(self, pos))
        status = EOUTOFRANGE;
    else
        c = *(self->c_str(self) + pos - 1);

    return c;
}

static
char front(STRING* self)
{
    return *(self->c_str(self));
}

static
char back(STRING* self)
{
    return *(self->c_str(self) + self->size(self) - 1);
}

static
char* c_str(STRING* self)
{
    return self->string;
}

static
int copy(STRING* self, STRING** dest)
{
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*dest = new_string(NULL)) == NULL)
        goto ERR;
    if ((*dest)->reserve(dest, self->capacity(self) - 1) < 0)
        goto ERR;
    if ((*dest)->assign(dest, self->c_str(self)) < 0)
        goto ERR;

    return 0;

ERR:
    if (*dest != NULL) {
        (*dest)->release(*dest);
        *dest = NULL;
    }

    return status;
}

static
size_t c_copy(STRING* self, char** dest)
{
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*dest = (char*)
                malloc(sizeof(char) * (self->size(self) + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(*dest, self->c_str(self), self->size(self));
        *((*dest) + self->size(self)) = '\0';
    }

    return self->size(self) + 1;

ERR:
    switch (status) {
        case    ESTRISEMPTY:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
int substr(STRING* self, size_t pos, size_t n, STRING** dest)
{
    if (n == 0)
        n = self->size(self) - pos;

    if (!is_in_range(self, pos) ||
            !is_in_range(self, pos + n)) {
        status = EOUTOFRANGE; goto ERR;
    }

    if ((*dest = new_string(NULL)) == NULL) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        (*dest)->length = n;
    }
    if ((*dest)->reserve(dest, (*dest)->size(*dest)) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy((*dest)->c_str(*dest),
                self->c_str(self) + pos, (*dest)->size(*dest));
        *((*dest)->string + (*dest)->size(*dest)) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    ESTRISEMPTY:
        case    EOUTOFRANGE:
            break;
        case    EMEMORYALLOC:
            if (*dest != NULL) {
                (*dest)->release(*dest);
                *dest = NULL;
            }
            break;
    }

    return status;
}

static
int c_substr(STRING* self, size_t pos, size_t n, char** dest)
{
    if (n == 0)
        n = self->size(self) - pos;

    if (!is_in_range(self, pos) ||
            !is_in_range(self, pos + n)){
        status = EOUTOFRANGE; goto ERR;
    }

    if ((*dest = (char*)
                malloc(sizeof(char) * (n + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(*dest, self->c_str(self) + pos, n);
        *((*dest) + n) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    ESTRISEMPTY:
        case    EOUTOFRANGE:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
size_t split(STRING* self, char* const delim, STRING*** dest)
{
    size_t  y       = 0,
            idx     = 0;

    char*   tok     = NULL,
        *   tmp     = NULL;

    if (delim == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((idx = self->count(self, delim)) == 0)
        return 0;
    else
        idx++;

    if ((tmp = (char*)
                malloc(sizeof(char) * (self->size(self) + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(tmp, self->c_str(self), self->size(self));
        *(tmp + self->size(self)) = '\0';
    }
    if ((*dest = (STRING**)
                malloc(sizeof(STRING*) * idx)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    }
    tok = mbstrtok(tmp, delim);
    while (tok != NULL) {
        if ((*((*dest) + y) = new_string(tok))
                == NULL)
            goto ERR;
        tok = mbstrtok(NULL, delim);
        y++;
    }
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }

    return idx;

ERR:
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }
    if (dest != NULL &&
            *dest != NULL) {
        y = 0;
        while (y < idx) {
            self->release(*((*dest) + y));
            *((*dest) + y) = NULL;
            y++;
        }
        free(*dest);
        *dest = NULL;
    }

    return status;
}

static
size_t c_split(STRING* self, char* const delim, char*** dest)
{
    size_t  y       = 0,
            len     = 0,
            idx     = 0;

    char*   tok     = NULL,
        *   tmp     = NULL;

    if (delim == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((idx = self->count(self, delim)) == 0)
        return 0;
    else
        idx++;

    if ((tmp = (char*)
                malloc(sizeof(char) * (self->size(self) + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(tmp, self->c_str(self), self->size(self));
        *(tmp + self->size(self)) = '\0';
    }
    if ((*dest = (char**)
                malloc(sizeof(char*) * idx)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    }
    tok = mbstrtok(tmp, delim);
    while (tok != NULL) {
        len = strlen(tok);
        if ((*((*dest) + y) = (char*)
                    malloc(sizeof(char) * (len + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EMEMORYALLOC; goto ERR;
        } else {
            memcpy(*((*dest) + y), tok, len);
            *(*((*dest) + y) + len) = '\0';
        }
        tok = mbstrtok(NULL, delim);
        y++;
    }
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }

    return idx;

ERR:
    if (tmp != NULL) {
        free(tmp);
        tmp = NULL;
    }
    if (dest != NULL &&
            *dest != NULL)
        release_char_arr(NULL, idx, *dest);

    return status;
}

static
int to_char_arr(STRING* self, char*** dest)
{
    int     ch      = 0;

    size_t  y       = 0;

    char*   p       = self->c_str(self);

    if (self->empty(self) ||
            self->mblen(self) == 0) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*dest = (char**)
                malloc(sizeof(char*) * self->mblen(self))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        y = 0;
        while (y < self->mblen(self)) {
            *((*dest) + y) = NULL;
            y++;
        }
    }

    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    y = 0;
    while (*p != '\0' && y < self->mblen(self)) {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EINVALIDCHAR; goto ERR;
        }
        if ((*((*dest) + y) = (char*)
                    malloc(sizeof(char) * (ch + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EMEMORYALLOC; goto ERR;
        } else {
            memcpy(*((*dest) + y), p, ch);
            *(*((*dest) + y) + ch) = '\0';
        }
        p += ch;
        y++;
    }

    return 0;

ERR:
    switch (status) {
        case    ESTRISEMPTY:
            break;
        case    EINVALIDCHAR:
        case    EMEMORYALLOC:
            if (dest != NULL ||
                    *dest != NULL)
                release_char_arr(self, 0, *dest);
            break;
    }

    return status;
}

static
int compare(STRING* self, STRING* opp)
{
    if (opp == NULL)
        return (status = EARGISNULPTR);

    if ((self->size(self) != opp->size(opp)) ||
            (memcmp(self->c_str(self), opp->c_str(opp), self->size(self)) != 0))
        return 1;

    return 0;
}

static
int c_compare(STRING* self, const char* s)
{
    if (s == NULL)
        return (status = EARGISNULPTR);

    if ((self->size(self) != strlen(s)) ||
            (memcmp(self->c_str(self), s, self->size(self)) != 0))
        return 1;

    return 0;
}

static
int casecmp(STRING* self, STRING* opp)
{
    int     cmp = 0;

    STRING* s1  = NULL,
          * s2  = NULL;

    if (opp == NULL)
        return (status = EARGISNULPTR);

    if (self->copy(self, &s1) < 0 ||
            opp->copy(opp, &s2) < 0)
        goto ERR;

    s1->downcase(&s1);
    s2->downcase(&s2);
    cmp = s1->compare(s1, s2);
    s1->release(s1);
    s2->release(s2);

    return cmp;

ERR:
    if (s1 != NULL)
        s1->release(s1);
    if (s2 != NULL)
        s2->release(s2);

    return status;
}

static
int c_casecmp(STRING* self, char* const s)
{
    int     cmp = 0;

    STRING* s1  = NULL,
          * s2  = NULL;

    if (s == NULL)
        return (status = EARGISNULPTR);

    if (self->copy(self, &s1) < 0 ||
            ((s2 = new_string(s)) == NULL))
        goto ERR;

    s1->downcase(&s1);
    s2->downcase(&s2);
    cmp = s1->compare(s1, s2);
    s1->release(s1);
    s2->release(s2);

    return cmp;

ERR:
    if (s1 != NULL)
        s1->release(s1);
    if (s2 != NULL)
        s2->release(s2);

    return status;
}

static
int concat(STRING** self, STRING* opp, ...)
{
    STRING* p   = NULL;

    va_list list;

    va_start(list, opp);
    p = opp;
    while (p != NULL) {
        if ((*self)->append(self, p->c_str(p)) < 0)
            goto ERR;
        p = va_arg(list, STRING*);
    }
    va_end(list);

    return 0;

ERR:
    va_end(list);

    return status;
}

static
int c_concat(STRING** self, char* const s, ...)
{
    char*   p   = NULL;

    va_list list;

    va_start(list, s);
    p = s;
    while (p != NULL) {
        if ((*self)->append(self, p) < 0)
            goto ERR;
        p = va_arg(list, char* const);
    }
    va_end(list);

    return 0;

ERR:
    va_end(list);

    return status;
}

static
size_t chomp(STRING** self)
{
    size_t  n   = 0;

    char*   p   = NULL;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY;
        return 0;
    }
    p = (*self)->c_str(*self) + (*self)->size(*self) - 1;
    while ((*self)->size(*self) > 0 &&
            (*p == '\r' || *p == '\n')) {
        *p = '\0';
        p--;
        (*self)->length--;
        n++;
    }

    return n;
}

static
size_t lstrip(STRING** self)
{
    size_t  n   = 0;

    char*   p   = NULL;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY;
        return 0;
    }
    p = (*self)->c_str(*self);
    while (*p != '\0' &&
            (*p == '\t' || *p == '\n' || *p == '\v' ||
             *p == '\f' || *p == '\r' || *p == ' ')) {
        p++;
        n++;
    }
    p = (*self)->c_str(*self);
    if (n > 0) {
        memmove(p, p + n, (*self)->size(*self) - n);
        memset(p + (*self)->size(*self) - n, '\0', n);
        (*self)->length -= n;
    }

    return n;
}

static
size_t rstrip(STRING** self)
{
    size_t  n   = 0;

    char*   p   = NULL;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY;
        return 0;
    }
    p = (*self)->c_str(*self) + (*self)->size(*self) - 1;
    while ((*self)->size(*self) > 0 &&
            (*p == '\t' || *p == '\n' || *p == '\v' ||
             *p == '\f' || *p == '\r' || *p == ' ')) {
        *p = '\0';
        p--;
        (*self)->length--;
        n++;
    }

    return n;
}

static
int rjust(STRING** self, size_t s, char c)
{
    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*self)->size(*self) >= s)
        return 0;

    if (c == '\0')
        c = ' ';
    if (reallocate_memory(self, s + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memmove((*self)->c_str(*self) + s - (*self)->size(*self),
                (*self)->c_str(*self),
                (*self)->size(*self));
        memset((*self)->c_str(*self), c, s - (*self)->size(*self));
        *((*self)->c_str(*self) + s) = '\0';
        (*self)->length = s;
    }

    return 0;

ERR:
    return status;
}

static
int ljust(STRING** self, size_t s, char c)
{
    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*self)->size(*self) >= s)
        return 0;

    if (c == '\0')
        c = ' ';
    if (reallocate_memory(self, s + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memset((*self)->c_str(*self) + (*self)->size(*self),
                c,
                s - (*self)->size(*self));
        *((*self)->c_str(*self) + s) = '\0';
        (*self)->length = s;
    }

    return 0;

ERR:
    return status;
}

static
int center(STRING** self, size_t s, char c)
{
    size_t  s2  = 0;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*self)->size(*self) >= s)
        return 0;

    if (c == '\0')
        c = ' ';
    s2 = (s - (*self)->size(*self)) >> 1;
    if (reallocate_memory(self, s + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memmove((*self)->c_str(*self) + s2,
                (*self)->c_str(*self),
                (*self)->size(*self));
        memset((*self)->c_str(*self), c, s2);
        memset((*self)->c_str(*self) + (*self)->size(*self) + s2,
                c,
                s2 + (s - (*self)->size(*self)) % 2);
        *((*self)->c_str(*self) + s) = '\0';
        (*self)->length = s;
    }

    return 0;

ERR:
    return status;
}

static
int mbrjust(STRING** self, size_t s, char c)
{
    size_t  s2  = 0;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if (count_mb_witdh(*self, &s2) < 0)
        return (status = EINVALIDCHAR);
    if (s <= s2)
        return 0;
    else
        s2 = s - s2;

    if (reallocate_memory(self, s + s2 + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memmove((*self)->c_str(*self) + s2,
                (*self)->c_str(*self),
                (*self)->size(*self));
        memset((*self)->c_str(*self), c, s2);
        (*self)->length += s2;
        *((*self)->c_str(*self) + (*self)->size(*self)) = '\0';
    }

    return 0;

ERR:
    return status;
}

static
int mbljust(STRING** self, size_t s, char c)
{
    size_t  s2  = 0;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if (count_mb_witdh(*self, &s2) < 0)
        return (status = EINVALIDCHAR);
    if (s <= s2)
        return 0;
    else
        s2 = s - s2;

    if (c == '\0')
        c = ' ';
    if (reallocate_memory(self, s + s2 + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memset((*self)->c_str(*self) + (*self)->size(*self),
                c,
                s2);
        (*self)->length += s2;
        *((*self)->c_str(*self) + (*self)->size(*self)) = '\0';
    }

    return 0;

ERR:
    return status;
}

static
int mbcenter(STRING** self, size_t s, char c)
{
    size_t  ps  = 0,
            s2  = 0;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if (count_mb_witdh(*self, &s2) < 0)
        return (status = EINVALIDCHAR);
    if (s <= s2)
        return 0;

    ps = s2;
    s2 = (s - s2) >> 1;
    if (c == '\0')
        c = ' ';
    if (reallocate_memory(self, s + (s - s2) + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memmove((*self)->c_str(*self) + s2,
                (*self)->c_str(*self),
                (*self)->size(*self));
        memset((*self)->c_str(*self), c, s2);
        memset((*self)->c_str(*self) + (*self)->size(*self) + s2,
                c,
                s2 + (s - ps) % 2);
        (*self)->length = strlen((*self)->c_str(*self));
        *((*self)->c_str(*self) + (*self)->size(*self)) = '\0';
    }

    return 0;

ERR:
    return status;
}

static
int upcase(STRING** self)
{
    char*   p   = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);

    p = (*self)->c_str(*self);
    while (*p != '\0') {
        if (islower(*p))
            *p = toupper(*p);
        p++;
    }

    return 0;
}

static
int include(STRING* self, char* const str)
{
    size_t  pos     = 0,
            len     = 0;

    char*   p       = NULL;

    if (self->empty(self))
        return (status = ESTRISEMPTY);
    if (self->size(self) < (len = strlen(str)) ||
            !len)
        return (status = EOUTOFRANGE);

    p = self->c_str(self);
    while (*p != '\0' &&
            pos <= (self->size(self) - len)) {
        if (memcmp(p, str, len) == 0)
            return 1;
        pos++;
        p++;
    }

    return 0;
}

static
int capitalize(STRING** self)
{
    char*   p               = NULL;

    int     (*f1)(int c)    = isascii,
            (*f2)(int c)    = toupper;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);

    p = (*self)->c_str(*self);
    while (*p != '\0') {
        if (f1(*p)) {
            *p = f2(*p);
            f1 = isascii;
            f2 = tolower;
        }
        p++;
    }

    return 0;
}

static
int downcase(STRING** self)
{
    char*   p   = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);

    p = (*self)->c_str(*self);
    while (*p != '\0') {
        if (isupper(*p))
            *p = tolower(*p);
        p++;
    }

    return 0;
}

static
int swapcase(STRING** self)
{
    char*   p   = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);

    p = (*self)->c_str(*self);
    while (*p != '\0') {
        if (isupper(*p))
            *p = tolower(*p);
        else if (islower(*p))
            *p = toupper(*p);
        p++;
    }

    return 0;
}

static
int slice(STRING** self, char* const str)
{
    size_t  pos     = 0,
            len     = 0;

    char*   p       = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);
    if ((*self)->size(*self) < (len = strlen(str)) ||
            !len)
        return (status = EOUTOFRANGE);

    p = (*self)->c_str(*self);
    while (*p != '\0' &&
            pos <= ((*self)->size(*self) - len)) {
        if (memcmp(p, str, len) == 0) {
            p = (*self)->c_str(*self);
            memmove(p + pos, p + pos + len, (*self)->size(*self) - len);
            memset(p + (*self)->size(*self) - len, '\0', len);
            (*self)->length -= len;
            break;
        }
        pos++;
        p++;
    }

    return 0;
}

static
int delete_prefix(STRING** self, char* const str)
{
    size_t  len = 0;

    char*   p   = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);
    if ((*self)->size(*self) < (len = strlen(str)) ||
            !len)
        return 0;

    p = (*self)->c_str(*self);
    if (memcmp(p, str, len) == 0) {
        memmove(p, p + len, (*self)->size(*self) - len);
        memset(p + (*self)->size(*self) - len, '\0', len);
        (*self)->length -= len;
    } else {
        return 0;
    }

    return 1;
}

static
int delete_suffix(STRING** self, char* const str)
{
    size_t  len = 0;

    char*   p   = NULL;

    if ((*self)->empty(*self))
        return (status = ESTRISEMPTY);
    if ((*self)->size(*self) < (len = strlen(str)) ||
            !len)
        return 0;

    p = (*self)->c_str(*self) + (*self)->size(*self) - len;
    if (memcmp(p, str, len) == 0) {
        memset(p, '\0', len);
        (*self)->length -= len;
    } else {
        return 0;
    }

    return 1;
}

static
int to_i(STRING* self, int base)
{
    if (self->empty(self))
        return (status = ESTRISEMPTY);

    if (base <= 0)
        base = 10;
    errno = 0;

    return (int)strtol(self->c_str(self), NULL, base);
}

static
long to_l(STRING* self, int base)
{
    if (self->empty(self))
        return (status = ESTRISEMPTY);

    if (base <= 0)
        base = 10;
    errno = 0;

    return strtol(self->c_str(self), NULL, base);
}

static
float to_f(STRING* self)
{
    if (self->empty(self))
        return (status = ESTRISEMPTY);

    return atof(self->c_str(self));
}

static
int reverse(STRING** self)
{
    int     ch      = 0;

    size_t  pos     = 0;

    char*   p       = NULL,
        *   dest    = NULL;

    if ((*self)->empty(*self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((dest = (char*)
                malloc(sizeof(char) * (*self)->capacity(*self))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memset(dest, '\0', (*self)->capacity(*self));
    }
    p = (*self)->c_str(*self);
    pos = (*self)->size(*self);
    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    while (*p != '\0' && pos) {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            status = EINVALIDCHAR; goto ERR;
        } else {
            pos -= ch;
            memcpy(dest + pos, p, ch);
            p += ch;
        }
    }
    free((*self)->string);
    (*self)->string = dest;

    return 0;

ERR:
    if (dest != NULL) {
        free(dest);
        dest = NULL;
    }

    return status;
}

static
int ascii_only(STRING* self)
{
    char*   p   = NULL;

    if (self->empty(self))
        return (status = ESTRISEMPTY);

    p = self->c_str(self);
    while (*p != '\0') {
        if (!isascii(*p))
            return 0;
        p++;
    }

    return 1;
}

static
int each_line(STRING* self, char* const delim, void (*fn)(STRING*))
{
    size_t      i   = 0,
                idx = 0;

    char*       dd  = "\n"; /* default delimiter */

    STRING**    s2  = NULL;

    if (fn == NULL)
        return (status = EARGISNULPTR);

    if (delim != NULL)
        dd = delim;

    status = 0;
    idx = self->split(self, dd, &s2);
    if (status < 0)
        return status;

    while (i < idx) {
        fn(s2[i]);
        free(s2[i]);
        i++;
    }
    free(s2);

    return 0;
}

static
int each_byte(STRING* self, void (*fn)(char))
{
    char*   p   = NULL;

    if (self->empty(self))
        return (status = ESTRISEMPTY);
    if (fn == NULL)
        return (status = EARGISNULPTR);

    p = self->c_str(self);
    while (*p != '\0') {
        fn(*p);
        p++;
    }

    return 0;
}

static
int each_char(STRING* self, void (*fn)(char*))
{
    size_t  y   = 0,
            idx = 0;

    char**  arr = NULL;

    if (self->empty(self))
        return (status = ESTRISEMPTY);
    if (fn == NULL)
        return (status = EARGISNULPTR);

    if ((self)->to_char_arr(self, &arr) < 0)
        return status;

    idx = self->mblen(self);
    while (y < idx) {
        fn(arr[y]);
        free(arr[y]);
        y++;
    }
    free(arr);

    return 0;
}

#ifdef  WITH_GLIB
static
int each_codepoint(STRING* self, void (*fn)(uint32_t))
{
    int         ch  = 0;

    char*       p   = NULL;

    gunichar*   cp  = NULL;

    if (self->empty(self))
        return (status = ESTRISEMPTY);
    if (fn == NULL)
        return (status = EARGISNULPTR);

    p = self->c_str(self);
    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    while (*p != '\0') {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            return (status = EINVALIDCHAR);
        }
        cp = g_utf8_to_ucs4_fast(p, sizeof(*p), NULL);
        fn(*cp);
        g_free(cp);
        p += ch;
    }

    return 0;
}
/* WITH_GLIB */
#endif

static
void clear(STRING** self)
{
    if ((*self)->string != NULL) {
        free((*self)->string);
        (*self)->string = NULL;
    }
    (*self)->length     = 0;
    (*self)->alloc_size = 0;

    return;
}

static
void release(STRING* self)
{
    if (self != NULL) {
        if (self->string != NULL) {
            free(self->string);
            self->string = NULL;
        }
        free(self);
        self = NULL;
    }
            
    return;
}

/*
 * いちいち alloc していたら効率が悪い
 * #今度にしましょう
 */
static
int is_in_range(STRING* self, size_t pos)
{
    if (self->size(self) < pos)
        return 0;

    return 1;
}

#ifdef  WITH_GLIB
static
int count_mb_witdh(STRING* self, size_t* s)
{
    int         ch  = 0;

    char*       p   = self->c_str(self);

    gunichar*   cp  = NULL;

    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    while (*p != '\0') {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            return (status = EINVALIDCHAR);
        }
        if (ch > 1) {
            cp = g_utf8_to_ucs4_fast(p, sizeof(*p), NULL);
            if ((*cp >= 0xff65 && *cp <= 0xff9f))
                (*s)++;
            else
                (*s) += 2;
            g_free(cp);
        } else {
            (*s)++;
        }
        p += ch;
    }

    return 0;
}
#else
static
int count_mb_witdh(STRING* self, size_t* s)
{
    int     ch  = 0;

    char*   p   = self->c_str(self);

    setlocale(LC_CTYPE, T_STRING_LOCALE_VALUE);
    while (*p != '\0') {
        if ((ch = mblen(p, MB_CUR_MAX)) < 0) {
#ifdef  LIBRARY_VERBOSE
            print_error();
/* LIBRARY_VERBOSE */
#endif
            return (status = EINVALIDCHAR);
        }
        if (ch > 1)
            (*s) += 2;
        else
            (*s)++;
        p += ch;
    }

    return 0;
}
/* WITH_GLIB */
#endif

static
char* mbstrtok(char* str, char* delim)
{
    static  char*   ptr = NULL;
            char*   bdy = NULL;

    if (!str)
        str = ptr;

    if (!str)
        return NULL;

    if ((bdy = strstr(str, delim)) != NULL) {
        *bdy = '\0';
        ptr = bdy + strlen(delim);
    } else {
        ptr = NULL;
    }

    return str;
}

static
int allocate_memory(STRING** self, size_t size)
{
    while ((*self)->alloc_size < size)
        (*self)->alloc_size += T_STRING_DEFAULT_ALLOC_SIZE;

    if (((*self)->string = (char*)
                malloc(sizeof(char) * (*self)->alloc_size)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        return -1;
    } else {
        memset((*self)->string, '\0', (*self)->alloc_size);
    }

    return 0;
}

static
int reallocate_memory(STRING** self, size_t size)
{
    if (((*self)->length + size) < (*self)->alloc_size)
        return 0;

    size_t  old_alloc_size  = (*self)->alloc_size;

    while ((*self)->alloc_size < ((*self)->length + size))
        (*self)->alloc_size += T_STRING_DEFAULT_ALLOC_SIZE;

    if (((*self)->string = (char*)
                realloc((*self)->string,
                    sizeof(char) * (*self)->alloc_size)) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        return -1;
    } else {
        memset((*self)->string + old_alloc_size,
                '\0', (*self)->alloc_size - old_alloc_size);
    }

    return 0;
}

int* wrap_type_string_errno(void)
{
    return (&status);
}
