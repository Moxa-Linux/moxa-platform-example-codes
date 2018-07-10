/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA LED Library
 *
 * Description:
 *	Example code for demonstrating the usage of MOXA LED Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <moxa/mx_led.h>

extern char mx_errmsg[256];

void test_led(int group, int index)
{
	int ret;

	printf("Setting group: %d, index: %d\n", group, index);

	printf("\ton\n");
	ret = mx_led_set_brightness(LED_TYPE_PROGRAMMABLE, group, index, LED_STATE_ON);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);

	printf("\toff\n");
	ret = mx_led_set_brightness(LED_TYPE_PROGRAMMABLE, group, index, LED_STATE_OFF);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);

	printf("\tblink\n");
	ret = mx_led_set_brightness(LED_TYPE_PROGRAMMABLE, group, index, LED_STATE_BLINK);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);

	printf("\toff\n");
	ret = mx_led_set_brightness(LED_TYPE_PROGRAMMABLE, group, index, LED_STATE_OFF);
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);
}

int main(int argc, char *argv[])
{
	int ret, group, index, num_of_group, num_of_led;

	ret = mx_led_init();
	if (ret < 0) {
		fprintf(stderr, "Initialize Moxa led control library failed\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("Testing all programmable LEDs:\n");

	ret = mx_led_get_num_of_groups(LED_TYPE_PROGRAMMABLE, &num_of_group);
	if (ret < 0) {
		fprintf(stderr, "Failed to get number of groups\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	ret = mx_led_get_num_of_leds_per_group(LED_TYPE_PROGRAMMABLE, &num_of_led);
	if (ret < 0) {
		fprintf(stderr, "Failed to get number of leds\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	for (group = 1; group <= num_of_group; group++) {
		for (index = 1; index <= num_of_led; index++)
			test_led(group, index);
	}
	printf("\n");

	printf("Setting all led on\n\n");
	ret = mx_led_set_all_on();
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);

	printf("Setting all led off\n\n");
	ret = mx_led_set_all_off();
	if (ret < 0) {
		fprintf(stderr, "Failed, Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}
	sleep(1);

	return 0;
}
