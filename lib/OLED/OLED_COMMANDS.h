/*
 * OLED_COMMANDS.h
 *
 * Created: 22.09.2017 13:30:08
 *  Author: tonjaj
 */ 


#ifndef OLED_COMMANDS_H_
#define OLED_COMMANDS_H_

#define ASCII_OFFSET 32
#define CAPITAL_LETTER_OFFSET 32
#define DISPLAY_OFF 0xae
#define SEGMENT_REMAP 0xa1
#define COMMON_PADS_HARDWARE 0xda 
#define DISPLAY_ON 0xaf
#define SET_MEMORY_ADDRESSING_MODE 0x20
#define SET_PAGE_ADDRESSING_MODE 0x02

/*
#define SET_UPPER_COLUMN 
#define SET_LOWER_COLUMN 0xf0*/


#define PAGE0 0xb0
#define	PAGE1 0xb1
#define PAGE2 0xb2
#define PAGE3 0xb3
#define PAGE4 0xb4
#define PAGE5 0xb5
#define PAGE6 0xb6
#define PAGE7 0xb7

#define FIRST_UPPER_COL 0x10
#define FIRST_LOWER_COL 0x00

//for OLED data
#define CLEAR 0x00
#define FILL 0xFF



#endif /* OLED_COMMANDS_H_ */