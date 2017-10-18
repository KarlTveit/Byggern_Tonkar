/*
 * Byggern134.c
 *
 * Created: 30.08.2017 10:04:34
 *  Author: karlmt
 */ 

#ifdef __AVR_ATmega162__
	#define F_CPU 4915200UL // clock frequency in Hz
#elif __AVR_ATmega2560__
	#define F_CPU 16000000UL  // clock frequency in Hz
#endif
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






uint8_t RECEIVED = 0;

ISR(USART0_RXC_vect)
{
	RECEIVED = 1;
	
	unsigned char temp = UDR0;
	UART_Transmit(temp); // for å teste at det funker
}






int main(void)
{
	
	_delay_ms(10);

	DDRA = 0xFF;

	UART_Init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	init_SRAM();
	CAN_init();
	JOY_init();
	_delay_ms(100);
	
	while(1){
		
		JOY_position_t p = JOY_getPosition();
		printf("(%d,%d)", p.X,p.Y);
	}
	
	
	/*OLED_init();
	OLED_clear_display();
	OLED_goto_line(0);
	OLED_goto_column(0);*/
/*
	MENU_create();
	MENU_run_menu();*/

	CAN_init();
	can_message_t m;
	m.id = 3;
	m.length = 1;
	m.data[0] = (uint8_t) 'H';

	CAN_send_message(&m);
	_delay_ms(300);
	//CAN_print_message(CAN_recieve_data());


	
	
	
	//MCP2515_init();
	
	/*while(1) {
		MCP2515_read_status();
		_delay_ms(10);
	}*/
	while(1);
	

	SPI_init();

	
	
	
	while(1) {
		//printf("Her er jeg \n");
		//_delay_ms(100);
		SPI_send(0b01000001);
		_delay_ms(100);
		printf("reading %d\n",SPI_read());
		
		
	}
	
	
	
	/*
	************************
			M E N U 
			
	************************
	*/
	
	
	
	
	
	
	
		
	
	
	
	
	


	








	JOY_init();
	while(1) {
		//JOY_calibrate();	//DENNE KLIKKER HJELP HVA SKJER
		/*_delay_ms(1000);
		printf("(%d,%d)\n", ADC_read(joyX),ADC_read(joyY));
		printf("(%d,%d)\n", JOY_getPosition().X,JOY_getPosition().Y);
		
		JOY_getDirectionString();*/
		
		
		//OLED_test();
		//printf("(%d)\n", ADC_read(joyX));	
	}

 
}