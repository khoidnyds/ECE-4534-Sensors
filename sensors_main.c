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

        Message("\r\n");
        if(newMsgUS.position==front){
            Message("Front: ");
        }
        else if(newMsgUS.position==left){
            Message("Left : ");
        }
        else if(newMsgUS.position==right){
            Message("Right: ");
        }
        else if(newMsgUS.position==back){
            Message("Back : ");
        }
        char text[12];
        sprintf(text, "%d", newMsgUS.distance);
        Message(text);


//        Message("\r\n");
//        Message("Carrying box: ");
//        if(newMsgSwitch.carrying==yes){
//            Message("yes");
//        }
//        else {
//            Message("no");
//        }
//
//        Message("\r\nFloor color: ");
//        switch(newMsgRGB.color){
//        case red:
//            Message("Red");
//            break;
//        case blue:
//            Message("Blue");
//            break;
//        case green:
//            Message("Green");
//            break;
//        case white:
//            Message("White");
//            break;
//        case black:
//            Message("Black");
//            break;
//        case unknown:
//            Message("Unknown");
//            break;
//        }
    }
}
