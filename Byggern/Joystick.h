/*
 * Joystick.h
 *
 * Created: 18.09.2025 15:33:33
 *  Author: johankna
 */ 
#include <avr/io.h>
#include "avr/iom162.h"
#include <stdio.h>



#ifndef JOYSTICK_H_
#define JOYSTICK_H_

void Calibrate_joystick();

struct Calc_curr_anal_pos();

struct Calc_curr_direction();

#endif /* JOYSTICK_H_ */