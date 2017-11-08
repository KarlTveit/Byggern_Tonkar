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
	
/*
	while(1){
		
		JOY_position_t p = JOY_getPosition();
		printf("(%d,%d)", p.X,p.Y);
	}
	*/
	
	/*OLED_init();
	OLED_clear_display();
	OLED_goto_line(0);
	OLED_goto_column(0);*/
/*
	MENU_create();
	MENU_run_menu();*/


	can_message_t m;
	
	m.length = 2;
	m.id = 169;
	m.data[0] = 'L';
	m.data[1] = 'Y';
	while(1){
		//CAN_send_message(&m);
		//JOY_getPosition();
	
		can_message_t* joy_message;
		joy_message->id = JOY_POS_ID;		// Jo lavere ID, desto høyere prioritering (lavfrekvente signaler burde ha høyere prioritering)
		joy_message->length = 2;
		
		joy_message->data[0] = ADC_read(joyX);
		joy_message->data[1] = ADC_read(joyY);
		
		printf("x = %d, y = %d\n", joy_message->data[0], joy_message->data[1]);
		
		CAN_send_message(joy_message);
		
		
		
		can_message_t* right_slider_msg;
		right_slider_msg->id = RIGHT_SLIDER_POS_ID;
		right_slider_msg->length = 1;
		right_slider_msg->data[0] = ADC_read(right_slider);
		CAN_send_message(right_slider_msg);
	
	_delay_ms(300);
	}
	can_message_t m2 = CAN_recieve_data();
	printf("ID: %d\n", m2.id);
	printf("Data: %d\n", m2.data[0]);
	CAN_print_message(m2);
/*
	can_message_t message;
	message.id = JOY_POS_ID;		// Jo lavere ID, desto høyere prioritering (lavfrekvente signaler burde ha høyere prioritering)
	message.length = 2;
	
	
	
		_delay_ms(100);
		message.data[0] = ADC_read(joyX);
		message.data[1] = ADC_read(joyY);
		CAN_send_message(&message);
		can_message_t joy = CAN_recieve_data();
		CAN_print_message(joy);
	*/
	
	/*
	can_message_t m;
	
	m.length = 2;
	m.id = 100;
	m.data[0] = ADC_read(joyX);
	m.data[1] = ADC_read(joyY);

	CAN_send_message(&m);
	
	_delay_ms(300);
	can_message_t m2 = CAN_recieve_data();
	printf("ID: %d\n", m2.id);
	printf("ADC_read(joyX) = %d \ndata[0]: %d\n",ADC_read(joyX), m2.data[0]);
	CAN_print_message(m2);
	
	
	*/
	//MCP2515_init();
	
	/*while(1) {
		MCP2515_read_status();
		_delay_ms(10);
	}*/

	

}