#include <sensors_queues.h>

QueueHandle_t xQueueUS = NULL;
QueueHandle_t xQueueRGB = NULL;
QueueHandle_t xQueueSwitch = NULL;
QueueHandle_t xQueueMQTT = NULL;
QueueHandle_t xQueueTriggerUS = NULL;
QueueHandle_t xQueueTriggerRGBSwitch = NULL;

int initQueue(){
    xQueueUS = xQueueCreate(QUEUESIZE, sizeof(msgUS));
    xQueueRGB = xQueueCreate(QUEUESIZE, sizeof(msgRGB));
    xQueueSwitch = xQueueCreate(QUEUESIZE, sizeof(msgSwitch));
    xQueueTriggerUS = xQueueCreate(QUEUESIZE, sizeof(msgTriggerUS));
    xQueueTriggerRGBSwitch = xQueueCreate(QUEUESIZE, sizeof(msgTriggerRGBSwitch));
    xQueueMQTT = xQueueCreate(QUEUESIZE, sizeof(msgMqtt));

    if(xQueueUS == NULL || xQueueRGB == NULL || xQueueSwitch == NULL ||
       xQueueTriggerUS == NULL || xQueueTriggerRGBSwitch == NULL || xQueueMQTT == NULL){
        //dbgOutputLoc(DLOC_QUEUES_CREATED_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_QUEUES_CREATED_SUCCESS);
    return 0;
}

int sendMsgToQueueUS(msgUS* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueUS, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_US_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_US_SEND_SUCCESS);
    return 0;
}

int receiveMsgFromQueueUS(msgUS* outMsg){
    BaseType_t result = xQueueReceiveFromISR(xQueueUS, outMsg, pdFALSE);
    if (result != pdPASS){
        //dbgOutputLoc(DLOC_MESSAGE_US_RECEIVE_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_US_RECEIVE_SUCCESS);
    return 0;
}

int sendMsgToQueueRGB(msgRGB* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueRGB, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_RGB_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_RGB_SEND_SUCCESS);
    return 0;
}

int receiveMsgFromQueueRGB(msgRGB* outMsg){
    BaseType_t result = xQueueReceiveFromISR(xQueueRGB, outMsg, pdFALSE);
    if (result != pdPASS){
        //dbgOutputLoc(DLOC_MESSAGE_RGB_RECEIVE_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_RGB_RECEIVE_SUCCESS);
    return 0;
}
int sendMsgToQueueSwitch(msgSwitch* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueSwitch, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_SUCCESS);
    return 0;
}
int receiveMsgFromQueueSwitch(msgSwitch* outMsg){
    BaseType_t result = xQueueReceiveFromISR(xQueueSwitch, outMsg, pdFALSE);
    if (result != pdPASS){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_SUCCESS);
    return 0;
}

int sendMsgToQueueTriggerUS(msgTriggerUS* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueTriggerUS, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_SUCCESS);
return 0;
}

int receiveMsgFromQueueTriggerUS(msgTriggerUS* outMsg){
    BaseType_t result = xQueueReceive(xQueueTriggerUS, outMsg, portMAX_DELAY);
    if (result != pdPASS){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_SUCCESS);
    return 0;
}

int sendMsgToQueueTriggerRGBSwitch(msgTriggerRGBSwitch* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueTriggerRGBSwitch, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_SUCCESS);
return 0;
}

int receiveMsgFromQueueTriggerRGBSwitch(msgTriggerRGBSwitch* outMsg){
    BaseType_t result = xQueueReceive(xQueueTriggerRGBSwitch, outMsg, portMAX_DELAY);
    if (result != pdPASS){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_RECEIVE_SUCCESS);
    return 0;
}
int sendMsgToQueueMQTT(msgMqtt* inMsg){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t result = xQueueSendToBackFromISR(xQueueMQTT, inMsg, &xHigherPriorityTaskWoken);
    if (result != pdTRUE){
        //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_FAIL);
        return -1;
    }
    //dbgOutputLoc(DLOC_MESSAGE_SWITCH_SEND_SUCCESS);
    return 0;
}
