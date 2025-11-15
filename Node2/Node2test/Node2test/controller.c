/*
 * controller.c
 *
 * Created: 06.11.2025 14:22:24
 *  Author: johankna
 */ 

#include "controller.h"

float compute_desired_pos(int joystick_ref, int joy_or_touch){
	float desired_pos = 0;
	if(joy_or_touch){
		float ratio = (float)2800/256;
		desired_pos = joystick_ref * ratio;
	}
	else{
		float ratio = (float)2800/(ADC_MAX-ADC_MIN);
		desired_pos = (joystick_ref-ADC_MIN) * ratio;
	}
	return desired_pos;
}


float PID_controller(int joystick_ref, int joy_or_touch){
	float e = compute_desired_pos(joystick_ref, joy_or_touch) - get_position();
	//static float last_error = 0;
	
	float T = 0.1;
	float k_p = 2;
	float k_i = 1;
	//float k_d = 0.5;
	static float sum_of_errors = 0;
// 	if(abs(sum_of_errors)>5000){
// 		sum_of_errors = sum_of_errors;
// 	}else{
// 		sum_of_errors += e * T;
// 	}
	sum_of_errors += e * T;
	float control_input = k_p*e + k_i*sum_of_errors;// + 0*  (k_d/T)*(e-last_error);
	//last_error = e;
	return control_input;
}

void set_duty_control_input(float control_input){
	if (control_input < 0){
		set_motor_direction(2);
		control_input = - control_input;
	}
	else{
		set_motor_direction(3);
	}
	set_duty_cycle_motor(control_input);
	
}

void PID_timer_init(){
	PMC->PMC_PCER0 |= (1 << (ID_TC1)); //enable clock tc0 channel 1, 
		
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS; // klokke av, ikke telle under config
	TC0->TC_CHANNEL[1].TC_IDR = 0xFFFFFFFF; // innterrupt av, ikke interrupt under config
	TC0->TC_CHANNEL[1].TC_SR; // lese statusregister for reset
	
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC; // MCK/128 = 625.25kHz, waveform mode, tell opp til compare match, interrupt ved topp.
	TC0->TC_CHANNEL[1].TC_RC = 65600; // tell opp til 65600 gir oss 10Hz sampling
	
	
	NVIC_EnableIRQ(TC1_IRQn); // innterupt handler som kalle pid regulator
	
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
	TC0->TC_CHANNEL[1].TC_IER = TC_IER_CPCS; // enable innterupts igjen, interrupt når RC compare match, aktivere PID via innterupt
	
}

void solenoid_init() {
	// Set output for the sol pin (24
	
	PMC->PMC_PCER0 = (1u << ID_PIOC); // enables PIOB clock
	
	PIOC->PIO_PER = (1u << 24); //PC24 to GPIO
	PIOC->PIO_OER   = (1u << 24); // configure as output
	PIOC->PIO_PUDR  = (1u << 24); // disables pull up
	PIOC->PIO_MDDR  = (1u << 24); // push-pull
	
	
}

void solenoid_action_on() {
	PIOC->PIO_CODR = PIO_PC24;
}

void solenoid_action_off() {
	PIOC->PIO_SODR = PIO_PC24;
}

void solenoid_hit(uint8_t input) {
	if (input) solenoid_action_on();
	else solenoid_action_off();
}

