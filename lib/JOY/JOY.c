/*
 * Joystick.c
 *
 * Created: 13.09.2017 16:17:40
 *  Author: karlmt
 */ 

#include <stdlib.h>
#include "JOY.h"
#include "../CAN/CAN.h"
//correction values
static int8_t corr_x = 0; 
static int8_t corr_y = 0;




void JOY_init(){
	ADC_init();
	
	//setting input pins
	DDRB &= ~(1<<PB0);
	
	DDRB &= ~(1<<PB1);
	
	DDRB &= ~(1<<PB2);
	PORTB |= (1<<PB2);
	
}


void JOY_calibrate(){
	
	corr_x = 0 - ADC_read(joyX) -127;
	corr_y = 0 - ADC_read(joyY)- 127;
}



JOY_position_t JOY_getPosition(void) {
	JOY_position_t pos;
	
	//reading ADC and scaling to 8-bit
	pos.X = (int)((ADC_read(joyX)*0.7874)) + corr_x - 100;
	pos.Y = (int) ((ADC_read(joyY)*0.7874)) + corr_y - 100;
	
	
	return pos;
}


JOY_direction_t JOY_getDirection(void) {
	
	JOY_position_t pos = JOY_getPosition();
	
	//creating a fraction to determine if the joystick is mostly x or y oriented
	double frac = pos.X/pos.Y;
	
	
	//creating an area near neutral position where small changes does not make a change in direction
	if (abs(pos.X) <= 25 && abs(pos.Y) <= 25) {
		return neutral;
	}
	
	if (pos.X > 0 && abs(frac) > 1) {
		return right;
	}
	else if (pos.X < 0 && abs(frac) > 1) {
		return left;
	}
	else if (pos.Y > 0 && abs(frac) < 1) {
		return up;
	}
	else if (pos.Y < 0 && abs(frac) < 1) {
		return down;
	}

}

void JOY_getDirectionString(void) {
		
		int dir = JOY_getDirection();
		
		switch (dir) {
			case 0:
			printf("LEFT\n");
			break;
			case 1:
			printf("RIGHT\n");
			break;
			case 2:
			printf("UP\n");
			break;
			case 3:
			printf("DOWN\n");
			break;
			case 4:
			printf("NEUTRAL\n");
			break;
		}
}
