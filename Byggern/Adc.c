/*
 * Adc.c
 *
 * Created: 23.09.2025 12:12:33
 *  Author: johankna
 */ 
#include "Clock.h"
#include "Adc.h"
#include "SRAM.h"



void ADC_init(){
	Clock_init(); 
	SRAM_init(); //For å sett A pinsan til både data og adresser. Maskerer ut de pinsa som JTAG bruker
	
	volatile char *ADC = (char *) 0x1000; // Start address for the SRAM
	uint16_t ADC_size = 0x400;
	ADC[0] = 0;
	//initialize ADC by putting the correct registers to the correct values
	
	
	//Somehow write a value to the ADC
	
}


volatile uint8_t adc_read(uint8_t channel){
	
	return 0;
}
