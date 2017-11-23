/*
 * CAN.c
 *
 * Created: 04.10.2017 09:05:26
 *  Author: tonjaj
 */ 
#include "CAN.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void CAN_init(void){
	
	MCP2515_init();
	//Receive buffer operating mode: receive any message
	MCP2515_bit_modify(MCP_RXB0CTRL,RXM_MODE_MASK, MODE_LISTENONLY);
	
	//Setting normal mode
	MCP2515_bit_modify(MCP_CANCTRL,MODE_MASK, MODE_NORMAL);
	
/*
	//Enable Transmit Complete Interrupt
	MCP2515_bit_modify(MCP_CANINTE,TX0_IE_MASK,ENABLE);*/
	
	//Receive Buffer Control: Receive Any
	MCP2515_bit_modify(MCP_RXB0CTRL,RXB0_CTRL_MASK,RECEIVE_ANY);
	
	
	
/*
	//Interrupt 0 Sense Control: Low Level
	MCUCR &= ~(1 << ISC10);
	MCUCR |= (1 << ISC11); 
	
	//Enable External Interrupt 0
	GICR |= (1 << INT1);
	
	//Global Interrupt Enable
	sei();*/
}


void CAN_send_message(can_message_t *message){
	
	if (!(MCP2515_read(MCP_TXB0CTRL) & TX0_REQ)) {
		
		//Writing id to Standard Identifier Buffer
		MCP2515_write(message->id>>3, MCP_TXB0SIDH); //SID 3:7
		MCP2515_write(message->id<<5, MCP_TXB0SIDL); //SID 0:2
		
		//Writing data length code
		MCP2515_write((message->length), MCP_TXB0DLC);
		
		//Writing data
		for (uint8_t i = 0; i < message->length; i++) {
			MCP2515_write(message->data[i], MCP_TXB0D0+i);
		}
	}
	
	MCP2515_request_to_send(MCP_RTS_TX0);
	
}




void CAN_recieve_data(can_message_t *message){
	
	
	if(MCP2515_read(MCP_CANINTF) & 1) {
		
		_delay_ms(50);
		
		//Retrieving id from Standard Identifier Buffer
		message->id = 0x7ff & (MCP2515_read(MCP_RXB0SIDH)<<3 | MCP2515_read(MCP_RXB0SIDL)>>5);
		
		//Retrieving length
		message->length = MCP2515_read(MCP_RXB0DLC) & DLC_MASK;
		
		//Retrieving data
		for (uint8_t i = 0; i < message->length; i++) {
			message->data[i] = MCP2515_read(MCP_RXB0D0+i);
		}
		
		MCP2515_bit_modify(MCP_CANINTF, 0b00000001, 0b00000000);
	}
	
}




void CAN_print_message(can_message_t message) {
	
	//Printing ID and length
	printf("MESSAGE: \nID: %d\nLength: %d\nData: ", message.id, message.length);
	
	//Printing data
	for (uint8_t i = 0; i < message.length; i++) {
		printf("%d ", message.data[i]);
	}
	printf("\n\n");
	
}


can_message_t* CAN_create_message(can_message_t* message, uint16_t id, uint8_t length, uint8_t data[]) {
	
	message->id = id;
	message->length = length;
	
	for (uint8_t i = 0; i < message->length; i = i+1) {
		message->data[i] = data[i];
	}
	
	return message;
}
