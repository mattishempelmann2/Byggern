/*
 * uart.h
 *
 * Created: 04.09.2025 12:16:57
 *  Author: johankna
 */ 
#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>


#ifndef UART_H_
#define UART_H_




void UART_init(unsigned int ubrr);

int UART_transmit(char data, FILE * file);

int UART_receive(FILE * file);




#endif /* UART_H_ */