/*
 * CAT.h
 *
 * Created: 09.10.2025 16:52:27
 *  Author: johankna
 */ 
#include "Includes.h"


#ifndef CAT_H_
#define CAT_H_

typedef struct {
	uint16_t id;
	uint8_t data_length;
	// Up to 8 byes of data
	uint8_t data[8];
} CANMessage;

void CAN_write();

void CAN_read();

void CAT_initialize();

ISR(INT0_vect);

#endif