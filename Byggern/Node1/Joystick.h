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
#include "Includes.h"

#ifndef JOYSTICK_H_
#define JOYSTICK_H_


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
	uint8_t x_min_seen;
	uint8_t x_max_seen;
	uint8_t y_min_seen;
	uint8_t y_max_seen;
} Controller ;

Controller controller;

void Calibrate_joystick();

signed int joystick_to_percent(uint8_t verdi, uint8_t null, uint8_t min_seen, uint8_t max_seen);

volatile void updateJoystick();

enum direction calc_direc(signed int x, signed int y);

void joystick_button_init();

uint8_t joystick_btn_press();

volatile void Joystick_CAN();


#endif /* JOYSTICK_H_ */