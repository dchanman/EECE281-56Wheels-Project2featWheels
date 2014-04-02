#ifndef SIGNAL_H_
#define SIGNAL_H_ 0

#define ADC_VCC 4.7281
#define ADC_MAXVAL 1023

#define SQRT2 1.41421356237
#define VDIODER 1.018	//where is this value from?                                            
#define VDIODEL 0.387	//where is this value from?

#define SIGNAL_PEAK_VOLTAGE 2.0	//voltage above this signals a "peak"

//Transmitter messages:
#define TRANSMITTER_CMD_ADVANCE		0b11000000
#define TRANSMITTER_CMD_RETREAT		0b00110000
#define TRANSMITTER_CMD_SPIN		0b00001100
#define TRANSMITTER_CMD_PARK		0b00000011
#define TRANSMITTER_CMD_IDLE		0b00000000

//Functions
void Signal_Init();

void Signal_SPIWrite(unsigned char);
unsigned int Signal_GetADC(unsigned char);

float Signal_Voltage(unsigned char);
float Signal_GetPhase(double);
double Signal_GetPeriod();
double Signal_GetFrequency();

void Signal_Wait1s();
void Signal_WaitBitTime();
void Signal_WaitBitTimeAndHalf();


//         MCP3004 ADC
//---------------------------
// MISO  - pin 10
// SCK   - pin 11
// MOSI  - pin 9
// CE*   - pin 8
// 4.8V  - pins 13, 14  (This is LP51B's VCC)
// 0V    - pins 7, 12   (This is LP51B's GND)
// CH0   - pin 1
// CH1   - pin 2
// CH2   - pin 3
// CH3   - pin 4

#include "Signal.c"

#endif