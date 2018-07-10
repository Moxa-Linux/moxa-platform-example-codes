CC := gcc
STRIP := strip

all:
	$(CC) -Wall -lmx_uart_ctl uart_set-test.c -o uart_set-test
	$(STRIP) -s uart_set-test

	$(CC) -Wall -lmx_uart_ctl uart_transmit-test.c -o uart_transmit-test
	$(STRIP) -s uart_transmit-test

.PHONY: clean
clean:
	rm -f uart_set-test uart_transmit-test
