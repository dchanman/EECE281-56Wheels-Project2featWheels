#include "General.h"
#include "LCD.h"
#include "Signal.h"
#include "Joystick.h"
#include "Transmitter.h"

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
void waitMillis(unsigned char millis){
	unsigned char i;
	for(i = 0; i < millis; i++){
			_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
	    mov R2, #10
	WMS_L2:	mov R0, #184
	WMS_L1:	djnz R0, WMS_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, WMS_L2 ; 200us*5=0.001s
	    ret
    _endasm;
	}
}


void CONTROLLER_Message_Advance(){		
	unsigned char i = 0;
	
	while(Joystick_GetDirection() == JOYSTICK_DOWN){
			if(i%3 == 0){
				LCD_WriteString("Advancing.                              == ))       <[ ]");
			}
			else if(i%3 == 1){
				LCD_WriteString("Advancing..                             == ))))    <[ ] ");
			}
			else{
				LCD_WriteString("Advancing...                            == )))))) <[ ]  ");
			}
			waitMillis(500);
			i++;
	}
}

void CONTROLLER_Message_Retreat(){
	unsigned char i = 0;
	
	while(Joystick_GetDirection() == JOYSTICK_DOWN){
			if(i%3 == 0){
				LCD_WriteString("Advancing.                              == ))     <[ ]  ");
			}
			else if(i%3 == 1){
				LCD_WriteString("Advancing..                             == ))))    <[ ] ");
			}
			else{
				LCD_WriteString("Advancing...                            == ))))))   <[ ]");
			}
			waitMillis(500);
			i++;
	}
}

void CONTROLLER_Message_Spin(unsigned char seconds){
	unsigned char i;
	for(i = 0; i < seconds; i++){
		waitMillis(250);
		LCD_WriteString("Spinning receiver.                      <[ ]  ");
		waitMillis(250);
		LCD_WriteString("Spinning receiver..                      [ ]>  ");
		waitMillis(250);
		LCD_WriteString("Spinning receiver...                    <[ ]  ");
		waitMillis(250);
		LCD_WriteString("Spinning receiver....                    [ ]>  ");		
	}
}

void CONTROLLER_Message_Park(unsigned char seconds){
	unsigned char i;
	for(i = 0; i < seconds; i++){
		waitMillis(250);
		LCD_WriteString("Parallel parking.                       <[ ]    ");
		waitMillis(250);
		LCD_WriteString("Parallel parking..                       <[ ]   ");
		waitMillis(250);
		LCD_WriteString("Parallel parking...                       <[ ]  ");
		waitMillis(250);
		LCD_WriteString("Parallel parking....                       <[ ] ");		
	}
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
	while(1){
		joystick_input = Joystick_GetDirection();
		
		if(joystick_input == JOYSTICK_IDLE){
			LCD_WriteString("Transmitter ready!");			
		}
		else if(joystick_input == JOYSTICK_UP){
			Transmitter_Transmit(TRANSMITTER_CMD_RETREAT);
			CONTROLLER_Message_Retreat();
		}
		else if(joystick_input == JOYSTICK_DOWN){
			Transmitter_Transmit(TRANSMITTER_CMD_ADVANCE);
			CONTROLLER_Message_Advance();
		}
		else if(joystick_input == JOYSTICK_LEFT){
			Transmitter_Transmit(TRANSMITTER_CMD_SPIN);
			CONTROLLER_Message_Spin(3);
		}
		else if(joystick_input == JOYSTICK_RIGHT){
			Transmitter_Transmit(TRANSMITTER_CMD_PARK);
			CONTROLLER_Message_Park(5);
		}
	
	}
	
}
