#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "test.h"
#include "thread.h"

// options
static int options;
const char* sopts = "d:h";
static struct option lopts[] = {
	{"device", required_argument, 0, 'd'},
	{"help", 0, 0, 'h'},
	{NULL, 0, 0, 0}
};

// print
static int print_help(void)
{
	printf("Usage: uart [-opt] [--option]\n\n");
	printf("===== options =====\n");
	printf("-d --device: select device to serial test\n");
	printf("-h --help: print help message\n");
	printf("[e.g]\n");
	printf("./uart -d /dev/ttyS0\n");
	printf("./uart -h\n");

	return 0;
}

static int print_err(void)
{
	printf("add or correct option\n");
	printf("add option -h or --help, help use testPi.\n");
	printf("hint: $ sudo ./uart -h	or	$ sudo ./uart --help\n");

	return 0;
}

// main
int main(int argc, char **argv)
{
	int pin;

	if(argc == 1) {
		print_err();
		return -1;
	}

	wiringPiSetup();
	while ((options = getopt_long(argc, argv, sopts, lopts, NULL)) != -1) {
		switch (options) {
			/* test all */
			case 'd':
				serial_test(optarg, serial_send, serial_receive);
				break;
			case 'h':
				print_help();
				break;
			default:
				print_err();
				break;
		}
	}

	return 0;
}
