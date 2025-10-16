/*
 * CAN.c
 *
 * Created: 09.10.2025 16:52:14
 *  Author: johankna
 */ 
#include "Includes.h"

void CAN_write(uint8_t buffer_number, CANMessage message) {
	mcp2515_load(message, buffer_number);
	mcp2515_request_to_send(buffer_number);
	
}

// @params buffer_number: [0-1]
void CAN_receive(CANMessage *message) {
	uint8_t can_status = mcp2515_read_status();
	
	
	if(can_status & 0b10 || can_status & 0b01){
		select_slave(CAN);
		
		
		if(can_status & 0b10){
			spi_transfer(MCP_READ_RX0);
		}else if (can_status & 0b01){
			spi_transfer(MCP_READ_RX1);	
		}
		
		uint8_t id_start = spi_read();
 		uint8_t id_end = spi_read();
		 spi_read();
		 spi_read();
		 message->id =(id_start<<3 | id_end >> 5) & 0x7FF;
		 message->data_length = spi_read() & 0x0F;
		 for (int i = 0; i<message->data_length;i++){
			 message->data[i]=spi_read();
		 }
		 deselect_slave(CAN);
	}
	
	
// 	
// 	uint8_t* received_data;
// 	received_data = mcp2515_read_rx(buffer_number);
// 	// First two values contain the SIDH and SIDL
// 	message->id = (received_data[0] << 3) | (received_data[1] >> 5);
// 	// The data length is in position 4
// 	message->data_length = received_data[4] & 0x0F; 
// 	for(int i = 0; i < message->data_length;i++) {
// 		message->data[i] = received_data[5+i];
// 	}
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
	uint8_t canstat_value;
	mcp2515_read(&canstat_value, 0x2C, 1);
	
	switch (canstat_value)
	{
		case 0b00000001:
			CAN_receive(&received_message);
			mcp2515_bit_modify(MCP_CANINTF,0x01,0x00);
			break;
		case 0b00000011:
			CAN_receive(&received_message);
			break;
		case 0b00001001:
			CAN_receive(&received_message);
			break;
		case 0b00001101:
			CAN_receive(&received_message);
			break;
		case 0b00010001:
			CAN_receive(&received_message);
			break;
		case 0b10000001:
			CAN_receive(&received_message);
			break;
		case 0b01010001:
			CAN_receive(&received_message);
			break;
 	}
// 	uint8_t flags;
// 	mcp2515_read(&flags, MCP_CANINTF, 1);
// 	mcp2515_bit_modify(MCP_CANINTF, flags, 0x00); // clear all set bits
	
}
// ISR(INT0_vect) {
// 	CANMessage received_message;
// 	uint8_t interrupt_flags;
// 	
// 	mcp2515_read(&interrupt_flags, MCP_CANINTF, 1);
// 
// 	if (interrupt_flags & 0x01) { // RX0IF
// 		CAN_receive(&received_message);
// 		mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00); // Clear RX0IF
// 	}
// 
// 	if (interrupt_flags & 0x02) { // RX1IF
// 		CAN_receive(&received_message);
// 		mcp2515_bit_modify(MCP_CANINTF, 0x02, 0x00); // Clear RX1IF
// 	}
// }
