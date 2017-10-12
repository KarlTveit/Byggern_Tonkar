#include <avr/io.h>
#include <avr/interrupt.h>

int UART_Init(unsigned int ubrr);

int UART_Transmit(unsigned char data);

unsigned char UART_Recieve(void);