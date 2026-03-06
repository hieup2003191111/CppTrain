CC=gcc
CFLAGS=-fPIC -Wall -I.
LDFLAGS=-shared -Wl,--version-script=version_script.map

all: libmylib.so

libmylib.so: version.c version.h version_script.map
	$(CC) $(CFLAGS) $(LDFLAGS) -o libmylib.so version.c

clean:
	rm -f libmylib.so
