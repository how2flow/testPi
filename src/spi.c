#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "test.h"

static int fd;

static int spi_setup (int speed)
{
	if ((fd = wiringPiSPISetup(SPI_BUS, speed)) < 0) {
		fprintf(stderr, "Can't open the SPI bus: %s\n", strerror (errno));
		exit(EXIT_FAILURE);
	}

	return 1;
}

// print
static int print_help(void)
{
	printf("Usage: spi [-opt] [--option]\n\n");
	printf("===== options =====\n");
	printf("-h --help: print help message\n");
	printf("[e.g]\n");
	printf("./spi\n");
	printf("./spi -h\n");

	return 0;
}

static int print_err(void)
{
	printf("add or correct option\n");
	printf("add option -h or --help, help use testPi.\n");
	printf("hint: $ sudo ./spi -h	or	$ sudo ./spi --help\n");
	return 0;
}

// main
int main(int argc, char **argv)
{
	int ret;
	int speed, size;
	unsigned char *data;
	unsigned int start, end;
	double timePerTransaction, perfectTimePerTransaction, dataSpeed;

	if (argc >= 2) {
		if (!strcmp("-h", (const char*)argv[1]) || !strcmp("--help", (const char*)argv[1])) {
			print_help();
		}
		else {
			print_err();
		}
		return 0;
	}

	if ((data = malloc(SPI_SIZE)) == NULL) {
		fprintf(stderr, "Unable to allocate buffer: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	wiringPiSetup();
	for (speed = 1; speed <= 32; speed *= 2)
	{
		printf("+-------+--------+----------+----------+-----------+------------+\n");
		printf("|   MHz |   Size | mS/Trans |      TpS |    Mb/Sec | Latency mS |\n");
		printf("+-------+--------+----------+----------+-----------+------------+\n");

		ret = spi_setup(speed * 1000000);
		for (size = 1; size <= SPI_SIZE; size *= 2) {
			printf("| %5d | %6d ", speed, size);
			start = millis();
			ret = spi_test(SPI_BUS, data, size);
			end = millis();

			if (!ret)
				break;

			timePerTransaction = ((double)(end - start) / (double)SPI_TIMES) / 1000.0;
			dataSpeed = (double)(size * 8) / (1024.0 * 1024.0) / timePerTransaction;
			perfectTimePerTransaction = ((double)(size * 8)) / ((double)(speed * 1000000));

			printf("| %8.3f ", timePerTransaction * 1000.0);
			printf("| %8.1f ", 1.0 / timePerTransaction);
			printf("| %9.5f ", dataSpeed);
			printf("|   %8.5f ", (timePerTransaction - perfectTimePerTransaction) * 1000.0);
			printf("|\n");
		}

		close(fd);
		printf("+-------+--------+----------+----------+-----------+------------+\n");
		printf("\n");
	}

	return 0;
}
