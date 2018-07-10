CC:=gcc
STRIP:=strip

all:
	$(CC) -o hello hello.c
	$(STRIP) -s hello

.PHONY: clean
clean:
	rm -f hello
