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
#include "./headers/LED.h"

/*******************************************************************************
 *                           Varibles                              *
 *******************************************************************************/

unsigned long TimerCount;

int playedCells, currentCell;

char turnMark, GameMatrix[9], xWins = 0, oWins = 0;

extern unsigned char Sw1Flag, Sw2Flag;

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
	Nokia5110_DisplayBuffer();			   // display that window
	Timer2_delay(30);					   // 3 seconds
	Nokia5110_Clear();					   // clear the whole screen
	Nokia5110_SetCursor(1, 2);			   // set cursor at first X place on the screen and the 3rd y to be nearly in the middle
	Nokia5110_OutString("Welcome To");	   // write this string to screen
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString(" XO Game");
	Timer2_delay(50);
	Nokia5110_Clear(); // clear the whole screen
	Nokia5110_SetCursor(2, 2);
	Nokia5110_OutString("X-Player");
	Nokia5110_SetCursor(1, 4);
	Nokia5110_OutString("Plays First");
	Set_Led_Pin();
	Timer2_delay(50);
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
	turnMark = 'X';	  // first player is always X
	currentCell = -1; // no cells are hovered or selected
	for (i = 0; i < 9; i++)
		GameMatrix[i] = ' '; // erase all drawings in cells matrix
	Timer2_delay(50);
	Set_Led_2();
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
	Timer2_delay(5);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, (SQUAREHEIGHT - 1), square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, (SQUAREHEIGHT - 1), square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP(0, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, 2 * (SQUAREHEIGHT - 1) + 3, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP(0, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP((SQUAREHEIGHT - 1) + 3, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

	Nokia5110_PrintBMP(2 * (SQUAREHEIGHT - 1) + 6, 3 * (SQUAREHEIGHT - 1) + 6, square, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(5);

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

	if (Sw1Flag)
	{
		Sw1Flag = 0;
		lastCell = currentCell; // store the cell location before moving to next one
		currentCell++;
		if (currentCell == 9)
			currentCell = 0;   // loop back to the beginning
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
		Timer2_delay(20);
	}
	if (Sw2Flag && currentCell != -1)
	{
		Sw2Flag = 0;
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
				GameMatrix[currentCell] = turnMark;																		// fill the matrix and take that place for X
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
					{			   // no enough playing, time to study
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
			// currentCell = -1;
			playedCells++;
			if (playedCells == 9) // Game finished with no winner
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
		else // if the cell was already taken
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
		Timer2_delay(20);
	}
}

/************************************************************************************
 * Service Name:checkWinner
 * Parameters (in): char player
 * Return value: 0 or 1
 * Description: Function to check if player x or o is winning or not
 ************************************************************************************/

int checkWinner(char player)
{
	int Winning_cell_1 = 0, Winning_cell_2 = 0, Winning_cell_3 = 0, i; // c: cell (they are 3 as 3 same connected cells are a must to win)
	if (GameMatrix[0] == player && GameMatrix[1] == player && GameMatrix[2] == player)
	{
		Winning_cell_1 = 0;
		Winning_cell_2 = 1;
		Winning_cell_3 = 2;
		i = 0;
	}
	else if (GameMatrix[3] == player && GameMatrix[4] == player && GameMatrix[5] == player)
	{
		Winning_cell_1 = 3;
		Winning_cell_2 = 4;
		Winning_cell_3 = 5;
		i = 1;
	}
	else if (GameMatrix[6] == player && GameMatrix[7] == player && GameMatrix[8] == player)
	{
		Winning_cell_1 = 6;
		Winning_cell_2 = 7;
		Winning_cell_3 = 8;
		i = 2;
	}
	else if (GameMatrix[0] == player && GameMatrix[3] == player && GameMatrix[6] == player)
	{
		Winning_cell_1 = 0;
		Winning_cell_2 = 3;
		Winning_cell_3 = 6;
		i = 3;
	}
	else if (GameMatrix[1] == player && GameMatrix[4] == player && GameMatrix[7] == player)
	{
		Winning_cell_1 = 1;
		Winning_cell_2 = 4;
		Winning_cell_3 = 7;
		i = 4;
	}
	else if (GameMatrix[2] == player && GameMatrix[5] == player && GameMatrix[8] == player)
	{
		Winning_cell_1 = 2;
		Winning_cell_2 = 5;
		Winning_cell_3 = 8;
		i = 5;
	}
	else if (GameMatrix[0] == player && GameMatrix[4] == player && GameMatrix[8] == player)
	{
		Winning_cell_1 = 0;
		Winning_cell_2 = 4;
		Winning_cell_3 = 8;
		i = 6;
	}
	else if (GameMatrix[2] == player && GameMatrix[4] == player && GameMatrix[6] == player)
	{
		Winning_cell_1 = 2;
		Winning_cell_2 = 4;
		Winning_cell_3 = 6;
		i = 7;
	}
	if (Winning_cell_1 || Winning_cell_2 || Winning_cell_2)
	{
		if (player == 'X')
		{ /*Hoovering the 3 selected winning cells*/
			Nokia5110_PrintBMP((Winning_cell_1 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_1 % 3), (Winning_cell_1 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_1 / 3), selectedX, 0);
			Nokia5110_PrintBMP((Winning_cell_2 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_2 % 3), (Winning_cell_2 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_2 / 3), selectedX, 0);
			Nokia5110_PrintBMP((Winning_cell_3 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_3 % 3), (Winning_cell_3 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_3 / 3), selectedX, 0);
			Clear_Led_Pin();
			Blink_LEDS_2();
			Clear_Led_Pin();
			GPIO_PORTF_DATA_R = 0x04; // LED is blue (X won)
			Nokia5110_DisplayBuffer();
		}
		else
		{
			Nokia5110_PrintBMP((Winning_cell_1 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_1 % 3), (Winning_cell_1 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_1 / 3), selectedO, 0);
			Nokia5110_PrintBMP((Winning_cell_2 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_2 % 3), (Winning_cell_2 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_2 / 3), selectedO, 0);
			Nokia5110_PrintBMP((Winning_cell_3 % 3) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_3 % 3), (Winning_cell_3 / 3 + 1) * (SQUAREHEIGHT - 1) + 3 * (Winning_cell_3 / 3), selectedO, 0);
			Clear_Led_Pin();
			Blink_LEDS_3();
			Clear_Led_Pin();
			GPIO_PORTF_DATA_R = 0x08; // LED is green  (O won)
			Nokia5110_DisplayBuffer();
		}
		/*draw the strike line with pixels (dots) on the 3 hoovered winning cells*/
		if (i == 0)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(i, 6);
		}
		else if (i == 1)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(i, 23);
		}
		else if (i == 2)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(i, 40);
		}
		else if (i == 3)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(6, i);
		}
		else if (i == 4)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(23, i);
		}
		else if (i == 5)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(40, i);
		}
		else if (i == 6)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(i, i);
		}
		else if (i == 7)
		{
			for (i = 0; i < 48; i++)
				Nokia5110_SetPixel(i, 47 - i);
		}
		Nokia5110_DisplayBuffer();
		Timer2_delay(5);
		GPIO_PORTF_DATA_R = 0x00; // LED is dark (end of round)
		Clear_Led_Pin();
		return 1; // there is a winner
	}
	return 0; // there is no winner
}

/************************************************************************************
 * Service Name:Display_Winner
 * Parameters (in): None
 * Return value: None
 * Description: Function to display the winner of xo game
 ************************************************************************************/
void Display_Winner(char player)
{
	(player == 'X') ? xWins++ : oWins++; // for every round count winning times
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 47, border, 0); // draw the game frame
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutChar(player);
	Nokia5110_OutString("-Player");
	Nokia5110_SetCursor(4, 4);
	Nokia5110_OutString("wins");
	Timer2_delay(50);
	Nokia5110_DisplayBuffer();
	// Nokia5110_Clear(); // clear the screen
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("X: ");
	Nokia5110_OutUDec(xWins);
	Nokia5110_SetCursor(2, 4);
	Nokia5110_OutString("O: ");
	Nokia5110_OutUDec(oWins);
	Timer2_delay(50);
	Nokia5110_Clear(); // clear the screen
}

/************************************************************************************
 * Service Name:displayDraw
 * Parameters (in): None
 * Return value: None
 * Description: Function to be executed if a draw game
 ************************************************************************************/
void displayDraw()
{
	GPIO_PORTF_DATA_R = 0x0E; // LED is white (draw game)
	Blink_LEDS();
	Timer2_delay(5);
	GPIO_PORTF_DATA_R = 0x00; // LED is dark  (end round)
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 47, border, 0); // draw the game frame
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("Game is");
	Nokia5110_SetCursor(2, 4);
	Nokia5110_OutString("a draw");
	Timer2_delay(20);
	Nokia5110_Clear();
}

/************************************************************************************
 * Service Name:displayStatus
 * Parameters (in): None
 * Return value: None
 * Description: Function to show whose turn it is every play
 ************************************************************************************/
void displayStatus()
{
	Nokia5110_SetCursor(8, 1);
	Nokia5110_OutChar('<');
	Nokia5110_OutChar(turnMark);
	Nokia5110_OutChar('>');
	Nokia5110_SetCursor(8, 2);
	Nokia5110_OutString("Turn");
}
/************************************************************************************
 * Service Name: CheckPlayAgain
 * Parameters (in): None
 * Return value: None
 * Description: function to check if want to play again or not
 ************************************************************************************/
int CheckPlayAgain()
{
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 47, border2, 0);
	Nokia5110_DisplayBuffer();
	Timer2_delay(50);
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 47, border, 0); // draw the game frame
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("SW1 |SW2");
	Nokia5110_SetCursor(2, 4);
	Nokia5110_OutString("Yes |No");
	while (1)
	{
		if (Sw1Flag == 1)
		{
			Sw1Flag = 0;
			return 1;
		}

		if (Sw2Flag == 1)
		{
			Sw2Flag = 0;
			return 0;
		}
	}
}

/************************************************************************************
 * Service Name: outr
 * Parameters (in): None
 * Return value: None
 * Description: function to out from game when fail
 ************************************************************************************/
void EndGame()
{ // if sw2 is pressed (no rematch)
	Nokia5110_ClearBuffer();
	Nokia5110_PrintBMP(0, 47, border, 0);
	Nokia5110_DisplayBuffer();
	Nokia5110_SetCursor(2, 3);
	Nokia5110_OutString("Goodbye");
	Set_Led_Pin();
	Timer2_delay(20);
	Clear_Led_Pin();
	Nokia5110_Clear();
}
