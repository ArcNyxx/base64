# base64 - simple encoding library
# Copyright (C) 2022 FearlessDoggo21
# see LICENCE file for licensing information

VERSION = 1.0.0

PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

WPROFILE = -Wall -Wextra -Wmissing-prototypes -Wstrict-prototypes \
-Wmissing-declarations -Wswitch-default -Wunreachable-code -Wcast-align \
-Wpointer-arith -Wbad-function-cast -Winline -Wundef -Wnested-externs \
-Wcast-qual -Wshadow -Wwrite-strings -Wno-unused-parameter -Wfloat-equal
STD = -D_POSIX_C_SOURCE=200809L

CFLAGS = $(WPROFILE) $(STD) -fpic -Os -DVERSION=\"$(VERSION)\"
LDFLAGS = -shared
