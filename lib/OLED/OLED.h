

#ifndef OLED_H_
#define OLED_H_

#include <avr/pgmspace.h>
#include <util/delay.h>
#include "OLED_COMMANDS.h"
#include "../DEFINITIONS.h"



void OLED_test(void);
void OLED_clear_display(void);
void OLED_init(void);
void OLED_reset(void);
void OLED_home();
void OLED_goto_line(uint8_t line);
void OLED_goto_column(uint8_t column);
void OLED_clear_line(uint8_t line);
uint8_t OLED_pos(uint8_t row);
void OLED_print_char(char c);
void OLED_print_capital_char(char c);
void OLED_print_inverted_char(char c);
char* OLED_int_to_string(int integer);
void OLED_print_string(char c[]);
void OLED_print_header(char c[]);
void OLED_print_inverted_string(char c[]);


#endif /* OLED_H_ */