/*
 * rgb.c
 *
 *  Created on: Jul 20, 2020
 *      Author: Kaito
 */

#include <task_rgb.h>

void* rgbTask(void *arg0){
    //Message("\r\nStarting rgbTask");

    initSwitch();
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

    uint8_t transmit_size = 1;
    size_t txBuffer[transmit_size];
    int i;
    for(i=0;i<transmit_size;i++){
        txBuffer[i] = 0;
    }
    uint8_t receive_size = 1;
    size_t rxBuffer[receive_size];
    for(i=0;i<receive_size;i++){
        rxBuffer[i] = 0;
    }


    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = transmit_size;
    i2cTransaction.readBuf    = rxBuffer;
    i2cTransaction.readCount  = receive_size;
    i2cTransaction.slaveAddress = TCS34725_ADDRESS;


    //check I2C connection
    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_ID;
    int rect = I2C_transfer(i2c, &i2cTransaction);

    //enable RGB reading
    transmit_size = 2;
    for(i=0;i<transmit_size;i++){
        txBuffer[i] = 0;
    }
    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_ENABLE;
    txBuffer[1] = TCS34725_ENABLE_PON & 0xFF;
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = transmit_size;
    rect = I2C_transfer(i2c, &i2cTransaction);

    transmit_size = 2;
    for(i=0;i<transmit_size;i++){
        txBuffer[i] = 0;
    }
    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_ENABLE;
    txBuffer[1] =  (TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN) & 0xFF;
    i2cTransaction.writeBuf   = txBuffer;
    i2cTransaction.writeCount = transmit_size;
    rect = I2C_transfer(i2c, &i2cTransaction);

    while(1){
        msgTriggerRGBSwitch newTriggerRGBSwitch;
        receiveMsgFromQueueTriggerRGBSwitch(&newTriggerRGBSwitch);
        if(newTriggerRGBSwitch.triggerRGBSwitch){
            //Send msgSwitch to queue
            msgSwitch newMsgSwitch;
            newMsgSwitch.type = limitSwitch;
            if(GPIO_read(LIMIT_SWITCH)==LOW){
                newMsgSwitch.carrying = yes;
            }
            else{
                newMsgSwitch.carrying = no;
            }
            int sent_switch_msg = sendMsgToQueueSwitch(&newMsgSwitch);
//            if(sent_switch_msg){
//               while(1);
//            }
//            Message("\r\n");
//            Message("Carrying box: ");
//            if(newMsgSwitch.carrying==yes){
//                Message("yes");
//            }
//            else {
//                Message("no");
//            }

//            write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
//              delay(3);
//              write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);

        }
    }

    //
    //
    //    transmit_size = 1;
    //    for(i=0;i<transmit_size;i++){
    //        txBuffer[i] = 0;
    //    }
    //    receive_size = 2;
    //    for(i=0;i<receive_size;i++){
    //        rxBuffer[i] = 0;
    //    }
    //    i2cTransaction.writeBuf   = txBuffer;
    //    i2cTransaction.writeCount = transmit_size;
    //    i2cTransaction.readBuf    = rxBuffer;
    //    i2cTransaction.readCount  = receive_size;
    //    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_CDATAL;
    //    rect = I2C_transfer(i2c, &i2cTransaction);
    //    uint16_t clearRaw = rxBuffer[0] << 8 | rxBuffer[1];
    //
    //    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_RDATAL;
    //    rect = I2C_transfer(i2c, &i2cTransaction);
    //    uint16_t redRaw = rxBuffer[0] << 8 | rxBuffer[1];
    //
    //    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_GDATAL;
    //    rect = I2C_transfer(i2c, &i2cTransaction);
    //    uint16_t greenRaw = rxBuffer[0] << 8 | rxBuffer[1];
    //
    //    txBuffer[0] = TCS34725_COMMAND_BIT | TCS34725_BDATAL;
    //    rect = I2C_transfer(i2c, &i2cTransaction);
    //    uint16_t blueRaw = rxBuffer[0] << 8 | rxBuffer[1];
    //
    //    float redRGB, greenRGB, blueRGB;
    //    redRGB = redRaw / (float)clearRaw * 255.0;
    //    greenRGB = greenRaw / (float)clearRaw * 255.0;
    //    blueRGB = blueRaw / (float)clearRaw * 255.0;




        //    auto data = i2cTransaction->readBuf;
    //
    //
    //
    //    msgRGB newMsgRGB;
    //    newMsgRGB.type = color;
    //    if(redRGB>205 && greenRGB<50 && blueRGB<50){
    //      newMsgRGB.color = red;
    //    }
    //    else if(redRGB<50 && greenRGB<50 && blueRGB>205){
    //      newMsgRGB.color = blue;
    //    }
    //    else if(redRGB<50 && greenRGB>205 && blueRGB<50){
    //      newMsgRGB.color = green;
    //    }
    //    else if(redRGB<50 && greenRGB<50 && blueRGB<50){
    //      newMsgRGB.color = black;
    //    }
    //    else if(redRGB>205 && greenRGB>205 && blueRGB>205){
    //      newMsgRGB.color = white;
    //    }
    //    else{
    //      newMsgRGB.color = unknown;
    //    }
    //    int sent_rgb = sendMsgToQueueRGB(&newMsgRGB);
    //    if(sent_rgb){
    //      while(1);
    //    }



//    msgMqtt sendMsg;
//    msgRGB outMsgRGB;
//    msgSwitch outMsgSwitch;
//    int receive_RGBMsg, receive_SwitchMsg;
//    receive_RGBMsg = receiveMsgFromQueueRGB(&outMsgRGB);  //Make one subroutine call to receive from a single queue
//    receive_SwitchMsg = receiveMsgFromQueueSwitch(&outMsgSwitch);  //Make one subroutine call to receive from a single queue
//    while(1){
//        if(receive_RGBMsg || receive_SwitchMsg){
//            //dbgOutputLoc(1);
//        }
//        else{
//
//            //            // send to MQTT broker
//            //            UART_PRINT("\r\n");
//            //            UART_PRINT("Color: ");
//            //            if(newMsgRGB.color==red){
//            //                UART_PRINT("red");
//            //            }
//            //            else if(newMsgRGB.color==green){
//            //                UART_PRINT("green");
//            //            }
//            //            else if(newMsgRGB.color==blue){
//            //                UART_PRINT("blue");
//            //            }
//            //            else if(newMsgRGB.color==white){
//            //                UART_PRINT("white");
//            //            }
//            //            else if(newMsgRGB.color==black){
//            //                UART_PRINT("black");
//            //            }
//            //            else {
//            //                UART_PRINT("unknown");
//            //            }
//
//            // send to MQTT broker
//            DBG_PRINT("\r\n");
//            DBG_PRINT("Carrying box: ");
//            if(outMsgSwitch.carrying==yes){
//                DBG_PRINT("yes");
//            }
//            else {
//                DBG_PRINT("no");
//            }
//        }
//    }
    //    I2C_Handle i2c = initI2C();
    ////    dbgOutputLoc(DLOC_TIMER_US_CB_BEGIN);
    //    uint8_t transmit_size = 1;
    //    uint8_t receive_size = 0;
    //
    //    I2C_Transaction i2cTransaction;
    //
    //    i2cTransaction.writeBuf   = txBuffer;
    //    i2cTransaction.writeCount = transmit_size + 1;
    //    i2cTransaction.readBuf    = rxBuffer;
    //    i2cTransaction.readCount  = receive_size;
    //    i2cTransaction.slaveAddress = TCS34725_ADDRESS;
    //
    //
    //    txBuffer[0] = TCS34725_ID;
    //    I2C_transfer(i2c, &i2cTransaction);
    //
    //    uint16_t c, r, g, b;
    //    Message("\r\nI2C start transfer");
    //
    //    // get c value
    //    txBuffer[0] = TCS34725_ID;
    //    //txBuffer[1] = TCS34725_COMMAND_BIT | TCS34725_CDATAL;
    //    bool rect = I2C_transfer(i2c, &i2cTransaction);
    //    if (rect) {
    //       c = (rxBuffer[0] << 8) | (rxBuffer[1]);
    //    }
    //    else {
    //       Message("\r\nI2C transfer failed");
    //       while(1); //error
    //    }
    // Read from limit switch
}
void initSwitch(){
    GPIO_setConfig(LIMIT_SWITCH, GPIO_CFG_INPUT | GPIO_CFG_IN_PU);
}
void i2cCallback(I2C_Handle i2c, I2C_Transaction* i2cTransaction, bool success){
    size_t* rxBuffer = i2cTransaction->readBuf;
    if (rxBuffer[0] == 0x44) {
        Message("\r\nI2C connect successful");
        return;
    }
}
