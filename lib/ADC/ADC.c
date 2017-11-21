#include "ADC.h"
#include <avr/io.h>
volatile uint8_t interrupt_flag;



void ADC_init(void){
	// enable external reset
	MCUCR |= (1 << SRE);
	
	DDRE &= ~(1<<PINE0);
		
	// mask pins, s. 32 i datablad atmega162
	SFIOR |= (1 << XMM2);
		
	//interrupt on falling edge PE0
	EMCUCR &= ~(1<<ISC2);
	
	//Enable interrupts on PE0
	GICR |= (1<<INT2);
	
	//Enable global interrupts
	sei();
	
	
}


uint8_t ADC_read(channel ch){
	//venter til interrupt 
	
	volatile char *ext_ADCCH = (char *) ADC_START_ADDRESS;// starter addressen til adc
	ext_ADCCH[0] = ch; // *ext_ADC = ch
	
	
	while (PINE & (1<<PINE0)) {}
	interrupt_flag = 1;

	
	return ext_ADCCH[0];	
}




ISR(INT2_vect){
	interrupt_flag = 0;
}