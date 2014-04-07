volatile int TOV;	//counter for the overflow of TO1

void Signal_TimerOverflow() interrupt 1{
	TOV ++;
}

void Signal_Init(){
	TR0=0; //Stop timer 0
	TMOD |= 0b_00000001; // Set timer 0 as 16-bit timer
	ET0 = 1;
	EA =1;
}

/**
*Signal_SPIWrite
*
*Writes a value for SPI
*/
void Signal_SPIWrite(unsigned char value){
	SPSTA&=(~SPIF); // Clear the SPIF flag in SPSTA
	SPDAT=value;
	while((SPSTA & SPIF)!=SPIF); //Wait for transmission to end
}

/**
*Signal_GetADC
*
*Reads 10 bits from the MCP3004 ADC converter
*@param: channel - the channel to be read
*@returns: the value from the ADC (0-1023)
*/
unsigned int Signal_GetADC(unsigned char channel){
	unsigned int adc;

	// initialize the SPI port to read the MCP3004 ADC attached to it.
	SPCON&=(~SPEN); // Disable SPI
	SPCON=MSTR|CPOL|CPHA|SPR1|SPR0|SSDIS;
	SPCON|=SPEN; // Enable SPI
	
	ADC_CE=0; // Activate the MCP3004 ADC.
	Signal_SPIWrite(channel|0x18);	// Send start bit, single/diff* bit, D2, D1, and D0 bits.
	for(adc=0; adc<10; adc++); // Wait for S/H to setup
	Signal_SPIWrite(0x55); // Read bits 9 down to 4
	adc=((SPDAT&0x3f)*0x100);
	Signal_SPIWrite(0x55);// Read bits 3 down to 0
	ADC_CE=1; // Deactivate the MCP3004 ADC.
	adc+=(SPDAT&0xf0); // SPDR contains the low part of the result. 
	adc>>=4;
		
	return adc;
}

/**
*Signal_Voltage
*
*Gets the voltage read by the ADC in a specified channel
*@param: channel - the channel to read
*@return:	The voltage read from the specified channel
*/
float Signal_Voltage (unsigned char channel)
{
	return ( (Signal_GetADC(channel)*4.792)/1023.0 ); // VCC=4.88V (measured)
	
	/*
	if( channel == 2)
		return( ( ((Signal_GetADC(channel)*ADC_VCC)/1023.0 ) + VDIODEL) / SQRT2 );
	else
		return( ( ((Signal_GetADC(channel)*ADC_VCC)/1023.0 ) + VDIODER) / SQRT2 );
		
		*/
}

/**
*Signal_GetPhase
*
*Prints the difference in phase between signals
*
*(Unverified function. What does P2_0 and 2_1 do?)
*@param: period - the period of the signal
*/
float Signal_GetPhase( double period )
{
	float timeDiff;
	float phaseDiff;
	
	// Time difference between reference and test
	TH0=0; TL0=0;	// Reset the timer
	TOV = 0;
	
	// Reference signal
	while(ZERO_CROSS_0==1); //Wait for the signal to be zero
	while(ZERO_CROSS_0==0); //Wait for the signal to be one
	TR0=1;	// Start timing
	// Test signal
	while(ZERO_CROSS_1==1);	//Wait for the signal to be zero
	while(ZERO_CROSS_1==0); //Wait for the signal to be one
	TR0=0;	// Stop timer 

	// Calculate time difference
	timeDiff = (TH0*256.0+TL0)*(12.0/CLK);
	printf( "Time difference = %.4fs\n\r", timeDiff );
	
	// Calculate phase difference
	phaseDiff = timeDiff / period * 360;
	if(phaseDiff < 400 )
	{

		if( timeDiff > ( period / 2 ) )
		{	
			phaseDiff = 360 - phaseDiff;	
			printf( "Phase difference = -%.1f degrees\n\n\r", phaseDiff ); 
		}
		else
			printf( "Phase difference =  %.1f degrees\n\n\r", phaseDiff ); 
	}
	
	return phaseDiff;
}

/**
*Signal_Wait1s
*
*Stalls the processor for 1 second
*@modifies: R2, R1, R0
*/
void Signal_Wait1s(void)
{
	_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
	    mov R2, #10
	SW1_L3:	mov R1, #248
	SW1_L2:	mov R0, #184
	SW1_L1:	djnz R0, SW1_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, SW1_L2 ; 200us*250=0.05s
	    djnz R2, SW1_L3 ; 0.05s*20=1s
	    ret
    _endasm;
}

/**
*Signal_WaitBitTime
*
*Stalls the processor for 20ms.
*Used to transmit at BAUDRATE 50bits/s
*@modifies: R2, R1, R0
*/
void Signal_WaitBitTime(void)
{
	_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R2, #10
	SWBT_L3:	mov R1, #100
	SWBT_L2:	mov R0, #184
	SWBT_L1:	djnz R0, SWBT_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, SWBT_L2 ; 200us*250=0.02s
	    djnz R2, SWBT_L3
	    ret
    _endasm;
}

/**
*Signal_WaitBitTimeAndHalf
*
*Stalls the processor for 30 ms
*Used by the receiver circuit to put itself 
*a half-signal period "out of phase" with the
*transmitter when receiving a signal
*@modifies: R2, R1, R0
*/
void Signal_WaitBitTimeAndHalf(void)
{
	_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R2, #15
	SWBTAH_L3:	mov R1, #100
	SWBTAH_L2:	mov R0, #184
	SWBTAH_L1:	djnz R0, SWBTAH_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, SWBTAH_L2 ; 200us*150=0.03s
	    djnz R2, SWBTAH_L3
	    ret
    _endasm;
}

void Signal_WaitHalfBitTime(void)
{
	_asm	
		;For a 22.1184MHz crystal one machine cycle 
		;takes 12/22.1184MHz=0.5425347us
		mov R2, #12
	SWHBT_L3:	mov R1, #100
	SWHBT_L2:	mov R0, #184
	SWHBT_L1:	djnz R0, SWHBT_L1 ; 2 machine cycles-> 2*0.5425347us*184=200us
	    djnz R1, SWHBT_L2 ; 200us*150=0.03s
	    djnz R2, SWHBT_L3
	    ret
    _endasm;
}

/**
*Signal_GetPeriod
*
*Gets the period of the signal
*(This function has not been verified. 
*	What does P2_0 do?)
*
*@return:	The period of the signal
/
float Signal_GetPeriod(){
	float period;
	double p2;
	
	// Measure period at P1.0 using timer 0
	TH0=0; TL0=0;	// Reset the timer
	
	while(ZERO_CROSS_0==1); //Wait for the signal to be zero	
	while(ZERO_CROSS_0==0); //Wait for the signal to be one
	
	TR0=1;	// Start timing
	
	while(ZERO_CROSS_0==1);	//Wait for the signal to be zero
	
	TR0=0;	// Stop timer 0
	
	// [TH0, TL0] is half the period in multiples of 12/CLK, so:
	period=(TH0*256.0+TL0)*(24.0/CLK);
	p2 = (TOV*65536.0) + (TH0*256.0+TL0)*(24.0/CLK);
	
	return period;
}
*/

/**
*Signal_GetPeriod
*
*Gets the period of the signal
*(This function has not been verified. 
*	What does P2_0 do?)
*
*@return:	The period of the signal
*/
double Signal_GetPeriod(){
	float period;
	double p2;
	
	// Measure period at P1.0 using timer 0
	TH0=0; TL0=0;	// Reset the timer
	TOV = 0;
	
	//while(ZERO_CROSS_0==1); //Wait for the signal to be zero	
	//while(ZERO_CROSS_0==0); //Wait for the signal to be one
	TR0=1;
	//printf("\t\tWaiting for signal to be high...\r");
	while(Signal_Voltage(SIGNAL_CHANNEL_L) >= SIGNAL_PEAK_VOLTAGE){
		if(TOV == 100){
			printf("Timeout! No period detected!\n");
			return 0;
		}
	}
	//printf("\t\tSignal went high! Now waiting for signal to be low...");
	TOV = 0;TH0 = 0; TL0 = 0;
	while(Signal_Voltage(SIGNAL_CHANNEL_L) < SIGNAL_PEAK_VOLTAGE){
		//printf("Timer: %d | %lf\r", TOV, (TOV*65536.0) + (TH0*256.0+TL0)*(24.0/CLK));
			if(TOV == 100){
			printf("Timeout! No period detected!\n");
			return 0;
		}
	}
	TOV = 0;TH0 = 0; TL0 = 0;
	//printf("\t\tSignal went high-low! Now timing period...\r");
	//TR0=1;	// Start timing
	
	while(Signal_Voltage(SIGNAL_CHANNEL_L) >= SIGNAL_PEAK_VOLTAGE);	//Wait for the signal to be zero
	while(Signal_Voltage(SIGNAL_CHANNEL_L) < SIGNAL_PEAK_VOLTAGE);
	
	printf("Success!\n");
	//while(ZERO_CROSS_0 == 1);
	
	TR0=0;	// Stop timer 0
	
	// [TH0, TL0] is half the period in multiples of 12/CLK, so:
	period=(TH0*256.0+TL0)*(24.0/CLK);
	p2 = (TOV*65536.0) + (TH0*256.0+TL0)*(24.0/CLK);
	
	return p2;
}

/**
*Signal_GetFrequency
*
*Gets the frequency of the signal. The
*frequency must be above 25Hz.
*
*(This function has not been verified. 
*	What does P2_0 do?)
*
*@returns: The frequency of the signal, or -1 if 
*			the frequency is less than 25Hz.
*
float Signal_GetFrequency(){
	float period;
	
	// Measure period at P1.0 using timer 0
	TH0=0; TL0=0;	// Reset the timer
	
	while(ZERO_CROSS_0==1); //Wait for the signal to be zero	
	while(ZERO_CROSS_0==0); //Wait for the signal to be one
	
	TR0=1;	// Start timing
	
	while(ZERO_CROSS_0==1);	//Wait for the signal to be zero
	
	TR0=0;	// Stop timer 0
	
	// [TH0, TL0] is half the period in multiples of 12/CLK, so:
	period=(TH0*256.0+TL0)*(24.0/CLK);
	
	if(TH0 != 0){
		return (1.0/period);
	}
	return -1;
}
*/

/**
*Signal_GetFrequency
*
*Gets the frequency of the signal. The
*frequency must be above 25Hz.
*
*(This function has not been verified. 
*	What does P2_0 do?)
*
*@returns: The frequency of the signal, or -1 if 
*			the frequency is less than 25Hz.
*/
double Signal_GetFrequency(){
	double period;
	
	// Measure period at P1.0 using timer 0
	TH0=0; TL0=0;	// Reset the timer
	TOV = 0;
	
	while(ZERO_CROSS_0==1); //Wait for the signal to be zero	
	while(ZERO_CROSS_0==0); //Wait for the signal to be one
	
	TR0=1;	// Start timing
	
	while(ZERO_CROSS_0==1);	//Wait for the signal to be zero
	
	TR0=0;	// Stop timer 0
	
	// [TH0, TL0] is half the period in multiples of 12/CLK, so:
	period=(TOV*65536+TH0*256.0+TL0)*(24.0/CLK);
	
	//if(TH0 != 0){
		return (1.0/period);
	//}
	//return -1;
}

