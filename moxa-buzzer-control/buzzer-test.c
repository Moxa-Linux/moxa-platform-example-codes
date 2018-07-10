/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA Buzzer Library
 *
 * Description:
 *	Example code for demonstrating the usage of MOXA Buzzer Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <moxa/mx_buzzer.h>

#define EXECUTION_TIME 11

extern char mx_errmsg[256];

int main(int argc, char *argv[])
{
	unsigned long duration;
	int ret;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <duration>\n", argv[0]);
		fprintf(stderr, "\t0: Keep beeping\n");
		fprintf(stderr, "\t1 ~ 10: in seconds\n");
		fprintf(stderr, "\tNote: the range of duration is 1 ~ 60 for\n");
		fprintf(stderr, "\t      Moxa buzzer control library\n");
		exit(99);
	}
	duration = atol(argv[1]);

	ret = mx_buzzer_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa buzzer control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Testing Buzzer:\n");
	printf("\tThe process will be executed for %d seconds.\n\n", EXECUTION_TIME);

	if (duration > 10) {
		fprintf(stderr, "Duration out of range: must be 0 ~ 10\n");
		exit(1);
	} else if (duration > 0) {
		printf("Play Buzzer for %ld seconds.\n", duration);
	} else {
		printf("Keep playing Buzzer.\n");
	}

	ret = mx_buzzer_play_sound(duration);
	if (ret < 0) {
		fprintf(stderr, "Failed to play Buzzer.\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Sleep for %d seconds.\n", EXECUTION_TIME);
	sleep(EXECUTION_TIME);

	if (duration == 0) {
		printf("\nStop Buzzer.\n");
		ret = mx_buzzer_stop_sound();
		if (ret < 0) {
			fprintf(stderr, "Failed to stop Buzzer.\n");
			fprintf(stderr, "Error code: %d\n", ret);
			fprintf(stderr, "Error message: %s\n", mx_errmsg);
			exit(1);
		}
	}

	exit(0);
}
