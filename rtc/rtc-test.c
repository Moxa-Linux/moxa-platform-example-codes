/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	Example code for Real Time Clock
 *
 * Description:
 *	This example code shows how to use Linux RTC API
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */


#include <stdio.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define RTC_DEVICE "/dev/rtc0"

void usage(FILE *fp)
{
	fprintf(fp, "Usage:\n");
	fprintf(fp, "	./rtc-test [-g|-s <#datetime>]\n\n");
	fprintf(fp, "OPTIONS:\n");
	fprintf(fp, "	-g\n");
	fprintf(fp, "		Get the current datetime of RTC.\n");
	fprintf(fp, "	--s <#datetime>\n");
	fprintf(fp, "		Set the datetime of RTC.\n");
	fprintf(fp, "\n");
	fprintf(fp, "Example:\n");
	fprintf(fp, "	Get the current datetime of RTC\n");
	fprintf(fp, "	# ./rtc-test -g\n");
	fprintf(fp, "\n");
	fprintf(fp, "	Set the datetime of RTC to 2018/1/1-12:34:56\n");
	fprintf(fp, "	# ./rtc-test -s 2018/1/1-12:34:56\n");
	fprintf(fp, "\n");
}

int open_rtc(void)
{
	int fd;

	fd = open(RTC_DEVICE, O_RDONLY);
	if (fd < 0) {
		perror(RTC_DEVICE);
		exit(EXIT_FAILURE);
	}
	return fd;
}

void read_rtc(void)
{
	struct rtc_time rtc_tm;
	int fd;

	fd = open_rtc();
	if (ioctl(fd, RTC_RD_TIME, &rtc_tm) == -1) {
		perror("ioctl: RTC_RD_TIME");
		close(fd);
		exit(EXIT_FAILURE);
	}

	printf("Current datetime is %d/%d/%d-%02d:%02d:%02d\n",
		rtc_tm.tm_year + 1900, rtc_tm.tm_mon + 1, rtc_tm.tm_mday,
		rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	close(fd);
}

void set_rtc(char *optarg)
{
	struct rtc_time rtc_tm;
	int fd, ret;

	ret = sscanf(optarg, "%d/%d/%d-%02d:%02d:%02d",
		&rtc_tm.tm_year, &rtc_tm.tm_mon, &rtc_tm.tm_mday,
		&rtc_tm.tm_hour, &rtc_tm.tm_min, &rtc_tm.tm_sec);
	if (ret < 0) {
		perror(optarg);
		exit(EXIT_FAILURE);
	}

	rtc_tm.tm_mon -= 1;
	rtc_tm.tm_year -= 1900;

	fd = open_rtc();
	if (ioctl(fd, RTC_SET_TIME, &rtc_tm) == -1) {
		perror("ioctl: RTC_SET_TIME");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int main(int argc, char *argv[])
{
	int c;

	while ((c = getopt(argc, argv, "hgs:")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			exit(0);
		case 'g':
			read_rtc();
			exit(0);
		case 's':
			set_rtc(optarg);
			read_rtc();
			exit(0);
		default:
			break;
		}
	}

	usage(stderr);
	exit(-1);
}
