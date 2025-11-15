/*
 * ADC.c
 *
 * Created: 30.10.2025 13:43:38
 *  Author: mattisjh
 */ 
#include "ADC.h"

void ADC_init(){
	PMC->PMC_PCER1 |= (1u << (ID_ADC-32));
	
	ADC->ADC_MR = ADC_MR_PRESCAL(2) | ADC_MR_STARTUP_SUT64 | ADC_MR_TRACKTIM(2) | ADC_MR_FREERUN_ON; // clk CONFIG = 14Mhz, freerun so it always measures
	ADC->ADC_CHER = ADC_CHER_CH5; //select channel 5
	ADC->ADC_CR = ADC_CR_START; // start
	
}

uint16_t adc_read(){
	while(!(ADC->ADC_ISR & ADC_ISR_EOC5)){	
}
	return ADC->ADC_CDR[5];
}

uint16_t count_score(uint16_t* previous_result){
	uint16_t result = 0;
	if (adc_read() < 1600 && !*previous_result){

		result = 1;
	}
	else if (adc_read() > 3000 && *previous_result){

			*previous_result = 0;
	}
	return result;
}
