/*
 * Adc.h
 *
 * Created: 23.09.2025 12:12:45
 *  Author: johankna
 */ 
#include <avr/io.h>
#include "avr/iom162.h"

#ifndef ADC_H_
#define ADC_H_


void ADC_init();
uint8_t adc_read(uint8_t channel); //volatile



#endif /* ADC_H_ */