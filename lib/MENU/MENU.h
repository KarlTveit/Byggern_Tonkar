/*
 * MENU.h
 *
 * Created: 27.09.2017 14:19:38
 *  Author: tonjaj
 */ 


#ifndef MENU_H_
#define MENU_H_

/*
#define MAX_SUBMENUS 6
#define NULL_PTR (void*)0
#define CLOCKS_PER_SEC 1000000

#define TRUE 1
#define FALSE 0
#define HIGHSCORE_1_ADDRESS 0x10
#define HIGHSCORE_2_ADDRESS 0x30
#define HIGHSCORE_3_ADDRESS 0x50 
#define HIGHSCORES_LENGTH 3*/

#include "stdint.h"
#include "../DEFINITIONS.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include "../SRAM/SRAM.h"
/*#include "../GAME/GAME.h"*/
#include "../CAN_DEFINES/CAN_DEFINES.h"
#include "../EEPROM/EEPROM.h"
struct menu_t{
	char* title;
	void (*item)();
	uint8_t number_of_submenus;
	struct menu_t** submenus;
	struct menu_t* parent;
}; 

typedef struct menu_t menu_t;
void MENU_create(void);
void MENU_display_menu(menu_t menu, uint8_t curr_line );
menu_t* MENU_add_submenu(char* t, void(*func)(), /*uint8_t num,*/ /*menu_t** sub,*/ menu_t* p);
void MENU_back(menu_t this);

menu_t MENU_get_current_menu(void);

void MENU_play_game(void);
void MENU_print_rocket();
void MENU_clear_highscores(void);
void MENU_print_highscores(void);
uint8_t MENU_update_highscores(uint8_t time);
uint8_t MENU_get_hichscore_rank(uint8_t time);

void MENU_scream_mode (void);
void MENU_normal_mode (void);

void MENU_choose(menu_t choice);
void MENU_run_menu(void);


#endif /* MENU_H_ */