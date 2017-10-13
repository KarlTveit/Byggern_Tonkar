#include "ADC.h"
#include <avr/io.h>
volatile uint8_t interrupt_flag;

#define ADC_START_ADDRESS 0x1400

void ADC_init(void){
	// enable external reset, s. --- i datablad atmega162
	MCUCR |= (1 << SRE);
	
	DDRE &= ~(1<<PINE0);
	
	
	
	#ifdef __AVR_ATmega162__
		
		// mask pins, s. 32 i datablad atmega162
		SFIOR |= (1 << XMM2);
		
		//interrupt on falling edge PE0
		EMCUCR &= ~(1<<ISC2);
	
		//Enable interrupts on PE0
		GICR |= (1<<INT2);
	
		//Enable global interrupts
		sei();
	#elif __AVR_ATmega2560__
		// mask pins
		 XMCRB |= (1 << XMM2);
		
		__enable_interrupt();
		__sleep();
	#endif
	
}


uint8_t ADC_read(channel ch){
	//venter til interrupt 
	
	volatile char *ext_ADCCH = (char *) 0x1400;// starter addressen til adc
	ext_ADCCH[0] = ch; // *ext_ADC = ch
	
	
	
	
	while (PINE & (1<<PINE0)) {}
	interrupt_flag = 1;

	
	return ext_ADCCH[0];	
}




ISR(INT2_vect){
	interrupt_flag = 0;
}