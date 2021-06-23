// BSD 4-Clause License

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

char *EncodeBase64(const char *string) {
    char *output;
    if (!(output = malloc(1 + ((strlen(string) + 2) / 3 * 4)))) {
        return (char *)0;
    }

    size_t index = 0;
    for (uint16_t storage = 0; *string; ) {
        storage |= *string++;
        output[index++] = encodeMap[(storage >> 2) & 0x3F];
        storage <<= 8;

        storage |= *string++;
        output[index++] = encodeMap[(storage >> 4) & 0x3F];

        if (storage <<= 8) {
            storage |= *string++;
            output[index++] = encodeMap[(storage >> 6) & 0x3F];
        } else {
            break;
        }

        if (storage <<= 8) {
            output[index++] = encodeMap[(storage >> 8) & 0x3F];
        } else {
            break;
        }
    }

    if (index & 1) {
        output[index] = '=';
        output[index + 1] = '\0';
    } else if (index & 2) {
        output[index] = '=';
        output[index + 1] = '=';
        output[index + 2] = '\0';
    }

    return output;
}
