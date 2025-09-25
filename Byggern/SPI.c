/*
 * SPI.c
 *
 * Created: 25.09.2025 13:09:37
 *  Author: mattisjh
 */ 


#include "SPI.h"

void init_SPI(){
	SPCR |= (1 << SPE) | (1<<MSTR) | (1 << SPR0); // enable SPI og set som master
	DDRB = (1 << PB5) | (1 << PB7) | (1 << PB4) | (1 << PB3) | (1 << PB2); // setter pb5 som output/MOSI pb7 som output/SCK, PB4. PB3, er SS PB2 er D!/C
	PORTB |= (1  << PB4) | (1 << PB3);
	
}

void clear_SPIF(){
	uint8_t static volatile dummy;
	dummy = SPSR;
	dummy = SPDR;
	return;
}


void spi_transmit(uint8_t Data, enum slave SS){
	printf("for\n\r");
	if( SS == IO){
		printf("etter\n\r");
		PORTB &= ~(1 << PB4);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF)));
		printf("spiferdig\n\r");
		PORTB |= (1 << PB4);
		clear_SPIF();
		return;
	}
	else if(SS == DISPLAY){
		PORTB &= ~(1 << PB3);
		SPDR = Data;
		while(!(SPSR & (1 << SPIF)));
		PORTB |= (1 << PB3);
		clear_SPIF();
		return;
	}
	return;
}

uint8_t spi_receive(enum slave SS){
	SPDR = 0x00;
	if(SS == IO){
		PORTB &= ~(1 << PB4);
		while(!(SPSR & (1 << SPIF)));
		PORTB |= (1 << PB4);
		return SPDR;
	}
	else if(SS == DISPLAY){
		PORTB &= ~(1 << PB3);
		while(!(SPSR & (1 << SPIF)));
		PORTB |= (1 << PB3);
		return SPDR;
	}
	return 'a';
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
		bytes[i] = spi_tranceive(bytes[i], SS);
		bytes[i] ++;
	}
	return;
}

	



//
// void SPI_MasterInit(void)
// {
// 	/* Set MOSI and SCK output, all others input */
// 	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
// 	/* Enable SPI, Master, set clock rate fck/16 */
// 	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
// }
// void SPI_MasterTransmit(char cData)
// {
// 	/* Start transmission */
// 	SPDR = cData;
// 	/* Wait for transmission complete */
// 	while(!(SPSR & (1<<SPIF)))
// 	;
// }
