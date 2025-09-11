/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#include <avr/io.h>
#include "avr/iom162.h"
#include "uart.h"

#define BAUD 9600 //Baud Rate
#define FOSC 4915200 //Clock speed
//#define MYUBRR FOSC/(16*BAUD)-1
#define MYUBRR 31

int main(void)
{
	//DDRA = 0xFF;
	//PORTA |= (0<<PA7);
	
    /* Replace with your application code */
	UART_init(MYUBRR);
	printf("Ting funker!");
    while (1) 
    {
		//UART_transmit('a');
		//UART_transmit(UART_receive());
		
		//for(int n=0;n<10000;n++){
			//PORTA |= (1<<PA7);
		//}
		//for(int n=0;n<10000;n++){
		//	PORTA &= (0<<PA7);
		//}
	}
}

