/*
 * uart.c
 *
 * Created: 04.09.2025 12:17:15
 *  Author: johankna
 */ 

#include "Uart.h"


UART_init(unsigned int ubrr){
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	fdevopen(UART_transmit, UART_receive);
}

int UART_transmit(char data, FILE * file){
	while(!( UCSR0A & (1<<UDRE0)));
	UDR0 = data;
	return 0;
}

int UART_receive(FILE * file){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
