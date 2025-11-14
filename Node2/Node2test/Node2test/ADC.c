/*
 * ADC.c
 *
 * Created: 30.10.2025 13:43:38
 *  Author: mattisjh
 */ 
#include "ADC.h"

void ADC_init(){
	PMC->PMC_PCER1 |= (1u << (ID_ADC-32));
	//ADC->ADC_WPMR = (0x414443 << 8) | 0b1; //removed write protect, unsure if needed for ADC
	
	ADC->ADC_MR = ADC_MR_PRESCAL(2) | ADC_MR_STARTUP_SUT64 | ADC_MR_TRACKTIM(2) | ADC_MR_FREERUN_ON; // clk CONFIG
	PIOB->PIO_PDR |= PIO_PDR_P17; // disable PIO for PB17, no idea why this is right
	ADC->ADC_CHER = ADC_CHER_CH5; // channel select A2 CH5 and PB17 for some reason??????
	ADC->ADC_CR = ADC_CR_START; // start?

}

uint16_t adc_read(){
	while(!(ADC->ADC_ISR & ADC_ISR_EOC5)){	
}
	return ADC->ADC_CDR[5];
}

uint16_t count_score(uint16_t* previous_result){
	uint16_t result = 0;
	if (adc_read() < 2000 && !*previous_result ){
		result = 1;
		// 		for(int i =0;i<10000;i++){
		// 			result = result;
		// 		}
	}
	else if (adc_read() > 2000 && *previous_result){
			*previous_result = 0;
	}
	return result;
}
