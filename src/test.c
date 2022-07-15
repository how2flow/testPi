/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.08             */
/* last-update: 2022.07.15      */
/*------------------------------*/

#include <stdio.h>
#include <string.h>

#include "test.h"
#include "thread.h"

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

int gpio_test(int pin)
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

	return 0;
}

int serial_test(char *dev, void *serial_send, void *serial_receive) {
	int fd;
	pthread_t th1, th2;

	if ((fd = serialOpen(dev, BAUD)) < 0) {
		printf("ERROR\n");
		return 1;
	}

	printf("serial TEST\n");
	pthread_create(&th1, NULL, serial_send, (void *)&fd);
	pthread_create(&th2, NULL, serial_receive, (void *)&fd);

	while (1);

	return 0;
}

int spi_test(int dev_id, unsigned char* data, int size)
{
	int times;

	for (times = 0; times < 100; ++times) {
		if (wiringPiSPIDataRW(0, data, size) == -1) {
			return 0;
		}
	}

	return 1;
}
