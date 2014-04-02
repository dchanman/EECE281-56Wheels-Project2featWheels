#include "General.h"
#include "Signal.h"
#include "Motor.h"

#define RECEIVER_THRESHOLD_LOGIC 2.0
#define RECEIVER_THRESHOLD_VOLTAGE 0.2
#define RECEIVER_THRESHOLD_PHASE 10

#define RECEIVER_INITIAL_VOLTAGE_TARGET 4.0

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

unsigned char _c51_external_startup(void)
{
	General_Init();
	Signal_Init();
	Motor_Init();
    return 0;
}

void main(){
	float voltageL, voltageR, phasediff, voltageTarget;
	double period;
	
	voltageTarget = RECEIVER_INITIAL_VOLTAGE_TARGET;

	while(1){
		printf("Getting Period...");
		period = Signal_GetPeriod();
		printf("\rGetting Voltage L");
		voltageL = Signal_Voltage(RECEIVER_CHANNEL_L);
		printf("\rGetting Voltage R");
		voltageR = Signal_Voltage(RECEIVER_CHANNEL_R);
		
		printf("\r\nPeriod: %lf, VoltageL: %f, VoltageR: %f\n\t", period, voltageL, voltageR);
		
		//if data is being transmitted, receive message
		if(voltageL < RECEIVER_THRESHOLD_LOGIC){
			//begin receiving data
			printf("Waiting for data...\n");
		}
		
		//otherwise, follow the beacon
		else{
			phasediff = Signal_GetPhase(period);
			printf("PhaseDiff: %f, ", phasediff);
			
			//handle turning first
			if(phasediff > RECEIVER_THRESHOLD_PHASE && phasediff < 180){
				Motor_TurnLeft(50);
				printf("Turning left...\n");
			}
			else if (phasediff > 180 && phasediff < 360-RECEIVER_THRESHOLD_PHASE){
				Motor_TurnRight(50);
				printf("Turning left...\n");
			}
			//then handle distance
			else{
				if (voltageL > voltageTarget+RECEIVER_THRESHOLD_VOLTAGE){
					Motor_Backward(50);
					printf("Moving backward...\n");
				}
				else if(voltageL < voltageTarget - RECEIVER_THRESHOLD_VOLTAGE){
					Motor_Forward(50);
					printf("Moving forward...\n");
				}
				else{
					Motor_Stop();
					printf("Idle...\n");
				}
			}
		}
		
		waitMillis(1000);
	}
	
	
}
