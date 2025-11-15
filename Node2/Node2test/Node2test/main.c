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
	set_duty_cycle_motor(0);
	encoder_init();
	solenoid_init();

	__enable_irq();
	
	disable_watchdog();
	
 	CanMsg IOboard;

	int previous_result;
	previous_result = 0;

	can_rx(&IOboard);
	
	
	
	printf("Restarting \n\r");
	

	int joy_or_touch = 1;
    while (1) 
    {  
		
 		while(!IOboard.byte[4]) can_rx(&IOboard);
		if(pid_flag){
 			
 			can_rx(&IOboard);
 			
  			solenoid_hit(IOboard.byte[7]);
  			if(joy_or_touch){
				  set_duty_joystick(IOboard.byte[2], IOboard.byte[0]);
				  set_duty_control_input(PID_controller(IOboard.byte[5],joy_or_touch)); // regulates based on touchpad
			  }
			else{
				set_duty_joystick(IOboard.byte[3], IOboard.byte[1]);
				set_duty_control_input(PID_controller(IOboard.byte[2],joy_or_touch)); // regulates based on joystick
				
			}

 			
  			if (count_score(&previous_result)){
  				uart_tx('p');
  				previous_result = 1;
  				can_score(); // Sends score
  			}
 			
			pid_flag = 0;
			
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