/* see LICENCE file for licensing information */
/* base64 - simple encoding library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

void diff_chars(const char *restrict string,
	const char *restrict compare, const size_t length);

void
diff_chars(const char *restrict string, 
	const char *restrict compare, const size_t length) {
	if (!length)
		return;

	char corr = string[0] == compare[0], swap;
	printf("\x1b[3%cm%c", '1' + corr, string[0]);
	for (size_t i = 1; i < length; ++i) {
		swap = string[i] == compare[i];
		if (corr != swap)
			printf("\x1b[3%cm", '1' + swap);
		printf("%c", string[i]);
		corr = swap;
	}
	printf("\x1b[m\n");
}

int main(int argc, char *argv[]) {
	printf("%s %c %c\n", encodeMap,
		CHAR(ENCODE_MAP_CHAR_62), CHAR(ENCODE_MAP_CHAR_63));

	const char *test_dec, *test_enc;
	size_t len_dec, len_enc;

	test_dec = "NXBUwl^MYZVJi47a1*n22@iTCD-%Z3rM&YJoLU&9Ss6Y_T5*sW?uf"
	"I27iKN4Lst%@sA2N7&IX9dXl-D&^-A-B$7=i9dDNdg7ygcK#KBFT?A9T&h|k#=l=3699Rp1pPhJ"
	"O+fx=fdD^b0s%$i?EPBq$mqX9n3xr*OEMk3*!dbHu=Uy5nc3O9U3h4rCW&lk$EkZ!@XD6*d0Bj#"
	"==qbCnW*g=E0r^ItOIizy0SdMe32xh9xupKZsRwx7hj-YG!Wpc$d^";
	len_enc = get_encoded_length(strlen(test_dec));

#ifdef USE_EQUALS_SIGN_PADDING
	test_enc = "TlhCVXdsXk1ZWlZKaTQ3YTEqbjIyQGlUQ0QtJVozck0mWUpvTFUmO"
	"VNzNllfVDUqc1c" STRING(ENCODE_MAP_CHAR_63) "dWZJMjdpS040THN0JUBzQTJONyZJWDl"
	"kWGwtRCZeLUEtQiQ3PWk5ZEROZGc3eWdjSyNLQkZUP0E5VCZofGsjPWw9MzY5OVJwMXBQaEpPK2"
	"Z4PWZkRF5iMHMlJGk" STRING(ENCODE_MAP_CHAR_63) "RVBCcSRtcVg5bjN4cipPRU1rMyoh"
	"ZGJIdT1VeTVuYzNPOVUzaDRyQ1cmbGskRWtaIUBYRDYqZDBCaiM9PXFiQ25XKmc9RTByXkl0T0l"
	"penkwU2RNZTMyeGg5eHVwS1pzUnd4N2hqLVlHIVdwYyRkXg==";
	len_dec = get_decoded_length(test_enc, strlen(test_enc));
#else
	test_enc = "TlhCVXdsXk1ZWlZKaTQ3YTEqbjIyQGlUQ0QtJVozck0mWUpvTFUmO"
	"VNzNllfVDUqc1c" STRING(ENCODE_MAP_CHAR_63) "dWZJMjdpS040THN0JUBzQTJONyZJWDl"
	"kWGwtRCZeLUEtQiQ3PWk5ZEROZGc3eWdjSyNLQkZUP0E5VCZofGsjPWw9MzY5OVJwMXBQaEpPK2"
	"Z4PWZkRF5iMHMlJGk" STRING(ENCODE_MAP_CHAR_63) "RVBCcSRtcVg5bjN4cipPRU1rMyoh"
	"ZGJIdT1VeTVuYzNPOVUzaDRyQ1cmbGskRWtaIUBYRDYqZDBCaiM9PXFiQ25XKmc9RTByXkl0T0l"
	"penkwU2RNZTMyeGg5eHVwS1pzUnd4N2hqLVlHIVdwYyRkXg";
	len_dec = get_decoded_length(strlen(test_enc));
#endif

	char encode[len_enc + 1];
	encode_base64(test_dec, len_dec, encode);
	encode[len_enc] = 0;

	char verify = verify_base64(encode, len_enc);
	printf("Encoded string \x1b[1m%s\x1b[m valid.\n", 
		verify ? "is" : "is not");

	char encoded = strcmp(encode, test_enc);
	printf("Encoded string \x1b[1m%s\x1b[m correct.\n", 
		encoded ? "is not" : "is");
	if (encoded) {
		/* test function actually working properly */
		memcpy(encode + 12, "aweouhwaeunaeriuanero", 21);
		memcpy(encode + 90, "w4ouyJwnnavriaweh", 17);

		diff_chars(encode, test_enc, len_enc);
		printf("%s\n", test_enc);
	}

	char decode[len_dec + 1];
	decode_base64(test_enc, len_enc, decode);
	decode[len_dec] = 0;

	char decoded = strcmp(decode, test_dec);
	printf("Decoded string \x1b[1m%s\x1b[m correct.\n", 
		decoded ? "is not" : "is");
	if (decoded) {
		diff_chars(decode, test_dec, len_dec);
		printf("%s\n", test_dec);
	}

	if (verify && !encoded && !decoded)
		printf("\x1b[1m\x1b[32mTesting success!\x1b[m\n");
	else
		printf("\x1b[1m\x1b[31mTesting failure!\x1b[m\n");

	if (argc == 2 && !strcmp(argv[1], "-v")) {
		printf("\n%s\n%s\n%s\n%s\n", encode, test_enc, decode, test_dec);
	}

	return 0;
}
