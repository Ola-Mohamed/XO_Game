#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"


volatile unsigned long delay;

void PortB_Init(void){
	
   SYSCTL_RCGC2_R |= 0x00000002;        // 1) B clock
  delay =  SYSCTL_RCGCGPIO_R; 	// delay
	GPIO_PORTB_LOCK_R = 0x4C4F434B;   // 2)unlock GPIO of PORTB
	GPIO_PORTB_CR_R = 0x01;          //Enable commit
	GPIO_PORTB_AMSEL_R = 0x00;      // 3) disable analog function
	GPIO_PORTB_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTB_DIR_R = 0xFF;        // 5) PORT output
	GPIO_PORTB_AFSEL_R = 0x00;      // 6) no alternate function
  GPIO_PORTB_DEN_R = 0xFF;        // 7) enable digital pins PF4-PF0
}

void PortF_Init(void)
{
 
  SYSCTL_RCGC2_R |= 0x00000020;   // 1) F clock
  delay = SYSCTL_RCGC2_R;         // delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // 2) unlock PortF PF0
  GPIO_PORTF_CR_R = 0x1F;         // allow changes to PF4-0
	GPIO_PORTF_LOCK_R = 0;            
  GPIO_PORTF_AMSEL_R = 0x00;      // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;        // 5) PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;      // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;        // enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;        // 7) enable digital pins PF4-PF0
	GPIO_PORTF_IS_R &= 0x00;     	  // (d) PF4, PF0 are edge-sensitive
	GPIO_PORTF_IBE_R &= 0x00;			  // PF4, PF0 are not both edges
  GPIO_PORTF_IEV_R |= 0x11;    	  // PF4, Pf0 are rising edge event
  GPIO_PORTF_ICR_R = 0x11;      						// (e) Clear flag4, flag0
  GPIO_PORTF_IM_R |= 0x11;      						// (f) Arm interrupt on PF4, PF0
	
}

