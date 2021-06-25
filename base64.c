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

void EncodeBase64(const unsigned char *input, size_t length, 
        unsigned char *buffer) {
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

    storage |= (*input++) << 16;
    *buffer++ = encodeMap[storage >> 18];
    if (!--length) {
        *buffer++ = encodeMap[(storage >> 12) & 0x3F];
        *buffer++ = '=';
        *buffer = '=';
        return;
    }

    storage |= (*input++) << 8;
    *buffer++ = encodeMap[(storage >> 12) & 0x3F];
    if (!--length) {
        *buffer++ = encodeMap[(storage >> 6) & 0x3F];
        *buffer = '=';
        return;
    }

    storage |= *input;
    *buffer++ = encodeMap[(storage >> 6) & 0x3F];
    *buffer = encodeMap[storage & 0x3F];
}
/*
uint8_t *DecodeBase64(const uint8_t *string) {
    uint8_t *output;
    size_t length = strlen(string);
    if (!(output = malloc(1 + (length >> 2) * 3 - (string[length - 1] == '=')
            - (string[length - 2] == '=')))) {
        return (uint8_t *)0;
    }

    size_t index = 0;
    uint32_t storage = 0;
    while (string[4]) {
        storage |= DecodeChar(*string++) << 18;
        storage |= DecodeChar(*string++) << 12;
        storage |= DecodeChar(*string++) << 6;
        storage |= DecodeChar(*string++);

        output[index++] = storage >> 16;
        output[index++] = (uint8_t)(storage >> 8);
        output[index++] = (uint8_t)storage;

        storage = 0;
    }

    storage |= DecodeChar(*string++) << 18;
    storage |= DecodeChar(*string++) << 12;
    output[index++] = storage >> 16;

    if (*string == '=') {
        output[index] = '\0';
        return output;
    }
    storage |= DecodeChar(*string++) << 6;
    output[index++] = (uint8_t)(storage >> 8);

    if (*string == '=') {
        output[index] = '\0';
        return output;
    }
    storage |= DecodeChar(*string);
    output[index++] = (uint8_t)storage;

    output[index] = '\0';
    return output;
}
*/
unsigned char VerifyBase64(const unsigned char *string, size_t length) {
    unsigned char temp;
    for (size_t index = 0; index < length; index++) {
        temp = string[index];
        if (!(
            (temp >= 'A' && temp <= 'Z') ||
            (temp >= 'a' && temp <= 'z') ||
            (temp >= '0' && temp <= '9') ||
            (temp == '-') ||
            (temp == '_')
        )) {
            if (temp == '=' && ((index + 1) == length ||
                (string[index + 1] == '=' && (index + 2) == length))
            ) {
                return 1;
            }
            return 0;
        }
    }
    return 1;
}
