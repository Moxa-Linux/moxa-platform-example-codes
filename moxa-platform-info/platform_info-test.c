/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Name:
 *	C Example code for MOXA Platform Information Library
 *
 * Description:
 *	Example code for demonstrating the usage of
 *	MOXA Platform Information Library in C
 *
 * Authors:
 *	2018	Ken CJ Chou	<KenCJ.Chou@moxa.com>
 */

#include <stdio.h>
#include <json-c/json.h>
#include <moxa/mx_platform_info.h>

extern char mx_errmsg[256];

int main(int argc, char *argv[])
{
	struct json_object *obj, *val;
	char **profiles;
	const char *conf_version;
	int ret, num, i;

	ret = mx_get_number_of_interfaces(&num);
	if (ret < 0) {
		fprintf(stderr, "Failed to get number of interfaces\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	printf("There are %d interfaces on this device:\n", num);

	ret = mx_get_platform_interface(&profiles);
	if (ret < 0) {
		fprintf(stderr, "Failed to get platform interfaces\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}


	for (i = 0; i < num; i++) {
		printf("\t--------\n");
		printf("\t(%d) \"%s\":\n", i + 1, profiles[i]);

		ret = mx_get_profile(profiles[i], &obj);
		if (ret < 0) {
			fprintf(stderr, "\t\tFailed to get profile\n");
			fprintf(stderr, "\t\tError code: %d\n", ret);
			fprintf(stderr, "\t\tError message: %s\n", mx_errmsg);
			continue;
		}

		if (!json_object_object_get_ex(obj, "CONFIG_VERSION", &val)) {
			fprintf(stderr, "\t\tFailed to get profile's config version\n");
			fprintf(stderr, "\t\tjson-c parsing error at key: \"CONFIG_VERSION\"\n");
			continue;
		}

		conf_version = json_object_get_string(val);
		printf("\t\tConfig version: %s\n", conf_version);
	}

	ret = mx_free_platform_interface(profiles);
	if (ret < 0) {
		fprintf(stderr, "Failed to free platform interfaces\n");
		fprintf(stderr, "Error code: %d\n", ret);
		fprintf(stderr, "Error message: %s\n", mx_errmsg);
		exit(1);
	}

	exit(0);
}
