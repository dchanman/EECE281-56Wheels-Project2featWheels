/**
*LCD.c
*
*@author: 	Derek Chan
*@date:		12 March, 2014
*
*Provides basic writing functions to a 
*16-pin Liquid Crystal Display.
*
*/

#include <stdio.h>
#include <at89lp51rd2.h>

#define CLK 22118400L
#define BAUD 115200L
#define TIMER_2_RELOAD (0x10000L-(CLK/(32L*BAUD)))

#define LCD_D P1
#define LCD_RS	P4_1
#define LCD_E	P3_2

#define LCD_ENABLE 1
#define LCD_DISABLE 0

void LCD_Delay(void);
void LCD_Clear(void);
void LCD_Put(unsigned char);
void LCD_WriteSring(unsigned char*);
void LCD_init(void);

/**
Stalls the processor for 1.4ms, which 
is required for calls to LCD_Clear
*/
void LCD_LongDelay(void){
	_asm
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R1, #7
		L2_50: mov R0, #184
		L1_50: djnz R0, L1_50 ; 2 machine cycles-> 2*0.5425347us*184=200us
		djnz R1, L2_50 ; 200us*25=0.005s
		ret
	_endasm;
}

/**
Stalls the processor so that the LCD
has enough time to do its work
*/
void LCD_ShortDelay(void){
	_asm
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R0, #46
		shortL1: djnz R0,shortL1  ; 2 machine cycles-> 2*0.5425347us*184=49.9us
		ret
	_endasm;
}

/**
Clears the LCD display

@modifies:	Sets LCD_RS to 0
*/
void LCD_Clear(){
	LCD_RS = 0;
	LCD_E = LCD_ENABLE;
	LCD_ShortDelay();
	LCD_D = 1;
	LCD_ShortDelay();
	LCD_E = LCD_DISABLE;
	LCD_LongDelay();
}

/**
Puts a single character onto the LCD display.
Note that this function DOES NOT change the 
value of LCD_RS, so it is indifferent to which register
from the LCD to use.
*/
void LCD_Put(unsigned char c){
	LCD_E = LCD_ENABLE;
	LCD_ShortDelay();
	LCD_D = c;
	LCD_ShortDelay();
	LCD_E = LCD_DISABLE;
	LCD_ShortDelay();
}

/**
Writes a string onto the LCD display

@modifies:	Sets LCD_RS to 1
*/
void LCD_WriteString(unsigned char *c){
	LCD_RS = 1;
	while(*c != '\0'){
		LCD_Put(*c);
		printf("%c",*c); 
		c++;
		
	}
}


/**
Initializes the LCD to be 8-bit, 2 lines, 5x7, 
Display ON, Cursor ON, Cursor Blinking
Entry mode, Increment cursor position, No display shift
*/
void LCD_Init(){
    LCD_E = 0;
    LCD_Clear();
    LCD_Put(((unsigned char)0b00111000));	//Function set, 8 bit, 2 lines, 5×7
    LCD_Put(((unsigned char)0b00001111));	//Display ON, Cursor On, Cursor Blinking
    LCD_Put(((unsigned char)0b00000011));   //Entry Mode, Increment cursor position, No display shift
    return;
}
