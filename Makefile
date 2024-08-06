PREFIX = local

CC = cc
CFLAGS = -std=c99 -Wall -Wno-error -pedantic

ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
else
	CFLAGS += -O3
endif

OBJECTS = remem.o reproc.o restor.o
TEST_BINARIES = tests/test-remem tests/test-restor

all: build

build: librcsae.a rcsae

test: tests/test-remem tests/test-restor
	./tests/test-remem
	./tests/test-restor

install:
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/bin
	cp librcsae.a $(PREFIX)/lib
	cp rcsae $(PREFIX)/bin

uninstall:
	rm -f $(PREFIX)/lib/librcsae.a
	rm -f $(PREFIX)/bin/rcsae

clean:
	rm $(OBJECTS)
	rm librcsae.a
	rm rcsae
	rm $(TEST_BINARIES)

.PHONY : all build install uninstall clean

librcsae.a: remem.o reproc.o restor.o
	$(AR) rcs $@ $^

remem.o: remem.c remem.h
	$(CC) $(CFLAGS) -c $< -o $@

reproc.o: reproc.c reproc.h
	$(CC) $(CFLAGS) -c $< -o $@

restor.o: restor.c restor.h
	$(CC) $(CFLAGS) -c $< -o $@

rcsae: rcsae.c
	$(CC) $(CFLAGS) $^ -o $@ -L. -lrcsae

tests/test-remem: tests/test-remem.c
	$(CC) $(CFLAGS) $< -o $@ -I. -L. -lrcsae

tests/test-restor: tests/test-restor.c
	$(CC) $(CFLAGS) $< -o $@ -I. -L. -lrcsae
