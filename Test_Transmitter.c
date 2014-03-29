#include "General.h"
#include "Signal.h"
#include "Transmitter.h"

#define SW	P4_4

void debounce(void){
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
	Transmitter_Init();    
    return 0;
}
void main (void)
{		
	
	while(1){
		printf(CLEAR_SCREEN);
		printf("Ready to transmit!\n");		
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting 0b01010101...\n");
		Transmitter_Transmit(0b01010101);
		printf("Transmitted 0b01010101!\n\n");
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting 0b10101010...\n");
		Transmitter_Transmit(0b10101010);
		printf("Transmitted 0b10101010!\n\n");
		
		/*
		#define TRANSMITTER_CMD_ADVANCE		0b11000000
		#define TRANSMITTER_CMD_RETREAT		0b00110000
		#define TRANSMITTER_CMD_SPIN		0b00001100
		#define TRANSMITTER_CMD_PARK		0b00000011
		*/
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting ADVANCE command... (0b11000000)\n");
		Transmitter_Transmit(TRANSMITTER_CMD_ADVANCE);
		printf("Transmitted ADVANCE!\n\n");
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting RETREAT command... (0b00110000)\n");
		Transmitter_Transmit(TRANSMITTER_CMD_RETREAT);
		printf("Transmitted RETREAT!\n\n");
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting SPIN command...(0b00001100)\n");
		Transmitter_Transmit(TRANSMITTER_CMD_SPIN);
		printf("Transmitted SPIN!\n\n");
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		printf("Transmitting PARK command...(0b00000011)\n");
		Transmitter_Transmit(TRANSMITTER_CMD_PARK);
		printf("Transmitted PARK!\n\n");
		
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
	}
	
}

