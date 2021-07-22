// Copyright (c) 2021, FearlessDoggo21
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. All advertising materials mentioning features or use of this software must
//    display the following acknowledgement:
//      This product includes the Base64 Utilities Library or a modified version,
//      originally developed by FearlessDoggo21.

// 4. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY FearlessDoggo21 "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL FearlessDoggo21 BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "base64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DiffChars(const char *string, const char *compare, const size_t length) {
    if (!length) {
        return;
    }
    char *swapCode = "\x1b[31m";
    char correct = *string == *compare, newCorrect;
    printf("\x1b[3%cm%c", '1' + correct, *string);

    for (size_t i = 1; i < length; i++) {
        newCorrect = string[i] == compare[i];
        if (correct != newCorrect) {
            printf("\x1b[3%cm", '1' + newCorrect);
        }
        printf("%c", string[i]);
        
        correct = newCorrect;
    }

    printf("\x1b[m\n");
}

int main(int argc, char *argv[]) {
    const char *testDec = "NXBUwl^MYZVJi47a1*n22@iTCD-%Z3rM&YJoLU&9Ss6Y_T5*sW?ufI27iKN"
    "4Lst%@sA2N7&IX9dXl-D&^-A-B$7=i9dDNdg7ygcK#KBFT?A9T&h|k#=l=3699Rp1pPhJO+fx="
    "fdD^b0s%$i?EPBq$mqX9n3xr*OEMk3*!dbHu=Uy5nc3O9U3h4rCW&lk$EkZ!@XD6*d0Bj#==qb"
    "CnW*g=E0r^ItOIizy0SdMe32xh9xupKZsRwx7hj-YG!Wpc$d^";
    
    const char *testEnc = "TlhCVXdsXk1ZWlZKaTQ3YTEqbjIyQGlUQ0QtJVozck0mWUpvTFUmOVNzNll"
    "fVDUqc1c_dWZJMjdpS040THN0JUBzQTJONyZJWDlkWGwtRCZeLUEtQiQ3PWk5ZEROZGc3eWdjS"
    "yNLQkZUP0E5VCZofGsjPWw9MzY5OVJwMXBQaEpPK2Z4PWZkRF5iMHMlJGk_RVBCcSRtcVg5bjN"
    "4cipPRU1rMyohZGJIdT1VeTVuYzNPOVUzaDRyQ1cmbGskRWtaIUBYRDYqZDBCaiM9PXFiQ25XK"
    "mc9RTByXkl0T0lpenkwU2RNZTMyeGg5eHVwS1pzUnd4N2hqLVlHIVdwYyRkXg==";

    size_t lenEnc = GetEncodedLength(strlen(testDec));
    size_t lenDec = GetDecodedLength(testEnc, strlen(testEnc));

    char encode[lenEnc + 1];
    EncodeBase64(testDec, lenDec, encode);
    encode[lenEnc] = 0;

    char verify = VerifyBase64(encode, lenEnc);
    printf("Encoded string \x1b[1m%s\x1b[m valid.\n", verify ? "is" : "is not");

    char encoded = strcmp(encode, testEnc);
    printf("Encoded string \x1b[1m%s\x1b[m correct.\n", encoded ? "is not" : "is");
    if (encoded) {
        // Testing for DiffChars function
        // memcpy(encode + 12, "aweouhwaeunaeriuanero", 21);
        // memcpy(encode + 90, "w4ouyJwnnavriaweh", 17);

        DiffChars(encode, testEnc, lenEnc);
        printf("%s\n", testEnc);
    }

    char decode[lenDec + 1];
    DecodeBase64(testEnc, lenEnc, decode);
    decode[lenDec] = 0;

    char decoded = strcmp(decode, testDec);
    printf("Decoded string \x1b[1m%s\x1b[m correct.\n", decoded ? "is not" : "is");
    if (decoded) {
        DiffChars(decode, testDec, lenDec);
        printf("%s\n", testDec);
    }
    
    if (verify && !encoded && !decoded) {
        printf("\x1b[1m\x1b[32mTesting success!\x1b[m\n");
    } else {
        printf("\x1b[1m\x1b[31mTesting failure!\x1b[m\n");
    }

    if (argc == 2 && !strcmp(argv[1], "-v")) {
        printf("\n%s\n%s\n%s\n%s\n", encode, testEnc, decode, testDec);
    }

    return 0;
}
