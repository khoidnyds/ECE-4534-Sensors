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
    // Initialization
    initTimerUS();
    initTimerRGB();

    I2C_init();
    I2C_Handle i2c;
    I2C_Params i2cParams;
    I2C_Transaction i2cTransaction;

    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;
    i2cParams.transferMode = I2C_MODE_CALLBACK;
    i2cParams.transferCallbackFxn = i2cCallback;

    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (!i2c) {
        Message("\r\nI2C open failed");
        while(1);
    }

    //dbgOutputLoc(DLOC_MAIN_INIT_COMPLETE);

    // Main loop
    while (1) {
        //dbgOutputLoc(DLOC_MAIN_Q1_REC_BEG);


        //dbgOutputLoc(DLOC_MAIN_Q1_REC_END);
    }
}
void i2cCallback(I2C_Handle i2c, I2C_Transaction* i2cTransaction, bool success){
    size_t* rxBuffer = i2cTransaction->readBuf;
    if (rxBuffer[0] == 0x44) {
        Message("\r\nI2C connect successful");
        return;
    }
}
