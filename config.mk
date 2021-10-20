# see LICENCE file for licensing information
# base64 version
VERSION = 0.1.1

# code macros to change code functionalities
# adds equals sign padding to end of unfinished strings
MACROS = -DUSE_EQUALS_SIGN_PADDING

# paths
PREFIX = /usr/local

# flags
WPROFILE = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes \
-Wmissing-declarations -Wswitch-default -Wunreachable-code -Wcast-align \
-Wpointer-arith -Wbad-function-cast -Winline -Wundef -Wnested-externs \
-Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal
BASE64CPPFLAGS = -DVERSION=\"$(VERSION)\" $(MACROS) $(WPROFILE) -fpic
BASE64CFLAGS = $(BASE64CPPFLAGS) $(CPPFLAGS) $(CFLAGS)
BASE64LDFLAGS = $(LDFLAGS)
