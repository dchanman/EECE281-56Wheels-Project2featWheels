
#include "General.h"
#include "Motor.h"

#define SW	P4_4

void waitMillis(int millis){
	int i;
	for(i = 0; i < millis/2; i++){
			_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
	    mov R1, #5
	WMS_L2:	mov R0, #184
	WMS_L1:	djnz R0, WMS_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, WMS_L2 ; 200us*5=0.001s
    _endasm;
	}
}

unsigned char _c51_external_startup(void)
{
	General_Init();
	Motor_Init();    
    return 0;
}



void main (void)
{		
/*
	Motor_TurnLeft(70);
	waitMillis(500);
	Motor_Forward(70);
	waitMillis(2000);
	Motor_TurnRight(70);
	waitMillis(500);
	Motor_Stop();
	*/
	Motor_TurnLeft(100);
	waitMillis(1625);
	Motor_Stop();

}

