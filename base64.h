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

#include <limits.h>
#if UCHAR_MAX != 255
#error "`unsigned char` does not hold 8 bits, FearlessDoggo21 Base64 Utils failure"
#endif

#ifndef FEARLESSDOGGO21_BASE64_UTILS
#define FEARLESSDOGGO21_BASE64_UTILS

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// If `USE_EQUALS_SIGN_PADDING` is defined, equals sign padding will be placed
// at the end of encoded strings to note an incomplete character bundle
#define USE_EQUALS_SIGN_PADDING
#undef USE_EQUALS_SIGN_PADDING

// Base64 encode map, defaults to Base64URL
static const unsigned char *encodeMap =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "-_";

// Decoding function to reverse ASCII offsets in encoding
// Does not check for errors, returns 63 if unrecognised char
static unsigned char DecodeChar(const unsigned char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A';
    }
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 26;
    }
    if (ch >= '0' && ch <= '9') {
        return ch - '0' + 52;
    }
    return 63 - (ch == '-');
}

#ifdef USE_EQUALS_SIGN_PADDING
// Returns the length of a CString were it to be encoded in base64
static inline size_t GetEncodedLength(const unsigned char *string) {
    return ((strlen(string) + 2) / 3) << 2;
}

// Returns the length of a base64 encoded CString were it to be decoded
static inline size_t GetDecodedLength(const unsigned char *string) {
    size_t len = strlen(string);
    return (len >> 2) * 3 - (string[len - 1] == '=')
            - (string[len - 2] == '=');
}
#else
// Returns the length of a CString were it to be encoded in base64
static inline size_t GetEncodedLength(const unsigned char *string) {
    size_t len = strlen(string);
    return len + ((len + 2) / 3);
}

// Returns the length of a base64 encoded CString were it to be decoded
static inline size_t GetDecodedLength(const unsigned char *string) {
    size_t len = strlen(string);
    return len - ((len + 2) >> 2);
}
#endif

// Encodes characters in base64, outputting to a buffer
// The buffer is assumed to be of proper length, made with `GetEncodedLength`
void EncodeBase64(const unsigned char *input, size_t length,
        unsigned char *buffer);

// Decodes a base64 string, outputting to a buffer
// The buffer is assumed to be of proper length, made with `GetDecodedLength`
void DecodeBase64(const unsigned char *input, size_t length,
        unsigned char *buffer);

// Verifies whether the inputted string is properly encoded in base64
unsigned char VerifyBase64(const unsigned char *string, size_t length);

#endif
