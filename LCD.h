/**
*LCD
*
*@author: 	Derek Chan
*@date:		12 March, 2014
*
*Provides basic writing functions to a 
*16-pin Liquid Crystal Display. The LCD
*is assumed to be connected in 8-bit mode,
*where all of its pins are used.
*/

#ifndef LCD_H_
#define LCD_H_ 0 

#define LCD_ENABLE 1
#define LCD_DISABLE 0

#define LCD_ROW1 0
#define LCD_ROW2 40

#include "LCD.c"


void LCD_LongDelay(void);
void LCD_ShortDelay(void);
void LCD_Clear(void);
void LCD_Put(unsigned char);
void LCD_WriteString(unsigned char *string);
void LCD_Init(void);



#endif