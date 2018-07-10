CC := gcc
STRIP := strip

all:
	$(CC) -Wall -ljson-c -lmx_platform_info platform_info-test.c -o platform_info-test
	$(STRIP) -s platform_info-test

.PHONY: clean
clean:
	rm -f platform_info-test
