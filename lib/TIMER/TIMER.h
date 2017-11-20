/*
 * TIMER_HS.h
 *
 * Created: 20.11.2017 13:33:43
 *  Author: karlmt
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


ISR(TIMER0_COMP_vect);


void TIMER_init();
void TIMER_start();
void TIMER_stop();
uint16_t TIMER_get_time();







#endif /* TIMER_H_ */