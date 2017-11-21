/*
 * EEPROM.h
 *
 * Created: 17.11.2017 16:00:29
 *  Author: karlmt
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include "../DEFINITIONS.h"


void EEPROM_write(uint8_t address, uint8_t data);
char* EEPROM_read(uint8_t address);



#endif /* EEPROM_H_ */