/*
 * PWM.h
 *
 * Created: 30.10.2025 08:38:54
 *  Author: mattisjh
 */ 

#include "includes.h"

#ifndef PWM_H_
#define PWM_H_
#define duty_cycle_max = 11;

void disable_watchdog();


void PWM_init();

int joystick_to_percent(int verdi);

void set_duty_cycle_x(int duty_cycle);

void set_duty_cycle_y(uint32_t duty_cycle);

void set_duty_joystick(uint8_t x_pos, uint8_t x_zero);

void quad_init();

void speed(uint8_t acceleration);

void set_motor_direction(uint16_t direction);

void encoder_init();


#endif /* PWM_H_ */