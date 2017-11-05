/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * spinner.h
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef SPINNER_H
#define SPINNER_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <unistd.h>

#ifndef LOCALE
#define LOCALE  ""
#endif

typedef struct SPINNER {
    pid_t   pid;
    char*   msg;
    char*   symbl;
    int     (*config)(struct SPINNER** spinner, const char* msg, const char* symbl);
    int     (*until)(struct SPINNER** spinner, const char* msg, const char* symbl);
    int     (*done)(struct SPINNER* spinner);
    void    (*release)(struct SPINNER* spinner);
} SPINNER;

extern int init_spinner(SPINNER** spinner);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* SPINNER_H */
#endif
