/* base64 - simple encoding library
 * Copyright (C) 2021-2022 ArcNyxx
 * see LICENCE file for licensing information */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

static void diff_chars(const char *restrict string,
	const char *restrict compare, const size_t length);

static void
diff_chars(const char *restrict string, const char *restrict compare,
		const size_t length)
{
	if (!length)
		return;

	bool previous = string[0] == compare[0];
	printf("\x1b[3%cm%c", '1' + previous, string[0]);

	for (size_t i = 1; i < length; ++i) {
		bool current = string[i] == compare[i];
		if (previous != current)
			printf("\x1b[3%cm%c", '1' + current, string[i]);
		else
			printf("%c", string[i]);
		previous = current;
	}
	printf("\x1b[m\n");
}

int
main(int argc, char **argv)
{
	if (argc > 1 && !strcmp(argv[1], "-w")) {
		diff_chars("This is a test!", "That as no esr.", 15);
		printf("That as no esr.\n");
		return 0;
	}

	printf("test: encode map: %s\n", encode_map);

	const char *test_dec = "NXBUwl^MYZVJi47a1*n22@iTCD-%Z3rM&YJoLU&9Ss6Y_T5*sW?uf"
	"I27iKN4Lst%@sA2N7&IX9dXl-D&^-A-B$7=i9dDNdg7ygcK#KBFT?A9T&h|k#=l=3699Rp1pPhJO"
	"+fx=fdD^b0s%$i?EPBq$mqX9n3xr*OEMk3*!dbHu=Uy5nc3O9U3h4rCW&lk$EkZ!@XD6*d0Bj#=="
	"qbCnW*g=E0r^ItOIizy0SdMe32xh9xupKZsRwx7hj-YG!Wpc$d^";
	size_t len_enc = base64_encode_len(strlen(test_dec));

	const char *test_enc = "TlhCVXdsXk1ZWlZKaTQ3YTEqbjIyQGlUQ0QtJVozck0mWUpvTFUmO"
	"VNzNllfVDUqc1c" _STRING(ENCODE_MAP_CHAR_63) "dWZJMjdpS040THN0JUBzQTJONyZJWDl"
	"kWGwtRCZeLUEtQiQ3PWk5ZEROZGc3eWdjSyNLQkZUP0E5VCZofGsjPWw9MzY5OVJwMXBQaEpPK2Z"
	"4PWZkRF5iMHMlJGk" _STRING(ENCODE_MAP_CHAR_63) "RVBCcSRtcVg5bjN4cipPRU1rMyohZ"
	"GJIdT1VeTVuYzNPOVUzaDRyQ1cmbGskRWtaIUBYRDYqZDBCaiM9PXFiQ25XKmc9RTByXkl0T0lpe"
#ifdef USE_EQUALS_SIGN_PADDING
	"nkwU2RNZTMyeGg5eHVwS1pzUnd4N2hqLVlHIVdwYyRkXg==";
	size_t len_dec = base64_decode_len(test_enc, strlen(test_enc));
#else
	"nkwU2RNZTMyeGg5eHVwS1pzUnd4N2hqLVlHIVdwYyRkXg";
	size_t len_dec = base64_decode_len(strlen(test_enc));
#endif

	char enc[len_enc];
	base64_encode(test_dec, strlen(test_dec), enc);

	char verify = base64_verify(enc, len_enc);
	printf("test: encoded string is%s valid\n", verify ? "" : " not");

	char encoded = memcmp(enc, test_enc, len_enc);
	printf("test: encoded string is%s correct\n", encoded ? " not" : "");
	if (encoded) {
		diff_chars(enc, test_enc, len_enc);
		printf("%s\n", test_enc);
	}

	char dec[len_dec];
	base64_decode(test_enc, len_enc, dec);

	char decoded = memcmp(dec, test_dec, len_dec);
	printf("test: decoded string is%s correct\n", decoded ? " not" : "");
	if (decoded) {
		diff_chars(dec, test_dec, len_dec);
		printf("%s\n", test_enc);
	}

	if (verify && !encoded && !decoded)
		printf("test: success\n");
	else
		printf("test: failure\n");
}
