CC=gcc
CFLAGS=-fPIC -Wall -I.
LDFLAGS=-shared

all: libdynlib.so main

libdynlib.so: dynlib.c dynlib.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o libdynlib.so dynlib.c

main: main.c
	$(CC) -o main main.c -ldl

clean:
	rm -f libdynlib.so main
