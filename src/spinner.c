/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * spinner.c
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./spinner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <signal.h>
#include <sys/wait.h>

static int until_spinner(SPINNER** spinner, const char* msg, const char* symbl);
static int config_spinner(SPINNER** spinner, const char* msg, const char* symbl);
static int done_spinner(SPINNER* spinner);
static void do_animation(SPINNER* spinner);
static void release_spinner(SPINNER* spinner);
static void release_msg(SPINNER* spinner);
static void release_symbl(SPINNER* spinner);
static int copy_message(SPINNER** spinner, const char* msg);
static int copy_symbol(SPINNER** spinner, const char* symbl);

int init_spinner(SPINNER** spinner)
{
    SPINNER*    sp  = NULL;

    if ((sp = (SPINNER*)
                malloc(sizeof(SPINNER))) == NULL)
        return -1;
    {
        sp->pid     = 0;
        sp->symbl   = NULL;
        sp->msg     = NULL;
        sp->config  = config_spinner;
        sp->until   = until_spinner;
        sp->done    = done_spinner;
        sp->release = release_spinner;
    }
    *spinner = sp;

    return 0;
}

static
int config_spinner(SPINNER** spinner, const char* msg, const char* symbl)
{
    int     status  = 0;

    if (msg != NULL) {
        if ((*spinner)->msg != NULL) {
            release_msg(*spinner);
            (*spinner)->msg = NULL;
        }
        if (copy_message(spinner, msg) < 0) {
            status = -1; goto ERR;
        }
    }
    if (symbl != NULL) {
        if ((*spinner)->symbl != NULL) {
            release_symbl(*spinner);
            (*spinner)->symbl = NULL;
        }
        if (copy_symbol(spinner, symbl) < 0) {
            status = -2; goto ERR;
        }
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            release_msg(*spinner);
    }

    return status;
}

static
int until_spinner(SPINNER** spinner, const char* msg, const char* symbl)
{
    if ((msg == NULL && (*spinner)->msg == NULL) ||
            (symbl == NULL && (*spinner)->symbl == NULL))
        return -1;

    if (msg != NULL || symbl != NULL)
        if ((*spinner)->config(spinner, msg, symbl) < 0)
            return -2;

    switch ((*spinner)->pid = fork()) {
        case    -1:
            return -3;
        case    0:
            do_animation(*spinner);
            exit(0);
        default:
            break;
    }

    return 0;
}

static
void do_animation(SPINNER* spinner)
{
    int     size    = 0;

    char*   symbl   = NULL;

    setlocale(LC_CTYPE, "");
    mblen(NULL, 0);
    while (1) {
        symbl = spinner->symbl;
        while (*symbl) {
            size = mblen(symbl, MB_CUR_MAX);
            fprintf(stdout, "%.*s %s",
                    size, symbl, spinner->msg);
            fflush(stdout);
            sleep(1);
            fprintf(stdout, "\r");
            symbl += size;
        }
    }

    return;
}

static
int done_spinner(SPINNER* spinner)
{
    if (spinner->pid < 0)
        return -1;

    kill(spinner->pid, SIGKILL);
    waitpid(spinner->pid, NULL, 0);
    fprintf(stdout, "\x1b[2K\r");

    return 0;
}

static
void release_spinner(SPINNER* spinner)
{
    if (spinner != NULL) {
        release_msg(spinner);
        release_symbl(spinner);
        free(spinner);
        spinner = NULL;
    }

    return;
}

static
void release_msg(SPINNER* spinner)
{
    if (spinner->msg != NULL) {
        free(spinner->msg);
        spinner->msg = NULL;
    }

    return;
}

static
void release_symbl(SPINNER* spinner)
{
    if (spinner->symbl != NULL) {
        free(spinner->symbl);
        spinner->symbl = NULL;
    }

    return;
}

static
int copy_message(SPINNER** spinner, const char* msg)
{
    size_t  len     = 0;

    len = strlen(msg);
    if (((*spinner)->msg = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL) {
        return -1;
    } else {
        memcpy((*spinner)->msg, msg, len);
        *((*spinner)->msg + len) = '\0';
    }

    return 0;
}

static
int copy_symbol(SPINNER** spinner, const char* symbl)
{
    size_t  len     = 0;

    len = strlen(symbl);
    if (((*spinner)->symbl = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL) {
        return -1;
    } else {
        memcpy((*spinner)->symbl, symbl, len);
        *((*spinner)->symbl + len) = '\0';
    }

    return 0;
}
