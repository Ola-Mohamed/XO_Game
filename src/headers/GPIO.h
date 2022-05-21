/******************************************************************************
 * Module:GPIO
 *
 * File Name: GPIO.h
 *
 * Description: Header file for GPIO
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
void PortA_Init(void);
void PortB_Init(void);
void PortC_Init(void);
void PortD_Init(void);
void PortE_Init(void);
void PortF_Init(void);

void EnableInterrupts(void);
void WaitForInterrupt(void);
void GPIOF_Handler(void);
