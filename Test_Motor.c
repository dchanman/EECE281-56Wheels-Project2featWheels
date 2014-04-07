
#include "General.h"
#include "Motor.h"

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
	Motor_Init();    
    return 0;
}

/**
*Prints the interface to the screen
*
*DOES NOT WORK YET
*/
void updateUI(){
//Print interface onto HyperTerminal
		printf( CLEAR_SCREEN );
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf("ษออออออออออออหออออออออออออป\n");
		printf("บ Speed L    บ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ Speed R    บ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ Direction Lบ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ Direction Rบ            บ\n");
		printf("ฬออออออออออออฮออออออออออออน\n");
		printf("บ            บ            บ\n");
		printf("ศออออออออออออสออออออออออออผ\n");
		printf( GOTO_YX , 2, 18);
		printf( FORE_BACK , COLOR_RED, COLOR_WHITE );
		printf("%d", motor_l_speed);
		printf( GOTO_YX , 4, 18);
		printf("%d", motor_r_speed);
		printf( GOTO_YX , 6, 18);
		printf("%s", (motor_l_direction ? "Fwd ":"Rev"));
		printf( GOTO_YX , 8, 18);
		printf("%s", (motor_r_direction ? "Fwd ":"Rev"));	
}

void main (void)
{		
	while(1){
		printf( CLEAR_SCREEN);
	
		Motor_Set(MOTOR_LEFT, 0, MOTOR_FORWARD);
		Motor_Set(MOTOR_RIGHT, 0, MOTOR_FORWARD);
		printf("Nothing is moving (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Set(MOTOR_LEFT, 100, MOTOR_FORWARD);
		Motor_Set(MOTOR_RIGHT, 0, MOTOR_FORWARD);
		printf("left motor moving forward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Set(MOTOR_LEFT, 100, MOTOR_BACKWARD);
		Motor_Set(MOTOR_RIGHT, 0, MOTOR_FORWARD);		
		printf("left motor moving backward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
	
		Motor_Set(MOTOR_LEFT, 0, MOTOR_FORWARD);
		Motor_Set(MOTOR_RIGHT, 100, MOTOR_FORWARD);
		printf("right motor moving forward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Set(MOTOR_LEFT, 0, MOTOR_FORWARD);
		Motor_Set(MOTOR_RIGHT, 100, MOTOR_BACKWARD);
		printf("right motor moving backward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Set(MOTOR_LEFT, 50, MOTOR_FORWARD);
		Motor_Set(MOTOR_RIGHT, 50, MOTOR_BACKWARD);		
		printf("left forward, right backward at 50 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Set(MOTOR_RIGHT, 50, MOTOR_FORWARD);
		Motor_Set(MOTOR_LEFT, 50, MOTOR_BACKWARD);		
		printf("left backward, right forward at 50 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Forward(25);	
		printf("both forward at 25 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Forward(50);	
		printf("both forward at 50 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Forward(75);	
		printf("both forward at 75 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Forward(100);	
		printf("both forward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Backward(25);	
		printf("both backward at 25 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Backward(50);
		printf("both backward at 50 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();

		Motor_Backward(75);	
		printf("both backward at 75 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		Motor_Backward(100);	
		printf("both backward at 100 speed (Enter anything please) \n");
		while(SW == 0);
		debounce();
		while(SW == 1);
		debounce();
		
		/*
		
		//Get next speed value from HyperTerminal	
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 10, 3);
		printf("New Speed L:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 10, 18);
		scanf("%d", &input);
		motor_l_direction = ((unsigned char)input);
		
		updateUI();
		
		//Get next speed value from HyperTerminal	
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 10, 3);
		printf("New Speed R:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 10, 18);
		scanf("%d", &input);
		motor_r_direction = ((unsigned char)input);
		
		updateUI();
		
		//Get next direction value from hyperterminal
		printf( GOTO_YX , 10, 28);
		printf( FORE_BACK , COLOR_GREEN, COLOR_WHITE );
		printf("(1 for forward, 0 for backward)");
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 10, 3);
		printf("New Dir L:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 10, 18);
		scanf("%d", &input);				
		motor_l_direction = input;
		
		//Get next direction value from hyperterminal
		printf( GOTO_YX , 10, 28);
		printf( FORE_BACK , COLOR_GREEN, COLOR_WHITE );
		printf("(1 for forward, 0 for backward)");
		printf( FORE_BACK , COLOR_BLACK, COLOR_WHITE );
		printf( GOTO_YX , 10, 3);
		printf("New Dir L:");
		printf( FORE_BACK , COLOR_BLUE, COLOR_WHITE );
		printf( GOTO_YX , 10, 18);
		scanf("%d", &input);				
		motor_l_direction = input;
		*/
		
	}
}

