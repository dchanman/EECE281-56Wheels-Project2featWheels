/**
*Motor_Init
*
*Initializes the variables for the motor.
*Sets up Timer 1 and enables interrupts.
*/
void Motor_Init()
{
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
	
	motor_l_speed=50;
	motor_r_speed=50;
	motor_l_direction = MOTOR_FORWARD;
	motor_r_direction = MOTOR_BACKWARD;
}

/**
*pwmcounter
*
*Timer 1 interrupt function. This function is executed
*every 100us. This function causes the motors to turn
*according to the motor variables
*/
void pwmcounter (void) interrupt 3
{
	if(++pwmcount>99){
		pwmcount=0;
	}
	
	if(motor_l_direction == MOTOR_BACKWARD && motor_r_direction == MOTOR_BACKWARD && IR_DETECT == IR_SOMETHING){
		MOTOR_L_FORWARD		=	0;
		MOTOR_L_BACKWARD	= 	0;
		MOTOR_R_FORWARD		=	0;
		MOTOR_R_BACKWARD	= 	0;
		return;
	}
	
	//Operate left motor
	if(motor_l_direction == MOTOR_FORWARD){
		MOTOR_L_FORWARD		=	(motor_l_speed>pwmcount)?1:0;
		MOTOR_L_BACKWARD	= 	0;
	}
	else{
		MOTOR_L_BACKWARD	=	(motor_l_speed>pwmcount)?1:0;
		MOTOR_L_FORWARD		= 	0;
	}
	
	//Operate right motor
	if(motor_r_direction == MOTOR_FORWARD){
		MOTOR_R_FORWARD		=	(motor_r_speed>pwmcount)?1:0;
		MOTOR_R_BACKWARD	= 	0;
	}
	else{
		MOTOR_R_BACKWARD	=	(motor_r_speed>pwmcount)?1:0;
		MOTOR_R_FORWARD		= 	0;
	}
}

/**
*Motor_set
*
*Sets the designated motor to a specific
*speed and direction.
*
*@param: motor - Motor to be selected (MOTOR_LEFT or MOTOR_RIGHT)
*@param: speed - speed that the motor will move (0-100)
*@param: direction - direction the motor will move (MOTOR_FORWARD or MOTOR_BACKWARD)
*/
void Motor_Set(int motor, unsigned char speed, int direction){
	if(motor == MOTOR_LEFT){
		motor_l_speed = speed;
		motor_l_direction = direction;
	}
	else if (motor == MOTOR_RIGHT){
		motor_r_speed = speed;
		motor_r_direction = direction;
	}
}

/**
*Motor_Forward
*
*Turns both motors forward at the same speed
*@param: speed - speed the motors will move (0-100)
*/
void Motor_Forward(unsigned char speed){
	motor_l_speed = speed;
	motor_r_speed = speed;
	motor_l_direction = MOTOR_FORWARD;
	motor_r_direction = MOTOR_FORWARD;
}

/**
*Motor_Backward
*
*Turns both motors backwards at the same speed.
*
*EXTRA FUNCTIONALITY: If the IR sensor detects
*an object, this function will NOT cause the motors
*to activate.
*
*@param: speed - speed the motors will move (0-100)
*/
void Motor_Backward(unsigned char speed){
		motor_l_speed = speed;
		motor_r_speed = speed;
		motor_l_direction = MOTOR_BACKWARD;
		motor_r_direction = MOTOR_BACKWARD;
	
}


/**
*Motor_TurnRight
*
*Turns both motors in opposite directions at the same speed.
*The vehicle should remain stationary while turning right.
*@param: speed - speed the motors will move (0-100)
*/
void Motor_TurnRight(unsigned char speed){
	motor_l_speed = speed;
	motor_r_speed = speed;
	motor_r_direction = MOTOR_BACKWARD;
	motor_l_direction = MOTOR_FORWARD;
}

/**
*Motor_TurnLeft
*
*Turns both motors in opposite directions at the same speed.
*The vehicle should remain stationary while turning left.
*@param: speed - speed the motors will move (0-100)
*/
void Motor_TurnLeft(unsigned char speed){
	motor_l_speed = speed;
	motor_r_speed = speed;
	motor_l_direction = MOTOR_BACKWARD;
	motor_r_direction = MOTOR_FORWARD;
}

/**
*Motor_Stop
*
*Stops all motor movement.
*/
void Motor_Stop(){
		motor_l_speed	=	0;
		motor_r_speed	= 	0;
}