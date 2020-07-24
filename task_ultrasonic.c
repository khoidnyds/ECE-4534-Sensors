#include <task_ultrasonic.h>

void* usTask(void *arg0){

    Timer_Params params;

    Timer_init();
    Timer_Params_init(&params);
    params.period = Timer_ECHO_PERIOD_IN_US;
    params.periodUnits = Timer_PERIOD_COUNTS;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = echoCallback;

    timerUS = Timer_open(CONFIG_TIMER_2, &params);
    if (timerUS == NULL) {
        Message("\r\nOpen timerUS failed");
        while(1);
    }

    if (Timer_start(timerUS) == Timer_STATUS_ERROR) {
        Message("\r\nStart timerUS failed");
        while(1);
    }

    currentState = INIT;
    currentInt = START;
    start=0;
    end=0;
    while(1){
        msgTriggerUS newMsgTriggerUS;
        receiveMsgFromQueueTriggerUS(&newMsgTriggerUS);
        if(newMsgTriggerUS.triggerUS){
        switch(currentState){
            case INIT:
                fsm(US1_TRIGGER, US1_ECHO);
                currentState = STATE_US1;
                break;
            case STATE_US1:
                fsm(US2_TRIGGER, US2_ECHO);
                currentState = STATE_US2;
                break;
            case STATE_US2:
                fsm(US3_TRIGGER, US3_ECHO);
                currentState = STATE_US3;
                break;
            case STATE_US3:
                fsm(US4_TRIGGER, US4_ECHO);
                currentState = STATE_US4;
                break;
            case STATE_US4:
                fsm(US1_TRIGGER, US1_ECHO);
                currentState = STATE_US1;
                break;
            default:
                break;
            }
        }
    }
}
void fsm(uint_least8_t pinin, uint_least8_t pinout){
    GPIO_setConfig(pinin, GPIO_CFG_OUTPUT | GPIO_CFG_OUT_LOW);
    GPIO_write(pinin, HIGH);
    int i;
    for(i=0;i<30;i++);
    GPIO_write(pinin, LOW);

    GPIO_setCallback(pinout, getTime);
    GPIO_enableInt(pinout);
}

void getTime(uint_least8_t index){
    switch(currentInt){
    case START:{
        currentInt = END;
        start = Timer_getCount(timerUS);
        break;
    }
    case END:{
        currentInt = START;
        end = Timer_getCount(timerUS);

        double speed = (331 + 0.6 * AMBIENT_TEMP) / 1000;
        double distance = speed * (end-start) / 16; //80MHz and 2*distance

        switch(index){
            case US1_ECHO:
                us1_total += distance;
                us1_count += 1;
                break;
            case US2_ECHO:
                us2_total += distance;
                us2_count += 1;
                break;
            case US3_ECHO:
                us3_total += distance;
                us3_count += 1;
                break;
            case US4_ECHO:
                us4_total += distance;
                us4_count += 1;
                break;
            default:
                break;
        }

        // take average in MAX_COUNT times measurement and send to queue
        if(us1_count == MAX_COUNT || us2_count == MAX_COUNT ||
           us3_count == MAX_COUNT || us4_count == MAX_COUNT){
            msgUS newMsgUS;
            if(us1_count==MAX_COUNT){
                newMsgUS.position = front;
                newMsgUS.distance = us1_total/MAX_COUNT;
                us1_total = 0;
                us1_count = 0;
            }
            else if(us2_count==MAX_COUNT){
                newMsgUS.position = left;
                newMsgUS.distance = us2_total/MAX_COUNT;
                us2_total = 0;
                us2_count = 0;
            }
            else if(us3_count==MAX_COUNT){
                newMsgUS.position = right;
                newMsgUS.distance = us3_total/MAX_COUNT;
                us3_total = 0;
                us3_count = 0;
            }
            else {
                newMsgUS.position = back;
                newMsgUS.distance = us4_total/MAX_COUNT;
                us4_total = 0;
                us4_count = 0;
            }

            newMsgUS.type = ultrasonic;
            int success = sendMsgToQueueUS(&newMsgUS);

            if(success==FAIL){
                Message("\r\nSend US message failed");
                while(1);
            }
        }
        start=0;
        end=0;
        break;
    }
    default:
        break;
    }
}
void echoCallback(Timer_Handle handle, int_fast16_t status){
    // do nothing
}
