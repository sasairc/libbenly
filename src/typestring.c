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

static size_t size(STRING* self);
static size_t t_string_mblen(STRING* self);
static size_t capacity(STRING* self);
static int assign(STRING** self, char* const str);
static int append(STRING** self, char* const str);
static int insert(STRING** self, size_t pos, char* const str);
static int push_back(STRING** self, char const c);
static void pop_back(STRING** self);
static int empty(STRING* self);
static char at(STRING* self, size_t pos);
static char front(STRING* self);
static char back(STRING* self);
static char* c_str(STRING* self);
static size_t copy(STRING* self, char** dest);
static STRING* substr(STRING* self, size_t pos, size_t n);
static int c_substr(STRING* self, size_t pos, size_t n, char** dest);
static int to_char_arr(STRING* self, char*** dest);
static int compare(STRING* self, STRING* opp);
static int c_compare(STRING* self, const char* s);
static int ascii_only(STRING* self);
static void clear(STRING** self);
static void release(STRING* self);

static int is_in_range(STRING* self, size_t pos);
static int allocate_memory(STRING** self, size_t size);
static int reallocate_memory(STRING** self, size_t size);

STRING* new_string(char* const str)
{
    int     status  = 0;

    STRING* string  = NULL;

    if ((string = (STRING*)
                malloc(sizeof(STRING))) == NULL) {
        status = -1; goto ERR;
    } else {
        string->alloc_size  = 0;
        string->length      = 0;
        string->string      = NULL;
        string->size        = size;
        string->mblen       = t_string_mblen;
        string->capacity    = capacity;
        string->assign      = assign;
        string->append      = append;
        string->push_back   = push_back;
        string->pop_back    = pop_back;
        string->insert      = insert;
        string->at          = at;
        string->empty       = empty;
        string->front       = front;
        string->back        = back;
        string->c_str       = c_str;
        string->substr      = substr;
        string->c_substr    = c_substr;
        string->to_char_arr = to_char_arr;
        string->copy        = copy;
        string->compare     = compare;
        string->c_compare   = c_compare;
        string->ascii_only  = ascii_only;
        string->clear       = clear;
        string->release     = release;
    }
    if (str != NULL) {
        if (string->assign(&string, str) < 0) {
            status = -3; goto ERR;
        }
    }

    return string;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
        case    -2:
        case    -3:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            if (string != NULL) {
                free(string);
                string = NULL;
            }
        break;
    }

    return NULL;
}

static
size_t size(STRING* self)
{
    return self->length;
}

static
size_t t_string_mblen(STRING* self)
{
    size_t  c   = 0;

    char*   p   = self->c_str(self);

    setlocale(LC_CTYPE, "");
    while (*p != '\0') {
        if ((p += mblen(p, MB_CUR_MAX)) < 0)
            goto ERR;
        c++;
    }

    return c;

ERR:
    fprintf(stderr, "invalid character\n");

    return 0;
}

static
size_t capacity(STRING* self)
{
    return self->alloc_size;
}

static
int assign(STRING** self, char* const str)
{
    int     status  = 0;

    if ((*self)->string != NULL) {
        free((*self)->string);
        (*self)->string = NULL;
    }
    (*self)->length = strlen(str);
    if (allocate_memory(self, (*self)->length + 1) < 0) {
        status = -1; goto ERR;
    } else {
        memcpy((*self)->string, str, (*self)->length);
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}

static
int append(STRING** self, char* const str)
{
    int     status  = 0;

    if (reallocate_memory(self, strlen(str) + 1) < 0) {
        status = -1; goto ERR;
    } else {
        memcpy((*self)->string + (*self)->length, str, strlen(str));
        (*self)->length += strlen(str);
        *((*self)->string + (*self)->length) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}

static
int insert(STRING** self, size_t pos, char* const str)
{
    if (!is_in_range(*self, pos))
        return -1;

    int     status  = 0;

    if (reallocate_memory(self, strlen(str) + 1) < 0) {
        status = -2; goto ERR;
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
        case    -2:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}

static
int push_back(STRING** self, char const c)
{
    int     status  = 0;

    if (reallocate_memory(self, sizeof(c) + 1) < 0) {
        status = -1; goto ERR;
    } else {
        *((*self)->string + (*self)->length) = c;
        *((*self)->string + (*self)->length + 1) = '\0';
        (*self)->length += 1;
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}

static
void pop_back(STRING** self)
{
    if ((*self)->length == 0)
        return;

    (*self)->length -= 1;
    *((*self)->string + (*self)->length) = '\0';

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
    if (!is_in_range(self, pos))
        return '\0';

    return *(self->string + pos - 1);
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
    if (self->length == 0)
        return 0;

    if ((*dest = (char*)
                malloc(sizeof(char) * (self->length + 1))) == NULL) {
        fprintf(stderr, "%s\n",
                strerror(errno));

        return 0;
    } else {
        memcpy(*dest, self->string, self->length);
        *((*dest) + self->length) = '\0';
    }

    return self->length + 1;
}

static
STRING* substr(STRING* self, size_t pos, size_t n)
{
    STRING*     s   = NULL;

    if (n == 0)
        n = self->size(self) - pos;
    if (!is_in_range(self, pos) ||
            (self->size(self) < (pos + n)))
        return NULL;

    if ((s = new_string(NULL)) == NULL)
        return NULL;
    else
        s->length = n;

    if (allocate_memory(&s, s->length + 1) < 0) {
        fprintf(stderr, "%s\n",
                strerror(errno));
        s->release(s);

        return NULL;
    } else {
        memcpy(s->string, self->string + pos, s->length);
        *(s->string + s->length) = '\0';
    }

    return s;
}

static
int c_substr(STRING* self, size_t pos, size_t n, char** dest)
{
    int     status  = 0;

    if (n == 0)
        n = self->size(self) - pos;
    if (!is_in_range(self, pos) ||
            (self->size(self) < (pos + n))) {
        status = -1; goto ERR;
    }

    if ((*dest = (char*)
                malloc(sizeof(char) * (n + 1))) == NULL) {
        status = -2; goto ERR;
    } else {
        memcpy(*dest, self->string + pos, n);
        *((*dest) + n) = '\0';
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}

static
int to_char_arr(STRING* self, char*** dest)
{
    int     status  = 0,
            ch      = 0;

    size_t  y       = 0;

    char*   p       = self->c_str(self);

    if (self->mblen(self) == 0) {
        status = -1; goto ERR;
    }
    if ((*dest = (char**)
                malloc(sizeof(char*) * self->mblen(self))) == NULL) {
        status = -2; goto ERR;
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
            status = -3; goto ERR;
        }
        if ((*((*dest) + y) = (char*)
                    malloc(sizeof(char) * (ch + 1))) == NULL) {
            status = -4; goto ERR;
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
        case    -4:
        case    -3:
            y = 0;
            if (*dest != NULL) {
                while (y < self->mblen(self)) {
                    if (*((*dest) + y) != NULL) {
                        free(*((*dest) + y));
                        *((*dest) + y) = NULL;
                    }
                    y++;
                }
                free(*dest);
                *dest = NULL;
            }
        case    -2:
            if (status == -3)
                fprintf(stderr, "invalid character\n");
            else
                fprintf(stderr, "%s\n",
                        strerror(errno));
        case    -1:
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
    if (s == NULL)
        return -1;

    if ((self->size(self) != strlen(s)) ||
            (memcmp(self->c_str(self), s, self->size(self)) != 0))
        return 1;

    return 0;
}

static
int ascii_only(STRING* self)
{
    char*   p   = self->c_str(self);

    while (*p != '\0') {
        if (isascii(*p) == 0)
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
        (*self)->string     = NULL;
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
int allocate_memory(STRING** self, size_t size)
{
    while ((*self)->alloc_size < size)
        (*self)->alloc_size += T_STRING_DEFAULT_ALLOC_SIZE;

    if (((*self)->string = (char*)
                malloc(sizeof(char) * (*self)->alloc_size)) == NULL)
        return -1;
    else
        memset((*self)->string, '\0', (*self)->alloc_size);

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
                    sizeof(char) * (*self)->alloc_size)) == NULL)
        return -1;
    else
        memset((*self)->string + old_alloc_size,
                '\0', (*self)->alloc_size - old_alloc_size);

    return 0;
}
