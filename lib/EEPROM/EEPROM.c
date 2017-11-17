/*
 * EEPROM.c
 *
 * Created: 17.11.2017 16:00:13
 *  Author: karlmt
 */ 
#include "eeprom.h"

void EEPROM_write(uint16_t address, uint8_t data){
	
	while(EECR & (1<<EEWE)){}
	
	EEAR = address;			//setting address register
	EEDR = data;			//setting data register
	EECR |= (1<<EEMWE);		
	EECR |= (EEWE);			//start EEPROM write
}

char* EEPROM_read(uint16_t addresse){
	while (EECR & (1 << EEWE));
	
	EEAR = addresse;
	EECR |= (1<<EERE);
	
	return EEDR;
}