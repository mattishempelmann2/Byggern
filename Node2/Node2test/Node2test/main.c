/*
 * Node2test.c
 *
 * Created: 21.10.2025 13:48:55
 * Author : mattisjh
 */ 


#include "includes.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	PMC->PMC_PCER0 = (1u << ID_PIOB); // enables PIOB clock
	
	PIOB->PIO_PER = (1u << 13); //PB13 to GPIO
	
	PIOB->PIO_OER   = (1u << 13); // configure as output
	PIOB->PIO_PUDR  = (1u << 13); // disables pull up                   
	PIOB->PIO_MDDR  = (1u << 13); // push-pull
	
	PIOB->PIO_SODR = (1u << 13); // sets pin high

	uart_init(F_CPU, 9600);
	uint8_t value = 'a';
	uint8_t tall = 1;
	uart_tx(value);
	

    while (1) 
    {
        if (uart_rx(&value)){    
	        uart_tx(value);
        }
	}
}
