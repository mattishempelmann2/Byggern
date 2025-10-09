/*
 * MCP2515.c
 *
 * Created: 09.10.2025 12:34:42
 *  Author: johankna
 */ 
#include "MCP2515.h"

void mcp2515_read(uint8_t* data, uint8_t address, uint8_t length){
	uint8_t command = 0x03;
	select_slave(CAN);
	spi_transfer(command);
	_delay_us(50);
	spi_command_read(address, CAN, data, length);
	
}
void mcp2515_write(uint8_t* data,uint8_t address,uint8_t length){
	uint8_t command = 0x02;
	select_slave(CAN);
	spi_transfer(command);
	_delay_us(50);
	spi_transfer(address);
	_delay_us(50);
	spi_write_bytes(data,length,CAN);
	
}
void mcp2515_request_to_send(uint8_t n){
	uint8_t command = (0x80 | n);
	select_slave(CAN);
	spi_transfer(command);
	deselect_slave(CAN);
}

uint8_t mcp2515_read_status(){
	uint8_t command = 0xA0;
	select_slave(CAN);
	spi_transfer(command);
	uint8_t data = spi_transfer(0);
	deselect_slave(CAN);
	return data;
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	uint8_t command = 0x05;
	select_slave(CAN);
	spi_transfer(command);
	spi_transfer(address);
	spi_transfer(mask);
	spi_transfer(data);
	deselect_slave(CAN);
}


void mcp2515_reset() {
	uint8_t command = 0xC0;
	select_slave(CAN);
	spi_transfer(command);  
	deselect_slave(CAN);
	_delay_ms(10);       
}


void mcp2515_init ()
{
	mcp2515_reset ();
	// Set the mode to config mode
	uint8_t CCR = 0xF; // can_controll_register
	uint8_t CCR_mask = 0b11100000;
	uint8_t CCR_data = 0b10000000;
	mcp2515_bit_modify(CCR, CCR_mask,CCR_data);

	// Disable the receive filtrers. It is only for debugging
	uint8_t RBC = 0x60; // Receive buffer 0 controll address
	uint8_t RBC_mask = 0b01100000;
	uint8_t RBC_data = 0b01100000;
	mcp2515_bit_modify(RBC, RBC_mask, RBC_data);

	
	// Set the mode to Loopback: REMOVE AFTER EXERCISES
	uint8_t CCR = 0xF; // can_controll_register 
	uint8_t CCR_mask = 0b11100000;
	uint8_t CCR_data = 0b01000000;
	mcp2515_bit_modify(CCR, CCR_mask,CCR_data);

	
	return 0;
}