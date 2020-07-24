/*
 * Copyright (c) 2016-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include <stdint.h>

#ifdef __ICCARM__
#include <DLib_Threads.h>
#endif

/* POSIX Header files */
#include <pthread.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

#include <ti/drivers/Board.h>
#include "debug_if.h"
#include <task_rgb.h>
#include <task_ultrasonic.h>

extern void *mainThread(void *arg0);

/* Stack size in bytes */
#define THREADSTACKSIZE   4096

#define US_TASK_PRIORITY 2
#define US_TASK_STACK_SIZE 4096

#define RGB_TASK_PRIORITY 2
#define RGB_TASK_STACK_SIZE 4096

/*
 *  ======== main ========
 */
int main(void)
 {
    pthread_t           thread;
    pthread_attr_t      attrs;
    struct sched_param  priParam;
    int                 retc;

    /* initialize the system locks */
#ifdef __ICCARM__
    __iar_Initlocks();
#endif

    Board_init();
    InitTerm();
    init_gpio();
    initQueue();

    /* Initialize the attributes structure with default values */
    pthread_attr_init(&attrs);

    /* Set priority, detach state, and stack size attributes */
    priParam.sched_priority = 1;
    retc = pthread_attr_setschedparam(&attrs, &priParam);
    retc |= pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    retc |= pthread_attr_setstacksize(&attrs, THREADSTACKSIZE);
    if (retc != 0) {
        /* failed to set attributes */
        while (1) {}
    }

    retc = pthread_create(&thread, &attrs, mainThread, NULL);
    if (retc != 0) {
        /* pthread_create() failed */
        while (1) {}
    }

    pthread_t us_thread;
    pthread_attr_t us_pAttrs;
    struct sched_param us_priParam;

    pthread_attr_init(&us_pAttrs);
    us_priParam.sched_priority = US_TASK_PRIORITY;
    if(pthread_attr_setdetachstate(&us_pAttrs, PTHREAD_CREATE_DETACHED))
        errorHalt(" pthread_attr_setdetachstate() failed");
    pthread_attr_setschedparam(&us_pAttrs, &us_priParam);
    if(pthread_attr_setstacksize(&us_pAttrs, US_TASK_STACK_SIZE))
        errorHalt("Unable to set stack size");
    if(pthread_create(&us_thread, &us_pAttrs, usTask, NULL))
        errorHalt("Unable to create thread");

    pthread_t rgb_thread;
    pthread_attr_t rgb_pAttrs;
    struct sched_param rgb_priParam;

    pthread_attr_init(&rgb_pAttrs);
    rgb_priParam.sched_priority = RGB_TASK_PRIORITY;
    if(pthread_attr_setdetachstate(&rgb_pAttrs, PTHREAD_CREATE_DETACHED))
        errorHalt(" pthread_attr_setdetachstate() failed");
    pthread_attr_setschedparam(&rgb_pAttrs, &rgb_priParam);
    if(pthread_attr_setstacksize(&rgb_pAttrs, RGB_TASK_STACK_SIZE))
        errorHalt("Unable to set stack size");
    if(pthread_create(&rgb_thread, &rgb_pAttrs, rgbTask, NULL))
        errorHalt("Unable to create thread");


    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return (0);
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
