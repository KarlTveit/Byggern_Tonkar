

#ifndef ADC_H_
#define ADC_H_

#define ext_ram         ((volatile char*) 0x1800)
#define ext_ram_size    0x800
#define ext_adc         ((volatile char*) 0x1400)





//#include "IncFile1.h"
#include "stdio.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "../DEFINITIONS.h"
#include "../UART/UART.h"


typedef enum{
	joyY = 0x4,
	joyX = 0x5,
	IR = 0x3,
	right_slider = 0x6,
	left_slider = 0x7
}channel;




uint8_t ADC_read(channel joystick);
void ADC_init(void);

#endif /* ADC_H_ */