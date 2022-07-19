/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.18             */
/* last-update: 2022.07.19      */
/*------------------------------*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "test.h"

// print
static int print_help(void)
{
	printf("Usage: i2c [-opt] [--option]\n\n");
	printf("===== options =====\n");
	printf("-h --help: print help message\n");
	printf("[e.g]\n");
	printf("./i2c\n");
	printf("./i2c -h\n");

	return 0;
}

static int print_err(void)
{
	printf("add or correct option\n");
	printf("add option -h or --help, help use testPi.\n");
	printf("hint: $ sudo ./i2c -h	or	$ sudo ./i2c --help\n");

	return 0;
}

// main
int main(int argc, char **argv)
{
	if (argc >= 2) {
		if (!strcmp("-h", (const char*)argv[1]) || !strcmp("--help", (const char*)argv[1])) {
			print_help();
		}
		else {
			print_err();
		}
		return 0;
	}

	if (!getuid()) {
		printf("===== detect i2c bus 0 =====\n");
		i2c_test(0);
		delay(300);
		printf("===== detect i2c bus 1 =====\n");
		i2c_test(1);
	}
	else {
		printf("run as root for detect i2c devices.\n");
	}

	return 0;
}
