/*
 * controller.c
 *
 * Created: 06.11.2025 14:22:24
 *  Author: johankna
 */ 

#include "controller.h"

int compute_desired_pos(int joystick_ref){
	float ratio = (float)2800/256;
	int desired_pos = joystick_ref * ratio;
	return desired_pos;
}


int PID_controller(int joystick_ref){
	int e = compute_desired_pos(joystick_ref) - get_position();
	
	float T = 0.1;
	uint16_t k_p = 14;
	uint16_t k_i = 2;
	static int sum_of_errors = 0;
	sum_of_errors += e;
	
	int control_input = k_p*e + T*k_i*sum_of_errors;
	//printf("Control input %d \n\r", control_input);
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

void PID_timer_init(){
	PMC->PMC_PCER0 |= (1 << (ID_TC1)); //enable clock tc2 channel 7, 
	
	//TC0->TC_WPMR = 0x54494D << 8 | 0b00000000;
	
	TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKDIS; // klokke av, ikke telle under config
	TC0->TC_CHANNEL[1].TC_IDR = 0xFFFFFFFF; // innterrupt av, ikke interrupt under config
	TC0->TC_CHANNEL[1].TC_SR; // lese statusregister for reset
	
	TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC; // MCK/128 = 625.25kHz, waveform mode, tell opp til compare match, interrupt ved topp.
	TC0->TC_CHANNEL[1].TC_RC = 65600; // tell opp til 656000 gir oss 10Hz sampling
	
	
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

