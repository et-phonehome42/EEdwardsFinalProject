/*
 * GyroDriver.h
 *
 *  Created on: Apr 17, 2025
 *      Author: ethan
 */

#ifndef INC_GYRODRIVER_H_
#define INC_GYRODRIVER_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>

//GYRO MACROS
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define DATA_CAPTURE 0x25
#define OUT_TEMP 0x26
#define CTRL_REG5  0x24
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_DURATION 0x38

#define GYRO_POWER_ON  0x0F
#define GYRO_BOOT      0x80

#define BIT_SET_FOR_READ 7

void GyroInit();
void GyroID();
void GyroPower();
void GyroTempGet();
void GyroRegConfig();
uint8_t GyroRegRead(uint8_t address);
void GyroRegWrite(uint8_t regAddress, uint8_t write_data);
void GyroHalVerify();
void GyroCommEnable();
void GyroCommDisable();

#endif /* INC_GYRODRIVER_H_ */
