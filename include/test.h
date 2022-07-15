/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.08             */
/*------------------------------*/

#ifndef _TEST_H_
#define _TEST_H_

// include
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiSPI.h>

// unit
#define BYTE 8

// phy
#define PHY 40+1

// serial
#define BAUD 115200
// spi
#define	SPI_BUS 0
#define	SPI_SIZE (1024*1024)
#define	SPI_TIMES 100

//test functions
int gpio_test(int pin);
int serial_test(char *dev, void *serial_send, void *serial_receive);
int spi_test(int dev_id, unsigned char* data, int size);
/*--------------------------------------------------------*/
#endif
