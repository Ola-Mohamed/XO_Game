/******************************************************************************
 * Module: LED
 *
 * File Name: LED.c
 *
 * Description: Source file for LED
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

#include "..\\./headers/tm4c123gh6pm.h" 
#include "..\\./headers/LED.h"
#include "..\\./headers/Timer.h"
#include "..\\./headers/GPIO.h"



int i;
/*******************************************************************************
 *                           Function                                     *
 *******************************************************************************/

void Set_Led_Pin(void)
{
    GPIO_PORTB_DATA_R|= (1<<PORTB_LED1_PIN); //PB2
   	Timer2_delay (500);
		GPIO_PORTB_DATA_R |= (1<<PORTB_LED2_PIN); //PB3
  	Timer2_delay (500);
		GPIO_PORTB_DATA_R |= (1<<PORTB_LED3_PIN); //PB4
	
}
void Set_Led_2(void)
{  
		GPIO_PORTB_DATA_R |= (1<<PORTB_LED2_PIN); //PB3	
}
void Clear_Led_2(void)
{  
		GPIO_PORTB_DATA_R &=~(1<<PORTB_LED2_PIN); //PB3	
}




void Set_Led_3(void)
{  
		GPIO_PORTB_DATA_R |= (1<<PORTB_LED3_PIN); //PB4	
}

void Clear_Led_3(void)
{  
		GPIO_PORTB_DATA_R &=~(1<<PORTB_LED3_PIN); //PB4	
}

void Clear_Led_Pin(void)
{
   	GPIO_PORTB_DATA_R &=~(1<<PORTB_LED1_PIN); //PB2 
	  GPIO_PORTB_DATA_R &=~(1<<PORTB_LED2_PIN); //PB3
	  GPIO_PORTB_DATA_R &=~(1<<PORTB_LED3_PIN); //PB4
	
}


void Blink_LEDS(void){
		for(i=0; i<3; i++){
				GPIO_PORTB_DATA_R |= (1<<PORTB_LED1_PIN); //PB2
				Timer2_delay (2000);
			  GPIO_PORTB_DATA_R &=~(1<<PORTB_LED1_PIN); //PB2
				Timer2_delay (2000);
			}
	
	
}

void Blink_LEDS_2(void){
		for(i=0; i<3; i++){
				GPIO_PORTB_DATA_R |= (1<<PORTB_LED2_PIN); //PB3
				Timer2_delay (2000);
			  GPIO_PORTB_DATA_R &=~(1<<PORTB_LED2_PIN); //PB3
				Timer2_delay (2000);
			}
	
	
}
void Blink_LEDS_3(void){
		for(i=0; i<3; i++){
				GPIO_PORTB_DATA_R |= (1<<PORTB_LED3_PIN); //PB4
				Timer2_delay (2000);
			  GPIO_PORTB_DATA_R &=~(1<<PORTB_LED3_PIN); //PB4
				Timer2_delay (2000);
			}
	
	
}
