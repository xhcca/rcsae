PREFIX = local

CC = cc
CFLAGS = -std=c99 -Wall -Wno-error -pedantic -I. -L.

MKBIN = ./tools/mkbin

ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
else
	CFLAGS += -O3
endif

all: build

build: librcsae.a rcsae build-system

build-system: sys/fp.bin

test: tests/test-remem tests/test-restor
	./tests/test-remem
	./tests/test-restor

pre-install:
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/bin
	mkdir -p $(PREFIX)/lib/rcsae-system-files

install: pre-install
	cp librcsae.a $(PREFIX)/lib
	cp rcsae $(PREFIX)/bin
	cp sys/*.bin $(PREFIX)/lib/rcsae-system-files

uninstall:
	rm -f $(PREFIX)/lib/librcsae.a
	rm -f $(PREFIX)/bin/rcsae
	rm -r -f $(PREFIX)/lib/rcsae-system-files

clean:
	rm *.o

.PHONY : all build pre-install install uninstall clean

librcsae.a: remem.o reproc.o restor.o
	$(AR) rcs $@ $^

remem.o: remem.c remem.h
	$(CC) $(CFLAGS) -c $< -o $@

reproc.o: reproc.c reproc.h
	$(CC) $(CFLAGS) -c $< -o $@

restor.o: restor.c restor.h
	$(CC) $(CFLAGS) -c $< -o $@

rcsae: rcsae.o
	$(CC) $(CFLAGS) $^ -o $@ -lrcsae

rcsae.o: rcsae.c
	$(CC) $(CFLAGS) -c $< -o $@

sys/fp.bin: sys/fp.hex
	$(MKBIN) $@ $^

tests/test-remem: tests/test-remem.c
	$(CC) $(CFLAGS) $< -o $@ -lrcsae

tests/test-restor: tests/test-restor.c
	$(CC) $(CFLAGS) $< -o $@ -lrcsae
