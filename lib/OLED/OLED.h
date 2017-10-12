

#ifndef OLED_H_
#define OLED_H_

//#include "fonts.h"
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "OLED_COMMANDS.h"

#define ext_oled_cmd    ((volatile char*) 0x1000)
#define ext_oled_data ((volatile char*) 0x1200)

void OLED_test(void);
void OLED_clear_display(void);
void OLED_init(void);
void OLED_reset(void);
void OLED_home();
void OLED_goto_line(uint8_t line);
void OLED_goto_column(uint8_t column);
void OLED_clear_line(line);
void OLED_pos(uint8_t row/*,uint8_t column*/);


void OLED_print_char(char c);
void OLED_print_capital_char(char c);
void OLED_print_inverted_char(char c);
void OLED_print_emphasized_inverted_char(char c);


void OLED_set_brightness(lvl);

void OLED_print_string(char c[]);
void OLED_print_header(char c[]);
void OLED_print_inverted_string(char c[]);
void OLED_emphasized_inverted_string(char c[]);



void OLED_print_rocket();

#endif /* OLED_H_ */