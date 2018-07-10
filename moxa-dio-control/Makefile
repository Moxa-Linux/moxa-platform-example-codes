CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_dio_ctl dio-test.c -o dio-test
	$(STRIP) -s dio-test

.PHONY: clean
clean:
	rm -f dio-test
