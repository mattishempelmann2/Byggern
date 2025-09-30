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
#include "util/delay.h"

#ifndef SPI_H_
#define SPI_H_

enum slave{
	IO, DISPLAY
};


void init_SPI();

void spi_transmit(uint8_t Data, enum slave SS);

uint8_t spi_receive(enum slave SS);

void clear_SPIF();

uint8_t spi_tranceive(uint8_t Data, enum slave SS);

void spi_tranceive_bytes(volatile uint8_t* bytes, int size, enum slave SS);

void spi_transmit_bytes(volatile uint8_t* bytes, int size, enum slave SS);

void spi_receive_bytes(volatile uint8_t* bytes, int size, enum slave SS);







#endif /* SPI_H_ */