#include "General.h"
#include "Signal.h"
#include "Motor.h"
#include <math.h>

//If the peak voltage drops below this value, it is a logic 0
#define RECEIVER_THRESHOLD_LOGIC 0.0040

//Threshold of voltage difference - used to determine the location of the transmitter
#define RECEIVER_THRESHOLD_VOLTAGE 0

//Sensitivity of controls - how quickly the car advances/retreats on command
#define RECEIVER_SENSITIVITY 2
#define RECEIVER_TURN_SENSITIVITY 4

//Initial voltage target for distance
#define RECEIVER_INITIAL_DISTANCE 35

//Noise filteration
#define RECEIVER_NOISE 0.0030

//Voltage polynomial constants

#define coefR5	0
#define coefR4	0
#define coefL3 -9.5928
#define coefL2 -42.0957
#define coefL1 -60.2518
#define coefLC 59.0742

#define coefL5	0
#define coefL4	0
#define coefR3 -5.4185
#define coefR2 28.9661
#define coefR1 -52.4874
#define coefRC 62.9946



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
unsigned char Receiver_Receive(float threshold){
	unsigned char k;
	unsigned char msg = 0;
	float val;
	printf("Message: ");
	Signal_WaitHalfBitTime();
	for(k=0; k<8; k++){
		val = Signal_Voltage(SIGNAL_CHANNEL_L);
		msg |= (val > threshold)?(0x01<<k):0x00;
		Signal_WaitBitTime();
		printf("%s", val>threshold?"1":"0");
			
	}
	printf("\n");
	printf("The message received was %b\n", msg);
	Signal_WaitBitTimeAndHalf();
	return msg;
}

void Receiver_Spin(){
	Motor_TurnLeft(100);
	waitMillis(1625);
	Motor_Stop();
}

void Receiver_Park(){
	Motor_TurnLeft(70);
	waitMillis(500);
	Motor_Forward(70);
	waitMillis(2000);
	Motor_TurnRight(70);
	waitMillis(500);
	Motor_Stop();
}

float Receiver_GetDistanceR(float voltage){
	return (coefR5*voltage*voltage*voltage*voltage*voltage
	+coefR4*voltage*voltage*voltage*voltage
	+coefR3*voltage*voltage*voltage
		+coefR2*voltage*voltage
			+coefR1*voltage
				+coefRC);
}

float Receiver_GetDistanceL(float voltage){
	return (coefR5*voltage*voltage*voltage*voltage*voltage
	+coefR4*voltage*voltage*voltage*voltage	
	+coefL3*voltage*voltage*voltage
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
	float voltageL, voltageR, distanceL, distanceR, filterL, filterR, filterL2, filterR2, distanceAverage;
	unsigned char distance;
	unsigned char cmd;
	int count =0;
			
	//initialize voltageTarget with the default value
	distance = RECEIVER_INITIAL_DISTANCE;
	filterL2 = 0;
	filterR2 = 0;
	filterL = 0;
	filterR = 0;
	voltageL = 0;
	voltageR = 0;
	distanceL = 0;
	distanceR = 0;
	

	
	/*

	while(1){	
		voltageL = Signal_Voltage(SIGNAL_CHANNEL_L);
		voltageR = Signal_Voltage(SIGNAL_CHANNEL_R);
	//	distanceL = Receiver_GetDistanceL(voltageL);
	//	distanceR = Receiver_GetDistanceR(voltageR);
		printf("VoltageL: %f | VoltageR: %f \n", voltageL, voltageR);
	//	printf("\tDistanceL: %f | DistanceR: %f \n", distanceL, distanceR); 
		count++;
	}
*/

	
	while(1){
		count++;
		if(count == 4){
			printf(CLEAR_SCREEN);
			printf("filterL2:%f filterL:%f voltageL:%f\n", filterL2, filterL, voltageL);
			printf("filterR2:%f filterR:%f voltageR:%f\n", filterR2, filterR, voltageR);
		/*
		*Apply filters
		*/
		if((filterL2 > filterL + RECEIVER_NOISE) && (filterL > voltageL + RECEIVER_NOISE) &&
			(filterR2 > filterR + RECEIVER_NOISE) && (filterR > voltageR + RECEIVER_NOISE)){
			
				printf("Receiving data...\n");
				Motor_Stop();
				cmd = Receiver_Receive(voltageL);
					
				//Process the command
				if(cmd == 0b00111111){	//Advance
					distance = ((distance > 30)?distance-5:25);
					printf("Advance: New distance set to %d", distance);
				}
				else if(cmd == 0b00000110){ 
					printf("Parking...\n");
					Receiver_Park();
				}
				else if(cmd == 0b00000000){//Retreat	
					distance = ((distance < 60)?distance+5:60);
					printf("Ret				reat: New distance set to %d", distance);
				}
				else if(cmd== 0b00011011){
				 //Spin
					printf("Spinning...\n");
					Motor_Stop();
					Receiver_Spin();
				}			
				else{
					printf("Invalid command %b\n", cmd);
				}
				//waitMillis(5000);
				count =0;
				filterL2 = 0;
				filterR2 = 0;
				filterL = 0;
				filterR = 0;
				continue; //restart the loop			
			}
			
			filterL2 = filterL;
			filterR2 = filterR;
			filterL = voltageL;
			filterR = voltageR;	
			if(count >= 4){count = 0;}		
		}
		/*
		*Update the values we are detecting
		*/
		//Motor_Stop();
		filterL2 = filterL;
		filterR2 = filterR;
		filterL = voltageL;
		filterR = voltageR;
		voltageL = Signal_Voltage(SIGNAL_CHANNEL_L);	//SIGNAL_CHANNEL_L is defined in General.h
		voltageR = Signal_Voltage(SIGNAL_CHANNEL_R);	//SIGNAL_CHANNEL_R is defined in General.h
;			
				
		/*
		*If the voltage is too high, we are too close to the controller. Back up.
		*/
		if(voltageL > 2.787136 || voltageR > 2.787136){
			printf("Too close!\n");
			Motor_Backward(80);
			continue;
		}		
		distanceL = Receiver_GetDistanceL(voltageL);
		distanceR = Receiver_GetDistanceR(voltageR);
		distanceAverage = (distanceL + distanceR)/2.0;		
		printf("L:%3.2f | R: %3.2f | VL:%f | VR: %f | cnt: %d | ", distanceL, distanceR, voltageL, voltageR);
		
		//handle turning first
		if(distanceL - distanceR > RECEIVER_TURN_SENSITIVITY){
			Motor_TurnLeft(20);
			printf("Turning left...\n");

		}
		else if (distanceR - distanceL > RECEIVER_TURN_SENSITIVITY*0.75){
			Motor_TurnRight(20);
			printf("Turning right...\n");
		}
		//then handle distance, using voltageL (voltageL and voltageR should be 
		//close to equal anyways, so it doesn't matter much
		else{
			
			if (distanceAverage > distance + RECEIVER_SENSITIVITY){
				Motor_Forward(40);
				printf("Moving forward...\n");
			}
			else if(distanceAverage < distance - RECEIVER_SENSITIVITY){
				Motor_Backward(40);
				printf("Moving backward...\n");
			}
			else{
				Motor_Stop();
				printf("Idle...\n");
			}
		}
	}	
}




