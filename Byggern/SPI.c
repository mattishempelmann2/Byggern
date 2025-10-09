/*
 * SPI.c
 *
 * Created: 25.09.2025 13:09:37
 *  Author: mattisjh
 */ 


#include "SPI.h"

void init_SPI(){
	SPCR |= (1 << SPE) | (1<<MSTR) | (1 << SPR0); // enable SPI og set som master
	DDRB = (1 << PB5) | (1 << PB7) | (1 << PB4) | (1 << PB3) | (1 << PB2) | (1 << PB1); // setter pb5 som output/MOSI pb7 som output/SCK, PB4. PB3, PB2, er SS PB1 er D!/C
	PORTB |= (1  << PB4) | (1 << PB3) | (1 << PB2) | (1<<PB1);
	
}

void select_slave(enum slave SS) {
	if (SS == IO) {
		PORTB &= ~(1 << PB4);
	}
	else if (SS == DISPLAY) {
		PORTB &= ~(1 << PB3);
	}
	else if (SS==CAN){
		PORTB &= ~(1<<PB2);
	}
}

void deselect_slave(enum slave SS) {
	if (SS == IO) {
		PORTB |= (1 << PB4);
	}
	else if (SS == DISPLAY) {
		PORTB |= (1 << PB3);
	}
	else if (SS==CAN){
		PORTB |= (1<<PB2);
	}
}



void spi_write_bytes(volatile uint8_t* bytes, int size, enum slave SS){
	select_slave(SS);
	for(uint8_t i = 0; i < size; i++){
		spi_transfer(bytes[i]);
			if (i==0){
				_delay_us(50);
			}
			else{
				_delay_us(5);
			}
		}
		deselect_slave(SS);
	return;
	};



uint8_t spi_transfer(uint8_t data) {
	SPDR = data;
	
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}
	

void spi_command_read(uint8_t command, enum slave SS, uint8_t* data, uint16_t length){
	select_slave(SS);
	spi_transfer(command);
	_delay_us(50);
	for(uint8_t i = 0; i < length; i++){
		data[i] = spi_transfer(0x00);
		_delay_us(5);
	}
	deselect_slave(SS);
}

