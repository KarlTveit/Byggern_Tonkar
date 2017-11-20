/*
 * EEPROM.c
 *
 * Created: 17.11.2017 16:00:13
 *  Author: karlmt
 */ 
#include "eeprom.h"

void EEPROM_write(uint8_t address, uint8_t data){
	
	//waiting until write enable is set
	while(EECR & (1<<EEWE)){} 
		
	//setting address register
	EEAR = address;	
		
	//setting data register
	EEDR = data;
	
	//master wrte enable			
	EECR |= (1<<EEMWE);			
	
	//start EEPROM write
	EECR |= (1<<EEWE);
}
				

char* EEPROM_read(uint8_t address){
	
	//waiting until read enable
	while (EECR & (1 << EEWE)); 
	
	EEAR = address;
	
	//reading address				
	EECR |= (1<<EERE);
	
	return EEDR;
}