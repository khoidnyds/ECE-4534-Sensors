/*
 * rgb.h
 *
 *  Created on: Jul 20, 2020
 *      Author: Kaito
 */

#ifndef TASK_RGB_H_
#define TASK_RGB_H_

#include <ti/drivers/I2C.h>
#include <ti/drivers/GPIO.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include "ti_drivers_config.h"
#include "uart_term.h"
#include "debug_if.h"
#include "sensors_queues.h"

#define LOW                     0
#define TCS34725_ADDRESS        0x29     /**< I2C address **/
#define TCS34725_COMMAND_BIT    0x80     /**< Command bit **/
#define TCS34725_ENABLE         0x00     /**< Interrupt Enable register */
#define TCS34725_ENABLE_AIEN    0x10     /**< RGBC Interrupt Enable */
#define TCS34725_ENABLE_WEN     0x08     /**< Wait Enable - Writing 1 activates the wait timer */
#define TCS34725_ENABLE_AEN     0x02     /**< RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define TCS34725_ENABLE_PON     0x01     /**< Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define TCS34725_ATIME          0x01     /**< Integration time */
#define TCS34725_WTIME          0x03     /**< Wait time (if TCS34725_ENABLE_WEN is asserted) */
#define TCS34725_WTIME_2_4MS    0xFF     /**< WLONG0 = 2.4ms   WLONG1 = 0.029s */
#define TCS34725_WTIME_204MS    0xAB     /**< WLONG0 = 204ms   WLONG1 = 2.45s  */
#define TCS34725_WTIME_614MS    0x00     /**< WLONG0 = 614ms   WLONG1 = 7.4s   */
#define TCS34725_AILTL          0x04     /**< Clear channel lower interrupt threshold (lower byte) */
#define TCS34725_AILTH          0x05     /**< Clear channel lower interrupt threshold (higher byte) */
#define TCS34725_AIHTL          0x06     /**< Clear channel upper interrupt threshold (lower byte) */
#define TCS34725_AIHTH          0x07     /**< Clear channel upper interrupt threshold (higher byte) */
#define TCS34725_PERS           0x0C     /**< Persistence register - basic SW filtering mechanism for interrupts */

#define TCS34725_PERS_NONE      0b0000   /**< Every RGBC cycle generates an interrupt */
#define TCS34725_PERS_1_CYCLE   0b0001   /**< 1 clean channel value outside threshold range generates an interrupt */
#define TCS34725_PERS_2_CYCLE   0b0010   /**< 2 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_3_CYCLE   0b0011   /**< 3 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_5_CYCLE   0b0100   /**< 5 clean channel values outside threshold range generates an interrupt */
#define TCS34725_PERS_10_CYCLE  0b0101   /**< 10 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_15_CYCLE  0b0110   /**< 15 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_20_CYCLE  0b0111   /**< 20 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_25_CYCLE  0b1000   /**< 25 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_30_CYCLE  0b1001   /**< 30 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_35_CYCLE  0b1010   /**< 35 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_40_CYCLE  0b1011   /**< 40 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_45_CYCLE  0b1100   /**< 45 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_50_CYCLE  0b1101   /**< 50 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_55_CYCLE  0b1110   /**< 55 clean channel values outside threshold range generates an interrupt*/
#define TCS34725_PERS_60_CYCLE  0b1111   /**< 60 clean channel values outside threshold range generates an interrupt*/

#define TCS34725_CONFIG         0x0D     /**< Configuration **/
#define TCS34725_CONFIG_WLONG   0x02     /**< Choose between short and long (12x) wait times via CS34725_WTIME */
#define TCS34725_CONTROL        0x0F     /**< Set the gain level for the sensor */
#define TCS34725_ID             0x12     /**< 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
#define TCS34725_STATUS         0x13     /**< Device status **/
#define TCS34725_STATUS_AINT    0x10     /**< RGBC Clean channel interrupt */
#define TCS34725_STATUS_AVALID  0x01     /**< Indicates that the RGBC channels have completed an integration cycle */

#define TCS34725_CDATAL         0x14     /**< Clear channel data low byte */
#define TCS34725_CDATAH         0x15     /**< Clear channel data high byte */
#define TCS34725_RDATAL         0x16     /**< Red channel data low byte */
#define TCS34725_RDATAH         0x17     /**< Red channel data high byte */
#define TCS34725_GDATAL         0x18     /**< Green channel data low byte */
#define TCS34725_GDATAH         0x19     /**< Green channel data high byte */
#define TCS34725_BDATAL         0x1A     /**< Blue channel data low byte */
#define TCS34725_BDATAH         0x1B     /**< Blue channel data high byte */

/** Integration time settings for TCS34725 */
typedef enum {
  TCS34725_INTEGRATIONTIME_2_4MS = 0xFF, /**<  2.4ms - 1 cycle    - Max Count: 1024  */
  TCS34725_INTEGRATIONTIME_24MS  = 0xF6, /**<  24ms  - 10 cycles  - Max Count: 10240 */
  TCS34725_INTEGRATIONTIME_50MS  = 0xEB, /**<  50ms  - 20 cycles  - Max Count: 20480 */
  TCS34725_INTEGRATIONTIME_101MS = 0xD5, /**<  101ms - 42 cycles  - Max Count: 43008 */
  TCS34725_INTEGRATIONTIME_154MS = 0xC0, /**<  154ms - 64 cycles  - Max Count: 65535 */
  TCS34725_INTEGRATIONTIME_700MS = 0x00  /**<  700ms - 256 cycles - Max Count: 65535 */
} tcs34725IntegrationTime_t;
tcs34725IntegrationTime_t integrationTime;

/** Gain settings for TCS34725  */
typedef enum {
  TCS34725_GAIN_1X  = 0x00,  /**<  No gain  */
  TCS34725_GAIN_4X  = 0x01,  /**<  4x gain  */
  TCS34725_GAIN_16X = 0x02,  /**<  16x gain */
  TCS34725_GAIN_60X = 0x03   /**<  60x gain */
} tcs34725Gain_t;
tcs34725Gain_t gain;

typedef enum {STATE_CLEAR, STATE_RED, STATE_GREEN, STATE_BLUE} state_rgb;
state_rgb stateRGB;
uint16_t clearRaw, redRaw, greenRaw, blueRaw;

void* rgbTask(void *arg0);
void i2cCallback(I2C_Handle i2c, I2C_Transaction* i2cTransaction, bool success);
void initSwitch();

#endif /* TASK_RGB_H_ */
