/*
 * sensor_queue.h
 *
 *  Created on: Jun 14, 2020
 *      Author: Khoi Dang
 */

#ifndef SENSOR_QUEUE_H
#define SENSOR_QUEUE_H

#include <FreeRTOS.h>
#include <queue.h>
#include "uart_term.h"
#include <stdio.h>


extern QueueHandle_t xQueueUS;
extern QueueHandle_t xQueueRGB;
extern QueueHandle_t xQueueSwitch;
extern QueueHandle_t xQueueTriggerUS;
extern QueueHandle_t xQueueTriggerRGBSwitch;
extern QueueHandle_t xQueueMQTT;

typedef enum { front, left, right, back } posUS;
typedef enum { red, green, blue, white, black, unknown } colors;
typedef enum { yes, no } carryingBox;
typedef enum { ultrasonic, color, limitSwitch } msgType;

typedef struct {
    msgType type;
    posUS position;
    unsigned int distance;
} msgUS;

typedef struct {
    msgType type;
    colors color;
} msgRGB;

typedef struct {
    msgType type;
    carryingBox carrying;
} msgSwitch;

typedef struct {
    bool triggerUS;
} msgTriggerUS;

typedef struct {
    bool triggerRGBSwitch;
} msgTriggerRGBSwitch;

typedef struct {
    char* topic;
    char* payload;
} msgMqtt;

int initQueue();

int sendMsgToQueueUS(msgUS* inMsg);
int sendMsgToQueueRGB(msgRGB* inMsg);
int sendMsgToQueueSwitch(msgSwitch* inMsg);
int sendMsgToQueueTriggerRGBSwitch(msgTriggerRGBSwitch* inMsg);
int sendMsgToQueueTriggerUS(msgTriggerUS* inMsg);
int sendMsgToQueueMQTT(msgMqtt* inMsg);

int receiveMsgFromQueueUS(msgUS* outMsg);
int receiveMsgFromQueueRGB(msgRGB* outMsg);
int receiveMsgFromQueueSwitch(msgSwitch* outMsg);
int receiveMsgFromQueueTriggerRGBSwitch(msgTriggerRGBSwitch* outMsg);
int receiveMsgFromQueueTriggerUS(msgTriggerUS* outMsg);

#endif
