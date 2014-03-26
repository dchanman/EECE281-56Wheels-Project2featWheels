/**
*General
*
*@author:	Derek Chan
*@date:		20 March, 2014
*
*Provides a standard header for test files
*and the main program so that the serial 
*port can be used and the standard C library.
*/
#ifndef GENERAL_H_
#define GENERAL_H_ 0

#include <stdio.h>
#include <stdlib.h>
#include <at89lp51rd2.h>

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))

//Pin assignments
	//LCD pins
#define LCD_D P1
#define LCD_RS	P4_1
#define LCD_E	P3_2

	//Motor pins
#define MOTOR_L_FORWARD		P4_3
#define MOTOR_L_BACKWARD	P3_7
#define MOTOR_R_FORWARD		P3_6
#define	MOTOR_R_BACKWARD	P3_5

	//ADC pins
#define ADC_SCK		P1_6//P0_4
#define ADC_MISO	P1_5//P0_5
#define ADC_MOSI	P1_7//P0_6
#define ADC_CE		P1_4//P0_7	//active low

	//Analog IR pins
#define IR_DETECT			P2_0

/*
		P0			P1			P2			P3			P4
.0					LCD			IR_ANALOG
.1					LCD			 						LCD		
.2					LCD						LCD
.3					LCD									MOTOR
.4		ADC			LCD
.5		ADC			LCD						MOTOR
.6		ADC			LCD						MOTOR
.7		ADC			LCD						MOTOR

*/


/* ANSI colors */
#define	COLOR_BLACK		0
#define	COLOR_RED		1
#define	COLOR_GREEN		2
#define	COLOR_YELLOW	3
#define	COLOR_BLUE		4
#define	COLOR_MAGENTA	5
#define	COLOR_CYAN		6
#define	COLOR_WHITE		7

/* Some ANSI escape sequences */
#define CURSOR_ON "\x1b[?25h"
#define CURSOR_OFF "\x1b[?25l"
#define CLEAR_SCREEN "\x1b[2J"
#define GOTO_YX "\x1B[%d;%dH"
#define CLR_TO_END_LINE "\x1B[K"
/* Black foreground, white background */
#define BKF_WTB "\x1B[0;30;47m"
#define FORE_BACK "\x1B[0;3%d;4%dm"
#define FONT_SELECT "\x1B[%dm"
/*
° ± ² ³ ´ µ ¶ · ¸ ¹ º » ¼ ½ ¾ ¿

À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï

Ð Ñ Ò Ó Ô Õ Ö × Ø Ù Ú Û Ü Ý Þ ß
*/

#include "General.c"

void General_Init();

#endif