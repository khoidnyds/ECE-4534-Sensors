
#ifndef TIMERUS_H_
#define TIMERUS_H_

#include <sensors_queues.h>
#include <ti/drivers/Timer.h>

#define Timer_US_PERIOD_IN_US   70000 //70ms

void initTimerUS();
void timerCallback(Timer_Handle handle, int_fast16_t status);
#endif /* TIMERONE_H_ */
