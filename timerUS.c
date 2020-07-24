#include "timerUS.h"

void initTimerUS()
{
    Timer_Params params;
    Timer_Handle timerUS;

    Timer_init();
    Timer_Params_init(&params);
    params.period = Timer_US_PERIOD_IN_US;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timerUS = Timer_open(CONFIG_TIMER_0, &params);

    if (timerUS == NULL) {
        while(1);
    }

    if (Timer_start(timerUS) == Timer_STATUS_ERROR) {
        while(1);
    }
}

void timerCallback(Timer_Handle handle, int_fast16_t status){
    msgTriggerUS newMsgTriggerUS;
    newMsgTriggerUS.triggerUS = true;
    sendMsgToQueueTriggerUS(&newMsgTriggerUS);
}




