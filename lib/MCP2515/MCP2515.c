/*
 * MCP2515.c
 *
 * Created: 04.10.2017 09:04:06
 *  Author: tonjaj
 */ 


#include "MCP2515.h"
#include <stdint.h>

uint8_t MCP2515_init() {
	
	uint8_t val;
	
	SPI_init();
	
	MCP2515_reset();
	_delay_ms(1);

	//test
	MCP2515_read(MCP_CANSTAT);
	if((val & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 in NOT in configuration mode after reset!\n");
		return 1;
	}
	
	return 0;
}
	
	

uint8_t MCP2515_read(uint8_t addr) {
	
	SPI_enable_chipselect();				//~CS written to low (enabled)
	
	SPI_send(MCP_READ);			//READ STATUS byte written to MCP2515
	SPI_send(addr);
	uint8_t val = SPI_read();
	
	SPI_disable_chipselect();
	
	return val;
}

uint8_t MCP2515_write(uint8_t val, uint8_t addr){
	
	SPI_enable_chipselect();
	
	SPI_send(MCP_WRITE);
	SPI_send(addr);
	SPI_send(val);
	
	SPI_disable_chipselect();
	
}

void MCP2515_request_to_send(uint8_t buffer){
	
	SPI_enable_chipselect();
	
	switch (buffer) {
		case 0:
			SPI_send(MCP_RTS_TX0);
			break;
		
		case 1:
			SPI_send(MCP_RTS_TX1);
			break;
		
		case 2:
			SPI_send(MCP_RTS_TX2);
			break;
		
		default:
			SPI_send(MCP_RTS_ALL);
	}
	
	
	SPI_disable_chipselect();
	
}

uint8_t MCP2515_read_status(void){
	
	SPI_enable_chipselect();
	
	SPI_send(MCP_READ_STATUS);
	uint8_t val = SPI_read();
	
	
	SPI_disable_chipselect();
	
	return val;
	
}

void MCP2515_bit_modify(uint8_t addr, uint8_t maskbyte, uint8_t databyte){
	
	SPI_enable_chipselect();
	
	SPI_send(MCP_BITMOD);
	SPI_send(maskbyte);
	SPI_send(databyte);
	
	SPI_disable_chipselect();
	
}


void MCP2515_reset(){
	
	SPI_enable_chipselect();		//Pulling CS to low
	SPI_send(MCP_RESET);
	SPI_disable_chipselect();		//Pulling CS to high
	
}