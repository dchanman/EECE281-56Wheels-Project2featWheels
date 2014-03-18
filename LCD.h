/**
*LCD
*
*@author: 	Derek Chan
*@date:		12 March, 2014
*
*Provides basic writing functions to a 
*16-pin Liquid Crystal Display.
*
*/

#include "LCD.c"

#define LCD_D P1
#define LCD_RS	P4_1
#define LCD_E	P3_2

#define LCD_ENABLE 1
#define LCD_DISABLE 0

void LCD_LongDelay(void);
void LCD_ShortDelay(void);
void LCD_Clear(void);
void LCD_Put(unsigned char);
void LCD_WriteSring(unsigned char*);
void LCD_init(void);