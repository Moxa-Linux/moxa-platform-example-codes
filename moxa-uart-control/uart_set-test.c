/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA UART Library
 *
 * Description:
 *	Example code for demonstrating the usage of MOXA UART Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <moxa/mx_uart.h>

extern char mx_errmsg[256];

void show_uart_mode_message(int mode)
{
	switch (mode) {
	case UART_MODE_RS232:
		printf("\tCurrent uart mode is RS232 interface.\n");
		break;
	case UART_MODE_RS485_2W:
		printf("\tCurrent uart mode is RS485-2W interface.\n");
		break;
	case UART_MODE_RS422_RS485_4W:
		printf("\tCurrent uart mode is RS422/RS485-4W interface.\n");
		break;
	default:
		printf("\tUnknown interface is set.\n");
		break;
	}
}

int main(int argc, char *argv[])
{
	int ret, uart_port, mode;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <uart_port>\n", argv[0]);
		exit(99);
	}
	uart_port = atoi(argv[1]);

	ret = mx_uart_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa uart control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Testing UART port %d:\n", uart_port);

	printf("Setting to RS232 mode\n");
	ret = mx_uart_set_mode(uart_port, UART_MODE_RS232);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Getting UART port mode:\n");
	ret = mx_uart_get_mode(uart_port, &mode);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	show_uart_mode_message(mode);
	printf("\n");

	sleep(1);

	printf("Setting to RS485-2W mode\n");
	ret = mx_uart_set_mode(uart_port, UART_MODE_RS485_2W);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Getting UART port mode:\n");
	ret = mx_uart_get_mode(uart_port, &mode);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	show_uart_mode_message(mode);
	printf("\n");

	sleep(1);

	printf("Setting to RS422/RS485-4W mode\n");
	ret = mx_uart_set_mode(uart_port, UART_MODE_RS422_RS485_4W);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Getting UART port mode:\n");
	ret = mx_uart_get_mode(uart_port, &mode);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	show_uart_mode_message(mode);
	printf("\n");

	sleep(1);

	exit(0);
}
