#include "General.h"
#include "AnalogInfraredProximity.h"

void Wait1s(void)
{
	_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
	    mov R2, #10
	L3:	mov R1, #248
	L2:	mov R0, #184
	L1:	djnz R0, L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, L2 ; 200us*250=0.05s
	    djnz R2, L3 ; 0.05s*20=1s
	    ret
    _endasm;
}

unsigned char _c51_external_startup(void)
{
	General_Init(); 
    return 0;
}

void main (void)
{
	while(1){		
		printf("There is %s nearby!\n", (IR_Analog_Detect() == IR_ANALOG_OBJECT ? "something":"nothing"));
		Wait1s();		
	}
}

