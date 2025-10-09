/*
 * Includes.h
 *
 * Created: 02.10.2025 11:25:07
 *  Author: johankna
 */ 


#ifndef F_CPU
#define F_CPU 4915200
#endif

#ifndef INCLUDES_H_
#define INCLUDES_H_



#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>
#include "avr/cpufunc.h"
#include "util/delay.h"
#include <avr/pgmspace.h>
#include "time.h"
#include "string.h"


#include "Adc.h"
#include "Clock.h"
#include "Display.h"
#include "Joystick.h"
#include "SPI.h"
#include "SRAM.h"
#include "uart.h"
#include "IO_board.h"
#include "MCP2515.h"

#define setBit(reg, bit) (reg |= (1<<bit))
#define clearBit(reg, bit) (reg &= ~(1<<bit))




#endif /* INCLUDES_H_ */