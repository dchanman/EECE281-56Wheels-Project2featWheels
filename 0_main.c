#include <stdio.h>
#include <at89lp51rd2.h>
#include "LCD.h"
#include "Motor.h"

#define CLK 22118400L
#define BAUD 115200L
#define BRG_VAL (0x100-(CLK/(32L*BAUD)))