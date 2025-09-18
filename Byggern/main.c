/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#include <avr/io.h>
#include "avr/iom162.h"
#include "uart.h"
#include "time.h"
#include "SRAM.h"

#define BAUD 9600 //Baud Rate
#define FOSC 4915200 //Clock speed
//#define MYUBRR FOSC/(16*BAUD)-1
#define MYUBRR 31
#define target_hz FOSC/2

int main(void)
{	
    /* Replace with your application code */
	//UART_init(MYUBRR);
  	//SRAM_init();
  	//SRAM_test();
	
	//printf("Ting funker!");
	
	
// 	DDRA = 0xFF;
	DDRD |= (1<<PD4);
	//OCR3A = 128;
	ICR3 = 1;
	OCR3A = 0;
// 	DDRE |= (1<<PE1);
// 	PORTA &= (0<<PA0);
	
// 		test av latch
// 		//PORTE |= (1<<PE1);
// 		PORTA |= (1<<PA0);
// 		PORTE &= (0<<PE1);
// 		PORTA &= (0<<PA0);

	TCCR3A |= (1<<COM3A1) | (1<<WGM31);
	TCCR3B |= (1<<WGM33) | (1<<WGM32) | (1<<CS30);

	
    while (1) 
    {
 		//UART_transmit('a');
		//printf("Ting funker!");
		//UART_transmit(UART_receive());
		
		//for(int n=0;n<10000;n++){
			//PORTA |= (1<<PA7);
		//}
		//for(int n=0;n<10000;n++){
			//PORTA &= (0<<PA7);
		//}
	}
}

