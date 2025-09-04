/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#include <avr/io.h>
#include "avr/iom162.h"
#include "uart.h"


int main(void)
{
	DDRA = 0xFF;
	PORTA |= (0<<PA7);
	
    /* Replace with your application code */
    while (1) 
    {
		for(int n=0;n<10000;n++){
			PORTA |= (1<<PA7);
		}
		for(int n=0;n<10000;n++){
			PORTA &= (0<<PA7);
		}
	}
}

