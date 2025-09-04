/*
 * uart.h
 *
 * Created: 04.09.2025 12:16:57
 *  Author: johankna
 */ 


#ifndef UART_H_
#define UART_H_

#define BAUD 9600 //Baud Rate
#define FOSC 4915200 //Clock speed


void UART_init();

void UART_transmit(unsigned char data);

unsigned char UART_receive();


#endif /* UART_H_ */