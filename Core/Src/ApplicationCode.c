/*
 * ApplicationCode.c
 *
 *  Created on: 4/17/25
 *      Author: Ethan Edwards
 */

#include "ApplicationCode.h"


/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS



static uint8_t InterruptPress = 0;
static uint8_t PlayerOneChoice = 1;
//volatile uint8_t initial_position = COLUMN_FOUR;
static uint8_t current_position = COLUMN_FOUR;
static uint8_t new_position = 0;
static uint8_t previous_position =0;
static uint8_t game_board[6][7] = {0};



void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_WHITE);

			if(StaticTouchData.x < LCD_PIXEL_WIDTH/2){
				LCD_Gameplay();
				//LCD_Clear(0, LCD_COLOR_GREY);
				//LCD_SetTextColor(LCD_COLOR_BLUE);
				//LCD_SetFont(&Font16x24);
				//LCD_DisplayChar(110,140,'1');

			} else {
				LCD_Visual_Demo();
				//LCD_Clear(0,LCD_COLOR_GREY);
				//LCD_SetTextColor(LCD_COLOR_GREY);
				//LCD_SetFont(&Font16x24);
				//LCD_DisplayChar(110,140,'2');

			}
		}else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_WHITE);
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&Font16x24);
			LCD_DisplayChar(50,140,'P');
			LCD_DisplayChar(60,140,'1');
			LCD_DisplayChar(180,140,'P');
			LCD_DisplayChar(190,140,'2');
			LCD_Draw_Circle_Fill(185,140,20,LCD_COLOR_GREY);
			LCD_Draw_Circle_Fill(55,140,20,LCD_COLOR_BLUE);



		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS


void LCD_Gameplay(void)
{
	/****************** Gameboard Visuals *******************/
	LCD_Clear(0, LCD_COLOR_WHITE);
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_SetFont(&Font16x24);

	LCD_Draw_Vertical_Line(205,45,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(170,45,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(135,45,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(100,45,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(65,45,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(33,45,270,LCD_COLOR_BLACK);

	LCD_Draw_Horizontal_Line(200,45,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,95,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,140,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,185,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,230,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,273,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,315,200,LCD_COLOR_BLACK);

	/*******************************************************/
	//LCD_Draw_Circle_Fill(COLUMN_SIX,295,12,LCD_COLOR_BLUE);
	//LCD_Draw_Circle_Fill(COLUMN_SEVEN,ROW_THREE,12,LCD_COLOR_BLUE);
	//LCD_Draw_Circle_Fill(COLUMN_ONE,ROW_THREE,12,LCD_COLOR_BLUE);







	/**************************** Gameplay ******************************/
	while(1) // set macro
	{
		//uint8_t game_board[6][7] = {0}; // Initialize game board to empty
		//uint8_t player1_turn = 1;
		if(PlayerOneChoice == 1)
		{
			LCD_PieceMovement();
			// Store value in matrix
			// Create function for matrix manipulation cases
			InterruptPress = 0; // Reset
			PLAYER_PiecePlacement(current_position);
			//PlayerOneChoice = 1;
			//LCD_Draw_Circle_Fill(current_position,ROW_THREE,12,LCD_COLOR_BLUE);
			//LCD_Draw_Circle_Fill(current_position,ROW_FOUR,12,LCD_COLOR_BLUE);
			//LCD_Draw_Circle_Fill(current_position,ROW_FIVE,12,LCD_COLOR_BLUE);


		}
		else
		{
			//Random Generator
			HAL_Delay(1000);
			PlayerOneChoice = 1;

		}


	  }

    }


void PLAYER_PiecePlacement(float vert_column)
{

	if(vert_column >= (COLUMN_ONE - 0.5) && vert_column < (COLUMN_ONE + 0.5))
	{
		GAME_MatrixHandling(COLUMN1, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_TWO - 0.5) && vert_column < (COLUMN_TWO + 0.5))
	{
		GAME_MatrixHandling(COLUMN2, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_THREE - 0.5) && vert_column < (COLUMN_THREE + 0.5))
	{
		GAME_MatrixHandling(COLUMN3, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_FOUR - 0.5) && vert_column < (COLUMN_FOUR + 0.5))
	{
		GAME_MatrixHandling(COLUMN4, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_FIVE - 0.5) && vert_column < (COLUMN_FIVE + 0.5))
	{
		GAME_MatrixHandling(COLUMN5, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_SIX - 0.5) && vert_column < (COLUMN_SIX + 0.5))
	{
		GAME_MatrixHandling(COLUMN6, PLAYER_ONE_TOKEN);
	}

	else if(vert_column >= (COLUMN_SEVEN - 0.5) && vert_column < (COLUMN_SEVEN + 0.5))
	{
		GAME_MatrixHandling(COLUMN7, PLAYER_ONE_TOKEN);
	}
}


void GAME_MatrixHandling(uint8_t column_num, uint8_t player_token)
{

	for(uint8_t row_num = 0; row_num <= 7; row_num++)
	{
		if(game_board[row_num][column_num] == 0)
		{
			game_board[row_num][column_num] = player_token;
				switch(row_num)
				{
				case ROW1:
					LCD_Draw_Circle_Fill(current_position,ROW_ZERO,12,LCD_COLOR_BLUE);
				break;

				case ROW2:
					LCD_Draw_Circle_Fill(current_position,ROW_ONE,12,LCD_COLOR_BLUE);
				break;

				case ROW3:
					LCD_Draw_Circle_Fill(current_position,ROW_TWO,12,LCD_COLOR_BLUE);
				break;

				case ROW4:
					LCD_Draw_Circle_Fill(current_position,ROW_THREE,12,LCD_COLOR_BLUE);
				break;

				case ROW5:
					LCD_Draw_Circle_Fill(current_position,ROW_FOUR,12,LCD_COLOR_BLUE);
				break;

				case ROW6:
					LCD_Draw_Circle_Fill(current_position,ROW_FIVE,12,LCD_COLOR_BLUE);
				break;
				}

			break; // get out of loop
		}
		LCD_PieceMovement();
	}

}













void LCD_PieceMovement(void)
{
	//LCD_Draw_Circle_Fill(55,140,20,LCD_COLOR_BLUE);
	//uint8_t initial_position = COLUMN_FOUR;
	//uint8_t current_position = initial_position;
	//uint8_t new_position = 0;
	//uint8_t previous_position =0;

	while(PlayerOneChoice)
	{


	  if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
	  {
		/* Touch valid */
		printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
		if(StaticTouchData.x < LCD_PIXEL_WIDTH/2)
		{
			if(current_position > COLUMN_ONE)
			{
				previous_position = current_position;
				new_position = current_position - 35;
				current_position = new_position;
			}
		}
		else
		{
			if(current_position < COLUMN_SIX)
			{
				previous_position = current_position;
				new_position = current_position + 35;
				current_position = new_position;
			}
		}
		LCD_Draw_Circle_Fill(previous_position,ROW_SIX,12,LCD_COLOR_WHITE);
		LCD_Draw_Circle_Fill(current_position,ROW_SIX,12,LCD_COLOR_BLUE);
		HAL_Delay(300);
	  }
	  else
	  {
		  // keep waiting for button push or piece movement
	  }
	  if(InterruptPress == 1)
	  {
		  PlayerOneChoice = 0;
	  }
	}


}






void appDelay(uint32_t time)
{
	char name[NAME_LENGTH] = {'E','t','h','a','n'};
	[[maybe_unused]]char destinationArray[NAME_LENGTH];

		for (uint32_t i = 0; i < time; i++){
			for(uint32_t j = 0; j < NAME_LENGTH; j++){
				destinationArray[j] = name[j];
			}
		}
}




// Button interrupt
void EXTI0_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	//HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	//HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
	InterruptPress = 1;
	//__HAL_GPIO_EXTI_CLEAR_FLAG(EXTI0_IRQn);
	//HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}



