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
