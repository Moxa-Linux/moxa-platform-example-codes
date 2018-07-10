/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	Example code for Watch Dog Timer (Test)
 *
 * Description:
 *	This example code shows how to use Linux WDT API
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>

#define WATCHDOG_DEVICE "/dev/watchdog"

void usage(FILE *fp)
{
	fprintf(fp, "Usage:\n");
	fprintf(fp, "	./watchdog-test [-d|-e]\n\n");
	fprintf(fp, "OPTIONS:\n");
	fprintf(fp, "	-d\n");
	fprintf(fp, "		Disable the watchdog device.\n");
	fprintf(fp, "	-e\n");
	fprintf(fp, "		Enable the watchdog device.\n");
	fprintf(fp, "\n");
	fprintf(fp, "Example:\n");
	fprintf(fp, "	Test ticking WDT\n");
	fprintf(fp, "	# ./watchdog-test\n");
	fprintf(fp, "\n");
	fprintf(fp, "	Disable WDT\n");
	fprintf(fp, "	# ./watchdog-test -d\n");
	fprintf(fp, "\n");
	fprintf(fp, "	Enable WDT\n");
	fprintf(fp, "	# ./watchdog-test -e\n");
	fprintf(fp, "\n");
}

/*
 * This function simply sends an IOCTL to the driver, which in turn ticks
 * the PC Watchdog card to reset its internal timer so it doesn't trigger
 * a computer reset.
 */
static void keep_alive(int fd)
{
	int dummy = 0;

	ioctl(fd, WDIOC_KEEPALIVE, &dummy);
}

int main(int argc, char *argv[])
{
	int flags, get_timeout, set_timeout = 60;
	int fd;
	int c;

	fd = open(WATCHDOG_DEVICE, O_WRONLY);
	if (fd < 0) {
		perror(WATCHDOG_DEVICE);
		exit(EXIT_FAILURE);
	}

	while ((c = getopt(argc, argv, "hde")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			close(fd);
			exit(0);
		case 'd':
			flags = WDIOS_DISABLECARD;
			ioctl(fd, WDIOC_SETOPTIONS, &flags);
			printf("Watchdog card disabled.\n");
			close(fd);
			exit(0);
		case 'e':
			flags = WDIOS_ENABLECARD;
			ioctl(fd, WDIOC_SETOPTIONS, &flags);
			printf("Watchdog card enabled.\n");
			close(fd);
			exit(0);
		default:
			usage(stderr);
			close(fd);
			exit(-1);
		}
	}

	ioctl(fd, WDIOC_GETTIMEOUT, &get_timeout);
	printf("The Default timeout is %d seconds\n", get_timeout);
	ioctl(fd, WDIOC_SETTIMEOUT, &set_timeout);
	printf("The timeout is set to %d seconds\n", set_timeout);
	ioctl(fd, WDIOC_GETTIMEOUT, &get_timeout);
	printf("The timeout is %d seconds\n", get_timeout);

	while (1) {
		keep_alive(fd);
		printf("Tick watchdog\n");
		sleep(10);
	}

	close(fd);
	return 0;
}
