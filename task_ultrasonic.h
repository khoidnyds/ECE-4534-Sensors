/*
 * ultrasonic.h
 *
 *  Created on: Jul 20, 2020
 *      Author: Kaito
 */

#ifndef TASK_ULTRASONIC_H_
#define TASK_ULTRASONIC_H_

#include <sensors_queues.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <ti/drivers/GPIO.h>
#include "ti_drivers_config.h"
#include "uart_term.h"
#include <ti/devices/cc32xx/inc/hw_types.h>
#include <ti/devices/cc32xx/driverlib/prcm.h>
#include <ti/drivers/Timer.h>

#define AMBIENT_TEMP            30 // in Celcius
#define HIGH                    1
#define LOW                     0
#define SUCCESS                 0
#define FAIL                    -1
#define MAX_COUNT               3 //sensor update every 0.84s
#define Timer_ECHO_PERIOD_IN_US 1000000

Timer_Handle timerUS;
double start, end;
double us1_total, us2_total, us3_total, us4_total;
int us1_count, us2_count, us3_count, us4_count;
typedef enum {INIT, STATE_US1, STATE_US2, STATE_US3, STATE_US4} state;
state currentState;

void* usTask(void *arg0);
void getTime(uint_least8_t index);
void fsm(uint_least8_t pinin, uint_least8_t pinout);
void echoCallback(Timer_Handle handle, int_fast16_t status);

#endif /* TASK_ULTRASONIC_H_ */
