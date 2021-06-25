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

## Licensing
The BSD 4-Clause “Original” or “Old” License has been used to license this project. \
Using code from this repository in a separate project requires the following acknowledgment displayed in all advertising materials, including the project README if present:
- This product includes the Base64 Utilities or modified versions, originally developed by FearlessDoggo21.

Even if the code is modified, this acknowledgment must be included. \
The following is a non-exhaustive list of possible modifications:
- meaningless changes to naming or the removal of code
- changes to the inputs and outputs of the functions
- use of the algorithm rewritten in another programming language

If the modifications include specific platform support, endianness detection, or SIMD, they violate the objective of this project and no acknowledgment must be made.

Note that this licence is incompatible with GNU General Public Licences, and any products including those licences will not be able to include this library.

## Contributions
If you find an inefficiency in the code please open an issue and possibly a matching pull request.
