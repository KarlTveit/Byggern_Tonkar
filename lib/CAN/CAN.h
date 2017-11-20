/*
 * CAN.h
 *
 * Created: 04.10.2017 09:05:37
 *  Author: tonjaj
 */ 


#ifndef CAN_H_
#define CAN_H_
#include "../DEFINITIONS.h"
#include "../MCP2515/MCP2515.h"
#include <avr/io.h>

typedef struct {
	uint16_t id;
	uint8_t length;
	uint8_t data[8];
}can_message_t;


void CAN_init(void);
void CAN_send_message(can_message_t *message);
void CAN_recieve_data(can_message_t *message);
void CAN_print_message(can_message_t message);



#endif /* CAN_H_ */