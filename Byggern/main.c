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

int main(void)
{	
    /* Replace with your application code */
	UART_init(MYUBRR);
  	SRAM_init();
  	SRAM_test();
	
	//printf("Ting funker!");
	
	
// 	DDRA = 0xFF;
// 	DDRE |= (1<<PE1);
// 	PORTA &= (0<<PA0);
	
// 		test av latch
// 		//PORTE |= (1<<PE1);
// 		PORTA |= (1<<PA0);
// 		PORTE &= (0<<PE1);
// 		PORTA &= (0<<PA0);
	
	

	
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

