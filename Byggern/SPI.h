/*
 * SPI.h
 *
 * Created: 25.09.2025 13:09:48
 *  Author: mattisjh
 */ 


#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>
#include "Adc.h"
#include "avr/cpufunc.h"

#ifndef SPI_H_
#define SPI_H_

enum slave{
	IO, DISPLAY
};

void init_SPI();

void spi_transmit(char Data, enum slave SS);

char spi_receive(enum slave SS);



#endif /* SPI_H_ */