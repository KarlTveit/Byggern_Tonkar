/*
 * DEFINITIONS.h
 *
 * Created: 19.11.2017 05:36:28
 *  Author: karlmt
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


#define CLOCKS_PER_SEC	1000000


#define TRUE		1
#define FALSE		0
#define NULL_PTR	(void*)0


#define TIMER_VAL  0


//CAN message IDs
#define GAME_ID				100
#define GAMEOVER_DATA_ID	90
#define WIRELESS_ID			80

//CAN masks
#define TX0_IE_MASK			0b00000100
#define	RXB0_CTRL_MASK		0b01100000

#define RECEIVE_ANY			0b01100000

//Game message indexes
#define SERVO_REF			0
#define MOTOR_REF			2	
#define SOLENOID_ENABLE		3
#define GAME_ENABLE			7


//Menu properties
#define MAX_SUBMENUS		6


//Highscore
#define HIGHSCORE_1_ADDRESS		10
#define HIGHSCORE_2_ADDRESS		30
#define HIGHSCORE_3_ADDRESS		50
#define HIGHSCORES_LENGTH		3

//JOY
#define RIGHT_BUTTON		0b00000001
#define LEFT_BUTTON			0b00000010
#define JOY_BUTTON			0b00000100


//ADC
/*
#define ext_ram				((volatile char*) 0x1800)
#define ext_ram_size		0x800
#define ext_adc				((volatile char*) 0x1400)
*/


//OLED 
#define ext_oled_cmd		(volatile char*) 0x1000
#define ext_oled_data		(volatile char*) 0x1200

#define font5_size			5
#define columns_in_line		128
#define number_of_lines		8

#define ASCII_OFFSET				32
#define CAPITAL_LETTER_OFFSET		32
#define DISPLAY_OFF					0xae
#define SEGMENT_REMAP				0xa1
#define COMMON_PADS_HARDWARE		0xda
#define DISPLAY_ON					0xaf
#define SET_MEMORY_ADDRESSING_MODE	0x20
#define SET_PAGE_ADDRESSING_MODE	0x02

#define PAGE0	0xb0
#define	PAGE1	0xb1
#define PAGE2	0xb2
#define PAGE3	0xb3
#define PAGE4	0xb4
#define PAGE5	0xb5
#define PAGE6	0xb6
#define PAGE7	0xb7

#define FIRST_UPPER_COL		0x10
#define FIRST_LOWER_COL		0x00

#define CLEAR	0x00
#define FILL	0xFF


//SPI 
#define DD_SS		DDB4
#define DD_MOSI		DDB5
#define DD_MISO		DDB6
#define DD_SCK		DDB7
#define DDR_SPI		DDRB


//SRAM
#define SRAM_START_ADDRESS 1800


//Application data
#define PLAY	1
#define RESET	2
#define QUIT	3
#define SHOOT	250

#define SERVO_LOWER_LIM		5
#define SERVO_UPPER_LIM		30

#define MOTOR_LOWER_LIM		50
#define MOTOR_UPPER_LIM		230


//Motor
#define	LEFT	0
#define	RIGHT	1


//PWM
#define PWM_min		14
#define PWM_max		30

//Memory mapping


#define ADC_START_ADDRESS 0x1400
#define SRAM_START_ADDRESS 0x1800

#define ENABLE	0xFF

#endif /* DEFINITIONS_H_ */