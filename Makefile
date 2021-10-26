# base64 - simple encoding library
# Copyright (C) 2021 FearlessDoggo21
# see LICENCE file for licensing information

.POSIX:

include config.mk

SRC = base64.c
OBJ = $(SRC:.c=.o)
INC = base64.h
TEST = test.c
TESTOBJ = $(TEST:.c=.o)

all: options base64.so

options:
	@echo base64 build options:
	@echo "CFLAGS  = $(BASE64CFLAGS)"
	@echo "LDFLAGS = $(BASE64LDFLAGS)"
	@echo "CC      = $(CC)"

.c.o:
	$(CC) $(BASE64CFLAGS) -c $<

base64.c: base64.h
test.c: base64.h

base64.so: $(OBJ)
	$(CC) -shared -o $@ $(OBJ) $(BASE64LDFLAGS)

test: $(OBJ) $(TESTOBJ)
	$(CC) -o $@ $(OBJ) $(TESTOBJ) $(BASE64LDFLAGS)

clean:
	rm -f base64.so test $(OBJ) $(TESTOBJ) base64-$(VERSION).tar.gz

dist: clean
	mkdir -p base64-$(VERSION)
	cp -R LICENCE Makefile README config.mk \
		$(SRC) $(INC) $(TEST) base64-$(VERSION)
	tar -cf - base64-$(VERSION) | gzip > base64-$(VERSION).tar.gz
	rm -rf base64-$(VERSION)

install: base64.so
	mkdir -p $(DESTDIR)$(PREFIX)/lib
	cp -f base64.so $(DESTDIR)$(PREFIX)/lib
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp -f base64.h $(DESTDIR)$(PREFIX)/include

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/base64.so \
		$(DESTDIR)$(PREFIX)/include/base64.h

.PHONY: all test options clean dist install uninstall
