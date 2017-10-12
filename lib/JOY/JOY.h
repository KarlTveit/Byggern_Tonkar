/*
 * Joystick.h
 *
 * Created: 13.09.2017 16:17:17
 *  Author: karlmt
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_


#include "../ADC/ADC.h"
#include <string.h>
#include <util/delay.h>

typedef struct{
	int X;
	int Y;
	}JOY_position_t;



typedef enum{
	left,
	right,
	up,
	down,
	neutral
}JOY_direction_t;	

	
void JOY_init();
void JOY_calibrate();
int JOY_button(int button);
JOY_position_t JOY_getPosition();
JOY_direction_t JOY_getDirection();
void JOY_getDirectionString(void);




#endif /* JOYSTICK_H_ */