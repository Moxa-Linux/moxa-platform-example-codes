CC:=gcc
STRIP:=strip

all:
	$(CC) -o rtc-test rtc-test.c
	$(STRIP) -s rtc-test

.PHONY: clean
clean:
	rm -f rtc-test
