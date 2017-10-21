/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * file.h
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef FILE_H
#define FILE_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <stdio.h>

extern int count_file_lines(FILE* fp);
extern int load_file_to_array(char*** dest, size_t th_x, size_t th_y, FILE* fp);
extern int file_is_binary(FILE* fp);
extern int watch_fd(int fd, long timeout);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* FILE_H */
#endif
