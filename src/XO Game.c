/******************************************************************************
 * Module: XO
 *
 * File Name: XO Game.c
 *
 * Description: Source file for XO Game
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

#include "./headers/tm4c123gh6pm.h"
#include "./headers/Nokia5110.h"
#include "./headers/TExaS.h"
#include "./headers/GameArt.h"
#include "./headers/XO Game.h"
#include "./headers/Timer.h"
#include "./headers/Interrupt.h"
#include "./headers/LED.h"

/*******************************************************************************
 *                           Varibles                              *
 *******************************************************************************/

unsigned long TimerCount;

int playedCells, currentCell;

char turnMark, GameMatrix[9], xWins = 0, oWins = 0;

extern unsigned char Sw1Flag,Sw2Flag;


/*******************************************************************************
 *                              Functions                                      *
 *******************************************************************************/

/************************************************************************************
 * Service Name:GameIntro
 * Parameters (in): None
 * Parameters (out): None
 * Return value: None
 * Description: function to enter to the game
 ************************************************************************************/

void GameIntro(void)
{
	Nokia5110_PrintBMP(0, 47, introbg, 0); // darwing the frame of welcome window
	Nokia5110_DisplayBuffer();	// display that window
	Timer2_delay (3000);
	Nokia5110_Clear(); // clear the whole screen
	Nokia5110_SetCursor(1, 2);			   // set cursor at first X place on the screen and the 3rd y to be nearly in the middle
	Nokia5110_OutString("Welcome To");	   // write this string to screen
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString(" XO Game");
	Timer2_delay (5000);
	Nokia5110_Clear(); // clear the whole screen
  Nokia5110_SetCursor(2, 2);
	Nokia5110_OutString("X-Player");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString("Plays First");
	Set_Led_Pin();
	Timer2_delay (5000);
	Clear_Led_Pin();
	Nokia5110_Clear(); // clear the whole screen
}

/************************************************************************************
 * Service Name: GameInitialization
 * Parameters (in): None
 * Return value: None
 * Description: Function for reset game "start again"
 ************************************************************************************/
void GameInitialization()
{
	int i;
	playedCells = 0;  // make all cells available to play at
	Timer2_delay (5000);
	turnMark = 'X';	  // first player is always X
	Set_Led_2();
	currentCell = -1; // no cells are hovered or selected
	for (i = 0; i < 9; i++)
		GameMatrix[i] = ' '; // erase all drawings in cells matrix
}

/************************************************************************************
 * Service Name:DrawClearGameMatrix
 * Parameters (in): None
 * Return value: None
 * Description: Function for drawing X O boxes and player turn
 ************************************************************************************/

void DrawClearGameMatrix()
{
	Nokia5110_ClearBuffer();
	// square is defined in gameArt to make the shape of the 9 squares of the game
	Nokia5110_PrintBMP(0, (SQUAREHEIGHT - 1), square, 0); // Nokia5110_printBMP(x_cor , y_cor , pointer_to_image (square or VL) , threshold(0 or 1))
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, (SQUAREHEIGHT - 1), square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, (SQUAREHEIGHT - 1), square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(0, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(0, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay (500);

	Nokia5110_PrintBMP(3 * (SQUAREHEIGHT - 1) + 9, (VH - 1), verticalLine, 0);
	Nokia5110_DisplayBuffer();

	displayStatus(); // to show whose player turn is it now
}

/************************************************************************************
 * Service Name   :RunGame
 * Parameters (in) : None
 * Return value: None
 * Description: Function for handeling xo game play
 ************************************************************************************/
void RunGame()
{
	int row, col, lastRow, lastCol, lastCell;
	//int f1 = 0, f2 = 0; // flags to to check if switches are pressed and released and act on them
		GPIOF_Handler();

	/*while (!(GPIO_PORTF_MIS_R & 0x10)){
	GPIOF_Handler();
	}
		
	while (!(GPIO_PORTF_MIS_R & 0x01)){
	GPIOF_Handler();
	}
	*/
	if(button_is_pressed(Sw1Flag))
	{Sw1Flag =0;
		lastCell = currentCell; //store the cell location before moving to next one
		currentCell++;
		if (currentCell == 9)
			currentCell = 0;  // loop back to the beginning
		// get the certain cell to play on
		// note: Game matrix is drown row by row and starting from index 0
			row = currentCell / 3; // ex: if currentCell = 5, so row = 1 , col = 2, and that's the true place of it
			col = currentCell % 3;
		
		// while hovered
		if (GameMatrix[currentCell] == 'X')
		{
			Nokia5110_PrintBMP(col * (SQUAREHEIGHT - 1) + 3 * col, (row + 1) * (SQUAREHEIGHT - 1) + 3 * row, selectedX, 0);
		}
		else if (GameMatrix[currentCell] == 'O')
		{
			Nokia5110_PrintBMP(col * (SQUAREHEIGHT - 1) + 3 * col, (row + 1) * (SQUAREHEIGHT - 1) + 3 * row, selectedO, 0);
		}
		else
		{
			Nokia5110_PrintBMP(col * (SQUAREHEIGHT - 1) + 3 * col, (row + 1) * (SQUAREHEIGHT - 1) + 3 * row, selectedSquare, 0);
		}
		
		// while unhovered get the last indicies and draw previous art
		if (lastCell == 8 || lastCell == -1)
		{
			lastRow = 2;
			lastCol = 2;
			lastCell = 8;
		}
		else
		{
			lastRow = (currentCell - 1) / 3;
			lastCol = (currentCell - 1) % 3;
		}

		if (GameMatrix[lastCell] == 'X')
		{
			Nokia5110_PrintBMP(lastCol * (SQUAREHEIGHT - 1) + 3 * lastCol, (lastRow + 1) * (SQUAREHEIGHT - 1) + 3 * lastRow, X, 0);
		}
		else if (GameMatrix[lastCell] == 'O')
		{
			Nokia5110_PrintBMP(lastCol * (SQUAREHEIGHT - 1) + 3 * lastCol, (lastRow + 1) * (SQUAREHEIGHT - 1) + 3 * lastRow, O, 0);
		}
		else
		{
			Nokia5110_PrintBMP(lastCol * (SQUAREHEIGHT - 1) + 3 * lastCol, (lastRow + 1) * (SQUAREHEIGHT - 1) + 3 * lastRow, square, 0); // not to leave the last cell hoovered
		}
		Nokia5110_DisplayBuffer();
		displayStatus();
		Timer2_delay (2000);
	}
	if((button_is_pressed(Sw2Flag)) && currentCell != -1)
	{ Sw2Flag =0;
		// confirm that switch 2 is pressed and there is a selected cell
		if (GameMatrix[currentCell] == ' ')
		{ // if nothing in the cell
			// get the certain cell to play on
			// note: Game Matrix is drown row by row and starting from index 0
			row = currentCell / 3; // ex: if currentCell = 5, so row = 1 , col = 2, and that's the true place of it
			col = currentCell % 3;
			// If Current Player is X
			
			if (turnMark == 'X')
			{
				
				Nokia5110_PrintBMP(col * (SQUAREHEIGHT - 1) + 3 * col, (row + 1) * (SQUAREHEIGHT - 1) + 3 * row, X, 0); // draw x in the chosen cell
				GameMatrix[currentCell] = turnMark;		// fill the matrix and take that place for X
				Clear_Led_2();
				Set_Led_3();
				if (checkWinner(turnMark))
				{ // if strike
					Display_Winner(turnMark);
					if (CheckPlayAgain())
					{ // want to play again?
						GameInitialization();
						DrawClearGameMatrix();
						return; // return to main while(1) loop which will call RunGame() again
					}
					else
					{			 // no enough playing, time to study
						EndGame(); // goodBye
						while (1)
							; // an unbreakable infinite loop after clearing screen by EndGame()
					}
				}
				// if game has no winner yet switch to player O
				turnMark = 'O';
			}
			// If Current Player is O
			else
			{

				Nokia5110_PrintBMP(col * (SQUAREHEIGHT - 1) + 3 * col, (row + 1) * (SQUAREHEIGHT - 1) + 3 * row, O, 0);
				GameMatrix[currentCell] = turnMark;
				Clear_Led_3();
				Set_Led_2();				
				if (checkWinner(turnMark))
				{
					Display_Winner(turnMark);
					if (CheckPlayAgain())
					{
						GameInitialization();
						DrawClearGameMatrix();
						return;
					}
					else
					{
						EndGame();
						while (1)
							;
					}
				}
				// if game has no winner yet switch to player X
				turnMark = 'X';
			}
			Nokia5110_DisplayBuffer();
			displayStatus();
			//currentCell = -1;
			playedCells++;
			if (playedCells == 9) //Game finished with no winner
			{
				displayDraw();
				if (CheckPlayAgain())
				{
					GameInitialization();
					DrawClearGameMatrix();
					return;
				}
				else
				{
					EndGame();
					while (1)
						;
				}
			}
		}
		else  // if the cell was already taken
		{							  
			Nokia5110_SetCursor(8, 3);
			Nokia5110_OutString("Not");
			Nokia5110_SetCursor(8, 4);
			Nokia5110_OutString("Your");
			Nokia5110_SetCursor(8, 5);
			Nokia5110_OutString("Spot");

			// Blink  LedS 3 times			
			Blink_LEDS();

			displayStatus();
		}
		Timer2_delay (2000);
	}
}
