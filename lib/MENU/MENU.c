
#include "MENU.h"
#include "../JOY/JOY.h"
#include "../OLED/OLED.h"
#include "../TIMER/TIMER.h"
static menu_t main_menu;
static menu_t current_menu;
static uint8_t current_line = 0; // første linje er linjen under tittel
static JOY_direction_t last_direction = neutral;

static unsigned int quit = 0;	//bool

static uint8_t highscores[HIGHSCORES_LENGTH] = {0};
	

void MENU_display_menu(menu_t menu, uint8_t curr_line) {
	if (menu.item != NULL_PTR) {
		current_menu = *menu.parent;
		MENU_back(menu);
		return;
	}
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header(menu.title);
	OLED_goto_line(++page);

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


menu_t* MENU_add_submenu(char* t, void(*func)(), /*uint8_t num,*/ menu_t* p) {
	
	
	p->submenus[p->number_of_submenus] = malloc(sizeof(menu_t)*5);
	//menu_t* submenu = p->submenus[p->number_of_submenus];
	
	
	p->submenus[p->number_of_submenus]->title = t;
	p->submenus[p->number_of_submenus]->number_of_submenus = 0;
	p->submenus[p->number_of_submenus]->item = *func;
	p->submenus[p->number_of_submenus]->parent = p;
	p->submenus[p->number_of_submenus]->submenus = malloc(sizeof(menu_t)*5);
	
	p->number_of_submenus++;
	
	return p->submenus[p->number_of_submenus-1];



}



void MENU_choose(menu_t choice) {
	
	/*OLED_emphasized_inverted_string(choice.title);*/
	_delay_ms(1000);
	
	if (choice.item == NULL_PTR) {
		if (choice.submenus[0] != NULL_PTR) {
			MENU_display_menu(choice,0);
		}
	}
	else {
		OLED_clear_display();
		choice.item();
	}
	
}


void MENU_back(menu_t this) {
	
	if (this.parent != NULL_PTR) {
		MENU_display_menu(*this.parent,0);
	}/*
	else {
		OLED_clear_display();
		
		OLED_goto_line(4);
		OLED_goto_column(70);
		OLED_print_string("    Q U I T");
	
		OLED_print_rocket();
		
		
	}*/
	
	
}


menu_t MENU_get_current_menu(void) {
	return current_menu;
}



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
	//Stjernestøv
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

void MENU_play_game(void){
	
	
	can_message_t receive_msg;	//for reading IR-interrupt
	
	
	
	can_message_t msg;
	msg.id = GAME_ID;
	msg.length = 7;
	
	
/*	clock_t start = clock(), diff;*/
	
	/*int a = 1;*/
	uint8_t gameover = FALSE;
	
	while(!gameover){
		printf("---- In MENU_play_game ---- \n\n ");
		
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
	
		
		
		//_delay_ms(5000);
		
		/*a = 0;*/
		CAN_recieve_data(&receive_msg);
		printf("RECEIVE MESSAGE \n");
		CAN_print_message(receive_msg);
		printf("\n\n");
		
		/*if (receive_msg.id == GAMEOVER_DATA_ID) {
			//printf("Game over message received");
			gameover = TRUE;
			uint8_t time = msg.data[TIMER_VAL];
			OLED_clear_display();
			OLED_print_string("GAME OVER");
			_delay_ms(10000);
			
			MENU_update_highscores(time);
			
			if (MENU_get_hichscore_rank(time)) {
				OLED_clear_display();
				/ *uint8_t rank = MENU_get_hichscore_rank(time);* /
				OLED_print_string("Congratulations! Your time reached the highscore list. Current rank: ");
				OLED_print_char(MENU_get_hichscore_rank(time));
				_delay_ms(3000);
			}
		}*/
		
	}
	/*uint8_t diff = clock() - start;
	uint8_t seconds = diff/CLOCKS_PER_SEC;
	printf("seconds = %d\n\n", seconds);*/
/*
	OLED_clear_display();
	OLED_print_string("GAME OVER");
	_delay_ms(3000);*/
	
	/*MENU_back(current_menu);*/	//necessary? test!
	
}


void MENU_clear_highscores(void){
	SRAM_write(HIGHSCORE_1_ADDRESS,0);
	SRAM_write(HIGHSCORE_2_ADDRESS,0);
	SRAM_write(HIGHSCORE_3_ADDRESS,0);
	
}



void MENU_print_highscores(void) {
	
	highscores[0] = SRAM_read(HIGHSCORE_1_ADDRESS);
	highscores[1] = SRAM_read(HIGHSCORE_2_ADDRESS);
	highscores[2] = SRAM_read(HIGHSCORE_3_ADDRESS);
	uint8_t page = 0;
	OLED_clear_display();
	OLED_print_header("HIGHSCORE LIST");
	OLED_goto_line(++page);
	/*char* numbers*/
	
	for (uint8_t i = 0; i < HIGHSCORES_LENGTH; i = i+1) {
		// OLED_int_to_string(i+1)
		//OLED_print_char(i+1);
		//OLED_print_string(". ");
		uint8_t score = OLED_int_to_string(highscores[i]);
		printf("higscores: %c\n", score);
		OLED_print_string(score);
		OLED_goto_line(++page);
	
	} 
	_delay_ms(7000);
}

uint8_t MENU_update_highscores(uint8_t time) { //Returns the position where you are on the higscore board
	
	uint8_t highscore_1 = SRAM_read(HIGHSCORE_1_ADDRESS);
	uint8_t highscore_2 = SRAM_read(HIGHSCORE_2_ADDRESS);
	uint8_t highscore_3 = SRAM_read(HIGHSCORE_3_ADDRESS);
	
	
	/*for(uint8_t i = 0; i < HIGHSCORES_LENGTH; i = i + 1) {*/
		
		if (time > highscore_1){
			SRAM_write(HIGHSCORE_1_ADDRESS,time);
			return 1;
		}
		else if(time > highscore_2){
			SRAM_write(HIGHSCORE_2_ADDRESS,time);
			return 2;
		}
		else if(time > highscore_3){
			SRAM_write(HIGHSCORE_3_ADDRESS,time);
			return 3;
		}
		return 0;
		
		/*if (highscores[i] <= time) {
			for (uint8_t j = HIGHSCORES_LENGTH-1; j > i; j = j-1) {
				highscores[j] = highscores[j-1];  
			}
			
			highscores[i] = time;
		
		}	
	}*/
}

uint8_t MENU_get_hichscore_rank(uint8_t time) {
	for (uint8_t i = 0; i < HIGHSCORES_LENGTH; i = i+1) {
		if (highscores[i] == time) {
			return i;
		}
	}
	return 0;
}

void MENU_scream_mode (void){
	DDRB |= (1<<PB3);
	PORTB &= ~(1<<PB3);
	
}

void MENU_normal_mode (void){
	DDRB |= (1<<PB3);
	PORTB |=(1<<PB3);
	
}

void MENU_create(){

	//Initializing Main Menu
	main_menu.title = "Main Menu";
	main_menu.number_of_submenus = 0;
	main_menu.item = NULL_PTR;
	main_menu.parent = NULL_PTR;
	main_menu.submenus = malloc(sizeof(menu_t)*5);
	
	

	
	
	
	//menu_t* game_f = MENU_add_submenu("Play game", &GAME_play, &main_menu);
	menu_t* playgame_m = MENU_add_submenu("Play game", &MENU_play_game, &main_menu);
	menu_t* highscores_m = MENU_add_submenu("Highscores", &MENU_print_highscores, &main_menu);
	menu_t* settings_m = MENU_add_submenu("Settings", NULL_PTR, &main_menu);
	
	
	/*menu_t* tonja_m = MENU_add_submenu("Tonja", NULL_PTR, &main_menu);
	menu_t* karl_m = MENU_add_submenu("Karl", NULL_PTR, &main_menu);*/
	menu_t* rocket_f = MENU_add_submenu("Rocket", &MENU_print_rocket, &main_menu);
	//menu_t* clear_highscores_f = MENU_add_submenu("Cl", &MENU_clear_highscores, settings_m);
	menu_t* scream_mode_f = MENU_add_submenu("Scream Mode", &MENU_scream_mode, settings_m);
	menu_t* normal_mode_f = MENU_add_submenu("Normal Mode", &MENU_normal_mode, settings_m);
	
	/*menu_t* lillagenser_m = MENU_add_submenu("Lilla genser", NULL_PTR, tonja_m);
	menu_t* ocd_m = MENU_add_submenu("ocd", NULL_PTR, tonja_m);
	menu_t* regnbue_m = MENU_add_submenu("Regnbue", NULL_PTR, tonja_m);*/
	
	/*menu_t* kul_m = MENU_add_submenu("Kul", NULL_PTR, karl_m);
	menu_t* svartbukse_m = MENU_add_submenu("Svart bukse", NULL_PTR, lillagenser_m);*/
	//printf("first submenu is %s\n", main_menu.submenus[0]->title);
	
	current_menu = main_menu;
	
	//main_menu.number_of_submenus = 3;
	
	
	
}


void MENU_run_menu(void){
	
	MENU_display_menu(main_menu,0);
		while(!quit) {
			
			JOY_position_t pos = JOY_getPosition();
			/*printf("pos.X =  %d\npos.Y =  %d\n\n", pos.X,pos.Y);
			
			printf("ADC->X =  %d\nADC->Y =  %d\n\n", ADC_read(joyX),ADC_read(joyY));*/
			
			
			JOY_direction_t dir = JOY_getDirection();
		
			/*printf("dir: ");
			JOY_getDirectionString();
			printf("\n");*/
			menu_t choice = *current_menu.submenus[current_line];		
		
		 
		
				switch (dir) {	
			
					case up:
					
						if (current_line > 0 && last_direction == neutral) {
							current_line--;
							MENU_display_menu(current_menu, current_line);
						}
						last_direction = dir;
						_delay_ms(100);
						break;
				
					case down:
						//printf("menus %d\n",current_menu.number_of_submenus);
						if ((current_line < (current_menu.number_of_submenus-1)) && last_direction == neutral) {
							current_line++;
							printf("current line = %d\n", current_line);
						
							MENU_display_menu(current_menu, current_line);
						}
						last_direction = dir;
						_delay_ms(100);
						break;
			
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
				
					case left:	
						if(last_direction == neutral){
						MENU_back(current_menu);
							if (current_menu.parent != NULL_PTR) {
								current_menu = *current_menu.parent;
							}
							else {
								//quit = 1;
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


