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
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <errno.h>

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
static size_t copy(STRING* self, char** dest);
static STRING* substr(STRING* self, size_t pos, size_t n);
static int c_substr(STRING* self, size_t pos, size_t n, char** dest);
static size_t split(STRING* self, char* const delim, STRING*** dest);
static size_t c_split(STRING* self, char* const delim, char*** dest);
static int to_char_arr(STRING* self, char*** dest);
static int compare(STRING* self, STRING* opp);
static int c_compare(STRING* self, const char* s);
static size_t chomp(STRING** self);
static size_t lstrip(STRING** self);
static size_t rstrip(STRING** self);
static int downcase(STRING** self);
static int upcase(STRING** self);
static int swapcase(STRING** self);
static int capitalize(STRING** self);
static int include(STRING* self, char* const str);
static int slice(STRING** self, char* const str);
static int ascii_only(STRING* self);
static char* mbstrtok(char* str, char* delim);
static void clear(STRING** self);
static void release(STRING* self);

static int is_in_range(STRING* self, size_t pos);
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
        string->compare         = compare;
        string->c_compare       = c_compare;
        string->chomp           = chomp;
        string->lstrip          = lstrip;
        string->rstrip          = rstrip;
        string->downcase        = downcase;
        string->swapcase        = swapcase;
        string->upcase          = upcase;
        string->capitalize      = capitalize;
        string->include         = include;
        string->slice           = slice;
        string->ascii_only      = ascii_only;
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
    if ((*s = new_string(buf)) == NULL)
        goto ERR;
    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    return 0;

ERR:
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
        status = ESTRISEMPTY;
    }
    p = self->c_str(self);
    setlocale(LC_CTYPE, "");
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
    if (self->size(self) <
            (len = strlen(str)))
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
    return !self->length;
}

static
char at(STRING* self, size_t pos)
{
    char    c   =   '\0';

    if (!is_in_range(self, pos))
        status = EOUTOFRANGE;
    else
        c = *(self->string + pos - 1);

    return c;
}

static
char front(STRING* self)
{
    return *(self->string);
}

static
char back(STRING* self)
{
    return *(self->string + self->length - 1);
}

static
char* c_str(STRING* self)
{
    return self->string;
}

static
size_t copy(STRING* self, char** dest)
{
    if (self->empty(self)) {
        status = ESTRISEMPTY; goto ERR;
    }
    if ((*dest = (char*)
                malloc(sizeof(char) * (self->length + 1))) == NULL) {
#ifdef  LIBRARY_VERBOSE
        print_error();
/* LIBRARY_VERBOSE */
#endif
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(*dest, self->string, self->length);
        *((*dest) + self->length) = '\0';
    }

    return self->length + 1;

ERR:
    switch (status) {
        case    ESTRISEMPTY:
        case    EMEMORYALLOC:
            break;
    }

    return status;
}

static
STRING* substr(STRING* self, size_t pos, size_t n)
{
    STRING*     s   = NULL;

    if (n == 0)
        n = self->size(self) - pos;

    if (!is_in_range(self, pos) ||
            !is_in_range(self, pos + n)){
        status = EOUTOFRANGE; goto ERR;
    }

    if ((s = new_string(NULL)) == NULL) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        s->length = n;
    }
    if (allocate_memory(&s, s->length + 1) < 0) {
        status = EMEMORYALLOC; goto ERR;
    } else {
        memcpy(s->string, self->string + pos, s->length);
        *(s->string + s->length) = '\0';
    }

    return s;

ERR:
    switch (status) {
        case    EOUTOFRANGE:
            break;
        case    EMEMORYALLOC:
            if (s != NULL) {
                s->release(s);
                s = NULL;
            }
            break;
    }

    return NULL;
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
        memcpy(*dest, self->string + pos, n);
        *((*dest) + n) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    EOUTOFRANGE:
            break;
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

    setlocale(LC_CTYPE, "");
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
    if ((self->size(self) != opp->size(opp)) ||
            (memcmp(self->c_str(self), opp->c_str(opp), self->size(self)) != 0))
        return 1;

    return 0;
}

static
int c_compare(STRING* self, const char* s)
{
    if (s == NULL) {
        status = EARGISNULPTR; goto ERR;
    }
    if ((self->size(self) != strlen(s)) ||
            (memcmp(self->c_str(self), s, self->size(self)) != 0))
        return 1;

    return 0;

ERR:
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
    if (self->size(self) < (len = strlen(str)))
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
    if ((*self)->size(*self) < (len = strlen(str)))
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