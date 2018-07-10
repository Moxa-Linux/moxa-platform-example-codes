/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA DIO Library
 *
 * Description:
 *	Example code for demonstrating the usage of MOXA DIO Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <moxa/mx_dio.h>

extern char mx_errmsg[256];

void event_func(int diport)
{
	printf("\t--------\n");
	printf("\tCatch low-to-high event on DIN port %d !!!\n", diport);
	printf("\t--------\n");
}

int main(int argc, char *argv[])
{
	int ret, diport, doport, state;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <dout_port> <din_port>\n", argv[0]);
		exit(99);
	}
	doport = atoi(argv[1]);
	diport = atoi(argv[2]);

	ret = mx_dio_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa dio control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Testing DIO from DOUT port %d to DIN port %d:\n", doport, diport);
	printf("Please make sure they are connected to each other.\n\n");

	printf("Setting DOUT port %d to low.\n", doport);
	ret = mx_dout_set_state(doport, DIO_STATE_LOW);
	if (ret < 0) {
		fprintf(stderr, "Failed to set DOUT port %d\n", doport);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	sleep(1);

	printf("Getting DIN port %d's state.\n", diport);
	ret = mx_din_get_state(diport, &state);
	if (ret < 0) {
		fprintf(stderr, "Failed to get DIN port %d\n", diport);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	printf("\tDIN port %d's state is %d.\n\n", diport, state);

	printf("Setting DIN port %d listening to low-to-high event.\n", diport);
	ret = mx_din_set_event(diport, &event_func, DIN_EVENT_LOW_TO_HIGH, 0);
	if (ret < 0){
		fprintf(stderr, "Failed to set event of DIN port %d\n", diport);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Sleep for 3 seconds.\n\n");
	sleep(3);

	printf("Setting DOUT port %d to high.\n", doport);
	ret = mx_dout_set_state(doport, DIO_STATE_HIGH);
	if (ret < 0) {
		fprintf(stderr, "Failed to set DOUT port %d\n", doport);
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	sleep(1);
	return 0;
}
