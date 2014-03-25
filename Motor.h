#ifndef MOTOR_H_
#define MOTOR_H_ 0

//We want timer 1 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define FREQ 10000L
#define TIMER1_RELOAD_VALUE (65536L-(CLK/(12L*FREQ)))

//Output for our PWM
#define MOTOR_L_FORWARD		P4_3
#define MOTOR_L_BACKWARD	P3_7
#define MOTOR_R_FORWARD		P3_6
#define	MOTOR_R_BACKWARD	P3_5

//Wheel select
#define MOTOR_LEFT	0
#define MOTOR_RIGHT	1

//Direction
#define MOTOR_FORWARD 	1
#define MOTOR_BACKWARD 	0

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char motor_l_speed;
volatile unsigned char motor_r_speed;
volatile int motor_l_direction;
volatile int motor_r_direction;

//Functions for the motor
void Motor_Init();
void Motor_Set(int motor, unsigned char speed, int direction);
void Motor_Forward(unsigned char speed);
void Motor_Backward(unsigned char speed);
void Motor_TurnLeft(unsigned char speed);
void Motor_TurnRight(unsigned char speed);

#include "Motor.c"

#endif