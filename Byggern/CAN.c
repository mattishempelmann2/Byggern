/*
 * CAN.c
 *
 * Created: 09.10.2025 16:52:14
 *  Author: johankna
 */ 
#include "Includes.h"

void CAN_write(uint8_t buffer_number, CANMessage message) {
	uint8_t command = 0;
	switch(buffer_number){
		case 0:
			command = 0x31;
			break;
		case 1:
			command = 0x41;
			break;
		case 2:
			command = 0x51;
			break;
		default:
			return;
	}

	mcp2515_write((message.id>>3) & 0xFF, command);
	mcp2515_write((message.id & 0x07)<<5, command+1);
	mcp2515_write(message.data_length & 0x0F, command+4);
	for(int i = 0; i < message.data_length; i++) {
		mcp2515_write(message.data[i], command+5+i);
	}
	mcp2515_request_to_send(buffer_number);
}

void CAN_receive(CANMessage *message) {
	uint8_t can_status = mcp2515_read_status();
	
	if(can_status & 0b10 || can_status & 0b01){
		select_slave(CAN);
		
		if(can_status & 0b01){
			spi_transfer(MCP_READ_RX0);
		}else if (can_status & 0b10){
			spi_transfer(MCP_READ_RX1);	
		}
		
		uint8_t id_start = spi_read();
 		uint8_t id_end = spi_read();
		 
		message->id =(id_start<<3 | id_end >> 5);
		spi_read(); spi_read();
		message->data_length = spi_read();
		printf("Id: %d, Data_length: %d \n\r", message->id, message->data_length);
		for (int i = 0; i<8;i++){
			 message->data[i]=spi_read();
			 printf("Data %d: %d\n\r", i, message->data[i]);
		 }
		 deselect_slave(CAN);
	}
}

void CAN_initialize() {
	mcp2515_init();
	DDRD &= ~(1 << PD2);
	// Set the falling edge for interruption
	MCUCR |= (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	
	// Enable interruption in INT0
	GICR |= (1 << INT0);
	
	sei();
}

ISR(INT0_vect) {
	CANMessage received_message;

	uint8_t intf;
	mcp2515_read(&intf, MCP_CANINTF, 1);

 	if (intf & (MCP_RX0IF)) {
 		CAN_receive(&received_message);
 		mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00);
 	}
 	if (intf & (MCP_RX1IF)) {
 		CAN_receive(&received_message);
 		mcp2515_bit_modify(MCP_CANINTF, MCP_RX1IF, 0x00);
 	}
 	
 	if (intf & (MCP_TX1IF)) {
 		mcp2515_bit_modify(MCP_CANINTF,  MCP_TX1IF, 0x00);
 	}
	 
	if (intf & (MCP_TX2IF)) {
		 mcp2515_bit_modify(MCP_CANINTF,  MCP_TX2IF, 0x00);
	 }
	 
	if (intf & (MCP_TX0IF)) {
		 mcp2515_bit_modify(MCP_CANINTF,  MCP_TX0IF, 0x00);
	 }
}