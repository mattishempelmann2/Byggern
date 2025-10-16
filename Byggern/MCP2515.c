/*
 * MCP2515.c
 *
 * Created: 09.10.2025 12:34:42
 *  Author: johankna
 */ 
#include "MCP2515.h"

void mcp2515_read(uint8_t* data, uint8_t address, uint8_t length){
	select_slave(CAN);
	spi_transfer(MCP_READ);
	_delay_us(50);
	spi_command_read(address, CAN, data, length);
	
}
void mcp2515_write(uint8_t* data,uint8_t address,uint8_t length){
	select_slave(CAN);
	spi_transfer(MCP_WRITE);
	_delay_us(50);
	spi_transfer(address);
	_delay_us(50);
	spi_write_bytes(data,length,CAN);
	
}
void mcp2515_request_to_send(uint8_t buffer_number){
	uint8_t command;
	switch (buffer_number)
	{
	case 0:
		command = MCP_RTS_TX0;
		break;
	case 1:
		command = MCP_RTS_TX1;
		break;
	case 2:
		command = MCP_RTS_TX2;
		break;
	case 3:
		command = MCP_RTS_ALL;
		break;
	default:
		return;
	}
	select_slave(CAN);
	spi_transfer(command);
	deselect_slave(CAN);
}

uint8_t mcp2515_read_status(){
	select_slave(CAN);
	spi_transfer(MCP_READ_STATUS);
	uint8_t data = spi_transfer(0);
	deselect_slave(CAN);
	return data;
}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	select_slave(CAN);
	spi_transfer(MCP_BITMOD);
	spi_transfer(address);
	spi_transfer(mask);
	spi_transfer(data);
	deselect_slave(CAN);
}


void mcp2515_reset() {
	select_slave(CAN);
	spi_transfer(MCP_RESET);  
	deselect_slave(CAN);
	_delay_ms(10);       
}

void mcp2515_load(CANMessage message, uint8_t address_point) {
	// IF address_point is 000 = ID, if is 001 goes to data
	// If addres_point is 01X indicates which buffer to use
	uint8_t command = (0b01000000 | address_point);
	uint8_t ID_high; uint8_t ID_low;
	uint8_t DIR_register;
	
	ID_high	= message.id >> 3; 
	ID_low = (message.id & 0b00000111) << 5;
	
	DIR_register = (message.data_length & 0b00001111);
	select_slave(CAN);
	spi_transfer(command);
	spi_transfer(ID_high);
	spi_transfer(ID_low);
	// This is for standard ID (11 bits)
	uint8_t extended_id[] = {0,0};
	spi_write_bytes(extended_id,2,CAN);
	
	command = (0b01000000 | address_point+1);
	select_slave(CAN);
	spi_transfer(command);
	spi_transfer(DIR_register);
	spi_write_bytes(message.data,message.data_length,CAN);
	deselect_slave(CAN);
}

// @params buffer_number: [0-1]
// This problably wont work due to the change of the command_read in cs
void mcp2515_read_rx(uint8_t buffer_number, uint8_t* output){
	uint8_t command = 0b10010000 | (buffer_number << 1);
	spi_command_read(command,CAN, output, 20);
}



void mcp2515_init ()
{
	mcp2515_reset ();
	
	// Set the mode to config mode
	uint8_t CCR = 0x0F; // can_controll_register
	uint8_t CCR_mask = 0b11100000;
	uint8_t CCR_data = 0b10000000;
	mcp2515_bit_modify(CCR, CCR_mask,CCR_data);
	
	// Give some time to change config
	_delay_ms(10);

	// Disable the receive filtrers. It is only for debugging
	uint8_t RBC0 = 0x60; // Receive buffer 0 controll address
	uint8_t RBC_mask = 0b01100000;
	uint8_t RBC_data = 0b01100000;
	mcp2515_bit_modify(RBC0, RBC_mask, RBC_data);
	
	uint8_t RBC1 = 0x70; // Receive buffer 1 controll address
	mcp2515_bit_modify(RBC1, RBC_mask, RBC_data);
	
	
	

	//
	//	INTERRUPTIONS
	//
	
	// Clean first if there were any interruptions before
	uint8_t IF_data = 0;
	mcp2515_write(IF_data, MCP_CANINTE, 1);
	
	uint8_t TE_mask = 0b00000011;
	uint8_t TE_data = TE_mask;
	mcp2515_bit_modify(MCP_CANINTE, TE_mask, TE_data);

	// Set the mode to Loopback: REMOVE AFTER EXERCISES
	CCR = 0x0F; // can_controll_register 
	CCR_mask = 0b11100000;
	CCR_data = 0b01000000;
	mcp2515_bit_modify(CCR, CCR_mask,CCR_data);
	
	// Give some time to change config
	_delay_ms(10);
	
}