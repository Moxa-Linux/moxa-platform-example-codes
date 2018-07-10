CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_push_btn pushbtn-test.c -o pushbtn-test
	$(STRIP) -s pushbtn-test

.PHONY: clean
clean:
	rm -f pushbtn-test
