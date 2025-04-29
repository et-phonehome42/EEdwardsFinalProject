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

#define PLAYER_ONE_TOKEN 1
#define PLAYER_TWO_TOKEN 2

#define rows 6
#define cols 7

#define COL1 1
#define COL2 2
#define COL3 3
#define COL4 4
#define COL5 5
#define COL6 6
#define COL7 7





#define COLUMN1 0
#define COLUMN2 1
#define COLUMN3 2
#define COLUMN4 3
#define COLUMN5 4
#define COLUMN6 5
#define COLUMN7 6

#define ROW1 0
#define ROW2 1
#define ROW3 2
#define ROW4 3
#define ROW5 4
#define ROW6 5


#define COLUMN_ONE     	12.5
#define COLUMN_TWO		(COLUMN_ONE + 35)//12.5+35 = 47.5
#define COLUMN_THREE	(COLUMN_TWO + 35)//47.5+35 = 82.5
#define COLUMN_FOUR		(COLUMN_THREE + 35)//82.5+35 = 117.5
#define COLUMN_FIVE		(COLUMN_FOUR + 35) //117.5+35=152.5
#define COLUMN_SIX		(COLUMN_FIVE + 35)//
#define COLUMN_SEVEN    (COLUMN_SIX + 35)

#define ROW_ZERO        295
#define ROW_ONE			250
#define ROW_TWO 		ROW_ONE - 40
#define ROW_THREE		ROW_TWO - 50
#define ROW_FOUR		ROW_THREE - 40
#define ROW_FIVE	    ROW_FOUR - 50
#define ROW_SIX			25

#define PIECE_POS_INIT 82.5
#define PIECE_MIN_XVAL 12.5
#define PIECE_MAX_VAL  187.5

void ApplicationInit(void);
void LCD_Visual_Demo(void);


void LCD_TwoPlayerGameplay(void);
void LCD_Gameplay(void);

void LCD_PlayerTwoPieceMovement();
void LCD_PieceMovement(void);

void RNG_PlayerTurn();


void RNG_PiecePlacement(uint32_t num);
void PLAYER_PiecePlacement(float vert_column);
void PIECE_PlayerColor(uint8_t color, float row, uint8_t column);
void PLAYER_GreyPiecePlacement(float vert_column);

void GAME_MatrixHandling(uint8_t column_num, uint8_t player_token);
void GAME_ClearBoard();

uint8_t check_questionMark(uint8_t GameBoard[rows][cols], uint8_t player_token);


void appDelay(uint32_t time);
void ApplInitButton();
void ApplInitButtonInterrupts();

static void MX_RNG_Init(void);
void LCD_FinalScreen(void);
void LCD_FinalScreenLose(void);
void LCD_FinalScreenTwoPlayer(void);
#if (COMPILE_TOUCH_FUNCTIONS == 1)
void LCD_ScreenOne(void);
#endif // (COMPILE_TOUCH_FUNCTIONS == 1)

#endif /* INC_APPLICATIONCODE_H_ */
