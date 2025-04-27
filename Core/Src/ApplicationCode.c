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

	LCD_Draw_Vertical_Line(205,5,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(170,5,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(135,5,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(100,5,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(65,5,270,LCD_COLOR_BLACK);
	LCD_Draw_Vertical_Line(33,5,270,LCD_COLOR_BLACK);

	LCD_Draw_Horizontal_Line(200,5,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,45,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,95,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,140,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,185,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,230,200,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(200,273,200,LCD_COLOR_BLACK);
	/*******************************************************/





	/**************************** Gameplay ******************************/
	while(1) // set macro
	{
		//uint8_t game_board[6][7] = {0}; // Initialize game board to empty
		//uint8_t player1_turn = 1;
		if(PlayerOneChoice == 1)
		{
			LCD_PieceMovement();
			// Store value in matrix
			InterruptPress = 0; // Reset
			//PlayerOneChoice = 1;
			LCD_Draw_Circle_Fill(current_position,ROW_THREE,12,LCD_COLOR_BLUE);
			LCD_Draw_Circle_Fill(current_position,ROW_FOUR,12,LCD_COLOR_BLUE);
			LCD_Draw_Circle_Fill(current_position,ROW_FIVE,12,LCD_COLOR_BLUE);


		}
		else
		{
			//Random Generator
			HAL_Delay(1000);
			PlayerOneChoice = 1;

		}


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
			if(current_position < COLUMN_SEVEN)
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



