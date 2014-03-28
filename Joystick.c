/**
*Joystick_Direction
*
*Returns a direction value from the joystick,
*prioritizing input from the Y-axis over the X-axis
*
*/
enum Joystick_Direction Joystick_GetDirection(){
	unsigned int Vx, Vy;	
		
	Vy = Signal_GetADC(JOYSTICK_CHANNEL_Y);
	
	if(Vy > (ADC_MAXVAL - JOYSTICK_SENSITIVITY)){
		return JOYSTICK_DOWN;
	}
	else if(Vy < JOYSTICK_SENSITIVITY){
		return JOYSTICK_UP;
	}
	
	Vx = Signal_GetADC(JOYSTICK_CHANNEL_X);
	
	if(Vx > (ADC_MAXVAL - JOYSTICK_SENSITIVITY)){
		return JOYSTICK_RIGHT;
	}
	else if(Vx < JOYSTICK_SENSITIVITY){
		return JOYSTICK_LEFT;
	}

	
	return JOYSTICK_IDLE;
	
	
	
	
}