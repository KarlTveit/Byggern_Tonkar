/*
 * SPI.h
 *
 * Created: 04.10.2017 09:03:13
 *  Author: tonjaj
 */ 


#ifndef SPI_H_
#define SPI_H_


#include <avr/io.h>
#include "../MCP2515/MCP2515.h"

void SPI_init();
void SPI_send(uint8_t message);
uint8_t SPI_read();
void SPI_enable_chipselect(void);
void SPI_disable_chipselect(void);





#endif /* SPI_H_ */