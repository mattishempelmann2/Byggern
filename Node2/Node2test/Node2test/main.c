/*
 * Node2test.c
 *
 * Created: 21.10.2025 13:48:55
 * Author : mattisjh
 */ 


#include "includes.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
// 	PMC->PMC_PCER0 = (1u << ID_PIOB); // enables PIOB clock
// 	
// 	PIOB->PIO_PER = (1u << 13); //PB13 to GPIO
// 	
// 	PIOB->PIO_OER   = (1u << 13); // configure as output
// 	PIOB->PIO_PUDR  = (1u << 13); // disables pull up                   
// 	PIOB->PIO_MDDR  = (1u << 13); // push-pull
// 	
// 	PIOB->PIO_SODR = (1u << 13); // sets pin high
	
	disable_watchdog();
	uart_init(F_CPU, 9600);
 	uint8_t value = 'a';
 	uart_tx(value);
	
	CanInit can100kbit_84MHz = {
		.phase2 = 2,
		.propag = 2,
		.phase1 = 2,
		.sjw = 0,
		.brp = 83,
		.smp = 0
	};
	
	can_init(can100kbit_84MHz,0);
	CanMsg msg;
	 
	msg.id = 0;
	msg.length = 8;
	msg.byte[0] = 0x11;
	msg.byte[1] = 0x22;
	msg.byte[2] = 0x33;
	msg.byte[3] = 0x44;
	msg.byte[4] = 0x55;
	msg.byte[5] = 0x66;
	msg.byte[6] = 0x77;
	msg.byte[7] = 0x88;
	//can_tx(msg);
	
	
 	CanMsg test;
	PWM_init();
	ADC_init();
	
	uint16_t score = 0;
	uint16_t previous_result;
	previous_result = 0;
    while (1) 
    {  
		//uint32_t a = ;
		//uart_send_u32_hex(a);
		if (count_score(&previous_result)){
			score = score +1;
			previous_result = 1;
		}
		
		//printf("ADC SIGNAL: %d`\n\r", adc_read());
		
		printf("Current score: %d \n\r", score);
		can_rx(&test);
		set_duty_joystick(test.byte[2], test.byte[3]);
// 		for(uint8_t i = 0; i < test.length; i++){
// 			 uart_tx(test.byte[i]);
// 		 }
//        printf("while loop\n\r");
	}
}
