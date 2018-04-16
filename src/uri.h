/*
 * libbenly (便利) - less a misc than a poor library.
 *
 * uri.h
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef URI_H
#define URI_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

extern int encode_uri(char* const src, char** dest);
extern int decode_uri(char* const src, char** dest);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* URI_H */
#endif
