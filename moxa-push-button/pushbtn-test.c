/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA Push button Library
 *
 * Description:
 *	Example code for demonstrating the usage of
 *	MOXA Push button Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <moxa/mx_pbtn.h>

extern char mx_errmsg[256];

void pressed_func(int sec)
{
	printf("\t--------\n");
	printf("\t This is in pressed_func, sec: %d\n", sec);
	printf("\t--------\n");
}

void released_func(int sec)
{
	printf("\t--------\n");
	printf("\t This is in released_func, sec: %d\n", sec);
	printf("\t--------\n");
}

void hold_func(int sec)
{
	printf("\t--------\n");
	printf("\t This is in hold_func, sec: %d\n", sec);
	printf("\t--------\n");
}

int main(int argc, char *argv[])
{
	int ret, btn_id;
	unsigned long hold_sec;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <hold_seconds>\n", argv[0]);
		fprintf(stderr, "\t0: function triggered every second\n");
		fprintf(stderr, "\t1 ~ 3600: function triggered over hold_seconds\n");
		exit(99);
	}
	hold_sec = atol(argv[1]);

	ret = mx_pbtn_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa pbtn control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Testing Push button:\n");

	btn_id = mx_pbtn_open(BUTTON_TYPE_SYSTEM, 1);
	if (btn_id < 0) {
		fprintf(stderr, "Open button failed\n");
		fprintf(stderr, "Error code: %d\n", btn_id);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	ret = mx_pbtn_pressed_event(btn_id, &pressed_func);
	if (ret < 0) {
		fprintf(stderr, "Set pressed function failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	ret = mx_pbtn_released_event(btn_id, &released_func);
	if (ret < 0) {
		fprintf(stderr, "Set released function failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	ret = mx_pbtn_hold_event(btn_id, &hold_func, hold_sec);
	if (ret < 0) {
		fprintf(stderr, "Set hold function failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Start testing. Press button to check the functions.\n");
	printf("\t[Ctrl + C] to terminate this process.\n\n");

	mx_pbtn_wait();

	mx_pbtn_close(btn_id);
	exit(0);
}
