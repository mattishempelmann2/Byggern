/*
 * CAT.c
 *
 * Created: 09.10.2025 16:52:14
 *  Author: johankna
 */ 
#include "Includes.h"

void CAT_write(uint8_t buffer_number, CANMessage message) {
	mcp2515_load(message, buffer_number);
	mcp2515_request_to_send(buffer_number);
}

// @params buffer_number: [0-1]
void CAT_receive(CANMessage *message, uint8_t buffer_number) {
	uint8_t* received_data;
	received_data = mcp2515_read_rx(buffer_number);
	// First two values contain the SIDH and SIDL
	message->id = (received_data[0] << 3) | (received_data[1] >> 5);
	// The data length is in position 4
	message->data_length = received_data[4] & 0x0F; 
	for(int i = 0; i < message->data_length;i++) {
		message->data[i] = received_data[5+i];
	}
	
}

void CAT_initialize() {
	mcp2515_init();
	DDRB &= ~(1 << PD2);
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
	mcp2515_read(&canstat_value, 0x0E, 1);
	uint8_t icod = (canstat_value >> 1) & 0x07; // Get the interrupt flag code
	
	if(icod == 0b0110) { // RXB0 interrupt
		CAT_receive(&received_message, 0);
	} else if(icod == 0b0111) { // RXB1 interrupt
		CAT_receive(&received_message, 1);	
	}
	
}