
#include "General.h"
#include "Signal.h"

void wait(void){
	_asm
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R0, #46
		shortL1: djnz R0,shortL1  ; 2 machine cycles-> 2*0.5425347us*184=49.9us
		ret
	_endasm;
}

unsigned char _c51_external_startup(void)
{
	General_Init();
	Signal_Init();    
    return 0;
}

void main (void)
{		
	unsigned char i = 0;
	while(1){
	
		printf("v0: %4.2f", Signal_Voltage(i));
		printf("\r");			
	}
}
