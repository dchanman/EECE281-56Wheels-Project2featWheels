/**
*The Joystick class requires code from the
*Signal class.
*
*/

#ifndef JOYSTICK_H_
#define JOYSTICK_H

#define JOYSTICK_CHANNEL_X 2
#define JOYSTICK_CHANNEL_Y 3

#define JOYSTICK_SENSITIVITY 200 //value between 0-512. 0 is no sensitivity, 512 is very sensitive

typedef enum Joystick_Direction{
	JOYSTICK_UP,
	JOYSTICK_DOWN,
	JOYSTICK_LEFT,
	JOYSTICK_RIGHT,
	JOYSTICK_IDLE
};


enum Joystick_Direction Joystick_GetDirection();


#include "Joystick.c"

#endif