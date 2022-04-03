/* base64 - simple encoding library
 * Copyright (C) 2021-2022 ArcNyxx
 * see LICENCE file for licensing information */

#include <limits.h>
#if UCHAR_MAX != 255
#error "'char' type does not hold 8 bits."
#endif /* UCHAR_MAX != 255 */

#ifndef _BASE64_H
#define _BASE64_H

#include <stdbool.h>
#include <stdlib.h>

#define _DOSTRING(x) #x
#define _STRING(x) _DOSTRING(x)
#define _CHAR(x) _STRING(x)[0]

#define ENCODE_MAP_CHAR_62 -
#define ENCODE_MAP_CHAR_63 _
#define ENCODE_MAP \
"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
"abcdefghijklmnopqrstuvwxyz" \
"0123456789" \
_STRING(ENCODE_MAP_CHAR_62) \
_STRING(ENCODE_MAP_CHAR_63)

static const char *encode_map = ENCODE_MAP;

#ifdef USE_EQUALS_SIGN_PADDING
size_t base64_encode_len(const size_t length);
size_t base64_decode_len(const char *string, const size_t length);
#else
size_t base64_encode_len(const size_t length);
size_t base64_decode_len(const size_t length);
#endif /* USE_EQUALS_SIGN_PADDING */

void base64_encode(const char *restrict input,
	size_t length, char *restrict buffer);
void base64_decode(const char *restrict input,
	size_t length, char *restrict buffer);
bool base64_verify(const char *string, size_t length);

#endif /* _BASE64_H */
