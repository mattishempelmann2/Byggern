/*
 * controller.h
 *
 * Created: 06.11.2025 14:22:49
 *  Author: johankna
 */ 

#include "includes.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


int compute_error(int ref);


int PID_controller(int ref, uint32_t* sum_of_errors);

void set_duty_control_input(int control_input);

#endif /* CONTROLLER_H_ */