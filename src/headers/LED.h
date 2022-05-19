/******************************************************************************
 * Module: LED
 *
 * File Name: LED.h
 *
 * Description: Header file for LED
 *
 * Authors: Ola Mohamed - Abdelrhman Atef - Abdelrhman Hesham -Diaa Eldin Hassan -Ahmed Gamal - Rammzi Muhammed
 ******************************************************************************/

#define PORTB_LED1_PIN 2

#define PORTB_LED2_PIN 3

#define PORTB_LED3_PIN 4


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void Set_Led_Pin(void);
void Set_Led_2(void);
void Set_Led_3(void);
void Clear_Led_2(void);
void Clear_Led_3(void);
void Clear_Led_Pin(void);

void Blink_LEDS_3(void);
void Blink_LEDS(void);
void Blink_LEDS_2(void);
