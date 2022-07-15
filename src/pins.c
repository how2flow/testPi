/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.08             */
/*------------------------------*/

#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "test.h"

#define CASE 31

// AIN0, AIN1 value: wpi number
static int ain[2] = {29, 25};

// options
static int options;
const char* sopts = "abghs:";
static struct option lopts[] = {
	{"analog", 0, 0, 'a'},
	{"byte", 0, 0, 'b'},
	{"gpio", 0, 0, 'g'},
	{"help", 0, 0, 'h'},
	{"single", required_argument, 0, 's'},
	{NULL, 0, 0, 0}
};

// functions
static int empty_pins(int pin)
{
	switch(pin) {
		case 17:
		case 18:
		case 19:
		case 20:
		case 25:
		case 28:
		case 29:
			return 1;
		break;
		default:
			return 0;
		break;
	}
}

static int initailize_pins(void)
{
	for(int pin = 0; pin < (CASE + 1); pin++) {
		if (empty_pins(pin))
			continue;
		pinMode(pin,OUTPUT);
		digitalWrite(pin,LOW);
	}

	for(int pin = 0; pin < (CASE + 1); pin++) {
		if (empty_pins(pin))
			continue;
		pinMode(pin,INPUT);
	}

	return 0;
}

static int adc_pins(void)
{
	printf("[test analogRead]\n");
	initailize_pins();
	for(int pin = 0; pin < 20; pin++) {
		printf("%d: %d\n",ain[0],analogRead(ain[0]));
		printf("%d: %d\n",ain[1],analogRead(ain[1]));
		delay(500);
	}

	return 0;
}

static int gpio_byte(void)
{
	uint8_t num;

	printf("[test Byte]\n");
	initailize_pins();
	srand(time(NULL));

	for(int pin = 0; pin < BYTE; pin++) {
		pinMode(pin,OUTPUT);
	}

	num = rand()%256;
	digitalWriteByte(num);
	printf("Input: %d data: %d\n", num, digitalReadByte());

	return 0;
}

static int gpio_pins(void)
{
	printf("[test 40 header gpio pins]\n");
	initailize_pins();
	for(int pin = 0; pin < (CASE + 1); pin++) {
		if (empty_pins(pin))
			continue;
		gpio_test(pin);
	}

	return 0;
}

// print
static int print_help(void)
{
	printf("Usage: gpio [-opt] [--option]\n\n");
	printf("===== options =====\n");
	printf("-a --analog: test ADC pin 25, 29\n");
	printf("-b --byte: test gpio pins 0 ~ 7\n");
	printf("-g --gpio: test gpio 40 pins\n");
	printf("-h --help: print help message\n");
	printf("-s --single: test gpio single pin\n\n");
	printf("[e.g]\n");
	printf("./gpio -g\n");
	printf("./gpio -s 21\n");

	return 0;
}

static int print_err(void)
{
	printf("add or correct option\n");
	printf("add option -h or --help, help use testPi.\n");
	printf("hint: $ sudo ./gpio -h	or	$ sudo ./gpio --help\n");

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
			case 'a':
				adc_pins();
				break;
			case 'b':
				gpio_byte();
				break;
			case 'g':
				gpio_pins();
				break;
				// print help
			case 'h':
				print_help();
				break;
			case 's':
				pin = atoi(optarg);
				gpio_test(pin);
				break;
			default:
				print_err();
				break;
		}
	}

	return 0;
}
