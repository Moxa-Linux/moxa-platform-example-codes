CC:=gcc
STRIP:=strip

all:
	$(CC) -o aes-test aes.c
	$(CC) -o sha-test sha.c
	$(STRIP) -s aes-test sha-test

.PHONY: clean
clean:
	rm -f aes-test sha-test
