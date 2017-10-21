/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * file.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/select.h>

int count_file_lines(FILE* fp)
{
    int     c       = 0;

    size_t  y       = 0;

    rewind(fp);
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n')
            y++;
    }

    return y;
}

int load_file_to_array(char*** dest, size_t th_x, size_t th_y, FILE* fp)
{
    int     c       = 0,
            status  = 0;

    size_t  x       = 0,
            y       = 0;

    char*   tmp     = NULL,
        **  buf     = NULL;

    if ((tmp = (char*)
                malloc(sizeof(char) * th_x)) == NULL) {
        status = -1; goto ERR;
    } else {
        memset(tmp, '\0', th_x);
    }
    if ((buf = (char**)
                malloc(sizeof(char*) * th_y)) == NULL) {
        status = -2; goto ERR;
    }
    while (1) {
        c = fgetc(fp);
        switch (c) {
            case    '\n':
            case    EOF:
                /* no data */
                if (c == EOF && x == 0 && y == 0) {
                    if (tmp != NULL) {
                        free(tmp);
                        tmp = NULL;
                    }
                    if (buf != NULL) {
                        free(buf);
                        buf = NULL;
                    }
                    return 0;
                }
                if (y >= th_y) {
                    th_y += th_y;
                    if ((buf = (char**)
                                realloc(buf, sizeof(char*) * th_y)) == NULL) {
                        status = -3; goto ERR;
                    }
                }
                if ((*(buf + y) = (char*)
                            malloc(sizeof(char) * (x + 1))) == NULL) {
                    status = -4; goto ERR;
                } else {
                    memcpy(*(buf + y), tmp, x);
                    *(*(buf + y) + x) = '\0';
                    memset(tmp, '\0', th_x);
                }
                if (c == '\n') {
                    x = 0;
                    y++;
                } else if (c == EOF) {
                    goto ENDLOOP;
                }
                break;
            default:
                if (x >= th_x) {
                    th_x += th_x;
                    if ((tmp = (char*)
                                realloc(tmp, sizeof(char) * th_x)) == NULL) {
                        status = -5; goto ERR;
                    }
                }
                *(tmp + x) = c;
                x++;
                break;
        }
    }

ENDLOOP:
    if (tmp != NULL)
        free(tmp);

    *(buf + y) = NULL;
    *dest = buf;

    return y;

ERR:
    switch (status) {
        case    -5:
        case    -4:
        case    -3:
            if (buf != NULL)
        case    -2:
            if (tmp != NULL)
                free(tmp);
        case    -1:
            break;
    }

    return status;
}

int file_is_binary(FILE* fp)
{
    int     c   = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c <= 0x08)
            return c;
    }

    return 0;
}

int watch_fd(int fd, long timeout)
{
    fd_set  fdset;

    struct  timeval tm;

    FD_ZERO(&fdset);
    FD_SET(fd, &fdset);

    tm.tv_sec = tm.tv_usec = timeout;

    return select(fd + 1, &fdset, NULL, NULL, &tm);
}
