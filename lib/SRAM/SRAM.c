/*
 * CFile1.c
 *
 * Created: 06.09.2017 16:28:18
 *  Author: karlmt
 */ 

#include "SRAM.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

static uint8_t highscore_uno;
#define HIGHSCORE_1_ADDRESS 0x10
#define HIGHSCORE_2_ADDRESS 0x20
#define HIGHSCORE_3_ADDRESS 0x30

void SRAM_init(void){
	
	#ifdef __AVR_ATmega162__
	// enable external reset, s. --- i datablad atmega162
	MCUCR |= (1 << SRE);
	
	//SRAM_write(HIGHSCORE_1_ADDRESS,5);
	//SRAM_write(HIGHSCORE_2_ADDRESS,6);
	//SRAM_write(HIGHSCORE_3_ADDRESS,7);
	//highscore_uno = SRAM_read(HIGHSCORE_1_ADDRESS);
	//highscore_uno = SRAM_read(HIGHSCORE_1_ADDRESS);
	//highscore_uno = SRAM_read(HIGHSCORE_1_ADDRESS);
	//printf("Highscore_uno = %d\n",SRAM_read(HIGHSCORE_1_ADDRESS));
	// mask pins, s. 32 i datablad atmega162
	SFIOR |= (1 << XMM2);
	#endif
	
}

void SRAM_write(uint16_t address, char data){
	if (address > 0x7FF){ // Out of SRAM domain
		//printf("HEIII");
		return;
	}
	
	else{
		volatile char* external_ram = SRAM_START_ADDRESS;
		external_ram[address] = data;
		//printf("data = %d\n",data);
		//return;
		_delay_ms(10);
	}
}
	
char SRAM_read(uint16_t address){
	
	if (address > 0x7FF){ // Out of SRAM domain
		return '0';
	}
	
	else{
		volatile char* external_ram = SRAM_START_ADDRESS;
		return external_ram[address];
	_delay_ms(10);
}

}


void SRAM_test(void)
{
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,
			retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",	i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase \n	\n", write_errors, retrieval_errors);
}
