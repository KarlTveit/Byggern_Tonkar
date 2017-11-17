/*
 * EEPROM.h
 *
 * Created: 17.11.2017 16:00:29
 *  Author: karlmt
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>


void EEPROM_write(uint16_t address, uint8_t data);
char* EEPROM_read(uint16_t addresse);



#endif /* EEPROM_H_ */