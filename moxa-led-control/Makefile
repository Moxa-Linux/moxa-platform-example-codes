CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_led_ctl led-test.c -o led-test
	$(STRIP) -s led-test

.PHONY: clean
clean:
	rm -f led-test
