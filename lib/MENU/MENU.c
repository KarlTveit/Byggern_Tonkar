
#include "MENU.h"
#include "../JOY/JOY.h"
#include "../OLED/OLED.h"


void MENU_display_menu(menu_t menu, uint8_t curr_line) {
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
	p->submenus[p->number_of_submenus]->item = func;
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
		choice.item();
	}
	
}


void MENU_back(menu_t this) {
	
	if (this.parent != NULL_PTR) {
		MENU_display_menu(*this.parent,0);
	}
	else {
		OLED_clear_display();
		
		OLED_goto_line(4);
		OLED_goto_column(70);
		OLED_print_string("    Q U I T");
	
		OLED_print_rocket();
		
		
	}
	
	
}