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
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include "ti_drivers_config.h"
#include "timerUS.h"
#include "timerRGB.h"
#include "debug_if.h"

#define LOOP_ERROR_THRESH 50

extern void *mainThread(void *arg0);
void i2cCallback(I2C_Handle i2c, I2C_Transaction* i2cTransaction, bool success);

#endif /* SENSORS_MAIN_H_ */
