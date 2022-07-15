/*------------------------------*/
/* Author: steve.jeong          */
/* e-mail: jkhpro1003@gmail.com */
/* date: 2022.07.15             */
/*------------------------------*/

#ifndef _THREAD_H_
#define _THREAD_H_

// include
#include <pthread.h>

// threads
void *serial_receive(void *);
void *serial_send(void *);
/*--------------------------------------------------------*/
#endif
