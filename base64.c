/* base64 - simple encoding library
 * Copyright (C) 2021-2022 FearlessDoggo21
 * see LICENCE file for licensing information */

#include <ctype.h>
#include <stdint.h>

#include "base64.h"

static char decode_char(const char ch);

static char
decode_char(const char ch) {
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A';
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;
	return 63 - (ch == _CHAR(ENCODE_MAP_CHAR_62));
}

#ifdef USE_EQUALS_SIGN_PADDING
size_t
base64_encode_len(const size_t length)
{
	return ((length + 2) / 3) * 4;
}

size_t
base64_decode_len(const char *string, const size_t length)
{
	return (length / 4) * 3 - (string[length - 1] == '=') -
			(string[length - 2] == '=');
}
#else
size_t
base64_encode_len(const size_t length)
{
	return length + ((length + 2) / 3);
}

size_t
base64_decode_len(const size_t length)
{
	return length - ((length + 2) / 4);
}
#endif /* USE_EQUALS_SIGN_PADDING */

void
base64_encode(const char *restrict input, size_t length,
		char *restrict buffer)
{
	uint32_t storage = 0;
	while (length >= 3) {
		storage |= (*input++) << 16;
		storage |= (*input++) << 8;
		storage |= *input++;

		*buffer++ = encode_map[storage >> 18];
		*buffer++ = encode_map[(storage >> 12) & 0x3F];
		*buffer++ = encode_map[(storage >> 6) & 0x3F];
		*buffer++ = encode_map[storage & 0x3F];

		storage = 0;
		length -= 3;
	}

	if (!length)
		return;

	storage |= (*input++) << 16;
	*buffer++ = encode_map[storage >> 18];
	if (!--length) {
		*buffer++ = encode_map[(storage >> 12) & 0x3F];
#ifdef USE_EQUALS_SIGN_PADDING
		*buffer++ = '=';
		*buffer = '=';
#endif
		return;
	}

	storage |= (*input++) << 8;
	*buffer++ = encode_map[(storage >> 12) & 0x3F];
	if (!--length) {
		*buffer++ = encode_map[(storage >> 6) & 0x3F];
#ifdef USE_EQUALS_SIGN_PADDING
		*buffer = '=';
#endif
		return;
	}

	storage |= *input;
	*buffer++ = encode_map[(storage >> 6) & 0x3F];
	*buffer = encode_map[storage & 0x3F];
}

void
base64_decode(const char *restrict input,
	size_t length, char *restrict buffer)
{
#ifdef USE_EQUALS_SIGN_PADDING
	length -= (input[length - 1] == '=') +
			(input[length - 2] == '=');
#endif

	uint32_t storage = 0;
	while (length >= 4) {
		storage |= decode_char(*input++) << 18;
		storage |= decode_char(*input++) << 12;
		storage |= decode_char(*input++) << 6;
		storage |= decode_char(*input++);

		*buffer++ = storage >> 16;
		*buffer++ = (char)(storage >> 8);
		*buffer++ = (char)storage;

		storage = 0;
		length -= 4;
	}

	if (!length)
		return;

	storage |= decode_char(*input++) << 18;
	storage |= decode_char(*input++) << 12;
	*buffer++ = storage >> 16;
	if (!(length - 2))
		return;

	storage |= decode_char(*input++) << 6;
	*buffer++ = (char)(storage >> 8);
	if (!(length - 3))
		return;

	storage |= decode_char(*input) << 6;
	*buffer = (char)storage;
}

bool
base64_verify(const char *string, size_t length)
{
	for (size_t index = 0; index < length; index++) {
		char temp = string[index];
		if (!(isalnum(temp) || temp == _CHAR(ENCODE_MAP_CHAR_62) ||
				temp == _CHAR(ENCODE_MAP_CHAR_63))) {
#ifdef USE_EQUALS_SIGN_PADDING
			/* if equals sign and length is next or next is
			 * another equals sign and length follows */
			if (temp == '=' && ((string[index + 1] == '=' &&
					index + 2 == length) || index + 1 == length))
				return true
#endif
			return false;
		}
	}
	return true;
}
