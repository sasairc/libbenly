/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * hash.c
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./hash.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static int put_shash(SHASH** shash, const char* key, const char* value);
static char* get_shash(SHASH* shash, const char* key);
static int empty_shash(SHASH* shash);
static int key_exists_shash(SHASH* shash, const char* key);
static void remove_shash(SHASH** shash, const char* key);
static void clear_shash(SHASH** shash);
static void release_shash(SHASH* shash);

static int put_key_elem(SHASH** shash, const char* key, int pos);
static int put_value_elem(SHASH** shash, const char* value, int pos);
static void remove_key_elem(SHASH* shash, int pos);
static void remove_value_elem(SHASH* shash, int pos);
static int allocate_elem(SHASH** shash);
static int reallocate_elem(SHASH** shash);

static int strcmp_lite(const char* str1, const char* str2);

int init_shash(SHASH** shash)
{
    int     status  = 0;

    SHASH*  shs     = NULL;

    if ((shs = (SHASH*)
                malloc(sizeof(SHASH))) == NULL) {
        status = -1; goto ERR;
    } else {
        shs->elemc      = 0;
        shs->put        = put_shash;
        shs->get        = get_shash;
        shs->empty      = empty_shash;
        shs->exists     = key_exists_shash;
        shs->remove     = remove_shash;
        shs->clear      = clear_shash;
        shs->release    = release_shash;
        shs->size       = DEFAULT_ELEM_SIZE;
    }
    if (allocate_elem(&shs) < 0) {
        status = -2; goto ERR;
    }
    *shash = shs;

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            if (shs != NULL) {
                free(shs);
                shs = NULL;
            }
            break;
    }

    return status;
}

static
int put_shash(SHASH** shash, const char* key, const char* value)
{
    int     status  = 0,
            pos     = 0;

    if ((pos = key_exists_shash(*shash, key)) < 0) {
        if ((*shash)->size <= (size_t)(*shash)->elemc) {
            if (reallocate_elem(shash) < 0) {
                status = -1; goto ERR;
            }
        }
        if (put_key_elem(shash, key, (*shash)->elemc) < 0) {
            status = -2; goto ERR;
        }
        if (put_value_elem(shash, value, (*shash)->elemc) < 0) {
            status = -3; goto ERR;
        }
        (*shash)->elemc++;
    } else {
        if (*(*((*shash)->elem + pos) + 1) != NULL) {
            free(*(*((*shash)->elem + pos) + 1));
            *(*((*shash)->elem + pos) + 1) = NULL;
        }
        if (put_value_elem(shash, value, pos) < 0) {
            status = -4; goto ERR;
        }
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
        case    -2:
            break;
        case    -3:
            remove_key_elem(*shash, (*shash)->elemc);
            *(*((*shash)->elem + (*shash)->elemc)) = NULL;
            break;
        case    -4:
            remove_key_elem(*shash, pos);
            *(*((*shash)->elem + pos)) = NULL;
            break;
    }

    return status;
}

static
char* get_shash(SHASH* shash, const char* key)
{
    int     pos     = 0;

    if ((pos = shash->exists(shash, key)) < 0)
        return NULL;

    return *(*(shash->elem + pos) + 1);
}

static
int empty_shash(SHASH* shash)
{
    return !(shash->elemc | 0);
}

static
int key_exists_shash(SHASH* shash, const char* key)
{
    int     i       = 0,
            j       = 0;

    j = shash->elemc - 1;
    while (i < shash->elemc) {
        if (strcmp_lite(*(*(shash->elem + i)), key) == 0)
            return i;
        if (strcmp_lite(*(*(shash->elem + j)), key) == 0)
            return j;
        i++;
        j--;
    }

    return -1;
}

static
void release_shash(SHASH* shash)
{
    int     i       = 0,
            j       = 0;

    if (shash != NULL) {
        if (shash->elem != NULL) {
            j = shash->elemc - 1;
            while (i < shash->elemc && i <= j) {
                if (*(shash->elem + i) != NULL) {
                    remove_key_elem(shash, i);
                    *(*(shash->elem + i)) = NULL;
                    remove_value_elem(shash, i);
                    *(*(shash->elem + i) + 1) = NULL;
                    free(*(shash->elem + i));
                    *(shash->elem + i) = NULL;
                }
                if (*(shash->elem + j) != NULL) {
                    remove_key_elem(shash, j);
                    *(*(shash->elem + j)) = NULL;
                    remove_value_elem(shash, j);
                    *(*(shash->elem + j) + 1) = NULL;
                    free(*(shash->elem + j));
                    *(shash->elem + j) = NULL;
                }
                i++;
                j--;
            }
            free(shash->elem);
            shash->elem = NULL;
        }
        free(shash);
        shash = NULL;
    }

    return;
}

static
void clear_shash(SHASH** shash)
{
    int     i       = 0,
            j       = 0;

    j = (*shash)->elemc - 1;
    while (i < (*shash)->elemc && i <= j) {
        if (*((*shash)->elem + i) != NULL) {
            remove_key_elem(*shash, i);
            remove_value_elem(*shash, i);
            free(*((*shash)->elem + i));
            *((*shash)->elem + i) = NULL;
        }
        if (*((*shash)->elem + j) != NULL) {
            remove_key_elem(*shash, j);
            remove_value_elem(*shash, j);
            free(*((*shash)->elem + j));
            *((*shash)->elem + j) = NULL;
        }
        i++;
        j--;
    }
    (*shash)->elemc = 0;

    return;
}

static
void remove_shash(SHASH** shash, const char* key)
{
    int     pos     = 0;

    if ((pos = (*shash)->exists(*shash, key)) < 0)
        return;

    remove_key_elem(*shash, pos);
    remove_value_elem(*shash, pos);
    while (pos < (*shash)->elemc &&
            (*((*shash)->elem + pos) = *((*shash)->elem + (pos + 1))))
        pos++;
    (*shash)->elemc--;
    *((*shash)->elem + (*shash)->elemc) = NULL;

    return;
}

static
int put_key_elem(SHASH** shash, const char* key, int pos)
{
    size_t  len     = 0;

    len = strlen(key);
    if ((*(*((*shash)->elem + pos)) = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL)
        return -1;

    memcpy(*(*((*shash)->elem + pos)), key, len);
    *(*(*((*shash)->elem + pos)) + len) = '\0';

    return 0;
}

static
int put_value_elem(SHASH** shash, const char* value, int pos)
{
    size_t  len     = 0;

    len = strlen(value);
    if ((*(*(((*shash)->elem + pos)) + 1) = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL)
        return -1;

    memcpy(*(*((*shash)->elem + pos) + 1), value, len);
    *(*(*((*shash)->elem + pos) + 1) + len) = '\0';

    return 0;
}

static
void remove_key_elem(SHASH* shash, int pos)
{
    if (*(*(shash->elem + pos)) != NULL) {
        free(*(*(shash->elem + pos)));
        *(*(shash->elem + pos)) = NULL;
    }

    return;
}

static
void remove_value_elem(SHASH* shash, int pos)
{
    if (*(*(shash->elem + pos) + 1) != NULL) {
        free(*(*(shash->elem + pos) + 1));
        *(*(shash->elem + pos) + 1) = NULL;
    }

    return;
}

static
int allocate_elem(SHASH** shash)
{
    int     status  = 0;

    size_t  i       = 0;

    if (((*shash)->elem = (char***)
                malloc(sizeof(char**) * (*shash)->size)) == NULL) {
        status = -1; goto ERR;
    }
    while (i < (*shash)->size) {
        if ((*((*shash)->elem + i) = (char**)
                malloc(sizeof(char*) * 2)) == NULL) {
            status = -2; goto ERR;
        }
        *(*((*shash)->elem + i)) = NULL;
        *(*((*shash)->elem + i) + 1) = NULL;
        i++;
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            if ((*shash)->elem != NULL) {
                i = 0;
                while (i < (*shash)->size &&
                        *((*shash)->elem + i) != NULL) {
                        free(*((*shash)->elem + i));
                        *((*shash)->elem + i) = NULL;
                    i++;
                }
                free((*shash)->elem);
                (*shash)->elem = NULL;
            }
            break;
    }

    return status;
}

static
int reallocate_elem(SHASH** shash)
{
    int     status  = 0;

    size_t  i       = 0;

    (*shash)->size += DEFAULT_ELEM_SIZE;
    if (((*shash)->elem = (char***)
                realloc((*shash)->elem, sizeof(char**) * (*shash)->size)) == NULL) {
        status = -1; goto ERR;
    }
    i = (*shash)->elemc;
    while (i < (*shash)->size) {
        if ((*((*shash)->elem + i) = (char**)
                malloc(sizeof(char*) * 2)) == NULL) {
            status = -2; goto ERR;
        }
        *(*((*shash)->elem + i)) = NULL;
        *(*((*shash)->elem + i) + 1) = NULL;
        i++;
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            if ((*shash)->elem != NULL) {
                while (i < (*shash)->size &&
                        *((*shash)->elem + i) != NULL) {
                        free(*((*shash)->elem + i));
                        *((*shash)->elem + i) = NULL;
                    i++;
                }
                free((*shash)->elem);
                (*shash)->elem = NULL;
            }
            break;
    }

    return status;
}

static
int strcmp_lite(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;

    size_t  cnt     = 0,
            len1    = 0,
            len2    = 0;

    len1 = strlen(str1);
    len2 = strlen(str2);

    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
        str1++;
        str2++;
        cnt++;
    }
    if (cnt == len1 && cnt == len2)
        return 0;

    return 1;
}
