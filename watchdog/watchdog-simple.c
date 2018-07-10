/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	Example code for Watch Dog Timer (Simple)
 *
 * Description:
 *	This example code shows how to tick watchdog device
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define WATCHDOG_DEVICE "/dev/watchdog"

int main(int argc, char *argv[])
{
	int fd;

	fd = open(WATCHDOG_DEVICE, O_WRONLY);
	if (fd < 0) {
		perror(WATCHDOG_DEVICE);
		exit(EXIT_FAILURE);
	}

	while (1) {
		if (write(fd, "\0", 1) != 1) {
			fprintf(stderr, "Write watchdog failed\n");
			return -1;
		}
		printf("Tick watchdog\n");
		sleep(10);
	}

	close(fd);
	return 0;
}
