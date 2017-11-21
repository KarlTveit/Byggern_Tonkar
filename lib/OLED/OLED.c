

#include "OLED.h"
#include "fonts.h"
#include "..\JOY\JOY.h"
#include "..\MENU\MENU.h"


static uint8_t current_line = 0;



void OLED_init ()
{
	volatile char *addresse = ext_oled_cmd;
	
	*addresse = DISPLAY_OFF;					//display  off *(adresse+0xae)
	*addresse = SEGMENT_REMAP;					//segment  remap
	*addresse = COMMON_PADS_HARDWARE;			//common  pads  hardware:  alternative
	*addresse = 0x12;
	*addresse = 0xc8;							//common
	//output scan direction:com63~com0
	*addresse = 0xa8;							//multiplex  ration  mode:63
	*addresse = 0x3f;
	*addresse = 0xd5;							//display
	//divide ratio/osc. freq. mode
	*addresse = 0x80;
	*addresse = 0x81;							//contrast  control
	*addresse = 0x50;
	*addresse = 0xd9;							//set  pre-charge  period
	*addresse = 0x21;
	*addresse = SET_MEMORY_ADDRESSING_MODE;     //Set  Memory  Addressing  Mode
	*addresse = SET_PAGE_ADDRESSING_MODE;
	*addresse = 0xdb;							//VCOM  deselect  level  mode
	*addresse = 0x30;
	*addresse = 0xad;							//master  configuration
	*addresse = 0x00;
	*addresse = 0xa4;							//out  follows  RAM  content
	*addresse = 0xa6;							//set  normal  display
	*addresse = DISPLAY_ON;						//  display  on
	DDRB &= ~(1<<PB1);
	DDRB &= ~(1<<PB2);

}


void OLED_clear_display(void){
	 
	 uint8_t c = PAGE0;
	for(uint8_t p = 0; p < number_of_lines;p++) {
 		*ext_oled_cmd = c++;
 		*ext_oled_cmd = FIRST_UPPER_COL;
		*ext_oled_cmd = FIRST_LOWER_COL;
	
	

		for (uint8_t i = 0; i< columns_in_line; i++) {
			*ext_oled_data = CLEAR;
		}
	}
	
	current_line = 0;
	
	OLED_goto_line(0);

}		

//Going to a line from 0 to 7	
void OLED_goto_line(uint8_t line){	
	
	
	*ext_oled_cmd = PAGE0 + line;
	*ext_oled_cmd = FIRST_UPPER_COL;
	*ext_oled_cmd = FIRST_LOWER_COL;
	
	current_line = line;
	
}

//Going to a column from 0 to 127
void OLED_goto_column(uint8_t column){
	
	*ext_oled_cmd = 0x10+((column & 0xf0)>>4);
	*ext_oled_cmd = column & 0x0f;
	
}

//Clearing a line
void OLED_clear_line(uint8_t line) {
	OLED_goto_line(line);
	for (uint8_t i = 0; i < columns_in_line; i++) {
		*ext_oled_data = CLEAR;
		_delay_ms(10);
	}
}

uint8_t OLED_pos(uint8_t row){
	return current_line;
}

//Printing a character to the OLED
void OLED_print_char(char c){
	for (int i = 0; i < font5_size; i++) {
		*ext_oled_data = pgm_read_byte(&(font5[c - ASCII_OFFSET][i]));
	}

}


void OLED_print_capital_char(char c){
	for (int i = 0; i < font5_size; i++) {
		*ext_oled_data = pgm_read_byte(&(font5[c - ASCII_OFFSET - CAPITAL_LETTER_OFFSET][i]));
	}

}

//Printing a character in black with a white bacground
void OLED_print_inverted_char(char c){
	for (int i = 0; i < font5_size; i++) {
		*ext_oled_data = ~pgm_read_byte(&((font5[c - ASCII_OFFSET][i])));
	}

}

//Printing a string to the OLEd	
void OLED_print_string(char c[]){
	
	uint8_t str_index = 0;
	uint8_t line_index = 0;
	OLED_goto_column(64-((strlen(c)*font5_size)/2));
	while (c[str_index] != '\0') {
		line_index++;
		
		OLED_print_char(c[str_index++]);
		if (line_index > 122/font5_size) {
			line_index = 0;
			OLED_goto_line(++current_line);
			
		}
	}
	
	
}

//Printing a string in all caps at the top of the OLED
void OLED_print_header(char c[]){
	
	uint8_t str_index = 0;
	uint8_t line_index = 0;
	OLED_goto_column(64-((strlen(c)*5)/2));
	
	while (c[str_index] != '\0') {
		line_index++;
		if (c[str_index] >= 97 && c[str_index] <= 122) {
			OLED_print_capital_char(c[str_index++]);
		}
		else {
			OLED_print_char(c[str_index++]);
		}
		if (line_index > 122/font5_size) {
			line_index = 0;
			OLED_goto_line(++current_line);
			
		}
	}
	
	
}

//Converting an integer to a string
char* OLED_int_to_string(int integer){
	int n;
	if (integer == 0){
		n = 1;
	}
	else{
		n = floor(log10(integer)+1);
	}
	char result[n+1];
	itoa(integer,result, 10);
	return result;
	
}


//Printing a black string with white background
void OLED_print_inverted_string(char c[]) {
	
	for (uint8_t i = 0; i < columns_in_line; i++) {
		*ext_oled_data = FILL;
	
	}
	
	
	uint8_t str_index = 0;
	uint8_t line_index = 0;
	uint8_t start_index_centralized = 64-((strlen(c)*font5_size)/2);
	OLED_goto_column(start_index_centralized);
	while (c[str_index] != '\0') {
		line_index++;
		OLED_print_inverted_char(c[str_index++]);
		
		if (line_index > 122/font5_size) {
			line_index = 0;
			OLED_goto_line(++current_line);
			
		}
	
	
	}
}



