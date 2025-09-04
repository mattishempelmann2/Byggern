/*
 * uart.c
 *
 * Created: 04.09.2025 12:17:15
 *  Author: johankna
 */ 

#include "uart.h"
#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>

UART_init(){
	unsigned int ubrr = FOSC/16/(BAUD-1);
	//Set all registers to desired value
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

UART_transmit(unsigned char data){
	while(!( UCSR0A & (1<<UDRE0)));
	
	UDR0 = data;
}

unsigned char UART_receive(){
	while(!(UCSR0A & (1<<RXC0)));
	
	return UDR0;
}