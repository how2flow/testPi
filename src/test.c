#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "test.h"

//wpi number at 40 pin header
int phyHeaderPins[PHY] = {
	-1,
	-1,-1,
	 8,-1,
	 9,-1,
	 7,15,
	-1,16,
	 0, 1,
	 2,-1,
	 3, 4,
	-1, 5,
	12,-1,
	13, 6,
	14,10,
	-1,11,
	30,31,
	21,-1,
	22,26,
	23,-1,
	24,27,
	25,28,
	-1,29
};

void gpio_test(int pin)
{
	pinMode(pin,OUTPUT);
	digitalWrite(pin,HIGH);
	printf("HIGH -> pin #%d: %d\n", pin, digitalRead(pin));
	delay(500);
	digitalWrite(pin,LOW);
	printf("LOW -> pin #%d: %d\n", pin, digitalRead(pin));
	delay(500);
	//reset pin
	pinMode(pin,INPUT);
}

int spi_test(int dev_id, unsigned char* data, int size)
{
	int times;

	for (times = 0; times < 100; ++times) {
		if (wiringPiSPIDataRW(0, data, size) == -1) {
			printf("SPI failure: %s\n", strerror(errno));
			return 0;
		}
	}

	return 1;
}
