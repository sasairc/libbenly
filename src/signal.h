/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * signal.h 
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef SIGNAL_H
#define SIGNAL_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

typedef struct SIGLIST_T {
    int     sig;
    void    (*func)(int sig);
} siglist_t;

extern int set_signal(int sig, void (*func)(int sig));
extern int set_signal_siglist(siglist_t* siglist);
extern void handl_zombie_proc(void);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* SIGNAL_H */
#endif
