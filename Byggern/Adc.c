/*
 * Adc.c
 *
 * Created: 23.09.2025 12:12:33
 *  Author: johankna
 */ 

#include "Adc.h"


#define adc_adress 0x1000 // start adresse
#define adc_channels 4

static volatile uint8_t * const adcVal = (volatile uint8_t *)adc_adress;

static uint8_t adcData[adc_channels];



void ADC_init(){
	Clock_init();
	SRAM_init();
		
}


volatile uint8_t * adc_read(void){
	*adcVal = 0;
	
	for(uint8_t i = 0; i < adc_channels; i++){
		adcData[i] = *adcVal;
		_NOP();
	}
	return adcData;
}
