# base64 - simple encoding library
# Copyright (C) 2021 FearlessDoggo21
# see LICENCE file for licensing information

.POSIX:

include config.mk

SRC = base64.c
HEAD = base64.h
MAN = man/base64_encode.3 man/base64_decode.3 man/base64_verify.3 \
	man/base64_encode_len.3 man/base64_decode_len.3
OBJ = $(SRC:.c=.o)

all: libbase64.so

$(OBJ): $(HEAD) config.mk

.c.o:
	$(CC) $(CFLAGS) -c $<

libbase64.so: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -f libbase64.so $(OBJ) base64-$(VERSION).tar.gz

dist: clean
	mkdir -p base64-$(VERSION)
	cp -R LICENCE README Makefile config.mk \
		$(SRC) $(HEAD) $(MAN) test.c base64-$(VERSION)
	tar -cf base64-$(VERSION).tar base64-$(VERSION)
	gzip base64-$(VERSION).tar
	rm -rf base64-$(VERSION)

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/lib $(DESTDIR)$(PREFIX)/include \
		$(DESTDIR)$(MANPREFIX)/man3
	cp -f libbase64.so $(DESTDIR)$(PREFIX)/lib
	cp -f base64.h $(DESTDIR)$(PREFIX)/include
	for PAGE in $(MAN); \
	do \
		sed "s/VERSION/$(VERSION)/g" "$$PAGE" > \
			$(DESTDIR)$(MANPREFIX)/man3/$$(basename $$PAGE); \
		chmod 644 $(DESTDIR)$(MANPREFIX)/man3/$$(basename $$PAGE); \
	done

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/lib/libbase64.so \
		$(DESTDIR)$(PREFIX)/include/base64.h

options:
	@echo base64 build options
	@echo "CFLAGS = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

# implementation defined
.PHONY: all clean dist install uninstall options
