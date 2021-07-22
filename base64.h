// Copyright (c) 2021 FearlessDoggo21. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following
// disclaimer in the documentation and/or other materials provided
// with the distribution.
//
// 3. All advertising materials mentioning features or use of this
// software must display the following acknowledgement:
//     This product includes software developed by FearlessDoggo21.
//
// 4. Neither the name of  the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY COPYRIGHT HOLDER "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#include <limits.h>
#if UCHAR_MAX != 255
#error "`char` type does not hold 8 bits, FearlessDoggo21 Base64 Utils failure"
#endif

#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// If `USE_EQUALS_SIGN_PADDING` is defined, equals sign padding will be placed
// at the end of encoded strings to note an incomplete character bundle
#define USE_EQUALS_SIGN_PADDING
// #undef USE_EQUALS_SIGN_PADDING

#define _STRING(x) #x
#define STRING(x)  _STRING(x)
#define CHAR(x)    *_STRING(x)

// Base64 encode map, defaults to Base64URL
#define ENCODE_MAP_CHAR_62 -
#define ENCODE_MAP_CHAR_63 _
#define ENCODE_MAP               \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
    "abcdefghijklmnopqrstuvwxyz" \
    "0123456789"                 \
    STRING(ENCODE_MAP_CHAR_62)   \
    STRING(ENCODE_MAP_CHAR_63)

static const char *encodeMap = ENCODE_MAP;

// Decoding function to reverse ASCII offsets in encoding
// Does not check for errors, returns 63 if unrecognised char
static char DecodeChar(const char ch) {
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
static inline size_t GetEncodedLength(const size_t length) {
    return ((length + 2) / 3) << 2;
}

// Returns the length of a base64 encoded CString were it to be decoded
static inline size_t GetDecodedLength(const char *string, const size_t length) {
    return (length >> 2) * 3 - (string[length - 1] == '=')
            - (string[length - 2] == '=');
}
#else
// Returns the length of a CString were it to be encoded in base64
static inline size_t GetEncodedLength(const size_t length) {
    return length + ((length + 2) / 3);
}

// Returns the length of a base64 encoded CString were it to be decoded
static inline size_t GetDecodedLength(const size_t length) {
    return length - ((length + 2) >> 2);
}
#endif

// Encodes characters in base64, outputting to a buffer
// The buffer is assumed to be of proper length, made with `GetEncodedLength`
void EncodeBase64(const char *input, size_t length, char *buffer);

// Decodes a base64 string, outputting to a buffer
// The buffer is assumed to be of proper length, made with `GetDecodedLength`
void DecodeBase64(const char *input, size_t length, char *buffer);

// Verifies whether the inputted string is properly encoded in base64
char VerifyBase64(const char *string, size_t length);

#endif
