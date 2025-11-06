/*
 * controller.c
 *
 * Created: 06.11.2025 14:22:24
 *  Author: johankna
 */ 

#include "controller.h"

int compute_error(int ref){
	int error = ref - get_position();
	return error;
}


int PID_controller(int ref, uint32_t* sum_of_errors){
	int error = compute_error(ref);
	printf("error: %d \n\r", error);
	uint16_t T = 1;
	uint16_t k_p = 10;
	uint16_t k_i = 0;
	*sum_of_errors = *sum_of_errors+error;
	
	int control_input = k_p*error + T*k_i**sum_of_errors;
	printf("Control input %d \n\r", control_input);
	return control_input;
}

void set_duty_control_input(int control_input){
	if (control_input < 0){
		set_motor_direction(2);
	}
	else{
		set_motor_direction(3);
	}
	
	set_duty_cycle_x(abs(control_input));
	
}