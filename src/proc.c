/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * proc.c
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./proc.h"
#include "./string.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define DELIMITER   " "

static int set_cmd_proc(PROC** proc, const char* cmd);
static int exec_proc(PROC* proc);
static int exec_ready_proc(PROC* proc);
static void release_proc(PROC* proc);
static void release_argv_proc(PROC* proc);

int init_proc(PROC** proc)
{
    PROC*   prc     = NULL;
    
    if ((prc = (PROC*)
                malloc(sizeof(PROC))) == NULL) {
        return -1;
    } else {
        prc->argc       = 0;
        prc->argv       = NULL;
        prc->envp       = NULL;
        prc->set        = set_cmd_proc;
        prc->exec       = exec_proc;
        prc->ready      = exec_ready_proc;
        prc->release    = release_proc;
    }
    *proc = prc;

    return 0;
}

int simple_exec(const char* cmd)
{
    int     status  = 0;

    PROC*   proc    = NULL;

    do {
        if (init_proc(&proc) < 0) {
            status = -1; break;
        }
        if (proc->set(&proc, cmd) < 0) {
            status = -2; break;
        }
        if (proc->ready(proc) < 0) {
            status = -3; break;
        }
        if (proc->exec(proc) < 0) {
            status = -4; break;
        }
    } while (0);

    switch (status) {
        case    -1:
            break;
        case    -2:
        case    -3:
        case    -4:
            proc->release(proc);
            break;
    }

    return status;
}

static
int set_cmd_proc(PROC** proc, const char* cmd)
{
    int     status  = 0;

    size_t  len     = 0;

    char*   tok     = NULL,
        *   cmd2    = NULL;

    if ((len = strlen(cmd)) == 0) {
        status = -1; goto ERR;
    }
    if ((cmd2 = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL) {
        status = -2; goto ERR;
    } else {
        memcpy(cmd2, cmd, len);
        *(cmd2 + len) = '\0';
    }

    if ((*proc)->argv != NULL) {
        release_argv_proc(*proc);
        (*proc)->argc = 0;
        (*proc)->argv = NULL;
    }
    if (((*proc)->argv = (char**)
                malloc(sizeof(char*) * sysconf(_SC_ARG_MAX))) == NULL) {
        status = -2; goto ERR;
    }

    tok = mbstrtok(cmd2, DELIMITER);
    while (tok != NULL) {
        if ((len = strlen(tok)) > 0) {
            if ((*((*proc)->argv + (*proc)->argc) = (char*)
                        malloc(sizeof(char) * (len + 1))) == NULL) {
                status = -3; goto ERR;
            }
            memcpy(*((*proc)->argv + (*proc)->argc), tok, len);
            *(*((*proc)->argv + (*proc)->argc) + len) = '\0';
            (*proc)->argc++;
        }
        tok = mbstrtok(NULL, DELIMITER);
    }
    *((*proc)->argv + (*proc)->argc) = NULL;

    return 0;

ERR:
    switch (status) {
        case    -1:
        case    -2:
            break;
        case    -3:
            release_argv_proc(*proc);
            (*proc)->argc = 0;
            (*proc)->argv = NULL;
            break;
    }

    return status;
}

#ifdef  _GNU_SOURCE
static
int exec_proc(PROC* proc)
{
    if (proc->envp != NULL)
        return execvpe(*(proc->argv), proc->argv, proc->envp);
    else
        return execvp(*(proc->argv), proc->argv);
}
#else
static
int exec_proc(PROC* proc)
{
    return execvp(*(proc->argv), proc->argv);
}
/* _GNU_SOURCE */
#endif

static
int exec_ready_proc(PROC* proc)
{
    if (proc->argc > 0 && proc->argv != NULL)
        return 0;

    return -1;
}

static
void release_proc(PROC* proc)
{
    if (proc != NULL) {
        release_argv_proc(proc);
        free(proc);
        proc = NULL;
    }

    return;
}

static
void release_argv_proc(PROC* proc)
{
    if (proc->argv != NULL) {
        while (proc->argc >= 0) {
            if (*(proc->argv + proc->argc) != NULL) {
                free(*(proc->argv + proc->argc));
                *(proc->argv + proc->argc) = NULL;
            }
            proc->argc--;
        }
        free(proc->argv);
        proc->argv = NULL;
    }

    return;
}
