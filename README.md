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
% make WITH_GNU=1     # build with GNU C Extensions support
% make WITH_GNU=0     # build without GNU C Extensions support
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
% gcc example1.c -o example1 -lbenly_env
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
#define _GNU_SOURCE

#include <benly/proc.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
/* #include <linux/sched.h> */

int main(void)
{
    PROC*   proc[MPROC_MAX];    /* MPROC_MAX 32 (default) */

    MPROC*  mproc   = NULL;

    int     n       = 0;

    /* commands */
    char*   cmd[]       = {
        "date -d tomorrow",
        "nocommand",
    };

    /* environments */
    char*   fra[]   = {
        "LANG=fr_FR.UTF-8", "TZ=Europe/Paris", NULL,
    };
    char*   gbr[]   = {
        "LANG=en_GB.UTF-8", "TZ=Europe/London", NULL,
    };
    char*   deu[]   = {
        "LANG=de_DE.UTF-8", "TZ=Europe/Berlin", NULL,
    };
    char*   jpn[]   = {
        "LANG=ja_JP.UTF-8", "TZ=Asia/Tokyo", NULL,
    };
    char*   ita[]   = {
        "LANG=it_IT.UTF-8", "TZ=Europe/Rome", NULL,
    };
    char*   rus[]   = {
        "LANG=ru_RU.UTF-8", "TZ=Europe/Moscow", NULL,
    };
    char**  tzs[]   = {
        fra, gbr, deu, jpn, ita, rus, NULL,
    };

    /*
     * date command
     */
    init_mproc(&mproc);
    while (*(tzs + n) != NULL) {
        init_proc(&proc[n]);
        (*proc)->set_env(proc + n, *(tzs + n));
        (*proc)->set(proc + n, *cmd);
        mproc->add(&mproc, *(proc + n));
        n++;
    }

    /*
     * no command
     */
    init_proc(&proc[n]);
    (*proc)->set(proc + n, *(cmd + 1));
    mproc->add(&mproc, *(proc + n));

    /*
     * create child process
     */
    n = mproc->rfork(mproc, SIGCHLD);
    if (mproc->is_parent(mproc, n)) {
        sleep(1);
        mproc->wait(&mproc, 0);
    } else {
        mproc->exec(mproc, n);
        exit(1);
    }

    /*
     * returns the exit status of the child
     */
    n = 0;
    while (n < mproc->procs) {
        fprintf(stdout, "proc_no = %d, exit status = %d\n",
                n, WEXITSTATUS(mproc->proc[n]->status));
        n++;
    }
    mproc->release(mproc);

    return 0;
}
```

```shellsession
% gcc example2.c -o example2 -lbenly_proc
% ./example2
Fri  6 Oct 07:54:35 BST 2017
Fr 6. Okt 08:54:35 CEST 2017
2017年 10月  6日 金曜日 15:54:35 JST
vendredi 6 octobre 2017, 08:54:35 (UTC+0200)
Пт окт  6 09:54:35 MSK 2017
ven  6 ott 2017, 08.54.35, CEST
proc_no = 0, exit status = 0
proc_no = 1, exit status = 0
proc_no = 2, exit status = 0
proc_no = 3, exit status = 0
proc_no = 4, exit status = 0
proc_no = 5, exit status = 0
proc_no = 6, exit status = 1
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

### column.h

```c
#include <benly/column.h>

int tablize(char** const array[]);
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

int count_file_lines(FILE* fp);
int load_file_to_array(char*** dest, size_t th_x, size_t th_y, FILE* fp);
int file_is_binary(FILE* fp);
int watch_fd(int fd, long timeout);
```

### hash.h

```c
#include <benly/hash.h>

#ifndef DEFAULT_ELEM_SIZE
#define DEFAULT_ELEM_SIZE   32
/* DEFAULT_ELEM_SIZE */
#endif

typedef struct SHASH {
    int     elemc;
    char*** elem;
    int     (*put)(struct SHASH** shash, const char* key, const char* value);
    char*   (*get)(struct SHASH* shash, const char* key);
    int     (*getv)(struct SHASH* shash, const char* key, char** ptr);
    char**  (*keys)(struct SHASH* shash);
    char**  (*values)(struct SHASH* shash);
    int     (*is_empty)(struct SHASH* shash);
    int     (*size)(struct SHASH* shash);
    int     (*exists)(struct SHASH* shash, const char* key);
    void    (*remove)(struct SHASH** shash, const char* key);
    void    (*clear)(struct SHASH** shash);
    void    (*release)(struct SHASH* shash);
    size_t  elem_size;  /* realloc(): elem_size += DEFAULT_ELEM_SIZE */
} SHASH;

int init_shash(SHASH** shash);
SHASH* new_shash(void);
SHASH* clone_shash(SHASH* shash);
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

#ifndef MPROC_MAX
#define MPROC_MAX   32
/* MPROC_MAX */
#endif

#define IS_PARENT(a,b) (a->procs == b)

typedef struct PROC {
    pid_t   pid;
    int     argc;
    char**  argv;
    char**  envp;
    int     (*set)(struct PROC** proc, const char* cmd);
    int     (*setv)(struct PROC** proc, char* const argv[]);
#ifdef  _GNU_SOURCE
    int     (*set_env)(struct PROC** proc, char* const envp[]);
    void    (*unset_env)(struct PROC** proc);
    pid_t   (*rfork)(struct PROC** proc, unsigned long flags);
/* _GNU_SOURCE */
#endif
    pid_t   (*fork)(struct PROC** proc);
    pid_t   (*wait)(struct PROC** proc, int opts);
    int     (*exec)(struct PROC* proc);
    int     (*ready)(struct PROC* proc);
    int     (*kill)(struct PROC* proc, int sig);
    void    (*release)(struct PROC* proc);
    int     status;
} PROC;

typedef struct MPROC {
    PROC**  proc;
    int     procs;
    int     proc_no;
    int     (*add)(struct MPROC** mproc, PROC* proc);
    int     (*del)(struct MPROC** mproc, int proc_no);
    int     (*fork)(struct MPROC* mproc);
#ifdef  _GNU_SOURCE
    int     (*rfork)(struct MPROC* mproc, unsigned long flags);
/* _GNU_SOURCE */
#endif
    int     (*is_parent)(struct MPROC* mproc, int proc_no);
    int     (*is_child)(struct MPROC* mproc, int proc_no);
    int     (*exec)(struct MPROC* mproc, int proc_no);
    int     (*wait)(struct MPROC** mproc, int opts);
    int     (*kill)(struct MPROC* mproc, int proc_no, int sig);
    int     (*killall)(struct MPROC* mproc, int sig);
    void    (*release)(struct MPROC* mproc);
} MPROC;

int init_proc(PROC** proc);
int init_mproc(MPROC** mproc);
int simple_exec(const char* cmd);
```

The cloning flags is defined in the file *linux/sched.h*.

### spinner.h

```c
#include <benly/spinner.h>

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

int init_spinner(SPINNER** spinner);
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

### typestring.h

```c
#include <benly/typestring.h>

#ifndef T_STRING_DEFAULT_ALLOC_SIZE
#define T_STRING_DEFAULT_ALLOC_SIZE 1024
/* T_STRING_DEFAULT_ALLOC_SIZE */
#endif

#ifndef  T_STRING_LOCALE_VALUE
#define T_STRING_LOCALE_VALUE   ""
/* T_STRING_DEFAULT_LOCALE_VALUE */
#endif

/*
 * typestring_errno
 */
#define EOUTOFRANGE         -1
#define EINVALIDCHAR        -2
#define EMEMORYALLOC        -3
#define ESTRISEMPTY         -4
#define EARGISNULPTR        -5

/*
 * string_errno check macros
 *
 * e.g.  if (WOUTOFRANGE(string_errno)) {
 *           ....
 *       }
 */
#define WOUTOFRANGE(x)      ((x) == EOUTOFRANGE)
#define WINVALIDCHAR(x)     ((x) == EINVALIDCHAR)
#define WMEORYALLOC(x)      ((x) == EMEMORYALLOC)
#define WSTRISEMPTY(x)      ((x) == ESTRISEMPTY)
#define WEARGISNULPTR(x)    ((x) == EARGISNULPTR)

extern int* wrap_type_string_errno(void);
#define string_errno    (*wrap_type_string_errno())

typedef struct STRING STRING;

typedef struct STRING {
    size_t  alloc_size;
    size_t  length;
    char*   string;
    size_t  (*size)(STRING* self);
    size_t  (*mblen)(STRING* self);
    size_t  (*capacity)(STRING* self);
    size_t  (*count)(STRING* self, char* const str);
    size_t  (*reconf)(STRING** self, size_t n);
    int     (*reserve)(STRING** self, size_t s);
    int     (*shrink_to_fit)(STRING** self);
    int     (*resize)(STRING** self, size_t n, char const c);
    int     (*assign)(STRING** self, char* const str);
    int     (*append)(STRING** self, char* const str);
    int     (*push_back)(STRING** self, char const c);
    void    (*pop_back)(STRING** self);
    void    (*swap)(STRING** s1, STRING** s2);
    int     (*insert)(STRING** self, size_t pos, char* const str);
    int     (*erase)(STRING** self, size_t pos, size_t n);
    int     (*empty)(STRING* self);
    char    (*at)(STRING* self, size_t pos);
    char    (*front)(STRING* self);
    char    (*back)(STRING* self);
    char*   (*c_str)(STRING* self);
    int     (*copy)(STRING* self, STRING** dest);
    size_t  (*c_copy)(STRING* self, char** dest);
    int     (*substr)(STRING* self, size_t pos, size_t n, STRING** dest);
    int     (*c_substr)(STRING* self, size_t pos, size_t n, char** dest);
    size_t  (*split)(STRING* self, char* const delim, STRING*** dest);
    size_t  (*c_split)(STRING* self, char* const delim, char*** dest);
    int     (*to_char_arr)(STRING* self, char*** dest);
    int     (*compare)(STRING* self, STRING* opp);
    int     (*c_compare)(STRING* self, const char* s);
    int     (*casecmp)(STRING* self, STRING* opp);
    int     (*c_casecmp)(STRING* self, char* const s);
    int     (*concat)(STRING** self, STRING* opp, ...);
    int     (*c_concat)(STRING** self, char* const s, ...);
    size_t  (*chomp)(STRING** self);
    size_t  (*lstrip)(STRING** self);
    size_t  (*rstrip)(STRING** self);
    int     (*rjust)(STRING** self, size_t s, char c);
    int     (*ljust)(STRING** self, size_t s, char c);
    int     (*center)(STRING** self, size_t s, char c);
    int     (*mbrjust)(STRING** self, size_t s, char c);
    int     (*mbljust)(STRING** self, size_t s, char c);
    int     (*mbcenter)(STRING** self, size_t s, char c);
    int     (*downcase)(STRING** self);
    int     (*upcase)(STRING** self);
    int     (*swapcase)(STRING** self);
    int     (*capitalize)(STRING** self);
    int     (*include)(STRING* self, char* const str);
    int     (*slice)(STRING** self, char* const str);
    int     (*delete_prefix)(STRING** self, char* const str);
    int     (*delete_suffix)(STRING** self, char* const str);
    int     (*to_i)(STRING* self, int base);
    long    (*to_l)(STRING* self, int base);
    float   (*to_f)(STRING* self);
    int     (*reverse)(STRING** self);
    int     (*ascii_only)(STRING* self);
    int     (*each_line)(STRING* self, char* const delim, void (*fn)(STRING*));
    int     (*each_byte)(STRING* self, void (*fn)(char));
    int     (*each_char)(STRING* self, void (*fn)(char*));
    int     (*each_codepoint)(STRING* self, void (*fn)(uint32_t));
    void    (*clear)(STRING** self);
    void    (*release)(STRING* self);
} STRING;

STRING* new_string(char* const str);
int fgetline(FILE* fp, STRING** s);
int fputline(FILE* fp, STRING* s);
void release_char_arr(STRING* self, size_t n, char** arr);
```

The value in *string_errno* is significant only when the return value of the call indicated an error from most library functions.

### uri.h

```c
#include <benly/uri.h>

int encode_uri(char* const src, char** dest);
int decode_uri(char* const src, char** dest);
```

## License

[WTFPL version 2](http://www.wtfpl.net/txt/copying/)


## Author

sasairc (https://github.com/sasairc)
