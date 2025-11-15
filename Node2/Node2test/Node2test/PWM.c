/*
 * PWM.c
 *
 * Created: 30.10.2025 08:38:42
 *  Author: mattisjh
 */ 
#include "PWM.h"

void disable_watchdog(){
	WDT->WDT_MR &= WDT_MR_WDDIS;
}

void PWM_init(){ //use PWMH0 on PA8
	PMC->PMC_PCER0 |= (1 << ID_PIOB);
	PMC->PMC_PCER1 |= (1u << (ID_PWM - 32)); // PERIpheral id 36?
	
	// Set output for the dir pin
	PIOC->PIO_PER = PIO_PC23;
	PIOC->PIO_OER = PIO_PC23;
	
	PIOB->PIO_PDR |= PIO_PDR_P13; // disable PIO
	PIOB->PIO_ABSR |= PIO_ABSR_P13; // AB peripheral select, we want B
	
	// enable/phase pwm
	PIOB->PIO_PDR |= PIO_PDR_P12; // disable PIO
	PIOB->PIO_ABSR |= PIO_ABSR_P12; // AB peripheral select, we want B
	
	PWM->PWM_WPCR = 0x50574D << 8 | 0b11111100; // disable write protection
	
	//clock
	PWM->PWM_CLK = PWM_CLK_PREA(0)  | PWM_CLK_DIVA(42); // CLK = MCK/(PREA+DIVA) should give 2Mhz
	
	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	PWM->PWM_CH_NUM[1].PWM_CPRD = 40000; // 40000 counts gives us 50Hz 
	PWM->PWM_CH_NUM[1].PWM_CDTY = 37000; // Duty cycle 7.5%

	// clock
	PWM->PWM_CH_NUM[0].PWM_CMR = PWM_CMR_CPRE_MCK; // use main clock 84Mhz, 84Mhz/20000Hz = 4200 steps
	PWM->PWM_CH_NUM[0].PWM_CPRD = 4200; //  was 40000 counts gives us 50Hz, now 100 -> 20000Hz to stop stuttering, changed clock for channel 0, now 4200 gives us 20kHz
	PWM->PWM_CH_NUM[0].PWM_CDTY = 4095; // same ratio as 39000 is for 40000

	PWM->PWM_ENA = PWM_ENA_CHID0 | PWM_ENA_CHID1; // enable
}

void set_duty_cycle_servo(uint32_t duty_cycle){
	if(duty_cycle > maxduty){
		duty_cycle = maxduty;
	}
	if(duty_cycle < minduty){
		duty_cycle = minduty;
	}
		
	PWM->PWM_CH_NUM[1].PWM_CDTY = 40000-duty_cycle;
	
}

void set_duty_cycle_motor(float duty_cycle){
	if(duty_cycle > maxDuty_x){
		duty_cycle = maxDuty_x;
	}
	if(duty_cycle < minDuty_x){
		duty_cycle = minDuty_x;
	}
	int duty_cycle_int = (uint32_t)duty_cycle;
	PWM->PWM_CH_NUM[0].PWM_CDTY = 4200-duty_cycle_int; // new max is 4200 change way duty cycle is calc
	
}



void set_duty_joystick(uint8_t x_pos, uint8_t x_zero){
	
	if(abs(x_pos - x_zero) > 10){
	
		int x_prosent = joystick_to_percent(x_pos);
	
		int duty_x = minduty + ((uint32_t)x_prosent * (maxduty - minduty)) / 100;
	
		set_duty_cycle_servo(duty_x);
	}
	else {
		
		set_duty_cycle_servo(3100);
	}
	
}




int joystick_to_percent(int verdi) {
	if (verdi < ADC_MIN) verdi = ADC_MIN;
	if (verdi > ADC_MAX) verdi = ADC_MAX;

	return ((int)(verdi - ADC_MIN) * 100) / (ADC_MAX - ADC_MIN);
}



void quad_init(){
	PMC->PMC_PCER1 |= (1u << (ID_TC6 - 32)); //Enable peripheral clock
	
	TC2 -> TC_WPMR |=	0x54494D; //PASSWD to disable write protection
	TC2->TC_BMR |= TC_BMR_QDEN;  //Enable quadrature mode
	TC2 ->TC_BMR |=TC_BMR_POSEN; //Enable position
	
	TC2 ->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN; //Enable the clock
	TC2 ->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG; //Software trigger
	
	PIOB->PIO_PDR = PIO_PC25;    // Disable PIO control of PB25
	PIOB->PIO_ABSR |= PIO_PC25;  // Select Peripheral B for PC25 (TIOA6)

	PIOC->PIO_PDR = PIO_PC26;    // Disable PIO control of PC26
	PIOC->PIO_ABSR |= PIO_PC26;  // Select Peripheral B for PC26 (TIOB6)
	

}


void encoder_init(){
	set_motor_direction(2);
	set_duty_cycle_motor(5000);
	for (volatile int i = 0; i < 1000000; i++); // small delay
	set_duty_cycle_motor(0);
	quad_init();
}

int get_position(){
	int pos = TC2->TC_CHANNEL[0].TC_CV;
	return pos;
}


void set_motor_direction(uint16_t direction){

	if(direction == 3) {
		// set the DIR = 0
		PIOC->PIO_CODR = PIO_PC23;
	} else if (direction == 2) {
		//left
		// set the DIR = 1
		PIOC->PIO_SODR = PIO_PC23;		
	}
}