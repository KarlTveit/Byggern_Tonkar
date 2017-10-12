/*
 * MENU.h
 *
 * Created: 27.09.2017 14:19:38
 *  Author: tonjaj
 */ 


#ifndef MENU_H_
#define MENU_H_

#define MAX_SUBMENUS 6
#define NULL_PTR (void*)0

#include "stdint.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


struct menu_t{
	char* title;
	void (*item)();
	uint8_t number_of_submenus;
	struct menu_t** submenus;
	struct menu_t* parent;
}; 

typedef struct menu_t menu_t;

void MENU_display_menu(menu_t menu, uint8_t curr_line );
menu_t* MENU_add_submenu(char* t, void(*func)(), /*uint8_t num,*/ /*menu_t** sub,*/ menu_t* p);
void MENU_back(menu_t this);
void MENU_choose(menu_t choice);


#endif /* MENU_H_ */