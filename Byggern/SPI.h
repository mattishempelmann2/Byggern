/*
 * SPI.h
 *
 * Created: 25.09.2025 13:09:48
 *  Author: mattisjh
 */ 



#include "Includes.h"

#ifndef SPI_H_
#define SPI_H_

enum slave{
	IO, DISPLAY, CAN
};


void init_SPI();

void spi_transmit(uint8_t Data, enum slave SS);

void spi_command_read(uint8_t command, enum slave SS, uint8_t* data, uint16_t length);

void clear_SPIF();

uint8_t spi_tranceive(uint8_t Data, enum slave SS);

void spi_tranceive_bytes(volatile uint8_t* bytes, int size, enum slave SS);

void spi_write_bytes(volatile uint8_t* bytes, int size, enum slave SS);

void spi_receive_bytes(volatile uint8_t* bytes, int size, enum slave SS);


void select_slave(enum slave SS);

void deselect_slave(enum slave SS);

uint8_t spi_transfer(uint8_t data);

void spi_write(uint8_t data);

uint8_t spi_read(void);

void spi_read_bytes(uint8_t* data, uint16_t length);





#endif /* SPI_H_ */