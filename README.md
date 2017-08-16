libbenly
===

[![license](https://img.shields.io/badge/License-WTFPL2-blue.svg?style=flat)](http://www.wtfpl.net/txt/copying/)

べんりライブラリの詰め合わせ。ギフトにも最適です。

## Install

```shellsession
% make
# make install
```


## Usage

```shellsession
% cat example.c
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
        fprintf(stdout, "%s\n", envt->envs[i]);

    release_env_t(envt);

    return 0;
}
% gcc example.c -o example -lbenly_env -lbenly_memory
% ./example
/usr/local/sbin
/usr/local/bin
/usr/sbin
/usr/bin
/sbin
/bin
```


## Function List

### env.h

```c
#include <benly/env.h>

typedef struct ENV_T {
    int     envc;
    char**  envs;
} env_t;

env_t* split_env(char* env);
void release_env_t(env_t* env);
```

### file.h

```c
#include <benly/file.h>

int check_file_type(char* filename);
int count_file_lines(FILE* fp);
int read_file(int lines, size_t length, char** buf, FILE* fp);
int p_count_file_lines(char** buf);
int p_read_file_char(char*** dest, int t_lines, size_t t_length, FILE* fp, int chomp);
int watch_fd(int fd, long timeout);

```

### memory.h

```c
#include <benly/memory.h>

char** malloc2d(int x, int y);
int init2d(char** buf, int x, int y);
void free2d(char** buf, int y);
```

### signal.h

```c
#include <benly/signal.h>

typedef struct SIGLIST_T {
    int     sig;
    void    (*func)(int sig);
} siglist_t;

/* This functions is required signal.c */
int set_signal(int sig, void (*func)(int sig));
int set_signal_siglist(siglist_t* siglist);
void handl_zombie_proc(void);
```

### string.h

```c
#include <benly/string.h>

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
#ifdef  WITH_GLIB
int mbstrlen_with_regex(char* src, regex_t* reg);
int strmax_with_regex(int val, char** src, regex_t* reg);
/* WITH_GLIB */
#endif
/* WITH_REGEX */
#endif
```

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

## License

[WTFPL version 2](http://www.wtfpl.net/txt/copying/)


## Author

sasairc (https://github.com/sasairc)
