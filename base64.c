/*
 * base64 - simple encoding library
 * Copyright (C) 2021 FearlessDoggo21
 * see LICENCE file for licensing information
 */

#include <ctype.h>
#include <stdint.h>

#include "base64.h"

char
decode_char(const char ch) {
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A';
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;
	return 63 - (ch == CHAR(ENCODE_MAP_CHAR_62));
}

void
encode_base64(const char *restrict input,
	size_t length, char *restrict buffer) {
	uint32_t storage = 0;
	while (length >= 3) {
		storage |= (*input++) << 16;
		storage |= (*input++) << 8;
		storage |= *input++;

		*buffer++ = encodeMap[storage >> 18];
		*buffer++ = encodeMap[(storage >> 12) & 0x3F];
		*buffer++ = encodeMap[(storage >> 6) & 0x3F];
		*buffer++ = encodeMap[storage & 0x3F];

		storage = 0;
		length -= 3;
	}

	if (!length)
		return;

	storage |= (*input++) << 16;
	*buffer++ = encodeMap[storage >> 18];
	if (!--length) {
		*buffer++ = encodeMap[(storage >> 12) & 0x3F];
	#ifdef USE_EQUALS_SIGN_PADDING
		*buffer++ = '=';
		*buffer = '=';
	#endif
		return;
	}

	storage |= (*input++) << 8;
	*buffer++ = encodeMap[(storage >> 12) & 0x3F];
	if (!--length) {
		*buffer++ = encodeMap[(storage >> 6) & 0x3F];
	#ifdef USE_EQUALS_SIGN_PADDING
		*buffer = '=';
	#endif
		return;
	}

	storage |= *input;
	*buffer++ = encodeMap[(storage >> 6) & 0x3F];
	*buffer = encodeMap[storage & 0x3F];
}

void
decode_base64(const char *restrict input,
	size_t length, char *restrict buffer) {
#ifdef USE_EQUALS_SIGN_PADDING
	length -= (input[length - 1] == '=')
			+ (input[length - 2] == '=');
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

char
verify_base64(const char *string, size_t length) {
	char temp;
	for (size_t index = 0; index < length; index++) {
		temp = string[index];
		if (!(
			isalnum(temp) ||
			(temp == CHAR(ENCODE_MAP_CHAR_62)) ||
			(temp == CHAR(ENCODE_MAP_CHAR_63))
		)) {
		#ifdef USE_EQUALS_SIGN_PADDING
			if (temp == '=' && ((index + 1) == length ||
				(string[index + 1] == '=' && (index + 2) == length))
			)
				return 1;
		#endif
			return 0;
		}
	}
	return 1;
}
