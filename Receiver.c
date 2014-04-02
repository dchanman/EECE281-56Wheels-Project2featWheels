#include "General.h"
#include "Signal.h"
#include "Motor.h"

//If the peak voltage drops below this value, it is a logic 0
#define RECEIVER_THRESHOLD_LOGIC 1.5

//Threshold of voltage difference - used to determine the location of the transmitter
#define RECEIVER_THRESHOLD_VOLTAGE 0.01

//Sensitivity of controls - how quickly the car advances/retreats on command
#define RECEIVER_SENSITIVITY 0.02

//Initial voltage target for distance
#define RECEIVER_INITIAL_VOLTAGE_TARGET 2.8400

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

/**
*Receiver_Receive
*
*Receives an unsigned char from
*an electromagnetic signal. The signal
*is assumed to be sent LSB to MSB, so
*an incoming signal (1100) will be interpreted
*as (0011)
*
*@return:	The received electromagnetic signal
*/
unsigned char Receiver_Receive(){
	unsigned char k;
	unsigned char msg = 0;
	Signal_WaitBitTimeAndHalf();
	for(k=0; k<8; k++){
		if (Signal_Voltage(SIGNAL_CHANNEL_L) > RECEIVER_THRESHOLD_LOGIC){
			msg |= (0x01 <<k);
		}
		Signal_WaitBitTime();	
	}
	printf("The message received was %b\n", msg);
	return msg;
}

void Receiver_Spin(){
	Motor_TurnLeft(100);
	waitMillis(200);
	while(Signal_Voltage(SIGNAL_CHANNEL_R) - Signal_Voltage(SIGNAL_CHANNEL_L) > RECEIVER_THRESHOLD_VOLTAGE);
	waitMillis(200);
	while(Signal_Voltage(SIGNAL_CHANNEL_L) - Signal_Voltage(SIGNAL_CHANNEL_R) > RECEIVER_THRESHOLD_VOLTAGE);
	Motor_Stop();
	waitMillis(500);
}

unsigned char _c51_external_startup(void)
{
	General_Init();
	Signal_Init();
	Motor_Init();
    return 0;
}

void main(){
	float voltageL, voltageR, voltageTarget;
	unsigned char cmd;
	unsigned char advanceFlag, retreatFlag;
			
	//initialize voltageTarget with the default value
	voltageTarget = RECEIVER_INITIAL_VOLTAGE_TARGET;
	//initialize flags
	advanceFlag = 0; retreatFlag = 0;

	while(1){
		printf("Getting Voltage L     ");
		voltageL = Signal_Voltage(SIGNAL_CHANNEL_L);	//SIGNAL_CHANNEL_L is defined in General.h
		printf("\rGetting Voltage R     ");
		voltageR = Signal_Voltage(SIGNAL_CHANNEL_R);	//SIGNAL_CHANNEL_R is defined in General.h
		
		printf("\rVoltageL: %f, VoltageR: %f\n\t", voltageL, voltageR);
		
		//if data is being transmitted, receive message
		if(voltageL < RECEIVER_THRESHOLD_LOGIC){
			printf("Receiving data...\n");
			cmd = Receiver_Receive();
			
			//Process the command
			if(cmd == TRANSMITTER_CMD_ADVANCE){
				advanceFlag = 1;
			}
			else if(cmd == TRANSMITTER_CMD_RETREAT){	
				advanceFlag = 1;
			}
			else if(cmd == TRANSMITTER_CMD_SPIN){
				printf("Spinning...\n");
				Receiver_Spin();
			}
			else if(cmd == TRANSMITTER_CMD_PARK){
				printf("Parking...\n");
				//not yet implemented
			}			
			else if (cmd == TRANSMITTER_CMD_IDLE){
				printf("Idle...\n");
				advanceFlag = 0;
				retreatFlag = 0;
			}
			else{
				printf("Invalid command %b\n", cmd);
			}
			continue; //restart the loop
		}
		
		//modify distances if flags are set
		if(advanceFlag){
			voltageTarget+=RECEIVER_SENSITIVITY;
			printf("Advancing... voltageTarget:%f\n", voltageTarget);
		}
		else if(retreatFlag){			
			voltageTarget-=RECEIVER_SENSITIVITY;
			printf("Retreating... voltageTarget:%f\n", voltageTarget);
		}
		
		//after processing the message, follow the beacon
	
		//handle turning first
		if(voltageL - voltageR > RECEIVER_THRESHOLD_VOLTAGE){
			Motor_TurnLeft(50);
			printf("Turning left...\n");
		}
		else if (voltageR - voltageL > RECEIVER_THRESHOLD_VOLTAGE){
			Motor_TurnRight(50);
			printf("Turning right...\n");
		}
		//then handle distance, using voltageL (voltageL and voltageR should be 
		//close to equal anyways, so it doesn't matter much
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
		Signal_WaitBitTime();	//we cannot wait longer than BitTime
								//otherwise we risk missing the Idle command
	}
	
	
}
