/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.15             */
/* last-update: 2022.07.15      */
/*------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "thread.h"

char th_text[100] = {'\0'};

void *serial_receive(void *arg)
{
	int fd;

	fd = *(int *)arg;
	printf("1");
	while (1) {
		if (serialDataAvail(fd)) {
			printf("%c", serialGetchar(fd));
			serialFlush(fd);
		}
	}
}

void *serial_send(void *arg)
{
	int fd;

	fd = *(int *)arg;
	while (1) {
		printf("\n send text : ");
		fgets(th_text, 100, stdin);
		fflush(stdin);
		serialPuts(fd, th_text);
		delay(100);
	}
}

