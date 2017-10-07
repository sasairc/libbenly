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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SP  " "

static int set_cmd_proc(PROC** proc, const char* cmd);
static int set_cmd_argv_proc(PROC** proc, char* const argv[]);
static pid_t fork_proc(PROC** proc);
static pid_t wait_proc(PROC** proc, int opts);
static int exec_proc(PROC* proc);
static int exec_ready_proc(PROC* proc);
static int kill_proc(PROC* proc, int sig);
static void release_proc(PROC* proc);
static void release_argv_proc(PROC* proc);
static char* mbstrtok(char* str, char* delimiter);

#ifdef  _GNU_SOURCE
#include <sys/syscall.h>

static pid_t rfork_proc(PROC** proc, unsigned long flags);
static int set_env_proc(PROC** proc, char* const envp[]);
static void unset_env_proc(PROC** proc);
static void release_env_proc(PROC* proc);
/* _GNU_SOURCE */
#endif

static int add_mproc(MPROC** mproc, PROC* proc);
static int del_mproc(MPROC** mproc, int proc_no);
static int fork_mproc(MPROC* mproc);
#ifdef  _GNU_SOURCE
static int rfork_mproc(MPROC* mproc, unsigned long flags);
/* _GNU_SOURCE */
#endif
static int is_parent_mproc(MPROC* mproc, int proc_no);
static int is_child_mproc(MPROC* mproc, int proc_no);
static int wait_mproc(MPROC** mproc, int opts);
static int exec_mproc(MPROC* mproc, int proc_no);
static int kill_mproc(MPROC* mproc, int proc_no, int sig);
static int killall_mproc(MPROC* mproc, int sig);
static void release_mproc(MPROC* mproc);

int init_proc(PROC** proc)
{
    PROC*   prc     = NULL;
    
    if ((prc = (PROC*)
                malloc(sizeof(PROC))) == NULL) {
        return -1;
    } else {
        prc->pid        = 0;
        prc->argc       = 0;
        prc->argv       = NULL;
        prc->envp       = NULL;
        prc->set        = set_cmd_proc;
        prc->setv       = set_cmd_argv_proc;
#ifdef  _GNU_SOURCE
        prc->set_env    = set_env_proc;
        prc->unset_env  = unset_env_proc;
        prc->rfork      = rfork_proc;
/* _GNU_SOURCE */
#endif
        prc->fork       = fork_proc;
        prc->wait       = wait_proc;
        prc->exec       = exec_proc;
        prc->ready      = exec_ready_proc;
        prc->kill       = kill_proc;
        prc->release    = release_proc;
        prc->status     = 0;
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

    if ((*proc)->argv != NULL) {
        release_argv_proc(*proc);
        (*proc)->argc = 0;
        (*proc)->argv = NULL;
    }
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
    if (((*proc)->argv = (char**)
                malloc(sizeof(char*) * sysconf(_SC_ARG_MAX))) == NULL) {
        status = -2; goto ERR;
    }

    tok = mbstrtok(cmd2, SP);
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
        tok = mbstrtok(NULL, SP);
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

static
int set_cmd_argv_proc(PROC** proc, char* const argv[])
{
    int     i       = 0,
            status  = 0;

    size_t  len     = 0;

    if ((*proc)->argv != NULL) {
        release_argv_proc(*proc);
        (*proc)->argc = 0;
        (*proc)->argv = NULL;
    }

    while (*(argv + (*proc)->argc) != NULL)
        (*proc)->argc++;

    if (((*proc)->argv = (char**)
            malloc(sizeof(char*) * ((*proc)->argc + 1))) == NULL) {
        status = -1; goto ERR;
    }
    while (i < (*proc)->argc) {
        len = strlen(*(argv + i));
        if ((*((*proc)->argv + i) = (char*)
                    malloc(sizeof(char) * (len + 1))) == NULL) {
            status = -2; goto ERR;
        }
        memcpy(*((*proc)->argv + i), *(argv + i), len);
        *(*((*proc)->argv + i) + len) = '\0';
        i++;
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

static
pid_t fork_proc(PROC** proc)
{
    (*proc)->pid = fork();

    return (*proc)->pid;
}

#ifdef  _GNU_SOURCE
static
pid_t rfork_proc(PROC** proc, unsigned long flags)
{
    (*proc)->pid = syscall(SYS_clone, flags, 0, 0, 0, 0);

    return (*proc)->pid;
}
/* _GNU_SOURCE */
#endif

static
pid_t wait_proc(PROC** proc, int opts)
{
    if (waitpid((*proc)->pid, &(*proc)->status, opts) < 0)
        return -1;

    return (*proc)->pid;
}

#ifdef  _GNU_SOURCE
static
int set_env_proc(PROC** proc, char* const env[])
{
    int     status  = 0;

    size_t  i       = 0,
            envc    = 0,
            len     = 0;

    if ((*proc)->envp != NULL) {
        release_env_proc(*proc);
        (*proc)->envp = NULL;
    }

    while (*(env + envc) != NULL)
        envc++;
    if (((*proc)->envp = (char**)
                malloc(sizeof(char*) * envc)) == NULL) {
        status = -1; goto ERR;
    }
    while (i < envc) {
        len = strlen(*(env + i));
        if ((*((*proc)->envp + i) = (char*)
                malloc(sizeof(char) * (len + 1))) == NULL) {
            status = -2; goto ERR;
        }
        memcpy(*((*proc)->envp + i), *(env + i), len);
        *(*((*proc)->envp + i) + len) = '\0';
        i++;
    }
    *((*proc)->envp + i) = NULL;

    return 0;

ERR:
    switch (status) {
        case    -1:
            break;
        case    -2:
            release_env_proc(*proc);
            (*proc)->envp = NULL;
            break;
    }

    return status;
}

static
void unset_env_proc(PROC** proc)
{
    if ((*proc)->envp != NULL) {
        release_env_proc(*proc);
        (*proc)->envp = NULL;
    }

    return;
}

static
void release_env_proc(PROC* proc)
{
    size_t  i   = 0;

    if (proc->envp != NULL) {
        while (*(proc->envp + i) != NULL) {
            free(*(proc->envp + i));
            *(proc->envp + i) = NULL;
            i++;
        }
        free(proc->envp);
        proc->envp = NULL;
    }

    return;
}
/* _GNU_SOURCE */
#endif

#ifdef  _GNU_SOURCE
static
int exec_proc(PROC* proc)
{
    if (proc->ready(proc) < 0)
        return -1;

    if (proc->envp != NULL)
        return execvpe(*(proc->argv), proc->argv, proc->envp);
    else
        return execvp(*(proc->argv), proc->argv);
}
#else
static
int exec_proc(PROC* proc)
{
    if (proc->ready(proc) < 0)
        return -1;

    return execvp(*(proc->argv), proc->argv);
}
/* _GNU_SOURCE */
#endif

static
int exec_ready_proc(PROC* proc)
{
    if (proc->argc <= 0 || proc->argv == NULL)
        return -1;

    return 0;
}

static
int kill_proc(PROC* proc, int sig)
{
    if (proc->pid < 0)
        return -1;

    return kill(proc->pid, sig);
}

static
void release_proc(PROC* proc)
{
    if (proc != NULL) {
#ifdef  _GNU_SOURCE
        if (proc->envp != NULL) {
            release_env_proc(proc);
        }
/* _GNU_SOURCE */
#endif
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

int init_mproc(MPROC** mproc)
{
    MPROC*  mprc    = NULL;

    if ((mprc = (MPROC*)
                malloc(sizeof(MPROC))) == NULL) {
        return -1;
    } else {
        mprc->procs     = 0;
        mprc->proc_no   = 0;
        mprc->add       = add_mproc;
        mprc->del       = del_mproc;
        mprc->fork      = fork_mproc;
#ifdef  _GNU_SOURCE
        mprc->rfork     = rfork_mproc;
/* _GNU_SOURCE */
#endif
        mprc->is_parent = is_parent_mproc;
        mprc->is_child  = is_child_mproc;
        mprc->exec      = exec_mproc;
        mprc->wait      = wait_mproc;
        mprc->kill      = kill_mproc;
        mprc->killall   = killall_mproc;
        mprc->release   = release_mproc;
    }
    *mproc = mprc;

    return 0;
}

static
int add_mproc(MPROC** mproc, PROC* proc)
{
    if ((*mproc)->procs >= MPROC_MAX)
        return -1;

    (*mproc)->proc[(*mproc)->procs] = proc;
    (*mproc)->procs++;

    return 0;
}

static
int del_mproc(MPROC** mproc, int proc_no)
{
    if ((*mproc)->procs <= 0)
        return -1;

    while (proc_no < (*mproc)->procs &&
            ((*mproc)->proc[proc_no] = (*mproc)->proc[proc_no + 1]))
        proc_no++;
    (*mproc)->procs--;

    return 0;
}

static
int fork_mproc(MPROC* mproc)
{
    int     proc_no = 0;

    for (proc_no = 0;
            proc_no < mproc->procs &&
            (mproc->proc_no = mproc->proc[proc_no]->fork(&mproc->proc[proc_no])); proc_no++);

    return proc_no;
}

#ifdef  _GNU_SOURCE
static
int rfork_mproc(MPROC* mproc, unsigned long flags)
{
    int     proc_no = 0;

    for (proc_no = 0;
            proc_no < mproc->procs &&
            (mproc->proc_no = mproc->proc[proc_no]->rfork(&mproc->proc[proc_no], flags)); proc_no++);

    return proc_no;
}
/* _GNU_SOURCE */
#endif

static
int is_parent_mproc(MPROC* mproc, int proc_no)
{
    if (mproc->procs == proc_no)
        return 1;

    return 0;
}

static
int is_child_mproc(MPROC* mproc, int proc_no)
{
    return !mproc->is_parent(mproc, proc_no);
}

static
int exec_mproc(MPROC* mproc, int proc_no)
{
    return mproc->proc[proc_no]->exec(mproc->proc[proc_no]);
}

static
int wait_mproc(MPROC** mproc, int opts)
{
    int     i   = 0;

    while (i < (*mproc)->procs) {
        (*mproc)->proc[i]->wait(&(*mproc)->proc[i], opts);
        i++;
    }

    return 0;
}

static
int kill_mproc(MPROC* mproc, int proc_no, int sig)
{
    if (proc_no >= mproc->procs)
        return -1;

    return mproc->proc[proc_no]->kill(mproc->proc[proc_no], sig);
}

static
int killall_mproc(MPROC* mproc, int sig)
{
    int     i   = 0;

    while (i < mproc->procs) {
        if ((mproc->proc[i]->kill(mproc->proc[i], sig)) < 0)
            return -1;
        i++;
    }

    return 0;
}

static
void release_mproc(MPROC* mproc)
{
    int     i   = 0;

    if (mproc != NULL) {
        while (i < mproc->procs) {
            if (mproc->proc[i] != NULL) {
                mproc->proc[i]->release(mproc->proc[i]);
                mproc->proc[i] = NULL;
                i++;
            }
        }
        free(mproc);
        mproc = NULL;
    }

    return;
}

static
char* mbstrtok(char* str, char* delimiter)
{
    static  char*   ptr = NULL;
            char*   bdy = NULL;

    if (!str)
        str = ptr;

    if (!str)
        return NULL;

    if ((bdy = strstr(str, delimiter)) != NULL) {
        *bdy = '\0';
        ptr = bdy + strlen(delimiter);
    } else {
        ptr = NULL;
    }

    return str;
}
