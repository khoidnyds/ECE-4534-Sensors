#include "timerRGB.h"

void initTimerRGB()
{
    Timer_Handle timerRGB;
    Timer_Params params;

    Timer_init();
    Timer_Params_init(&params);
    params.period = Timer_RGB_PERIOD_IN_US;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerRGBCallback;
    timerRGB = Timer_open(CONFIG_TIMER_1, &params);
    if (timerRGB == NULL) {
        // Failed to initialized timer
        while(1);
    }
    if (Timer_start(timerRGB) == Timer_STATUS_ERROR) {
        // Failed to start timer
        while(1);
    }
//    dbgOutputLoc(DLOC_TIMER_US_INIT_SUCCESS);

    return;
}

void timerRGBCallback(Timer_Handle myHandle, int_fast16_t status)
{
    msgTriggerRGBSwitch newTriggerRGBSwitch;
    newTriggerRGBSwitch.triggerRGBSwitch = true;
    sendMsgToQueueTriggerRGBSwitch(&newTriggerRGBSwitch);
}



