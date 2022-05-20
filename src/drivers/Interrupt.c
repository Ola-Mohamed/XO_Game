/******************************************************************************
 * Module: Interrupt
 *
 * File Name: Interrupt.c
 *
 * Description: Source file for Interrupt
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/
 
#include "..\\./headers/tm4c123gh6pm.h" 
#include "..\\./headers/Interrupt.h"
#include "..\\./headers/Timer.h"
#include "..\\./headers/GPIO.h"


/*******************************************************************************
 *                           Varibles                              *
 *******************************************************************************/
 
unsigned char Sw1Flag=0,Sw2Flag=0;

/*******************************************************************************
 *                        Functions                             *
 *******************************************************************************/

/* SW1 is connected to PF4 pin, SW2 is connected to PF0. */
/* Both of them trigger PORTF falling edge interrupt */
void  GPIOPortF_Handler(void)
{	
	
  if (GPIO_PORTF_MIS_R & 0x10) /* check if interrupt causes by PF4/SW1*/
    {  	
        Timer2_delay (3000);
   	 if (GPIO_PORTF_MIS_R & 0x10) /* check if interrupt causes by PF4/SW1*/
       { 			 
           Sw1Flag=1 ;
           GPIO_PORTF_ICR_R |= 0x10; /* clear the interrupt flag */
			 }
	  }
						
   if (GPIO_PORTF_MIS_R & 0x01) /* check if interrupt causes by PF0/SW2 */
    {
      Timer2_delay (3000);	
        if (GPIO_PORTF_MIS_R & 0x01) /* check if interrupt causes by PF0/SW2 */
         {			
      Sw2Flag=1 ;
      GPIO_PORTF_ICR_R|= 0x01; /* clear the interrupt flag */
    
	}
 }
}
