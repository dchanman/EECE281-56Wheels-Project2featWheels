#include "General.h"
#include "Signal.h"
#include "Joystick.h"

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

	enum Joystick_Direction dir;
	while(1){
		
		dir = Joystick_GetDirection();
		
		if(dir == JOYSTICK_IDLE){
			printf("Idle   ");
		}
		else if(dir == JOYSTICK_UP){
			printf("Up     ");
		}
		else if(dir == JOYSTICK_DOWN){
			printf("Down     ");
		}
		else if(dir == JOYSTICK_LEFT){
			printf("Left     ");
		}
		else if(dir == JOYSTICK_RIGHT){
			printf("Right     ");
		}
		else{
			printf("ERROR");
		}
		printf("\r");			
	}
}

