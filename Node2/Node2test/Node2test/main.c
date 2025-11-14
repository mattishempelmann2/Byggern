/*
 * Node2test.c
 *
 * Created: 21.10.2025 13:48:55
 * Author : mattisjh
 */ 


#include "includes.h"

volatile int pid_flag = 0;

void TC1_Handler(void);

int main(void)
{
	CanInit can100kbit_84MHz = {
		.phase2 = 2,
		.propag = 2,
		.phase1 = 2,
		.sjw = 0,
		.brp = 83,
		.smp = 0
	};
	
    SystemInit();
	PID_timer_init();
	uart_init(F_CPU, 9600);
	can_init(can100kbit_84MHz,0);
	PWM_init();
	ADC_init();
	encoder_init();

	__enable_irq();
	
	disable_watchdog();
	
 	CanMsg IOboard;

	int score = 100;
	int previous_result;
	previous_result = 0;

	can_rx(&IOboard);
	
	solenoid_init();
	
	solenoid_action_on();
	for(volatile int i = 0; i < 1000000; i++);
	solenoid_action_off();
	int something = 0;
    while (1) 
    {  
		
		int joystick_ref = IOboard.byte[5];
		
		//printf(" %d ", adc_read());
		if(pid_flag){
// 			something++;
// 			if(something % 2 == 0)	solenoid_action_on();
//  			else solenoid_action_off();
// 			if(IOboard[7] == 1) solenoid_hit();
			can_rx(&IOboard);
			pid_flag = 0;
			set_duty_joystick(IOboard.byte[2], IOboard.byte[0]);
			//printf("adc val : %d \n\r", IOboard.byte[2]);
			int control_input = PID_controller(joystick_ref); // regulates based on reference and current pos
			set_duty_control_input(control_input);
			if (count_score(&previous_result)){
				score = score - 1;
				previous_result = 1;
				printf("Score: %d \n\r", score);
				
			}
		}
	}
}

		

void TC1_Handler(void){
	int status = TC0->TC_CHANNEL[1].TC_SR; // lese/clear status register
	if(status & TC_SR_CPCS){
		pid_flag = 1;
	}
	NVIC_ClearPendingIRQ(TC1_IRQn);
}