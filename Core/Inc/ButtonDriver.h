/*
 * ButtonDriver.h
 *
 *  Created on: Apr 17, 2025
 *      Author: Ethan Edwards
 */

#ifndef INC_BUTTONDRIVER_H_
#define INC_BUTTONDRIVER_H_


#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define BUTTON_PORT_A	AHB1_BASE_ADDR
#define BUTTON_PIN_NUM  GPIO_PIN_0
#define BUTTON_PRESS	1
#define BUTTON_RELEASE	0

void InitButton();
bool pressButton();

void InitButtonInterrupts();

#define GPIO_PIN_NUM_0         0
#define GPIO_PIN_NUM_1         1
#define GPIO_PIN_NUM_2         2
#define GPIO_PIN_NUM_3         3
#define GPIO_PIN_NUM_4         4
#define GPIO_PIN_NUM_5         5
#define GPIO_PIN_NUM_6         6
#define GPIO_PIN_NUM_7         7
#define GPIO_PIN_NUM_8         8
#define GPIO_PIN_NUM_9         9
#define GPIO_PIN_NUM_10        10
#define GPIO_PIN_NUM_11        11
#define GPIO_PIN_NUM_12        12
#define GPIO_PIN_NUM_13        13
#define GPIO_PIN_NUM_14        14
#define GPIO_PIN_NUM_15        15

#define GPIO_PIN_MODE_IN       0x0
#define GPIO_PIN_MODE_OUT      0x1
#define GPIO_PIN_MODE_ALT      0x2
#define GPIO_PIN_MODE_ANALOG   0x3

#define GPIO_OPTYPE_pushpull    0
#define GPIO_OPTYPE_opendrain   1

#define GPIO_PIN_SPEED_0       0x0
#define GPIO_PIN_SPEED_1       0x1
#define GPIO_PIN_SPEED_2       0x2
#define GPIO_PIN_SPEED_3       0x3

#define GPIO_PIN_PUPD_none     0x0
#define GPIO_PIN_PUPD_up       0x1
#define GPIO_PIN_PUPD_down     0x0
#define GPIO_PIN_PUPD_3        0x1

#define NO_INTERRUPT           0x0
#define FALLING_EDGE           0x1
#define RISING_EDGE            0x2
#define FALL_RISE              0x3

#define BUTTON_PORTA            0




























#endif /* INC_BUTTONDRIVER_H_ */
