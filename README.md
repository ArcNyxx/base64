# Base64
A library to encode and decode binary or textual data as base64.

Useful for:
- basic authentication and jwt on the web
- compact, swift, and human unreadable encoding
- encode alternative data to send as text

## Philosophy
Provide the fastest encode/decode functions possible which conform to the following criteria:
- readable by programmers of any skill level
- cross-platform and system

This disallows the use of any tricks which assume the endianness of the system, making the code slightly slower. \
However, this speed penalty is quite minimal as the string will near certainly be cached at runtime.

## Licensing
The BSD 4-Clause “Original” or “Old” License has been used to license this project. \
Using code from this repository in a separate project requires the following acknowledgment displayed in all advertising materials, including the project README if present:
- This product includes the Base64 Utilities Library or a modified version, originally developed by FearlessDoggo21.

Even if the code is modified, this acknowledgment must be included. \
The following is a non-exhaustive list of possible modifications:
- meaningless changes to naming or the removal of code
- changes to the inputs and outputs of the functions
- use of the algorithm rewritten in another programming language
- built-in endianness support

Note that this licence is incompatible with GNU General Public Licences, and any products including those licences will not be able to include this library.

## Contributions
If you find an inefficiency in the code, whether it be in the main library or its tests, please open an issue and possibly a matching pull request.
