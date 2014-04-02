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
	printf(CLEAR_SCREEN);
	
    return 0;
}

void main (void)
{		
	unsigned char i = 0;
	float voltage, v0, v1;
	//double frequency, period;
	while(1){
	//	printf("Getting V0...");
		v0 = Signal_Voltage(0);
	//	printf("\rGetting V1...");
		v1 = Signal_Voltage(1);
		
		printf("v0: %4.2f | v1: %4.2f \r", v0, v1);
		
		/*
		voltage = Signal_Voltage(0);
		frequency = Signal_GetFrequency();
		period = Signal_GetPeriod();
		printf("v0: %4.2f | freq: %lf | period: %lf", voltage, frequency, period);
		printf("\r");			
		*/
	}
}

