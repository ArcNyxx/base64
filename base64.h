/* see LICENCE file for licensing information */
/* base64 - simple encoding library */
#include <limits.h>
#if UCHAR_MAX != 255
#error `char` type does not hold 8 bits.
#endif /* UCHAR_MAX != 255 */

#ifndef BASE64_H
#define BASE64_H

#include <stdlib.h>

#define _STRING(x) #x
#define STRING(x) _STRING(x)
#define CHAR(x) *_STRING(x)

#define ENCODE_MAP_CHAR_62 -
#define ENCODE_MAP_CHAR_63 _
#define ENCODE_MAP \
"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
"abcdefghijklmnopqrstuvwxyz" \
"0123456789" \
STRING(ENCODE_MAP_CHAR_62) \
STRING(ENCODE_MAP_CHAR_63)

static const char *encodeMap = ENCODE_MAP;

#ifdef USE_EQUALS_SIGN_PADDING
/* returns length of base64 encoded string */
static inline size_t
get_encoded_length(const size_t length) {
	return ((length + 2) / 3) << 2;
}

/* returns length of decoded base64 string */
static inline size_t
get_decoded_length(const char *string, 
		const size_t length) {
	return (length >> 2) * 3 - (string[length - 1] == '=')
			- (string[length - 2] == '=');
}
#else
/* returns length of a base64 encoded string */
static inline size_t
get_encoded_length(const size_t length) {
	return length + ((length + 2) / 3);
}

/* returns length of decoded base64 string */
static inline size_t
get_decoded_length(const size_t length) {
	return length - ((length + 2) >> 2);
}
#endif /* USE_EQUALS_SIGN_PADDING */

char decode_char(const char ch);
void encode_base64(const char *restrict input,
	size_t length, char *restrict buffer);
void decode_base64(const char *restrict input,
	size_t length, char *restrict buffer);
char verify_base64(const char *string, size_t length);

#endif /* BASE64_H */
