/*
 * GAME.c
 *
 * Created: 12.11.2017 20:16:14
 *  Author: karlmt
 */ 
#include "MENU_ITEMS.h"



/*

void MENU_ITEMS_play(void){
	
	can_message_t game_over_msg;	//for reading IR-interrupt
	
	
	
	can_message_t msg;
	msg.id = 100;
	msg.length = 6;
	
	while(1/ *!game_over_msg.data[0]* /){
		
		
		CAN_recieve_data(&node_2_msg);
		
		
		
		msg.data[0] = ADC_read(joyX);
		msg.data[1] = ADC_read(joyY);
		msg.data[2] = ADC_read(right_slider);
		msg.data[3] = PINB & RIGHT_BUTTON;
		msg.data[4] = PINB & LEFT_BUTTON;
		msg.data[5] = PINB & JOY_BUTTON;
		
		CAN_print_message(msg);
		printf("\n\n");
		
		CAN_send_message(&msg);
		
		
		_delay_ms(300);
	}
	
	OLED_clear_display();
	OLED_print_string("GAME OVER");
	_delay_ms(3000);
	
	MENU_back(current_menu);
	
}*/