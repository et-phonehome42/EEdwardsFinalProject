/*
 * ApplicationCode.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "LCD_Driver.h"
#include "stm32f4xx_hal.h"
#include "ButtonDriver.h"

#include <stdio.h>


#ifndef INC_APPLICATIONCODE_H_
#define INC_APPLICATIONCODE_H_

#define NAME_LENGTH 5
#define DEFAULT 	25000





#define PLAYER_ONE_CHOICE 1


#define COLUMN_ONE     	12.5
#define COLUMN_TWO		(COLUMN_ONE + 35)
#define COLUMN_THREE	(COLUMN_TWO + 35)
#define COLUMN_FOUR		(COLUMN_THREE + 35)
#define COLUMN_FIVE		(COLUMN_FOUR + 35)
#define COLUMN_SIX		(COLUMN_FIVE + 35)
#define COLUMN_SEVEN    187.5

#define ROW_ONE			250
#define ROW_TWO 		ROW_ONE - 40
#define ROW_THREE		ROW_TWO - 50
#define ROW_FOUR		ROW_THREE - 40
#define ROW_FIVE		ROW_FOUR - 50
#define ROW_SIX			25


#define PIECE_POS_INIT 82.5
#define PIECE_MIN_XVAL 12.5
#define PIECE_MAX_VAL  187.5

void ApplicationInit(void);
void LCD_Visual_Demo(void);



void LCD_Gameplay(void);
void LCD_PieceMovement(void);


void appDelay(uint32_t time);
void ApplInitButton();
void ApplInitButtonInterrupts();

#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_Touch_Polling_Demo(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
