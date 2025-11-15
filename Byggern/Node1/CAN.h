/*
 * CAN.h
 *
 * Created: 09.10.2025 16:52:27
 *  Author: johankna
 */ 
#include "Includes.h"


#ifndef CAN_H_
#define CAN_H_

typedef struct {
	uint16_t id;
	uint8_t data_length;
	// Up to 8 byes of data
	uint8_t data[8];
} CANMessage;

void CAN_write(uint8_t buffer_number, CANMessage message);

void CAN_initialize();

void CAN_receive(CANMessage *message);

volatile void CAN_start();

uint8_t get_start();


#endif