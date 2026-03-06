CC=gcc
CFLAGS=-fPIC -Wall -I.
LDFLAGS=-shared
VISIBILITY=-fvisibility=hidden

all: libmylib.so

libmylib.so: core.c core.h
	$(CC) $(CFLAGS) $(VISIBILITY) $(LDFLAGS) -o libmylib.so core.c

clean:
	rm -f libmylib.so
