#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

//We want timer 1 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define FREQ 30150L
#define TIMER1_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

#define TRANSMITTER_PWM 1

//Transmitter messages:
#define TRANSMITTER_CMD_ADVANCE		0b11000000
#define TRANSMITTER_CMD_RETREAT		0b00110000
#define TRANSMITTER_CMD_SPIN		0b00001100
#define TRANSMITTER_CMD_PARK		0b00000011

//These variables are used in the ISR
volatile unsigned char pwmcount;

//Functions for the motor
void Transmitter_Init();
void Transmitter_Start();
void Transmitter_Stop();
void Transmitter_Transmit(unsigned char message);

#include "Transmitter.c"

#endif