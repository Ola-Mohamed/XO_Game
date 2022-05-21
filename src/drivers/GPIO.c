/******************************************************************************
 * Module: GPIO
 *
 * File Name: GPIO.c
 *
 * Description: Source file for GPIO
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

#include "..\\./headers/GPIO.h"
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/TExaS.h"
#include "..\\./headers/Timer.h"

volatile unsigned long delay;
unsigned char Sw1Flag = 0, Sw2Flag = 0;

void PortB_Init(void)
{

  SYSCTL_RCGC2_R |= 0x00000002;   // 1) B clock
  delay = SYSCTL_RCGCGPIO_R;      // delay
  GPIO_PORTB_LOCK_R = 0x4C4F434B; // 2)unlock GPIO of PORTB
  GPIO_PORTB_CR_R = 0x01;         // Enable commit
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
  GPIO_PORTF_AMSEL_R = 0x00;      // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000; // 4) GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;        // 5) PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;      // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;        // enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;        // 7) enable digital pins PF4-PF0
  GPIO_PORTF_IS_R &= ~0x11;       // (d) PF4, PF0 are edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;      // PF4, PF0 are not both edges
  GPIO_PORTF_IEV_R &= ~0x11;      // PF4, Pf0 are falling edge event
  GPIO_PORTF_ICR_R = 0x11;        // (e) Clear flag4, flag0
  GPIO_PORTF_IM_R |= 0x11;        // (f) Arm interrupt on PF4, PF0
  NVIC_PRI7_R = (NVIC_PRI7_R & 0xff00ffff) | 0x00A00000;
  NVIC_EN0_R = 0x40000000;
  EnableInterrupts();
}

void GPIOPortF_Handler(void)
{
  while (GPIO_PORTF_MIS_R != 0)
  {
    if (GPIO_PORTF_MIS_R & 0x10) /* is it SW1 (PF4)?*/
    {                            /* GPIOF4 pin interrupt */
      /* turn ON green LED (PD3) */
      Timer2_delay(35);
      if (!(GPIO_PORTF_DATA_R & 0x10))
      {
        Sw1Flag = 1;
        GPIO_PORTF_ICR_R |= 0x10;
      }
    }
    else if (GPIO_PORTF_MIS_R & 0x01) /* then it must be SW2 (PF0) */
    {                                 /* GPIOF0 pin interrupt */
      /* turn ON blue LED (PD3) */
      Timer2_delay(35);
      if (!(GPIO_PORTF_DATA_R & 0x01))
      {
        Sw2Flag = 1;
        GPIO_PORTF_ICR_R |= 0x01;
      }
    }
    else
    { /* We should never get here */
      /* But if we do, clear all pending interrupts */
      GPIO_PORTF_ICR_R = GPIO_PORTF_MIS_R;
    }
  }
}
