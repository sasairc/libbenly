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
#include <string.h>
#include <errno.h>

static size_t size(STRING* self);
static int assign(STRING** self, char* const str);
static int append(STRING** self, char* const str);
static int insert(STRING** self, size_t pos, char* const str);
static int push_back(STRING** self, char const c);
static void pop_back(STRING** self);
static int empty(STRING* self);
static char* c_str(STRING* self);
static int compare(STRING* self, STRING* opp);
static void clear(STRING** self);
static void release(STRING* self);

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
        string->assign      = assign;
        string->append      = append;
        string->push_back   = push_back;
        string->pop_back    = pop_back;
        string->insert      = insert;
        string->empty       = empty;
        string->c_str       = c_str;
        string->compare     = compare;
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

    if (reallocate_memory(self, (*self)->alloc_size + strlen(str)) < 0) {
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
    if (pos > (*self)->length)
        return -2;

    int     status  = 0;

    if (reallocate_memory(self, (*self)->alloc_size + strlen(str)) < 0) {
        status = -1; goto ERR;
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
        case    -1:
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

    if (reallocate_memory(self, (*self)->alloc_size + 1) < 0) {
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
    *((*self)->string + (*self)->length - 1) = '\0';
    (*self)->length -= 1;

    return;
}

static
int empty(STRING* self)
{
    if (self->string == NULL && self->length == 0)
        return 1;

    return 0;
}

static
char* c_str(STRING* self)
{
    return self->string;
}

static
int compare(STRING* self, STRING* opp)
{
    if ((self->length != opp->length)   ||
            (memcmp(self->string, opp->string, self->length) != 0))
        return 1;

    return 0;
}

static
void clear(STRING** self)
{
    if ((*self)->string != NULL) {
        free((*self)->string);
        (*self)->string = NULL;
        {
            (*self)->length     = 0;
            (*self)->alloc_size = 0;
        }
    }

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
int allocate_memory(STRING** self, size_t size)
{
    if (size == 1)
        (*self)->alloc_size = 2;
    else if (size > 0)
        (*self)->alloc_size = size;

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
    int     status          = 0;
    size_t  old_alloc_size  = (*self)->alloc_size;

    if (size == 1)
        (*self)->alloc_size = 2;
    else if (size > 0)
        (*self)->alloc_size = size;

    if (((*self)->string = (char*)
                realloc((*self)->string, sizeof(char) * (*self)->alloc_size)) == NULL) {
        status = -1; goto ERR;
    } else {
        memset((*self)->string + old_alloc_size, '\0', (*self)->alloc_size - old_alloc_size);
    }

    return 0;

ERR:
    switch (status) {
        case -1:
            fprintf(stderr, "%s\n",
                    strerror(errno));
            break;
    }

    return status;
}
