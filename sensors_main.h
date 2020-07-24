/*
 * sensorsmain.h
 *
 *  Created on: Jul 9, 2020
 *      Author: Khoi Dang
 */

#ifndef SENSORS_MAIN_H_
#define SENSORS_MAIN_H_

#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <ti/drivers/GPIO.h>
#include "timerUS.h"
#include "timerRGB.h"
#include "debug_if.h"
#include <sensors_queues.h>
#include "uart_term.h"

extern void *mainThread(void *arg0);

#endif /* SENSORS_MAIN_H_ */
