#include <stdio.h>
#include <at89lp51rd2.h>
#include "LCD.h"

// ~C51~ 
 
#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))

//We want timer 0 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define FREQ 10000L
#define TIMER0_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

//Output for our PWM
#define PWM_OUTPUT1	P4_3
#define PWM_OUTPUT2	P3_7

//LCD variables
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

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char pwm1;
volatile int direction;

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
		PWM_OUTPUT2= 0;
	}
	else{
		PWM_OUTPUT2=(pwm1>pwmcount)?1:0;
		PWM_OUTPUT1 = 0;
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

/*
ฐ ฑ ฒ ณ ด ต ถ ท ธ น บ ป ผ ฝ พ ฟ

ภ ม ย ร ฤ ล ฦ ว ศ ษ ส ห ฬ อ ฮ ฯ

ะ ั า ำ ิ ี ึ ื ุ ู ฺ Û Ü Ý Þ ฿
*/

void updateUI(int input){
	int k;
	unsigned char s[56];
//Print interface onto HyperTerminal
		printf( CLEAR_SCREEN );
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf("ษออออออออออออหออออออออออออป\n");
		printf("บ Speed:     บ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ Direction: บ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ            บ            บ\n");
		printf("ศออออออออออออสออออออออออออผ\n");
		printf( GOTO_YX , 2, 18);
		printf( FORE_BACK , COLOR_RED, COLOR_WHITE );
		printf("%d", input);
		printf( GOTO_YX , 4, 18);
		printf( FORE_BACK , COLOR_RED, COLOR_WHITE );
		printf("%s", (direction ? "CW ":"CCW"));
	
		//Print on LCD
		sprintf(s, "spd: %d%% %s                                     ", input, (direction ? "CW ":"CCW"));
			//generate waveform diagram on LCD
		s[42] = '|';			//2nd row of display starts at index 40
		for(k = 1; k <= 10; k++){
			s[42+k] = (pwm1 >= 10*k ? '-':' ');	//boolean expression determines if - or _
		}
		sprintf(&s[53], "|   \0");
		LCD_WriteString(s);
}

void main (void)
{
	int input, oldinput;	
	pwm1=50;
	input = 50;
	LCD_WriteString("Hi");
	while(1){
		updateUI(input);		
		
		//Get next speed value from HyperTerminal	
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 6, 3);
		printf("New Speed:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 6, 18);
		scanf("%d", &input);
		pwm1 = ((unsigned char)input);
		
		oldinput = input;
		updateUI(input);
		
		//Get next direction value from hyperterminal
		printf( GOTO_YX , 8, 28);
		printf( FORE_BACK , COLOR_GREEN, COLOR_WHITE );
		printf("(0 for CCW, 1 for CW)");
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 6, 3);
		printf("New Dir:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 6, 18);
		scanf("%d", &direction);		
		
		input = oldinput;
		
	}
}

