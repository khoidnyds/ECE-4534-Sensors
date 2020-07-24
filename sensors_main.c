/*
 * sensorsmain.c
 *
 *  Created on: Jul 9, 2020
 *      Author: Khoi Dang
 */

#include <sensors_main.h>

void *mainThread(void *arg0)
{
    //dbgOutputLoc(DLOC_MAIN_BEGIN);
    initTimerUS();
    initTimerRGB();
    while(1){
        msgUS newMsgUS;
        msgRGB newMsgRGB;
        msgSwitch newMsgSwitch;
        msgMqtt newMsgMqtt;

        receiveMsgFromQueueUS(&newMsgUS);
        receiveMsgFromQueueRGB(&newMsgRGB);
        receiveMsgFromQueueSwitch(&newMsgSwitch);
    }
}
