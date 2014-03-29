#ifndef SIGNAL_H_
#define SIGNAL_H_ 0

#define ADC_VCC 4.7281
#define ADC_MAXVAL 1023

#define SQRT2 1.41421356237
#define VDIODER 1.018	//where is this value from?                                            
#define VDIODEL 0.387	//where is this value from?

//Functions
void Signal_Init();

void Signal_SPIWrite(unsigned char);
unsigned int Signal_GetADC(unsigned char);

float Signal_Voltage(unsigned char);
void Signal_GetPhase(float);
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