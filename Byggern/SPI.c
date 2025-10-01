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
	PORTB |= (1  << PB4) | (1 << PB3) | (1 << PB2);
	
}

void clear_SPIF(){
	uint8_t static volatile dummy;
	dummy = SPSR;
	dummy = SPDR;
	return;
}


void spi_transmit(uint8_t Data, enum slave SS){
	if( SS == IO){
		PORTB &= ~(1 << PB4);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF))); 
		clear_SPIF();
		return;
	}
	else if(SS == DISPLAY){
		PORTB &= ~(1 << PB3);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF)));
		clear_SPIF();
		return;
	}
	return;
}


uint8_t spi_tranceive(uint8_t Data, enum slave SS){
	volatile uint8_t motatt;
	static volatile uint8_t kast;
	if( SS == IO){
		PORTB &= ~(1 <<PB4);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF)));
		kast = SPSR;
		motatt = SPDR;
		PORTB |= (1 << PB4);
		return motatt;
		}
	else if(SS == DISPLAY){
		PORTB &= ~(1 <<PB3);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF)));
		kast = SPSR;
		motatt = SPDR;
		PORTB |= (1 << PB3);
		return motatt;
		}
	return 'a';
	}
	

void spi_tranceive_bytes(volatile uint8_t* bytes, int size, enum slave SS){
	for(uint8_t i = 0; i < size; i++){
		bytes[i] = spi_tranceive(bytes[i], SS) + 1;
	}
	
	return;
}

void spi_transmit_bytes(volatile uint8_t* bytes, int size, enum slave SS){
	for(uint8_t i = 0; i < size; i++){
		spi_transmit(bytes[i], SS);
			if (i==0){
				_delay_us(40);
			}
			else{
				_delay_us(2);
			}
		}
		clear_PB4(SS);
	return;
	};

void spi_receive_bytes(volatile uint8_t* bytes, int size, enum slave SS){
	printf("\n\r");
	for(uint8_t i = 0; i < size; i++){
		uint8_t temp = spi_receive(SS);
		printf("%c, ",temp);
		bytes[i] = temp;
		_delay_ms(20);
		}
		_delay_us(500);
		clear_PB4(SS);
		printf("\n\r");
	return;
}

void select_slave(enum slave SS) {
	if (SS == IO) {
		PORTB &= ~(1 << PB4);
		}
	else if (SS == DISPLAY) {
		PORTB &= ~(1 << PB3);
	}
}

void deselect_slave(enum slave SS) {
	if (SS == IO) {
		PORTB |= (1 << PB4);
	}
	else if (SS == DISPLAY) {
		PORTB |= (1 << PB3);
		} 
}

uint8_t spi_transfer(uint8_t data) {
	SPDR = data;
	
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

void spi_write(uint8_t data) {spi_transfer(data);}
	
uint8_t spi_read(void) { return spi_transfer(0x01); }
	
void spi_read_bytes(uint8_t* data, uint16_t length){
	for(uint16_t i = 0; i < length; i++){
		data[i]=spi_read();
		_delay_us(2);
	}
}


void spi_receive(uint8_t command, enum slave SS, uint8_t* data, uint16_t length){
	select_slave(SS);
	spi_write(command);
	spi_read_bytes(data, length);
	deselect_slave(SS);
}

