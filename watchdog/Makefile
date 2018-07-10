CC:=gcc
STRIP:=strip

all:
	$(CC) -o watchdog-simple watchdog-simple.c
	$(CC) -o watchdog-test watchdog-test.c
	$(STRIP) -s watchdog-simple watchdog-test

.PHONY: clean
clean:
	rm -f watchdog-simple watchdog-test
