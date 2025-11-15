/*
 * controller.h
 *
 * Created: 06.11.2025 14:22:49
 *  Author: johankna
 */ 

#include "includes.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


float compute_desired_pos(int joystick_ref, int joy_or_touch);

float PID_controller(int joystick_ref, int joy_or_touch);


void set_duty_control_input(float control_input);

void PID_timer_init();

void solenoid_init();

void solenoid_action_off();

void solenoid_action_on();

void solenoid_hit(uint8_t input);


#endif /* CONTROLLER_H_ */