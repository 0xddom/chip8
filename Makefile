CC=gcc
CFLAGS=-Wall
LDFLAGS=

.PHONY: all clean

all: chip8 chip8dump

chip8: chip8.c handlers.c vm.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

chip8dump: chip8dump.c handlers.c vm.c disass.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f chip8
	rm -f chip8dump
