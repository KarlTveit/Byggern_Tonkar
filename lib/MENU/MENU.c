
#include "MENU.h"
#include "../JOY/JOY.h"
#include "../OLED/OLED.h"

static menu_t main_menu;
static menu_t current_menu;
static uint8_t current_line = 0; 
static JOY_direction_t last_direction = neutral;
/*static unsigned int quit = 0;*/
static uint8_t highscores[HIGHSCORES_LENGTH] = {0};
uint8_t gameover = 0;	

//Displaying current menu
void MENU_display_menu(menu_t menu, uint8_t curr_line) {
	
	//Not displaying if menu-variable contains an function.  
	if (menu.item != NULL_PTR) {
		current_menu = *menu.parent;
		MENU_back(menu);
		return;
	}
	
	//Going to top of page
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header(menu.title);
	OLED_goto_line(++page);
	
	//Displaying submenus on different lines
	for (uint8_t i = 0; i < menu.number_of_submenus; i++) {
		if (i == (curr_line) ) {
			OLED_print_inverted_string(menu.submenus[i]->title);
		}
		else {
			OLED_print_string(menu.submenus[i]->title);
		}
		
		OLED_goto_line(++page);
	}
	

}



//Adding submenu. The func pointer indicates if the submenu is a menu or an function
menu_t* MENU_add_submenu(char* t, void(*func)(), menu_t* p) {
	
	//Allocating memory for the new submenu
	p->submenus[p->number_of_submenus] = malloc(sizeof(menu_t)*4);
	
	p->submenus[p->number_of_submenus]->title = t;
	p->submenus[p->number_of_submenus]->number_of_submenus = 0;
	p->submenus[p->number_of_submenus]->item = *func;
	p->submenus[p->number_of_submenus]->parent = p;
	
	//Allocating memory for the submenus of the new submenu
	p->submenus[p->number_of_submenus]->submenus = malloc(sizeof(menu_t)*4);
	
	//Increasing the number of submenus for the parent
	p->number_of_submenus++;
	
	return p->submenus[p->number_of_submenus-1];
	
}


//Choosing within a menu
void MENU_choose(menu_t choice) {
	
	//Adding a delay for a more natural feeling
	_delay_ms(500);
	
	//If the choice is a menu
	if (choice.item == NULL_PTR) {
		if (choice.submenus[0] != NULL_PTR) {
			MENU_display_menu(choice,0);
		}
	}
	//If the choice is an function
	else {
		OLED_clear_display();
		choice.item();
	}
	
}

//Returning to the previous menu
void MENU_back(menu_t this) {
	
	if (this.parent != NULL_PTR) {
		MENU_display_menu(*this.parent,0);
	}
	
}


menu_t MENU_get_current_menu(void) {
	return current_menu;
}


//Printing an animation of a rocket
void MENU_print_rocket() {
	OLED_print_header("byggolini");
	 OLED_goto_line(7);
	 OLED_print_string("Right to start");
	//Upper horizontal line
	OLED_goto_line(2);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b11000000;
	}
	
	
	//Lower horizontal line
	OLED_goto_line(6);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b00000011;
	}
	
	
	
	//Vertical line
	for (uint8_t i = 3; i <= 5; i++) {
		OLED_goto_line(i);
		OLED_goto_column(50);
		*ext_oled_data = FILL;
		*ext_oled_data = FILL;
	}
	
	
	//Rocket-nose<3
	OLED_goto_line(3);
	OLED_goto_column(95);
	
	*ext_oled_data = 0b00000011;
	*ext_oled_data = 0b00000110;
	*ext_oled_data = 0b00001100;
	*ext_oled_data = 0b00011000;
	*ext_oled_data = 0b00110000;
	*ext_oled_data = 0b01100000;
	*ext_oled_data = 0b11000000;
	*ext_oled_data = 0b10000000;
	
	OLED_goto_line(4);
	OLED_goto_column(95+7);
	
	*ext_oled_data = 0b10000001;
	*ext_oled_data = 0b11000011;
	*ext_oled_data = 0b01100110;
	*ext_oled_data = 0b00111100;
	
	
	OLED_goto_line(5);
	OLED_goto_column(95);
	*ext_oled_data = 0b11000000;
	*ext_oled_data = 0b01100000;
	*ext_oled_data = 0b00110000;
	*ext_oled_data = 0b00011000;
	*ext_oled_data = 0b00001100;
	*ext_oled_data = 0b00000110;
	*ext_oled_data = 0b00000011;
	*ext_oled_data = 0b00000001;
	
	JOY_direction_t dir = JOY_getDirection();
	
	//Ziggy Stardust
	while (dir != right)  {
		for(uint8_t j = 3; j <= 5 ; j++) {
			OLED_goto_line(j);
			for(uint8_t i = 0; i< 50; i++) {
				*ext_oled_data = rand() % 255;
			}
		}
		_delay_ms(500);
		dir = JOY_getDirection();
		
	}
	
}

//Playing the game with the P1000 multifunction board
void MENU_play_game(void){
	
	//For reading IR-interrupt and detecting gameover
	can_message_t receive_msg;	
	
	
	//Initializing the message containing the control references
	can_message_t control_msg;
	control_msg = *(CAN_create_message(&control_msg,GAME_ID,7,0));
	
	uint8_t gameover = FALSE;
	
	//Starting the higscore timer
	TIMER_start();
	
	//Running until the IR is triggered
	while(!gameover){
		
		
		control_msg.data[0] = ADC_read(joyX);
		control_msg.data[1] = ADC_read(joyY);
		control_msg.data[2] = ADC_read(right_slider);
		control_msg.data[3] = PINB & RIGHT_BUTTON;
		control_msg.data[4] = PINB & LEFT_BUTTON;
		control_msg.data[5] = PINB & JOY_BUTTON;
		control_msg.data[7] = gameover ? 0:1;
		
		CAN_send_message(&control_msg);
	
		
		//Checking if IR is triggered
		CAN_recieve_data(&receive_msg);
		
		if (receive_msg.id == GAMEOVER_DATA_ID) {
	
			gameover = TRUE;
			MENU_gameover();
			receive_msg.id = 0;
		}
	
	}
	
}

void MENU_clear_highscores(void){
	
	EEPROM_write(HIGHSCORE_1_ADDRESS,0);
	EEPROM_write(HIGHSCORE_2_ADDRESS,0);
	EEPROM_write(HIGHSCORE_3_ADDRESS,0);
	
}


void MENU_gameover(void){
	
	//Stops the highscore timer
	TIMER_stop();
	
	uint8_t rank = MENU_update_highscores(TIMER_get_time());
	uint8_t time = TIMER_get_time();
	OLED_clear_display();
	OLED_print_string("GAME OVER");
	OLED_goto_line(3);
	OLED_print_string("Your score:");
	OLED_goto_line(4);
	OLED_print_string(OLED_int_to_string(time));
	_delay_ms(5000);
	
	
	if (rank) {
		OLED_clear_display();
		
		OLED_print_string("Congratulations!");
		
		OLED_goto_line(2);
		OLED_print_string("Your score reached");
		
		OLED_goto_line(3);
		OLED_print_string("the highscore list.");
		
		OLED_goto_line(4);
		OLED_print_string("Current rank:");
		
		OLED_goto_line(5);
		OLED_print_string(OLED_int_to_string(rank));
		
		_delay_ms(7000);
		MENU_display_menu(main_menu,0);
	}
	gameover = FALSE;
}



void MENU_print_highscores(void) {
	
	highscores[0] = EEPROM_read(HIGHSCORE_1_ADDRESS);
	highscores[1] = EEPROM_read(HIGHSCORE_2_ADDRESS);
	highscores[2] = EEPROM_read(HIGHSCORE_3_ADDRESS);
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header("HIGHSCORE LIST");
	OLED_goto_line(++page);
	
	for (uint8_t i = 0; i < HIGHSCORES_LENGTH; i = i+1) {
		
		OLED_print_string(OLED_int_to_string(highscores[i]));
		OLED_goto_line(++page);
	
	}
	while(JOY_getDirection()!=left){ 
	}
}

//Returning rank and writing to EEPROM if highscore reaches top 3.
uint8_t MENU_update_highscores(uint8_t time) { 
	
	uint8_t highscore_1 = EEPROM_read(HIGHSCORE_1_ADDRESS);
	uint8_t highscore_2 = EEPROM_read(HIGHSCORE_2_ADDRESS);
	uint8_t highscore_3 = EEPROM_read(HIGHSCORE_3_ADDRESS);
		
		if (time > highscore_1){
			EEPROM_write(HIGHSCORE_1_ADDRESS,time);
			return 1;
		}
		else if(time > highscore_2){
			EEPROM_write(HIGHSCORE_2_ADDRESS,time);
			return 2;
		}
		else if(time > highscore_3){
			EEPROM_write(HIGHSCORE_3_ADDRESS,time);
			return 3;
		}
		return 0;
		
}


//Enabling the microphone for controlling the solenoid with the sheer force of your voice
void MENU_scream_mode (void){
	DDRB |= (1<<PB3);
	PORTB &= ~(1<<PB3);
	
}

//Standard mode using the button to control the solenoid
void MENU_normal_mode (void){
	DDRB |= (1<<PB3);
	PORTB |=(1<<PB3);
	
}

//Enabling the bluetooth device to send control data from the "Byggolini" app
void MENU_wireless_mode (void){
	TIMER_start();
	can_message_t receive_msg;
	CAN_create_message(&receive_msg,GAME_ID,7,0);
	
	
	while(!gameover){
		
		can_message_t msg;
		CAN_create_message(&msg, WIRELESS_ID,1,1);
		CAN_send_message(&msg);
		
		//Checking if IR is triggered
		CAN_recieve_data(&receive_msg);
		
		if (receive_msg.id == GAMEOVER_DATA_ID) {
			
			gameover = TRUE;
			
			MENU_gameover();
		}
		
	}
	
}

void MENU_create(){

	//Initializing Main Menu
	main_menu.title = "Main Menu";
	main_menu.number_of_submenus = 0;
	main_menu.item = NULL_PTR;
	main_menu.parent = NULL_PTR;
	main_menu.submenus = malloc(sizeof(menu_t)*4);

	
	//Adding submenus and functions
	menu_t* playgame_f = MENU_add_submenu("Play game", &MENU_play_game, &main_menu);
	menu_t* highscores_m = MENU_add_submenu("Highscores", &MENU_print_highscores, &main_menu);
	menu_t* settings_m = MENU_add_submenu("Settings", NULL_PTR, &main_menu);
	
	menu_t* scream_mode_f = MENU_add_submenu("Scream Mode", &MENU_scream_mode, settings_m);
	menu_t* normal_mode_f = MENU_add_submenu("Normal Mode", &MENU_normal_mode, settings_m);
	menu_t* wireless_mode_f = MENU_add_submenu("Wireless Mode", &MENU_wireless_mode, settings_m);
	
	//Setting current menu to main menu
	current_menu = main_menu;
	
	
}


//Navigating in the menus
void MENU_run_menu(void){
	
	MENU_display_menu(main_menu,0);
	
	while(1) {
			
		JOY_position_t pos = JOY_getPosition();
		JOY_direction_t dir = JOY_getDirection();
		
		menu_t choice = *current_menu.submenus[current_line];		
		
			//Establishing the joystick commands
			switch (dir) {	
					
					
				case up:
						
					//Ensuring that the user returns the joystick to neutral position before making another choice
					if (current_line > 0 && last_direction == neutral) {
						current_line--;
						MENU_display_menu(current_menu, current_line);
					}
					last_direction = dir;
					
					_delay_ms(100);
					break;
				
				case down:
	
					if ((current_line < (current_menu.number_of_submenus-1)) && last_direction == neutral) {
						current_line++;
						printf("current line = %d\n", current_line);
						
						MENU_display_menu(current_menu, current_line);
					}
					last_direction = dir;
					
					_delay_ms(100);
					break;
					
				//Enabling a choice to be made by moving the joystick right
				case right:
					if (last_direction == neutral) {
						MENU_choose(choice);
						current_menu = choice;
						current_line = 0;
						MENU_display_menu(current_menu, current_line);
						
					}
					last_direction = dir;
					
					_delay_ms(100);
					break;
				
				//Enabling going to the previous menu by moving the joystick left
				case left:	
					if(last_direction == neutral){
					MENU_back(current_menu);
						if (current_menu.parent != NULL_PTR) {
							current_menu = *current_menu.parent;
						}
							
						current_line = 0;
					}
					
					last_direction = dir;
					
					_delay_ms(100);
					break;
					
				case neutral:
					last_direction = dir;
					
					_delay_ms(100);
					break;
						
			}
	
		}
		
}

