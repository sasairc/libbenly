/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * proc.h
 *
 * Copyright (c) 2017 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef BENLY_PROC_H
#define BENLY_PROC_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <unistd.h>

typedef struct PROC {
    pid_t   pid;
    int     argc;
    char**  argv;
    char**  envp;
    int     (*set)(struct PROC** proc, const char* cmd);
#ifdef  _GNU_SOURCE
    int     (*set_env)(struct PROC** proc, char* const envp[]);
    void    (*unset_env)(struct PROC** proc);
/* _GNU_SOURCE */
#endif
    pid_t   (*fork)(struct PROC** proc);
    int     (*wait)(struct PROC* proc, int opts);
    int     (*exec)(struct PROC* proc);
    int     (*ready)(struct PROC* proc);
    void    (*release)(struct PROC* proc);
} PROC;

extern int init_proc(PROC** proc);
extern int simple_exec(const char* cmd);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* BENLY_PROC_H */
#endif
