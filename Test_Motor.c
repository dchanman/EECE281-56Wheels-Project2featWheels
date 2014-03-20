#include "General.h"
#include "Motor.h"

unsigned char _c51_external_startup(void)
{
	Motor_Init();    
    return 0;
}

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
	int input;
		
	while(1){
		updateUI();		
		
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
		
	}
}

