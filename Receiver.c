#include "General.h"
#include "Signal.h"
#include "Motor.h"
#include <math.h>

//If the peak voltage drops below this value, it is a logic 0
#define RECEIVER_THRESHOLD_LOGIC 0.020

//Threshold of voltage difference - used to determine the location of the transmitter
#define RECEIVER_THRESHOLD_VOLTAGE 0

//Sensitivity of controls - how quickly the car advances/retreats on command
#define RECEIVER_SENSITIVITY 1
#define RECEIVER_TURN_SENSITIVITY 1

//Initial voltage target for distance
#define RECEIVER_INITIAL_DISTANCE 40

//Voltage polynomial constants
/*old
#define coefL3 -19.5948
#define coefL2 62.9132
#define coefL1 -6.1026
#define coefLC 58.2774

#define coefR3 -0.00018971355
#define coefR2 0.029084943809
#define coefR1 -1.48107822777
#define coefRC 25.11287711904
*/
#define coefL3	-3.6076
#define coefL2   19.4649
#define coefL1  -36.7559
#define coefLC   59.5052

#define coefR3   -8.0475
#define coefR2   34.6667
#define coefR1  -48.6592
#define coefRC   57.9873




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
/*
float Receiver_GetTargetVR(unsigned char distance){
	return (coefR3*distance*distance*distance 
		+coefR2*distance*distance
			+coefR1*distance
				+coefRC);

}

float Receiver_GetTargetVL(unsigned char distance){
	return (coefL3*distance*distance*distance 
		+coefRL*distance*distance
			+coefL1*distance
				+coefLC);
}
*/

float Receiver_GetDistanceR(float voltage){
	return (coefR3*voltage*voltage*voltage
		+coefR2*voltage*voltage
			+coefR1*voltage
				+coefRC);
}

float Receiver_GetDistanceL(float voltage){
	return (coefL3*voltage*voltage*voltage
		+coefL2*voltage*voltage
			+coefL1*voltage
				+coefLC);
}

unsigned char _c51_external_startup(void)
{
	General_Init();
	Signal_Init();
	Motor_Init();
    return 0;
}

void main(){
	float voltageL, voltageR, distanceL, distanceR, filterL, filterR;
	unsigned char distance;
	unsigned char cmd;
	int count =0;
			
	//initialize voltageTarget with the default value
	distance = RECEIVER_INITIAL_DISTANCE;
	filterL = 0;
	filterR = 0;
	
	
/*

	while(1){	
		voltageL = Signal_Voltage(SIGNAL_CHANNEL_L);
		voltageR = Signal_Voltage(SIGNAL_CHANNEL_R);
		distanceL = Receiver_GetDistanceL(voltageL);
		distanceR = Receiver_GetDistanceR(voltageR);
		printf("VoltageL: %f | VoltageR: %f \n", voltageL, voltageR);
		printf("\tDistanceL: %f | DistanceR: %f \n", distanceL, distanceR); 
		count++;
	}

*/
	
	while(1){
		/*
		*Update the values we are detecting
		*/
		voltageL = Signal_Voltage(SIGNAL_CHANNEL_L);	//SIGNAL_CHANNEL_L is defined in General.h
		voltageR = Signal_Voltage(SIGNAL_CHANNEL_R);	//SIGNAL_CHANNEL_R is defined in General.h
		//printf("\rVoltageL: %f, VoltageR: %f\n\t", voltageL, voltageR);
		distanceL = Receiver_GetDistanceL(voltageL);
		distanceR = Receiver_GetDistanceR(voltageR);		
		printf("L:%f | R: %f | VL:%f | VR: %f | ", distanceL, distanceR, voltageL, voltageR);
		
		/*
		*Apply filter on the most recently read value
		*/
		if(abs(filterL - distanceL) > RECEIVER_TURN_SENSITIVITY){
			filterL = distanceL;
			filterR = distanceR;
			printf("Filtered!\n");
			continue;
		}
		else if(abs(filterR - distanceR) > RECEIVER_TURN_SENSITIVITY){
			filterL = distanceL;
			filterR = distanceR;
			printf("Filtered!\n");
			continue;
		}
		
		filterL = distanceL;
		filterR = distanceR;
		
		/*
		*If the voltage is too high, we are too close to the controller. Back up.
		*/
		if(voltageL > 2.8059 || voltageR > 2.3849){
			printf("Too close!\n");
			Motor_Backward(50);
		}
		
		//if data is being transmitted, receive message
		if(voltageL < RECEIVER_THRESHOLD_LOGIC){
			printf("Receiving data...\n");
			cmd = Receiver_Receive();
			
			//Process the command
			if(cmd == TRANSMITTER_CMD_ADVANCE){
				distance = ((distance > 25)?distance-5:25);
				printf("New distance set to %d", distance);
			}
			else if(cmd == TRANSMITTER_CMD_RETREAT){	
				distance = ((distance < 60)?distance+5:60);
				printf("New distance set to %d", distance);
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
			}
			else{
				printf("Invalid command %b\n", cmd);
			}
			continue; //restart the loop
		}

		//after processing the message, follow the beacon
		
	
		//handle turning first
		if(distanceL - distanceR > RECEIVER_TURN_SENSITIVITY){
			Motor_TurnLeft(50);
			printf("Turning left...\n");
		}
		else if (distanceR - distanceL > RECEIVER_TURN_SENSITIVITY){
			Motor_TurnRight(50);
			printf("Turning right...\n");
		}
		//then handle distance, using voltageL (voltageL and voltageR should be 
		//close to equal anyways, so it doesn't matter much
		else{
			if (distanceL > distance + RECEIVER_SENSITIVITY){
				Motor_Forward(50);
				printf("Moving forward...\n");
			}
			else if(distanceL < distance - RECEIVER_SENSITIVITY){
				Motor_Backward(50);
				printf("Moving backward...\n");
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