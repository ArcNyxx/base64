# Base64
A library to encode and decode binary or textual data as base64.

Useful for:
- basic authentication and jwt on the web
- compact, swift, and human unreadable encoding
- encode alternative data to send as text

## Objective
Provide the fastest encode/decode functions possible which conform to the following criteria:
- readable by programmers of any skill level
- easily translatable into any other common programming language
- cross-platform and system

This disallows the use of both SIMD instructions and tricks based on memory endianness, making this library slower than others that utilise those.

## Contributions
If you find an inefficiency in the code please open an issue and possibly a matching pull request.
