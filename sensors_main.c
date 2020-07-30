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


//        receiveMsgFromQueueRGB(&newMsgRGB);
//        newMsgMqtt.payload = "colors";
//        newMsgMqtt.topic = "/sensors/colors"
//
//        receiveMsgFromQueueSwitch(&newMsgSwitch);
//        newMsgMqtt.payload = "switch";
//        newMsgMqtt.topic = "/sensors/switch"


//        if(newMsgMqtt.statsCmd==RECEIVED){
//            dbgOutputLoc(DLOC_GT_RECEIVED);
//            LOG_INFO("TOPIC: %s \tPAYLOAD: %s\r\n", outMsg.topic, outMsg.payload);
//        }
//        else{
//
//            dbgOutputLoc(DLOC_GT_MAKEMSG_START);
//            outMsg.timestamp=(portTICK_PERIOD_MS*xTaskGetTickCount())/1000.0;
//            dbgOutputLoc(DLOC_GT_MAKEMSG_TS);
//            outMsg.sequenceNum=seqNum;
//            dbgOutputLoc(DLOC_GT_MAKEMSG_SN);
//            seqNum++;
//            strcpy(outMsg.payload, PUB_MESSAGE);
//            dbgOutputLoc(DLOC_GT_MAKEMSG_PAYLOAD);
//            outMsg.statsCmd = PUBLISHED;
//            strcpy(outMsg.topic, PUB_TOPIC_0);
//            dbgOutputLoc(DLOC_GT_MAKEMSG_TOPIC);
//            outMsg.msgType = GENERAL;
//            strcpy(sendMsg.payload, "[");
//            json_pack(&outMsg, sendMsg.payload);
//            dbgOutputLoc(DLOC_GT_MSG_PACKED);
//            strcat(sendMsg.payload, "]");
//            dbgOutputLoc(DLOC_GT_MAKEMSG_FINISH);
//            strcpy(sendMsg.topic, outMsg.topic);
//            sendToMqttQueue(&sendMsg);
//
//            dbgOutputLoc(DLOC_GT_STAT_SEND);
//            if(sendToStatsQueue(&outMsg)){
//                errorHalt("error adding to queue");
//                dbgOutputLoc(DLOC_GT_ERROR);
//            }
//        }

//        Message("\r\n");
//        if(newMsgUS.position==front){
//            Message("Front: ");
//        }
//        else if(newMsgUS.position==left){
//            Message("Left : ");
//        }
//        else if(newMsgUS.position==right){
//            Message("Right: ");
//        }
//        else if(newMsgUS.position==back){
//            Message("Back : ");
//        }
//        char text[12];
//        sprintf(text, "%d", newMsgUS.distance);
//        Message(text);

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
