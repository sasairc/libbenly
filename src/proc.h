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

typedef struct PROC {
    int     argc;
    char**  argv;
    char**  envp;
    int     (*set)(struct PROC** proc, const char* cmd);
    int     (*exec)(struct PROC* proc);
    int     (*ready)(struct PROC* proc);
    void    (*release)(struct PROC* proc);
} PROC;

extern int init_proc(PROC** proc);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* BENLY_PROC_H */
#endif
