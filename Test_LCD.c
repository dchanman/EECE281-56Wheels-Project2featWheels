#include <stdio.h>
#include <at89lp51rd2.h>
#include "LCD.h"
//#include "LCD.c"

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))


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
	
	
	printf("hi\n");
	
	LCD_Init();
	
	printf("ho\n");
    
    return 0;
}

void main(){
	int k = 0;
	int count = 0;
	unsigned char buffer[56];
	unsigned char *row;
	
	while(1){
		LCD_Clear();
		row = &buffer[LCD_ROW1];
		sprintf(row , "%d                                       ", count);
		row = &buffer[LCD_ROW2];
		sprintf(row, "0123456789ABCDEF");
		
		LCD_WriteString(buffer);
		for(k = 0; k < 1000; k++){
			LCD_LongDelay();
			
		}
		count++;
	}
}