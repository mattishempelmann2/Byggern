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
	spi_command_read(address, CAN, data, length);
	
}
void mcp2515_write(uint8_t data, uint8_t address){
	select_slave(CAN);
	spi_transfer(MCP_WRITE);
	spi_transfer(address);
	spi_transfer(data);
	deselect_slave(CAN);
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
	uint8_t RBC0 = 0x60; // Receive buffer 0 control address
	uint8_t RBC_mask = 0b01100000;
	uint8_t RBC_data = 0b01100000;
	mcp2515_bit_modify(RBC0, RBC_mask, RBC_data);
	
	uint8_t EI = 0b01100000; // Extended id
	//mcp2515_bit_modify(M, EI, Ei);
	
	
	uint8_t RBC1 = 0x70; // Receive buffer 1 control address
	mcp2515_bit_modify(RBC1, RBC_mask, RBC_data);

	//
	//	INTERRUPTIONS
	//
	
// 	Clean first if there were any interruptions before
//	uint8_t IF_data = 0;
//	mcp2515_write(IF_data, MCP_CANINTE, 1);
	
	//uint8_t TE_mask = 0b00000011;
	uint8_t TE_mask = 0xFF;
	uint8_t TE_data = TE_mask;
	mcp2515_bit_modify(MCP_CANINTE, TE_mask, TE_data);
	
	//
	//	CNF
	//

	uint8_t CNF1_data = 0x00;
	mcp2515_write(CNF1_data, MCP_CNF1);
	
	uint8_t CNF2_data = 0x98;
	mcp2515_write(CNF2_data, MCP_CNF2);
	
	uint8_t CNF3_data = 0x01;
	mcp2515_write(CNF3_data, MCP_CNF3);
		
	// Set the mode to Loopback: REMOVE AFTER EXERCISES
	CCR = 0x0F; // can_controll_register 
	CCR_mask = 0b11100000;
	CCR_data = 0b00000000;
	mcp2515_bit_modify(CCR, CCR_mask,CCR_data);
	
	// Give some time to change config
	_delay_ms(10);
	
}