/******************************************************************************
 * Module: Main File
 *
 * File Name: Main.c
 *
 * Description: Source file for Main File
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

#include "./headers/Nokia5110.h"
#include "./headers/TExaS.h"
#include "./headers/GPIO.h"
#include "./headers/XO Game.h"
#include "./headers/Interrupt.h"

int main(void)
{
	TExaS_Init(SSI0_Real_Nokia5110_Scope);

	PortF_Init(); // intialization Port F
	
	PortB_Init();
	
	Nokia5110_Init(); // intialization Nokia Lcd
	
	Nokia5110_ClearBuffer(); // Clear buffer for nokia lcd

	Nokia5110_DisplayBuffer(); // draw buffer

	GameIntro(); // enter to the game

	GameInitialization(); // reset

	DrawClearGameMatrix(); // clear data

	while (1)
	{
		RunGame(); // start game
	}
}
