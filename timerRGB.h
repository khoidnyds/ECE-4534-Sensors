#ifndef TIMERRGB_H_
#define TIMERRGB_H_

#include <sensors_queues.h>
#include <ti/drivers/Timer.h>

#define Timer_RGB_PERIOD_IN_US  1000000 //1s

void initTimerRGB();
void timerRGBCallback(Timer_Handle myHandle, int_fast16_t status);
#endif
