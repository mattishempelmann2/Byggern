/*
 * Joystick.h
 *
 * Created: 18.09.2025 15:33:33
 *  Author: johankna
 */ 
#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>
#include "Adc.h"
#include "avr/cpufunc.h"

#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#define ADC_MIN 66
#define ADC_MAX 245

enum direction{
	UP, DOWN, LEFT, RIGHT, CENTER
};

typedef struct Controller{
	signed int x_zero;
	signed int y_zero;
	volatile uint8_t x_int;
	volatile uint8_t y_int;
	volatile signed int x_prosent;
	volatile signed int y_prosent;
	volatile enum direction dir;
	volatile uint8_t touchpad_x;
	volatile uint8_t touchpad_y	;
} Controller ;

Controller controller;

void Calibrate_joystick();

signed int joystick_to_percent(uint8_t verdi, uint8_t null);

void updateJoystick();

enum direction calc_direc(signed int x, signed int y);

#endif /* JOYSTICK_H_ */