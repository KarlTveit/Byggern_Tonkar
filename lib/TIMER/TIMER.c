/*
 * TIMER_HS.c
 *
 * Created: 20.11.2017 13:33:21
 *  Author: karlmt
 */ 


#include "TIMER.h"

uint16_t volatile static stopwatch = 0;
uint8_t counter = 0;


ISR(TIMER1_COMPA_vect) {
	
	stopwatch = stopwatch + 1;
	_delay_ms(1);
} 


void TIMER_init() {
	
	
	//CTC mode for highscore_timer
	TCCR1B |= (1 << WGM12);
	
	//Want to count each second:
	//Clock frequency = 16 000 000 and prescaler = 1024 ---> 4915200/1024 = 4800 ticks per sec
	
	//Defining top value of counter for highscore_timer --> reset each second
	OCR1A = 4800;

	
	//Enable global interrupt
	sei();
	
	//Enable Timer Output Compare Match A Interrupt for highscore_timer
	TIMSK |= (1 << OCIE1A);

	
}

void TIMER_start(){
	
	stopwatch = 0;
	
	// initialize counter
	TCNT1 = 0;
	
	//Prescaler = 1024
	TCCR1B |= (1 << CS12)|(1 << CS10);
}
	
	
	


void TIMER_stop() {
	
	//Turning off clock source
	TCCR0 &= ~(1<<CS12) & ~(1 << CS11) & ~(1 << CS10);
	

}



uint16_t TIMER_get_time() {
	return stopwatch;
}
