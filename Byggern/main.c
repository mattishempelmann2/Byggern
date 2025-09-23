/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#include <avr/io.h>
#include "avr/iom162.h"
#include "Uart.h"
#include "time.h"
#include "SRAM.h"
#include "Joystick.h"
#include "Adc.h"

#define BAUD 9600 //Baud Rate
#define FOSC 4915200 //Clock speed
#define MYUBRR 31



int main(void)
{	
	UART_init(MYUBRR);
	ADC_init();
	
	//Clock_init();

    while (1) 
    {
		volatile uint8_t *p = adc_read();
		printf("Verdi på 0 = %u\n\r", *p);
		printf("Verdi på 1 = %u\n\r", *(p+1));
		printf("Verdi på 2 = %u\n\r", *(p+2));
		printf("Verdi på 3 = %u\n\r", *(p+3));

	}
}

