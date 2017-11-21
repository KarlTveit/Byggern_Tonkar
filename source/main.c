/*
 * Byggern134.c
 *
 * Created: 30.08.2017 10:04:34
 *  Author: karlmt
 */ 

#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "stdio.h"



#include "../lib/UART/UART.h"
#include "../lib/ADC/ADC.h"
#include "../lib/JOY/JOY.h"
#include "../lib/SRAM/SRAM.h"
#include "../lib/OLED/OLED.h"
#include "../lib/MENU/MENU.h"
#include "../lib/SPI/SPI.h"
#include "../lib/MCP2515/MCP2515.h"
#include "../lib/CAN/CAN.h"
#include "../lib/CAN_DEFINES/CAN_DEFINES.h"
#include "../lib/EEPROM/EEPROM.h"
#include "../lib/DEFINITIONS.h"
#include "../lib/TIMER/TIMER.h"




uint8_t RECEIVED = 0;

ISR(USART0_RXC_vect)
{
	RECEIVED = 1;
	
	unsigned char temp = UDR0;
	UART_Transmit(temp);
}






int main(void)
{
	
	//_delay_ms(10);
	
	//Setting port A as output	
	DDRA = 0xFF;
	
	//Initializing drivers
	UART_Init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	SRAM_init();
	CAN_init();
	JOY_init();
	_delay_ms(100);
	OLED_init();
	OLED_clear_display();
	OLED_goto_line(0);
	OLED_goto_column(0);
	MENU_print_rocket();
	TIMER_init();
	
	MENU_create();

	MENU_run_menu();
}