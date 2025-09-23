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
volatile uint8_t * adc_read(void); //volatile



#endif /* ADC_H_ */