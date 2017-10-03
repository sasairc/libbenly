libbenly
===

[![version](http://img.shields.io/github/tag/sasairc/libbenly.svg?style=flat&label=version)](https://github.com/sasairc/libbenly/releases)
[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](https://raw.githubusercontent.com/sasairc/libbenly/master/LICENSE)
[![language](https://img.shields.io/badge/language-C%2FC%2B%2B-lightgrey.svg)]()
[![build](https://img.shields.io/travis/sasairc/libbenly.svg?style=flat)](https://travis-ci.org/sasairc/libbenly)

libbenly (便利) - less a misc than a poor library.

## Install

```shellsession
% make
% make WITH_GLIB=1    # build with libglib-2 support
% make WITH_GLIB=0    # build without libglib-2 support
% make WITH_REGEX=1   # build with POSIX Regular expression matching types (regex.h)
% make WITH_REGEX=0   # build without POSIX Regular expression matching types (regex.h)
% make CMDLINE=1      # verbose mode
% make CMDLINE=0      # silent mode
# make install
```

## Usage

### sample 1

```c
/*
 * example1.c
 */
#include <stdio.h>
#include <benly/env.h>

int main(void)
{
    int     i       = 0;
    char*   str     = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin\0";
    env_t*  envt    = NULL;

    if (split_env(str, &envt) < 0)
        return 1;

    for (i = 0; i < envt->envc; i++)
        fprintf(stdout, "%s\n",
            *(envt->envs + i));

    release_env_t(envt);

    return 0;
}
```

```shellsession
% gcc example1.c -o example1 -lbenly_env -lbenly_memory
% ./example1
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
```

### sample 2

```c
/*
 * example2.c
 */
#include <benly/proc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    PROC*   proc    = NULL;

    int     n       = 12;

    /* command line */
    char*   cmd     = "date -d tomorrow";

    /* environment */
    char*   utc[]   = {
        "LANG=C", "TZ=UTC", NULL,
    };
    char*   fra[]   = {
        "LANG=fr_FR.UTF-8", "TZ=Paris", NULL,
    };

    init_proc(&proc);
    proc->set(&proc, cmd);
    while (n > 0) {
        if (!(n % 2))
            proc->unset_env(&proc);
        else if (!(n % 3))
            proc->set_env(&proc, fra);
        else
            proc->set_env(&proc, utc);

        switch (proc->fork(&proc)) {
            case    0:
                proc->exec(proc);
                exit(0);
            default:
                proc->wait(proc, 0);
        }
        n--;
    }
    proc->release(proc);

    return 0;
}
```

```shellsession
% gcc example2.c -o example2 -lbenly_memory -lbenly_string -lbenly_proc -D_GNU_SOURCE
% ./example2
2017年 10月  4日 水曜日 17:40:28 JST
Wed Oct  4 08:40:28 UTC 2017
2017年 10月  4日 水曜日 17:40:28 JST
mercredi 4 octobre 2017, 08:40:28 (UTC+0000)
2017年 10月  4日 水曜日 17:40:28 JST
Wed Oct  4 08:40:28 UTC 2017
2017年 10月  4日 水曜日 17:40:28 JST
Wed Oct  4 08:40:28 UTC 2017
2017年 10月  4日 水曜日 17:40:28 JST
mercredi 4 octobre 2017, 08:40:28 (UTC+0000)
2017年 10月  4日 水曜日 17:40:28 JST
Wed Oct  4 08:40:28 UTC 2017
```

## Function List

### cmd.h

```c
#include <benly/cmd.h>

#define TCOM    1   /* command */
#define TPAREN  2   /* a ; b */
#define TPIPE   3   /* a | b */
#define TAND    4   /* a && b */
#define TOR     5   /* a || b*/

#define IOREAD  1   /* < */
#define IOHERE  2   /* << */
#define IOWRITE 3   /* > */
#define IOCAT   4   /* >> */

typedef struct IO_T {
    short   io_unit;
    short   io_flag;
    char*   io_name;
} io_t;

typedef struct CMD_T {
    int             type;
    char**          args;
    struct IO_T*    io;
    struct CMD_T*   next;
    struct CMD_T*   prev;
} cmd_t;

cmd_t* add_cmdline_t(cmd_t** cmd);
int set_io_val(char* str, int flag, cmd_t** cmd);
int set_cmd_val(char* str, int type, cmd_t** cmd);
int parse_cmdline(char* str, cmd_t** dest_cmd, cmd_t** dest_start);
int file_redirect(cmd_t* cmd);
int check_file_stat(cmd_t* cmd, int is_redirect, mode_t chk);
int exec_cmd(cmd_t* cmd, int ret, int in_fd);
int mwait(void);
void redirect(int oldfd, int newfd);
void release_cmd_t(cmd_t* cmd);
```

### env.h

```c
#include <benly/env.h>

typedef struct ENV_T {
    int     envc;
    char**  envs;
} env_t;

int split_env(char* env, env_t** dest);
void release_env_t(env_t* env);
```

### file.h

```c
#include <benly/file.h>

int p_count_file_lines(char** buf);
int p_read_file_char(char*** dest, int t_lines, size_t t_length, FILE* fp, int chomp);
int file_is_binary(FILE* fp);
int watch_fd(int fd, long timeout);
```

### memory.h

```c
#include <benly/memory.h>

void* smalloc(size_t size, const char* fmt, ...);
void* srealloc(void* ptr, size_t size, const char* fmt, ...);
void free2d(char** buf, int y);
```

### proc.h

```c
#include <benly/proc.h>

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

int init_proc(PROC** proc);
int simple_exec(const char* cmd);
```

### signal.h

```c
#include <benly/signal.h>

typedef struct SIGLIST_T {
    int     sig;
    void    (*func)(int sig);
} siglist_t;

int set_signal(int sig, void (*func)(int sig));
int set_signal_siglist(siglist_t* siglist);
void handl_zombie_proc(void);
```

### string.h

```c
#include <benly/string.h>

int strisdigit(char* str);
int strrep(char* src, char* haystack, char* needle);
char* strlion(int argnum, ...);
int mbstrlen(char* src);
int strunesc(char* src);
int strmax(int val, char** src);
int strlftonull(char* str);
char** str_to_args(char* str);
char* mbstrtok(char* str, char* delimiter);
int trim(char* str);
int strcmp_lite(const char* str1, const char* str2);

#ifdef  WITH_REGEX
#include <regex.h>
int mbstrlen_with_regex(char* src, regex_t* reg);
int strmax_with_regex(int val, char** src, regex_t* reg);
/* WITH_REGEX */
#endif
```


## License

[WTFPL version 2](http://www.wtfpl.net/txt/copying/)


## Author

sasairc (https://github.com/sasairc)
