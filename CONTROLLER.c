#include "General.h"
#include "LCD.h"
#include "Signal.h"
#include "Joystick.h"
#include "Transmitter.h"

#define ANIMATION_TIME 500

/**
*debounce
*
*Stalls the processor for 50us to debounce button inputs
*/
void debounce(void){
	_asm
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R0, #46
		debounceL1: djnz R0,debounceL1  ; 2 machine cycles-> 2*0.5425347us*184=49.9us
		ret
	_endasm;
}

/**
*waitMillis
*
*Stalls the processor for a defined
*number of milliseconds
*
*@param: millis - the amount of time in ms the processor waits
*/
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


void CONTROLLER_Message_Advance(){		
	unsigned char i = 0;
	
	while(Joystick_GetDirection() == JOYSTICK_DOWN){
			if(i%3 == 0){
				LCD_Clear();
				LCD_WriteString("Advancing.                              == ))       <[ ]");
			}
			else if(i%3 == 1){
				LCD_Clear();
				LCD_WriteString("Advancing..                             == ))))    <[ ] ");
			}
			else{
				LCD_Clear();
				LCD_WriteString("Advancing...                            == )))))) <[ ]  ");
			}
			waitMillis(ANIMATION_TIME);
			i++;
	}
}

void CONTROLLER_Message_Retreat(){
	unsigned char i = 0;
	
	while(Joystick_GetDirection() == JOYSTICK_UP){
			if(i%3 == 0){
				LCD_Clear();
				LCD_WriteString("Retreating.                             == ))     <[ ]  ");
			}
			else if(i%3 == 1){
				LCD_Clear();
				LCD_WriteString("Retreating..                            == ))))    <[ ] ");
			}
			else{
				LCD_Clear();
				LCD_WriteString("Retreating...                           == ))))))   <[ ]");
			}
			waitMillis(ANIMATION_TIME);
			i++;
	}
}

void CONTROLLER_Message_Spin(unsigned char seconds){
	unsigned char i;
	for(i = 0; i < seconds*2; i++){
		if(i%2==0){
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Spinning                                      <[ ]        ");
		}
		else{
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Spinning                                       [ ]>       ");
		}
	}
}

void CONTROLLER_Message_Park(unsigned char seconds){
	unsigned char i;
	for(i = 0; i < seconds*2; i++){
		if(i%4==0){
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Parallel park                           <[ ]              ");		
		}
		else if (i%4 == 1){
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Parallel park                            <[ ]             ");		
		}
		else if(i%4 == 2){
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Parallel park                             <[ ]            ");
		}
		else if(i%4 == 3){
			waitMillis(ANIMATION_TIME);
			LCD_Clear();
			LCD_WriteString("Parallel park                              <[ ]           ");	
		}	
	}
}

void CONTROLLER_Message_Standby(){
	LCD_Clear();
	LCD_WriteString("Transmitter                             Ready!                     ");	
}

unsigned char _c51_external_startup(void)
{
	General_Init();
	LCD_Init();
	Signal_Init();
	Transmitter_Init();    
    return 0;
}

void main(){
	
	enum Joystick_Direction joystick_input;
	
	Transmitter_Start();	
	CONTROLLER_Message_Standby();
	while(1){
		joystick_input = Joystick_GetDirection();
		
		if(joystick_input == JOYSTICK_IDLE){
		
		}
		else if(joystick_input == JOYSTICK_UP){
			Transmitter_Transmit(TRANSMITTER_CMD_RETREAT);
			CONTROLLER_Message_Retreat();
			CONTROLLER_Message_Standby();
			Transmitter_Transmit(TRANSMITTER_CMD_IDLE);
		}
		else if(joystick_input == JOYSTICK_DOWN){
			Transmitter_Transmit(TRANSMITTER_CMD_ADVANCE);
			CONTROLLER_Message_Advance();
			CONTROLLER_Message_Standby();
			Transmitter_Transmit(TRANSMITTER_CMD_IDLE);
		}
		else if(joystick_input == JOYSTICK_LEFT){
			Transmitter_Transmit(TRANSMITTER_CMD_SPIN);
			CONTROLLER_Message_Spin(3);
			CONTROLLER_Message_Standby();
		}
		else if(joystick_input == JOYSTICK_RIGHT){
			Transmitter_Transmit(TRANSMITTER_CMD_PARK);
			CONTROLLER_Message_Park(5);
			CONTROLLER_Message_Standby();
		}
	
	}
	
}
