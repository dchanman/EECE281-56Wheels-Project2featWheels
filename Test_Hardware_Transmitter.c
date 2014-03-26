#include <stdio.h>
#include <at89lp51rd2.h>

// ~C51~ 
 
#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))

//We want timer 0 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define FREQ 15000L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

//Output for our PWM
#define PWM_OUTPUT1	P3_6
#define PWM_OUTPUT2	P3_7

//LCD variables
#define LCD_D P0
#define LCD_RS	P2_1
#define LCD_E	P2_2
#define LCD_ENABLE 1
#define LCD_DISABLE 0



void LCD_Delay(void);
void LCD_Clear(void);
void LCD_Put(unsigned char);
void LCD_WriteSring(unsigned char*);
void LCD_init(void);

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char pwm1;
volatile int direction;

/**
Stalls the processor for 1.4ms
*/
void LCD_Delay(void){
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
	LCD_Delay();
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
	LCD_Clear();
	LCD_RS = 1;
	while(*c != '\0'){
		LCD_Put(*c);
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


unsigned char _c51_external_startup(void)
{
	// Configure ports as a bidirectional with internal pull-ups.
	P0M0=0;	P0M1=0;
	P1M0=0;	P1M1=0;
	P2M0=0;	P2M1=0;
	P3M0=0;	P3M1=0;
	AUXR=0B_0001_0001; // 1152 bytes of internal XDATA, P4.4 is a general purpose I/O
	P4M0=0;	P4M1=0;
    
    // Initialize the serial port and baud rate generator
    PCON|=0x80;
	SCON = 0x52;
    BDRCON=0;
    BRL=BRG_VAL;
    BDRCON=BRR|TBCK|RBCK|SPD;
	
	// Initialize timer 0 for ISR 'pwmcounter()' below
	TR0=0; // Stop timer 0
	TMOD=0x01; // 16-bit timer
	// Use the autoreload feature available in the AT89LP51RB2
	// WARNING: There was an error in at89lp51rd2.h that prevents the
	// autoreload feature to work.  Please download a newer at89lp51rd2.h
	// file and copy it to the crosside\call51\include folder.
	TH0=RH0=TIMER0_RELOAD_VALUE/0x100;
	TL0=RL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0 (bit 4 in TCON)
	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
	
	pwmcount=0;
	
	direction = 0;
	LCD_Init();
    
    return 0;
}

// Interrupt 1 is for timer 0.  This function is executed every time
// timer 0 overflows: 100 us.
void pwmcounter (void) interrupt 1
{
	if(++pwmcount>99){
		pwmcount=0;
		}
	if(direction){
		PWM_OUTPUT1=(pwm1>pwmcount)?1:0;
		//PWM_OUTPUT2=(pwm1>pwmcount)?0:1;
		PWM_OUTPUT2= 0;
	}
	else{
		PWM_OUTPUT2=(pwm1>pwmcount)?1:0;
		//PWM_OUTPUT1 =(pwm1>pwmcount)?0:1;
		PWM_OUTPUT1 =0;
	}
}

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


void main (void)
{	
	pwm1=50;
	while(1);
}

