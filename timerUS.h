
#ifndef TIMERUS_H_
#define TIMERUS_H_

#include <sensors_queues.h>
#include <ti/drivers/Timer.h>
#include "ti_drivers_config.h"
#include <stdio.h>
#include "uart_term.h"
#include <ti/drivers/PWM.h>
#include <unistd.h>
#include <stddef.h>
#include <ti/drivers/GPIO.h>

#define Timer_US_PERIOD_IN_US   70000 //70ms
#define AMBIENT_TEMP            30 // in Celcius
#define HIGH                    1
#define LOW                     0
#define SUCCESS                 0
#define FAIL                    -1
#define MAX_COUNT               3 //sensor update every 0.84s
double start, end;
int us1_total, us2_total, us3_total, us4_total;
int us1_count, us2_count, us3_count, us4_count;
Timer_Handle timerUS;
typedef enum {INIT, STATE_US1, STATE_US2, STATE_US3, STATE_US4} state;
state currentState;

void initTimerUS();
void getTime(uint_least8_t index);
void fsm(uint_least8_t pinin, uint_least8_t pinout);
void timerCallback(Timer_Handle handle, int_fast16_t status);
#endif /* TIMERONE_H_ */
