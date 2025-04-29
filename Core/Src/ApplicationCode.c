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
static uint8_t PlayerTwoChoice = 1;
//volatile uint8_t initial_position = COLUMN_FOUR;
static uint8_t current_position = COLUMN_FOUR;
static uint8_t new_position = 0;
static uint8_t previous_position =0;
static uint8_t game_board[6][7] = {0};
static uint8_t StartTime = 0;
static uint8_t EndTime = 0;
static uint8_t PlayerOneScore = 0;
static uint8_t PlayerTwoScore = 0;
static uint8_t TotalTime = 0;

RNG_HandleTypeDef hrng;

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
	InitButtonInterrupts();
	MX_RNG_Init();
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

static void MX_RNG_Init(void)
{
  hrng.Instance = RNG;

  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    LCD_Error_Handler();
  }

}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_ScreenOne(void)
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	while (1)
	{
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
		{
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_WHITE);

			if(StaticTouchData.x < LCD_PIXEL_WIDTH/2)
			{
				LCD_Gameplay();
			}
			else
			{
				LCD_TwoPlayerGameplay();
			}
		}
		else
		{
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			//LCD_Clear(0, LCD_COLOR_WHITE);
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&Font16x24);
			LCD_Draw_Circle_Fill(185,140,20,LCD_COLOR_GREY);
			LCD_Draw_Circle_Fill(55,140,20,LCD_COLOR_BLUE);
			LCD_DisplayChar(45,135,'P');
			LCD_DisplayChar(55,135,'1');
			LCD_DisplayChar(175,135,'P');
			LCD_DisplayChar(185,135,'2');

		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS





void LCD_TwoPlayerGameplay(void)
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

		LCD_Draw_Horizontal_Line(1,45,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,95,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,140,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,185,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,230,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,273,235,LCD_COLOR_BLACK);
		LCD_Draw_Horizontal_Line(1,315,235,LCD_COLOR_BLACK);

		/*******************************************************/





		StartTime = HAL_GetTick();
		/**************************** Gameplay ******************************/
		while(1) // set macro
		{
			if(PlayerOneChoice == 1)
			{
				LCD_PieceMovement(); // Loops and waits for player movement.
				InterruptPress = 0; // Reset variable
				PLAYER_PiecePlacement(current_position); // Handles peice/matrix placement
			}
			else
			{
				HAL_Delay(1000); // Avoid program crash
				LCD_PlayerTwoPieceMovement();
				InterruptPress = 0;
				PlayerTwoChoice = 1;
				PLAYER_GreyPiecePlacement(current_position);
				PlayerOneChoice = 1; // Resets variable to go back to player one loop
				}

			if(check_questionMark(game_board, 1))
			{
				EndTime = HAL_GetTick(); // Get tick at end of game
				TotalTime = (EndTime - StartTime) / 1000; // Get time elapsed in seconds
				PlayerOneScore += 1; // Increment score counter
				HAL_Delay(200);
				LCD_FinalScreenTwoPlayer(); // Go to final screen to show data
			}
			if(check_questionMark(game_board,2))
			{
				EndTime = HAL_GetTick() - StartTime;
				TotalTime = EndTime / 1000;
				PlayerTwoScore += 1;
				HAL_Delay(200);
				LCD_FinalScreenTwoPlayer();
			}


		}
}










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

	LCD_Draw_Horizontal_Line(1,45,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,95,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,140,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,185,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,230,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,273,235,LCD_COLOR_BLACK);
	LCD_Draw_Horizontal_Line(1,315,235,LCD_COLOR_BLACK);

	/*******************************************************/







	StartTime = HAL_GetTick();
	/**************************** Gameplay ******************************/
	while(1) // set macro
	{
		if(PlayerOneChoice == 1)
		{
			LCD_PieceMovement(); // Loops and waits for player movement.
			InterruptPress = 0; // Reset variable
			PLAYER_PiecePlacement(current_position); // Handles peice/matrix placement
		}
		else
		{
			HAL_Delay(1000); // Avoid program crash
			RNG_PlayerTurn(); // Handles the RNG turn
			PlayerOneChoice = 1; // Resets variable to go back to player one loop
		}

		if(check_questionMark(game_board, 1))
		{
			EndTime = HAL_GetTick(); // Get tick at end of game
			TotalTime = (EndTime - StartTime) / 1000; // Get time elapsed in seconds
			PlayerOneScore += 1; // Increment score counter
			HAL_Delay(200);
			LCD_FinalScreen(); // Go to final screen to show data
		}
		if(check_questionMark(game_board,2))
		{
			EndTime = HAL_GetTick() - StartTime;
			TotalTime = EndTime / 1000;
			PlayerTwoScore += 1;
			HAL_Delay(200);
			LCD_FinalScreenLose();
		}


	  }

}



void RNG_PlayerTurn()
{
	uint32_t rand32bit;
	HAL_RNG_GenerateRandomNumber(&hrng, &rand32bit);
	RNG_PiecePlacement(rand32bit);
}


void RNG_PiecePlacement(uint32_t num)
{
	uint8_t column_num = num % 7;

				switch(column_num)
				{
				case COLUMN1:
					GAME_MatrixHandling(COLUMN1, PLAYER_TWO_TOKEN);
				break;

				case COLUMN2:
					GAME_MatrixHandling(COLUMN2, PLAYER_TWO_TOKEN);
				break;

				case COLUMN3:

					GAME_MatrixHandling(COLUMN3, PLAYER_TWO_TOKEN);
				break;

				case COLUMN4:

					GAME_MatrixHandling(COLUMN4, PLAYER_TWO_TOKEN);
				break;

				case COLUMN5:

					GAME_MatrixHandling(COLUMN5, PLAYER_TWO_TOKEN);
				break;

				case COLUMN6:
					GAME_MatrixHandling(COLUMN6, PLAYER_TWO_TOKEN);
				break;

				default:
					GAME_MatrixHandling(COLUMN7, PLAYER_TWO_TOKEN);
				break;
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


void PLAYER_GreyPiecePlacement(float vert_column)
{

	if(vert_column >= (COLUMN_ONE - 0.5) && vert_column < (COLUMN_ONE + 0.5))
	{
		GAME_MatrixHandling(COLUMN1, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_TWO - 0.5) && vert_column < (COLUMN_TWO + 0.5))
	{
		GAME_MatrixHandling(COLUMN2, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_THREE - 0.5) && vert_column < (COLUMN_THREE + 0.5))
	{
		GAME_MatrixHandling(COLUMN3, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_FOUR - 0.5) && vert_column < (COLUMN_FOUR + 0.5))
	{
		GAME_MatrixHandling(COLUMN4, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_FIVE - 0.5) && vert_column < (COLUMN_FIVE + 0.5))
	{
		GAME_MatrixHandling(COLUMN5, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_SIX - 0.5) && vert_column < (COLUMN_SIX + 0.5))
	{
		GAME_MatrixHandling(COLUMN6, PLAYER_TWO_TOKEN);
	}

	else if(vert_column >= (COLUMN_SEVEN - 0.5) && vert_column < (COLUMN_SEVEN + 0.5))
	{
		GAME_MatrixHandling(COLUMN7, PLAYER_TWO_TOKEN);
	}
}














void GAME_MatrixHandling(uint8_t column_num, uint8_t player_token)
{

	for(uint8_t row_num = 0; row_num < 6; row_num++)
	{
		if(game_board[row_num][column_num] == 0)
		{
			game_board[row_num][column_num] = player_token;
				switch(row_num)
				{
				case ROW1:
					PIECE_PlayerColor(player_token, ROW_ZERO, column_num);
				break;

				case ROW2:
					PIECE_PlayerColor(player_token, ROW_ONE, column_num);
				break;

				case ROW3:

					PIECE_PlayerColor(player_token, ROW_TWO, column_num);
				break;

				case ROW4:

					PIECE_PlayerColor(player_token, ROW_THREE, column_num);
				break;

				case ROW5:

					PIECE_PlayerColor(player_token, ROW_FOUR, column_num);
				break;

				case ROW6:
					PIECE_PlayerColor(player_token, ROW_FIVE, column_num);
				break;

				default:

				break;
				}

			break; // get out of loop
		}

	}

}

void PIECE_PlayerColor(uint8_t color, float row, uint8_t column)
{
	switch(color)
	{
	case PLAYER_ONE_TOKEN:
		LCD_Draw_Circle_Fill(current_position,row,12,LCD_COLOR_BLUE);
	break;

	case PLAYER_TWO_TOKEN:
		if(column == COLUMN1)
		{
			LCD_Draw_Circle_Fill(COLUMN_ONE,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN2)
		{
			LCD_Draw_Circle_Fill(COLUMN_TWO,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN3)
		{
			LCD_Draw_Circle_Fill(COLUMN_THREE,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN4)
		{
			LCD_Draw_Circle_Fill(COLUMN_FOUR,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN5)
		{
			LCD_Draw_Circle_Fill(COLUMN_FIVE,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN6)
		{
			LCD_Draw_Circle_Fill(COLUMN_SIX,row,12,LCD_COLOR_GREY);
		}
		else if(column == COLUMN7)
		{
			LCD_Draw_Circle_Fill(COLUMN_SEVEN,row,12,LCD_COLOR_GREY);
		}
	break;
	}
}











void LCD_PieceMovement(void)
{
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

void LCD_PlayerTwoPieceMovement()
{
	while(PlayerTwoChoice)
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
		LCD_Draw_Circle_Fill(current_position,ROW_SIX,12,LCD_COLOR_GREY);
		HAL_Delay(300);
	  }
	  else
	  {
		  // keep waiting for button push or piece movement
	  }
	  if(InterruptPress == 1)
	  {
		  PlayerTwoChoice = 0;
	  }
	}


}















uint8_t check_questionMark(uint8_t GameBoard[rows][cols], uint8_t player_token)
{
	// Check if there is a horizontal four in a row
	for(uint8_t ROW = 0; ROW < rows; ROW++)
	{
		for(uint8_t COL = 0; COL <= (cols - 4); COL++)
		{
			if(GameBoard[ROW][COL] == player_token &&
			   GameBoard[ROW][COL + 1] == player_token &&
			   GameBoard[ROW][COL + 2] == player_token &&
			   GameBoard[ROW][COL + 3] == player_token)
			{
				return 1;
			}
		}
	}

	//Check if there four in a row vertically
	for(uint8_t COL = 0; COL < cols; COL++)
	{
		for(uint8_t ROW = 0; ROW <= (rows - 4); ROW++)
		{
			if(GameBoard[ROW][COL] == player_token &&
			   GameBoard[ROW + 1][COL] == player_token &&
			   GameBoard[ROW + 2][COL] == player_token &&
			   GameBoard[ROW + 3][COL] == player_token)
			{
				return 1;
			}
		}
	}

	// Diagonal
	for(uint8_t ROW = 3; ROW < rows; ROW++)
	{
		for(uint8_t COL = 0; COL <= (cols - 4); COL++)
		{
			if(GameBoard[ROW][COL] == player_token &&
			   GameBoard[ROW - 1][COL + 1] == player_token &&
			   GameBoard[ROW - 2][COL + 2] == player_token &&
			   GameBoard[ROW - 3][COL + 3] == player_token)
			{
				return 1;
			}
		}
	}

	for(uint8_t COL = 0; COL <= (cols - 4); COL++)
	{
		for(uint8_t ROW = 0; ROW <= (rows - 4); ROW++)
		{
			if(GameBoard[ROW][COL] == player_token &&
			   GameBoard[ROW + 1][COL + 1] == player_token &&
			   GameBoard[ROW + 2][COL + 2] == player_token &&
			   GameBoard[ROW + 3][COL + 3] == player_token)
			{
				return 1;
			}
		}
	}


	return 0;

}



/************************************ Final Screen **************************************/

void LCD_FinalScreen(void)
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	while (1)
	{
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
		{
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_WHITE);

			if(StaticTouchData.y < LCD_PIXEL_WIDTH/3)
			{
				GAME_ClearBoard(game_board);
				LCD_Gameplay();
			}
			else
			{
			}
		}
		else
		{
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&Font16x24);

			LCD_DisplayChar(30,50,'Y');
			LCD_DisplayChar(40,50,'a');
			LCD_DisplayChar(50,50,'y');
			LCD_DisplayChar(60,50,'!');

			LCD_DisplayChar(80,50,'Y');
			LCD_DisplayChar(90,50,'o');
			LCD_DisplayChar(100,50,'u');

			LCD_DisplayChar(120,50,'d');
			LCD_DisplayChar(130,50,'i');
			LCD_DisplayChar(138,50,'d');

			LCD_DisplayChar(160,50,'i');
			LCD_DisplayChar(165,50,'t');
			LCD_DisplayChar(175,50,'!');

			LCD_Draw_Horizontal_Line(1,90,235,LCD_COLOR_GREY);


			/******* Player One Score *******/
			LCD_DisplayChar(35,120,'P');
			LCD_DisplayChar(45,120,'1');

			LCD_DisplayChar(65,120,'S');
			LCD_DisplayChar(75,120,'c');
			LCD_DisplayChar(85,120,'o');
			LCD_DisplayChar(95,120,'r');
			LCD_DisplayChar(105,120,'e');
			LCD_DisplayChar(115,120,':');

			LCD_DisplayChar(140,120,PlayerOneScore + '0');

			/******* Player Two Score **********/
			LCD_DisplayChar(35,140,'P');
			LCD_DisplayChar(45,140,'2');

			LCD_DisplayChar(65,140,'S');
			LCD_DisplayChar(75,140,'c');
			LCD_DisplayChar(85,140,'o');
			LCD_DisplayChar(95,140,'r');
			LCD_DisplayChar(105,140,'e');
			LCD_DisplayChar(115,140,':');

			LCD_DisplayChar(140,140,PlayerTwoScore + '0');

			/****** Time Elapsed ********/
			LCD_DisplayChar(35,170,'T');
			LCD_DisplayChar(45,170,'i');
			LCD_DisplayChar(55,170,'m');
			LCD_DisplayChar(68,170,'e');
			LCD_DisplayChar(75,170,':');

			LCD_DisplayChar(140,170,TotalTime + '0');

			/********* Play Again Message ******************/
			LCD_Draw_Horizontal_Line(1,215,235,LCD_COLOR_BLUE);

			LCD_DisplayChar(35,260,'P');
			LCD_DisplayChar(45,260,'l');
			LCD_DisplayChar(55,260,'a');
			LCD_DisplayChar(65,260,'y');

			LCD_DisplayChar(80,260,'A');
			LCD_DisplayChar(95,260,'g');
			LCD_DisplayChar(107,260,'a');
			LCD_DisplayChar(115,260,'i');
			LCD_DisplayChar(122,260,'n');
			LCD_DisplayChar(133,260,'?');

		}
	}
}


void GAME_ClearBoard(uint8_t GameBoard[rows][cols])
{
	for(uint8_t ROW = 0; ROW < rows; ROW++)
	{
		for(uint8_t COL = 0; COL < cols; COL++)
		{
			GameBoard[ROW][COL] = 0;
		}
	}
}


void LCD_FinalScreenLose(void)
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	while (1)
	{
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
		{
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_WHITE);

			if(StaticTouchData.y < LCD_PIXEL_WIDTH/3)
			{
				GAME_ClearBoard(game_board);
				LCD_Gameplay();
			}
			else
			{
			}
		}
		else
		{
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&Font16x24);

			LCD_DisplayChar(25,30,'R');
			LCD_DisplayChar(40,30,'e');
			LCD_DisplayChar(50,30,'a');
			LCD_DisplayChar(60,30,'l');
			LCD_DisplayChar(70,30,'l');
			LCD_DisplayChar(80,30,'y');
			LCD_DisplayChar(90,30,'?');

			LCD_DisplayChar(110,30,'Y');
			LCD_DisplayChar(120,30,'o');
			LCD_DisplayChar(130,30,'u');

			LCD_DisplayChar(150,30,'L');
			LCD_DisplayChar(160,30,'o');
			LCD_DisplayChar(170,30,'s');
			LCD_DisplayChar(180,30,'t');

			LCD_DisplayChar(25,50,'T');
			LCD_DisplayChar(35,50,'o');

			LCD_DisplayChar(55,50,'T');
			LCD_DisplayChar(65,50,'h');
			LCD_DisplayChar(75,50,'e');

			LCD_DisplayChar(95,50,'C');
			LCD_DisplayChar(105,50,'o');
			LCD_DisplayChar(115,50,'m');
			LCD_DisplayChar(125,50,'p');
			LCD_DisplayChar(135,50,'u');
			LCD_DisplayChar(145,50,'t');
			LCD_DisplayChar(155,50,'e');
			LCD_DisplayChar(165,50,'r');
			LCD_DisplayChar(175,50,'?');


			LCD_Draw_Horizontal_Line(1,90,235,LCD_COLOR_GREY);


			/******* Player One Score *******/
			LCD_DisplayChar(35,120,'P');
			LCD_DisplayChar(45,120,'1');

			LCD_DisplayChar(65,120,'S');
			LCD_DisplayChar(75,120,'c');
			LCD_DisplayChar(85,120,'o');
			LCD_DisplayChar(95,120,'r');
			LCD_DisplayChar(105,120,'e');
			LCD_DisplayChar(115,120,':');

			LCD_DisplayChar(140,120,PlayerOneScore + '0');

			/******* Player Two Score **********/
			LCD_DisplayChar(35,140,'P');
			LCD_DisplayChar(45,140,'2');

			LCD_DisplayChar(65,140,'S');
			LCD_DisplayChar(75,140,'c');
			LCD_DisplayChar(85,140,'o');
			LCD_DisplayChar(95,140,'r');
			LCD_DisplayChar(105,140,'e');
			LCD_DisplayChar(115,140,':');

			LCD_DisplayChar(140,140,PlayerTwoScore + '0');

			/****** Time Elapsed ********/
			LCD_DisplayChar(35,170,'T');
			LCD_DisplayChar(45,170,'i');
			LCD_DisplayChar(55,170,'m');
			LCD_DisplayChar(68,170,'e');
			LCD_DisplayChar(75,170,':');

			LCD_DisplayChar(140,170,TotalTime + '0');

			/********* Play Again Message ******************/
			LCD_Draw_Horizontal_Line(1,215,235,LCD_COLOR_BLUE);

			LCD_DisplayChar(35,260,'P');
			LCD_DisplayChar(45,260,'l');
			LCD_DisplayChar(55,260,'a');
			LCD_DisplayChar(65,260,'y');

			LCD_DisplayChar(80,260,'A');
			LCD_DisplayChar(95,260,'g');
			LCD_DisplayChar(107,260,'a');
			LCD_DisplayChar(115,260,'i');
			LCD_DisplayChar(122,260,'n');
			LCD_DisplayChar(133,260,'?');

		}
	}
}



















void LCD_FinalScreenTwoPlayer(void)
{
	LCD_Clear(0,LCD_COLOR_WHITE);
	while (1)
	{
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
		{
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_WHITE);

			if(StaticTouchData.y < LCD_PIXEL_WIDTH/3)
			{
				GAME_ClearBoard(game_board);
				LCD_TwoPlayerGameplay();
			}
			else
			{
			}
		}
		else
		{
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_SetTextColor(LCD_COLOR_BLACK);
			LCD_SetFont(&Font16x24);

			LCD_DisplayChar(70,50,'G');
			LCD_DisplayChar(85,50,'a');
			LCD_DisplayChar(100,50,'m');
			LCD_DisplayChar(115,50,'e');

			LCD_DisplayChar(135,50,'O');
			LCD_DisplayChar(150,50,'v');
			LCD_DisplayChar(160,50,'e');
			LCD_DisplayChar(170,50,'r');
			LCD_DisplayChar(173,50,'.');

			LCD_Draw_Horizontal_Line(1,90,235,LCD_COLOR_GREY);


			/******* Player One Score *******/
			LCD_DisplayChar(35,120,'P');
			LCD_DisplayChar(45,120,'1');

			LCD_DisplayChar(65,120,'S');
			LCD_DisplayChar(75,120,'c');
			LCD_DisplayChar(85,120,'o');
			LCD_DisplayChar(95,120,'r');
			LCD_DisplayChar(105,120,'e');
			LCD_DisplayChar(115,120,':');

			LCD_DisplayChar(140,120,PlayerOneScore + '0');

			/******* Player Two Score **********/
			LCD_DisplayChar(35,140,'P');
			LCD_DisplayChar(45,140,'2');

			LCD_DisplayChar(65,140,'S');
			LCD_DisplayChar(75,140,'c');
			LCD_DisplayChar(85,140,'o');
			LCD_DisplayChar(95,140,'r');
			LCD_DisplayChar(105,140,'e');
			LCD_DisplayChar(115,140,':');

			LCD_DisplayChar(140,140,PlayerTwoScore + '0');

			/****** Time Elapsed ********/
			LCD_DisplayChar(35,170,'T');
			LCD_DisplayChar(45,170,'i');
			LCD_DisplayChar(55,170,'m');
			LCD_DisplayChar(68,170,'e');
			LCD_DisplayChar(75,170,':');

			LCD_DisplayChar(140,170,TotalTime + '0');

			/********* Play Again Message ******************/
			LCD_Draw_Horizontal_Line(1,215,235,LCD_COLOR_BLUE);

			LCD_DisplayChar(35,260,'P');
			LCD_DisplayChar(45,260,'l');
			LCD_DisplayChar(55,260,'a');
			LCD_DisplayChar(65,260,'y');

			LCD_DisplayChar(80,260,'A');
			LCD_DisplayChar(95,260,'g');
			LCD_DisplayChar(107,260,'a');
			LCD_DisplayChar(115,260,'i');
			LCD_DisplayChar(122,260,'n');
			LCD_DisplayChar(133,260,'?');

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



