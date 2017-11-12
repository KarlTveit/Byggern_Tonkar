/*
 * CAN.c
 *
 * Created: 04.10.2017 09:05:26
 *  Author: tonjaj
 */ 
#include "CAN.h"

void CAN_init(void){
	//MCP2515_reset();
	MCP2515_init();
	MCP2515_bit_modify(MCP_RXB0CTRL,0b01100100, 0b01100000);
	MCP2515_bit_modify(MCP_CANCTRL,MODE_MASK, MODE_NORMAL);
	MCP2515_bit_modify(MCP_CANINTE,0b00000001,0xff);
	MCP2515_bit_modify(0x60,0b01100000,0xff);
	
}


void CAN_send_message(can_message_t *message){
	
	
	
	 
	
	if (!(MCP2515_read(MCP_TXB0CTRL) & 0b00001000)) {
		
		/*MCP_TXB0CTRL &= ~(1<<MCP_ABTF);
		MCP_TXB0CTRL &= ~(1<<MCP_MLOA);
		MCP_TXB0CTRL &= ~(1<<MCP_TXERR);*/
		
// 		MCP2515_bit_modify(MCP_TXB0CTRL, 0b00000011, 0b00000000 );
// 		//placing message id into SID 0:7
		//printf("Hello\n");
		MCP2515_write(message->id>>3, MCP_TXB0SIDH); //SID 3:7
		MCP2515_write(message->id<<5, MCP_TXB0SIDL); //SID 0:2
		
		MCP2515_write((message->length), MCP_TXB0DLC);
		
		for (uint8_t i = 0; i < message->length; i++) {
			MCP2515_write(message->data[i], MCP_TXB0D0+i);
		}
	}
	
	
	MCP2515_request_to_send(MCP_RTS_TX0);
	
}
void CAN_error(){
	
	
	
	
}
void CAN_transmit_complete(){
	
	
	
	
}
void CAN_recieve_data(can_message_t *message){
	//memset(&message, 0, sizeof(can_message_t));
	
	if(MCP2515_read(MCP_CANINTF) & 1) {
		//printf("Jeg er i datarecieve__");
		message->id = 0xff & (MCP2515_read(MCP_RXB0SIDH)<<3 | MCP2515_read(MCP_RXB0SIDL)>>5);
		message->length = MCP2515_read(MCP_RXB0DLC) & 0b00001111;						//DLC3:0 in TXB0DLC-register
		
		for (uint8_t i = 0; i < message->length; i++) {
			message->data[i] = MCP2515_read(MCP_RXB0D0+i);
			//printf("Msg i = %d = %d\n", i, message->data[i]);
		}
		MCP2515_bit_modify(MCP_CANINTF, 0b00000001, 0b00000000);
	}
	
	
	
	//MCP_CANINTF &= (~(0b00000001));

	
	
}

void CAN_int_vect();



void CAN_print_message(can_message_t message) {
	
	
	
	printf("MESSAGE: \nID: %d\nLength: %d\nData: ", message.id, message.length);
	
	for (uint8_t i = 0; i < message.length; i++) {
			
		printf("%d ", message.data[i]);
	}
	
	printf("\n");
}