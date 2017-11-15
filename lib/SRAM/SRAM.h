/*
 * IncFile1.h
 *
 * Created: 06.09.2017 16:29:04
 *  Author: karlmt
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_
#include <avr/io.h>
#define SRAM_START_ADDRESS 1800
void SRAM_init(void);
void SRAM_test(void);
void SRAM_write(uint16_t address, char data);
char SRAM_read(uint16_t address);

#endif /* INCFILE1_H_ */