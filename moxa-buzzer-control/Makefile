CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_buzzer_ctl buzzer-test.c -o buzzer-test
	$(STRIP) -s buzzer-test

.PHONY: clean
clean:
	rm -f buzzer-test
