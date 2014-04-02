/**
*Transmitter_Init
*
*Initializes the variables for the transmitter.
*Sets up Timer 1 and enables interrupts.
*/
void Transmitter_Init(){
	// Initialize timer 1 for ISR 'pwmcounter()' below
	TR1=0; // Stop timer 1
	TMOD |= 0x10; // 16-bit timer
	// Use the autoreload feature available in the AT89LP51RB2
	// WARNING: There was an error in at89lp51rd2.h that prevents the
	// autoreload feature to work.  Please download a newer at89lp51rd2.h
	// file and copy it to the crosside\call51\include folder.
	TH1=RH1=TIMER1_RELOAD_VALUE/0x100;
	TL1=RL1=TIMER1_RELOAD_VALUE%0x100;
	TR1=1; // Start timer 1 (bit 4 in TCON)
	ET1=1; // Enable timer 1 interrupt
	EA=1;  // Enable global interrupts
	
	pwmcount=0;
}

// Interrupt 3 is for timer 1.  This function is executed every time
// timer 1 overflows: 100 us.
void pwmcounter (void) interrupt 3
{
	if(++pwmcount>1) pwmcount=0;
	P1_0=(TRANSMITTER_PWM>pwmcount)?1:0;
	P1_1=(TRANSMITTER_PWM>pwmcount)?0:1;
}

/**
*Transmitter_Start
*
*Turns on the transmitter
*@modifies: TR1
*/
void Transmitter_Start(){
	pwmcount = 0;
	TR1 = 1;
}

/**
*Transmitter_Stop
*
*Turns off the transmitter
*@modifies: TR1
*/
void Transmitter_Stop(){
	TR1 = 0;
}

/**
*Transmitter_Transmit
*
*Sends an unsigned char as an
*electromagnetic signal. The signal
*is sent LSB to MSB, so (0011) would be sent
*as (1100). Requires 220ms to finish.
*
*@param: message - 8 bit message to send
*@modifies: TR1 - will be toggled during entire function call
*/
void Transmitter_Transmit(unsigned char message){
	unsigned char k;
	
		//printf("sending...");
		
	//Send start bit
	Transmitter_Stop();
	//printf("-%c-", TR1?'1':'0');
	Signal_WaitBitTime();

	
	//Send data
	for(k=0; k < 8; k++){
		TR1 = message&(0x01<<k)?1:0;
	//	printf("%c", TR1?'1':'0');
		Signal_WaitBitTime();
	}
	
	
	//Send stop bits
	Transmitter_Start();
	//printf("-%c-\n", TR1?'1':'0');
	Signal_WaitBitTime();
	Signal_WaitBitTime();	
}