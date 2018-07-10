/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	UART Testing Example program
 *
 * Description:
 *	Routines to test RS232/RS422.
 *
 * Authors:
 *	2011	SZ Lin		<sz.lin@moxa.com>
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <moxa/mx_uart.h>

#define default_count 50
#define default_baudrate 115200
#define default_data_byte 128

struct test_struct {
	int ports[2];
	int count;
	int baudrate;
	int data_byte;
};

extern char mx_errmsg[256];

void usage(FILE *fp, const char *ex_name)
{
	fprintf(fp, "Usage:\n");
	fprintf(fp, "	%s #port1 #port2 [options]\n\n", ex_name);
	fprintf(fp, "OPTIONS:\n");
	fprintf(fp, "	-c <#count>\n");
	fprintf(fp, "		Set test count.\n");
	fprintf(fp, "		Default test counts is %d.\n", default_count);
	fprintf(fp, "	-b <#baudrate>\n");
	fprintf(fp, "		Set baudrate.\n");
	fprintf(fp, "		Default baudrate is %d.\n", default_baudrate);
	fprintf(fp, "	-d <#data_byte>\n");
	fprintf(fp, "		Set data_byte.\n");
	fprintf(fp, "		Default data_byte is %d.\n", default_data_byte);
	fprintf(fp, "\n");
	fprintf(fp, "Example:\n");
	fprintf(fp, "	Testing transmission from port 0 to port 1\n");
	fprintf(fp, "	# %s 0 1\n", ex_name);
	fprintf(fp, "\n");
}

/*
 * Set serial parameter to each serial port.
 *	Inputs:
 *		<fd> file descriptor
 *		<baudrate> Specific baudrate
 *		<databits> Specific databits
 *		<stopbits> Specific stopbits
 *		<parity> Specific parity
 *	Returns:
 *		0 on success
 *		-1 on error
 */
int set_serial(int port, int baudrate, int databits, int stopbits, int parity)
{
	int ret;

	ret = mx_uart_set_baudrate(port, baudrate);
	if (ret < 0) 
		return ret;

	ret = mx_uart_set_databits(port, databits);
	if (ret < 0) 
		return ret;

	ret = mx_uart_set_stopbits(port, stopbits);
	if (ret < 0) 
		return ret;

	ret = mx_uart_set_parity(port, parity);
	if (ret < 0) 
		return ret;

	return 0;
}

void exit_close_port(int exit_code, int ports[2])
{
	mx_uart_close(ports[0]);
	mx_uart_close(ports[1]);
	exit(exit_code);
}

void open_serial(struct test_struct test)
{
	int ret;

	ret = mx_uart_open(test.ports[0]);
	if (ret < 0) {
		fprintf(stderr, "Open UART port %d failed.\n", test.ports[0]);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit_close_port(1, test.ports);
	}
		
	ret = set_serial(test.ports[0], test.baudrate, 8, 1, 0);
	if (ret < 0) {
		fprintf(stderr, "Set UART port %d failed.\n", test.ports[0]);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit_close_port(1, test.ports);
	}

	ret = mx_uart_open(test.ports[1]);
	if (ret < 0) {
		fprintf(stderr, "Open UART port %d failed.\n", test.ports[1]);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit_close_port(1, test.ports);
	}
		
	ret = set_serial(test.ports[1], test.baudrate, 8, 1, 0);
	if (ret < 0) {
		fprintf(stderr, "Set UART port %d failed.\n", test.ports[1]);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit_close_port(1, test.ports);
	}
}

/*
 * generate random data and assign to buffer
 *	Inputs:
 *		<snd_data> The buffer used to send data
 *		<data_byte> Number of bytes in data
 *	Outputs:
 *		Array with random data
 *	Returns:
 *		snd_data
 */
void generate_random_data(char *snd_data, int data_byte)
{
	int value, count = 0;

	/* Initialize buffer */
	memset(snd_data, '\0', data_byte);

	/* Use random function to generate random data */
	for (count = 0; count < data_byte; count++) {
		srand((unsigned int) time(NULL));
		value = (rand() + count) % 255;
		snd_data[count] = value;
	}
}

/*
 * compare data between snd_data and rcv_data
 *	Inputs:
 *		<snd_data> The buffer used to send data
 *		<rcv_data> The buffer used to receive data
 *		<data_byte> Number of bytes in data
 *	Outputs:
 *		Two buffers are the same or not
 *	Returns:
 *		1 on different
 *		0 on the same
 */
int compare(char *snd_data, char *rcv_data, int data_byte)
{
	int i;

	for (i = 0; i < data_byte; i++) {
		if (snd_data[i] != rcv_data[i])
			return 1;
	}
	return 0;
}

void com_test(struct test_struct test)
{
	int ret, count, i, rem_bytes;
	char snd_data[test.data_byte], rcv_data[test.data_byte];
	float wait_time;

	open_serial(test);

	generate_random_data(snd_data, test.data_byte);

	for (count = 0; count < test.count; count++) {
		/* Send data */
		for (i = 0; i < 2; i++) {
			ret = mx_uart_write(test.ports[i], snd_data, test.data_byte);
			if (ret < 0) {
				fprintf(stderr, "Write UART port %d failed.\n", test.ports[i]);
				fprintf(stderr, "Error code: %d\n", ret);
				fprintf(stderr, "Error message: %s\n", mx_errmsg);
				exit_close_port(1, test.ports);
			}
		}

		/* wait time depends on baud rate */
		wait_time = (float) test.data_byte / (test.baudrate / 8) * 1500;
		usleep(wait_time * 1000);

		/* Rcv data */
		for (i = 0; i < 2; i++) {
			rem_bytes = test.data_byte;
			memset(rcv_data, '\0', test.data_byte);

			while (rem_bytes) {
				ret = mx_uart_read(test.ports[i], rcv_data + test.data_byte - rem_bytes, rem_bytes);
				if (ret < 0) {
					fprintf(stderr, "Read UART port %d failed.\n", test.ports[i]);
					fprintf(stderr, "Error code: %d\n", ret);
					fprintf(stderr, "Error message: %s\n", mx_errmsg);
					exit_close_port(1, test.ports);
				}

				rem_bytes -= ret;
			}

			/* Compare data */
			if (compare(snd_data, rcv_data, test.data_byte)) {
				printf("Transmission test failed!\n");
				exit_close_port(1, test.ports);
			}
		}
	}

	/* Pass the test */
	printf("Transmission test passed!\n");
	exit_close_port(0, test.ports);
}

int main(int argc, char *argv[])
{
	struct test_struct test = {
		.count = default_count,
		.baudrate = default_baudrate,
		.data_byte = default_data_byte
	};
	int c, ret;

	while ((c = getopt(argc, argv, "hc:b:d:")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout, argv[0]);
			exit(0);
		case 'c':
			test.count = atoi(optarg);
			break;
		case 'b':
			test.baudrate = atoi(optarg);
			break;
		case 'd':
			test.data_byte = atoi(optarg);
			break;
		default:
			usage(stderr, argv[0]);
			exit(99);
		}
	}

	if ((argc - optind) != 2) {
		usage(stderr, argv[0]);
		exit(99);
	}
	test.ports[0] = atoi(argv[optind]);
	test.ports[1] = atoi(argv[optind + 1]);

	if (test.ports[0] == test.ports[1]) {
		fprintf(stderr, "port1 and port2 are the same.\n");
		exit(2);
	}

	ret = mx_uart_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa uart control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		exit(1);
	}

	printf("Start testing port %d to port %d with:\n", test.ports[0], test.ports[1]);
	printf("\tdata bytes: %d\n", test.data_byte);
	printf("\tbaudrate: %d\n", test.baudrate);
	printf("\ttest count: %d\n", test.count);

	com_test(test);
}
