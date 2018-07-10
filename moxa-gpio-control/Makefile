CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_gpio_ctl gpio-test.c -o gpio-test
	$(STRIP) -s gpio-test

.PHONY: clean
clean:
	rm -f gpio-test
