
#include "MENU.h"
#include "../JOY/JOY.h"
#include "../OLED/OLED.h"
//#include "../DEFINITIONS.h"
static menu_t main_menu;
static menu_t current_menu;
static uint8_t current_line = 0; // første linje er linjen under tittel
static JOY_direction_t last_direction = neutral;

static unsigned int quit = 0;	//bool

static uint8_t highscores[HIGHSCORES_LENGTH] = {0};
	

//function for displaying the current menu
void MENU_display_menu(menu_t menu, uint8_t curr_line) {
	
	//if the submenu contains a function, the menu does not get displayed and the menu goes back to the previous after running the function
	if (menu.item != NULL_PTR) {
		current_menu = *menu.parent;
		MENU_back(menu);
		return;
	}
	
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header(menu.title);
	OLED_goto_line(++page);
	
	//display submenus on different lines
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

//function for adding new submenus. The func pointer is a nullpointer for a submenu and a function pointer for a function
menu_t* MENU_add_submenu(char* t, void(*func)(), /*uint8_t num,*/ menu_t* p) {
	
	//allocating memory for the new submenu
	p->submenus[p->number_of_submenus] = malloc(sizeof(menu_t)*4);
	
	p->submenus[p->number_of_submenus]->title = t;
	p->submenus[p->number_of_submenus]->number_of_submenus = 0;
	p->submenus[p->number_of_submenus]->item = *func;
	p->submenus[p->number_of_submenus]->parent = p;
	//allocating memory for the submenus of the new submenu
	p->submenus[p->number_of_submenus]->submenus = malloc(sizeof(menu_t)*4);
	
	//increasing the number of submenus for the parent by one
	p->number_of_submenus++;
	
	return p->submenus[p->number_of_submenus-1];



}


//function for choosing the within a menu
void MENU_choose(menu_t choice) {
	
	//adding a delay for a more natural feeling
	_delay_ms(500);
	
	//if the choice is a menu
	if (choice.item == NULL_PTR) {
		if (choice.submenus[0] != NULL_PTR) {
			MENU_display_menu(choice,0);
		}
	}
	//if the coice is a function
	else {
		OLED_clear_display();
		choice.item();
	}
	
}

//function for returning to the previous menu
void MENU_back(menu_t this) {
	
	if (this.parent != NULL_PTR) {
		MENU_display_menu(*this.parent,0);
	}
	
}


menu_t MENU_get_current_menu(void) {
	return current_menu;
}


//function for printing an animation of a rocket
void MENU_print_rocket() {
	
	
	//Øvre vannrette strek
	OLED_goto_line(2);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b11000000;
	}
	
	
	
	//Nedre vannrette strek
	OLED_goto_line(6);
	OLED_goto_column(50);
	
	for (uint8_t i = 50; i < 95; i++) {
		*ext_oled_data = 0b00000011;
	}
	
	
	
	//Loddrett strek
	for (uint8_t i = 3; i <= 5; i++) {
		OLED_goto_line(i);
		OLED_goto_column(50);
		*ext_oled_data = FILL;
		*ext_oled_data = FILL;
	}
	
	
	//Rocket-nose<3<3
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
	while (dir != left)  {
		for(uint8_t j = 3; j <=5 ; j++) {
			OLED_goto_line(j);
			for(uint8_t i = 0; i< 50; i++) {
				*ext_oled_data = rand() % 255;
			}
			
		}
		_delay_ms(200);
		dir = JOY_getDirection();
		
	}
	
}

//function for playing the game with the P1000 multifunction board
void MENU_play_game(void){
	
	//for reading IR-interrupt
	can_message_t receive_msg;	
	
	
	//initializing the message containing the controls
	can_message_t msg;
	msg.id = GAME_ID;
	msg.length = 7;
	
	
	
	
	uint8_t gameover = FALSE;
	
	//starting the higscore timer
	TIMER_start();
	
	//running until the IR is triggered
	while(!gameover){
		
		
		msg.data[0] = ADC_read(joyX);
		msg.data[1] = ADC_read(joyY);
		msg.data[2] = ADC_read(right_slider);
		msg.data[3] = PINB & RIGHT_BUTTON;
		msg.data[4] = PINB & LEFT_BUTTON;
		msg.data[5] = PINB & JOY_BUTTON;
		msg.data[7] = gameover ? 0:1;
		
		CAN_print_message(msg);
		printf("\n\n");
		
		CAN_send_message(&msg);
	
		
		//Recieving an eventual message saying the IR is triggered
		CAN_recieve_data(&receive_msg);
		
		CAN_print_message(receive_msg);
		
		if (receive_msg.id == GAMEOVER_DATA_ID) {
	
			gameover = TRUE;
			//stops the highscore timer
			TIMER_stop();
			
			uint8_t rank = MENU_update_highscores(TIMER_get_time());
			uint8_t time = TIMER_get_time();
			OLED_clear_display();
			OLED_print_string("GAME OVER");
			OLED_goto_line(3);
			OLED_print_string("Your score:");
			OLED_goto_line(4);
			OLED_print_string(OLED_int_to_string(time));
			_delay_ms(10000);
			
			
			
			if (rank) {
				OLED_clear_display();
				OLED_print_string("Congratulations!");
				OLED_goto_line(2);
				OLED_print_string("Your time reached the highscore list.");
				OLED_goto_line(3);
				OLED_print_string("Current rank:");
				OLED_goto_line(4);
				OLED_print_char(rank);
				_delay_ms(3000);
			}
		}
		
	}
	
}


void MENU_clear_highscores(void){
	EEPROM_write(HIGHSCORE_1_ADDRESS,0);
	EEPROM_write(HIGHSCORE_2_ADDRESS,0);
	EEPROM_write(HIGHSCORE_3_ADDRESS,0);
	
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

//Returns the position where you are on the higscore board and writes to the EEPROM if you have made top three
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


//Enabling the microfone for controlling the solenoid with the sheer force of your voice
void MENU_scream_mode (void){
	DDRB |= (1<<PB3);
	PORTB &= ~(1<<PB3);
	
}

//standard mode using the button to control the solenoid
void MENU_normal_mode (void){
	DDRB |= (1<<PB3);
	PORTB |=(1<<PB3);
	
}

//enables the bluetooth device to send control data from the "Byggolini" app
void MENU_wireless_mode (void){
	while(!quit){
		can_message_t msg;
		
		msg.length = 1;
		msg.id = WIRELESS_ID;
		msg.data[0] = 1;
		
		CAN_send_message(&msg);
	
	}
	
	
	
	
	
}

void MENU_create(){

	//Initializing Main Menu
	main_menu.title = "Main Menu";
	main_menu.number_of_submenus = 0;
	main_menu.item = NULL_PTR;
	main_menu.parent = NULL_PTR;
	main_menu.submenus = malloc(sizeof(menu_t)*4);
	
	

	
	
	
	//adding submenus and functions
	menu_t* playgame_f = MENU_add_submenu("Play game", &MENU_play_game, &main_menu);
	menu_t* highscores_m = MENU_add_submenu("Highscores", &MENU_print_highscores, &main_menu);
	menu_t* settings_m = MENU_add_submenu("Settings", NULL_PTR, &main_menu);
	
	menu_t* scream_mode_f = MENU_add_submenu("Scream Mode", &MENU_scream_mode, settings_m);
	menu_t* normal_mode_f = MENU_add_submenu("Normal Mode", &MENU_normal_mode, settings_m);
	menu_t* wireless_mode_f = MENU_add_submenu("Wireless Mode", &MENU_wireless_mode, settings_m);
	
	//setting the current menu to be the main menu
	current_menu = main_menu;
	
	
}


//function for navigating the menus
void MENU_run_menu(void){
	
	MENU_display_menu(main_menu,0);
		while(!quit) {
			
			JOY_position_t pos = JOY_getPosition();
			
			JOY_direction_t dir = JOY_getDirection();
		
			menu_t choice = *current_menu.submenus[current_line];		
		
				//establishing the joystick commands
				switch (dir) {	
					
					
					case up:
						
						//ensuring that the user returns the joystick to neutral position before making another choice
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
					
					//enabling a choice to be made by moving the joystick right
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
				
					//enabling going to the previous menu by moving the joystick left
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


