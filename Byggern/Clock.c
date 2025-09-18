/*
 * Clock.c
 *
 * Created: 18.09.2025 15:10:24
 *  Author: johankna
 */ 

#include "Clock.h"

void Clock_init(){
		DDRD |= (1<<PD4);
		ICR3 = 1;
		OCR3A = 0;
		TCCR3A |= (1<<COM3A1) | (1<<WGM31);
		TCCR3B |= (1<<WGM33) | (1<<WGM32) | (1<<CS30);
}