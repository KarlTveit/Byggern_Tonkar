/*
 * SPI.c
 *
 * Created: 04.10.2017 09:03:00
 *  Author: tonjaj
 */ 


#include "SPI.h"



void SPI_init() {
	SPCR &= ~(1<<DORD);						//MSB of data word transmitted first
	SPCR |= (1<<SPE);						//SPI Enable
	SPCR |= (1<<MSTR);						//Master mode enable
	
	SPCR |= (1<<SPR0);						//SCK frequency = F_OSC/16 
	SPCR &= ~(1<<SPR1);
	
	
	
}



void SPI_send(uint8_t message) {
	
	SPDR = message;							//Start transmission
	
	
	//while (!(SPSR & (1<<SPIF))) {};			//Wait until transmission is complete
	
}



uint8_t SPI_read() {
	
	SPI_send(0x00);							//Transmisson of dummy byte, to be able to read from slave
	
	//while (!(SPSR & (1<<SPIF))) {};			//Wait until transmission is complete
	
	return SPDR;							//All messages will end with the dummy byte????
	
}


void SPI_enable_chipselect(void) { // 1 --> enable
	PORTB &= ~(1<<PB4);
}



void SPI_disable_chipselect(void) { // 1 --> enable
	PORTB |= (1<<PB4);
}