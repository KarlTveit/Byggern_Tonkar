/*
 * Byggern134.c
 *
 * Created: 30.08.2017 10:04:34
 *  Author: karlmt
 */ 

#define F_CPU 4915200 // clock frequency in Hz
#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "stdio.h"



#include "../lib/UART/UART.h"
#include "../lib/ADC/ADC.h"
#include "../lib/JOY/JOY.h"
#include "../lib/SRAM/SRAM.h"
#include "../lib/OLED/OLED.h"
#include "../lib/MENU/MENU.h"
#include "../lib/SPI/SPI.h"
#include "../lib/MCP2515/MCP2515.h"
#include "../lib/CAN/CAN.h"






uint8_t RECEIVED = 0;

ISR(USART0_RXC_vect)
{
	RECEIVED = 1;
	
	unsigned char temp = UDR0;
	UART_Transmit(temp); // for å teste at det funker
}






int main(void)
{
	_delay_ms(10);

	DDRA = 0xFF;

	UART_Init(UBRR);
	fdevopen(&UART_Transmit, &UART_Recieve);
	init_SRAM();
	
	
	OLED_init();
	OLED_clear_display();
	OLED_goto_line(0);
	OLED_goto_column(0);
	
	
	SPI_init();
	printf("Etter OLED \n");
	while(1) {
		_delay_ms(100);
		SPI_read(0b01010101);
		printf("Her er jeg \n");
		//SPI_send(0b00000001);
	}
	
	
	
	/*
	************************
			M E N U 
			
	************************
	*/
	
	
	static menu_t main_menu;
	static menu_t current_menu;
	
	//Initializing Main Menu
	main_menu.title = "Main Menu";
	main_menu.number_of_submenus = 0;
	main_menu.item = NULL_PTR;
	main_menu.parent = NULL_PTR;
	main_menu.submenus = malloc(sizeof(menu_t)*5);
	
	
	static uint8_t current_line = 0; // første linje er linjen under tittel
	static JOY_direction_t last_direction = neutral; 
	
	static unsigned int quit = 0;	//bool
	
	
	
		
	menu_t* settings_m = MENU_add_submenu("Settings", NULL_PTR, &main_menu);
	menu_t* tonja_m = MENU_add_submenu("Tonja", NULL_PTR, &main_menu);
	menu_t* karl_m = MENU_add_submenu("Karl", NULL_PTR, &main_menu);
	
	
	menu_t* lillagenser_m = MENU_add_submenu("Lilla genser", NULL_PTR, tonja_m);
	menu_t* ocd_m = MENU_add_submenu("ocd", NULL_PTR, tonja_m);
	menu_t* regnbue_m = MENU_add_submenu("Regnbue", NULL_PTR, tonja_m);
	
	menu_t* kul_m = MENU_add_submenu("Kul", NULL_PTR, karl_m);
	menu_t* svartbukse_m = MENU_add_submenu("Svart bukse", NULL_PTR, lillagenser_m);
	//printf("first submenu is %s\n", main_menu.submenus[0]->title);
		
	current_menu = main_menu;
	
	//main_menu.number_of_submenus = 3;
	
	
	MENU_display_menu(main_menu,0);
	while(!quit) {
		
		
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
					printf("menus %d\n",current_menu.number_of_submenus);
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
							quit = 1;
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
	
		
	
	
	
	
	


	








	JOY_init();
	while(1) {
		//JOY_calibrate();	//DENNE KLIKKER HJELP HVA SKJER
		/*_delay_ms(1000);
		printf("(%d,%d)\n", ADC_read(joyX),ADC_read(joyY));
		printf("(%d,%d)\n", JOY_getPosition().X,JOY_getPosition().Y);
		
		JOY_getDirectionString();*/
		
		
		//OLED_test();
		//printf("(%d)\n", ADC_read(joyX));	
	}

 
}