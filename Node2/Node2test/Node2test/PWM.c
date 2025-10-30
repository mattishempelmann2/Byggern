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
	
	PIOB->PIO_PDR |= PIO_PDR_P13; // disable PIO
	PIOB->PIO_ABSR |= PIO_ABSR_P13; // AB peripheral select, we want B
	
	PWM->PWM_WPCR = 0x50574D << 8 | 0b11111100; // disable write protection
	
	//clock
	PWM->PWM_CLK = PWM_CLK_PREA(0)  | PWM_CLK_DIVA(42); // CLK = MCK/(PREA*DIVA) should give 2Mhz
	
	PWM->PWM_CH_NUM[1].PWM_CMR = PWM_CMR_CPRE_CLKA;
	
	PWM->PWM_CH_NUM[1].PWM_CPRD = 40000; // 40000 counts gives us 50Hz 
	PWM->PWM_CH_NUM[1].PWM_CDTY = 37000; // Duty cycle 7.5%
	
	PWM->PWM_ENA = PWM_ENA_CHID1; // enable
}

void set_duty_cycle(uint32_t duty_cycle){
	//max = 10.5%
	//min = 4.5%
	//duty_cycle = 10.5% = 10.5*10 = 105
	
	if(duty_cycle > maxduty){
		duty_cycle = maxduty;
	}
	if(duty_cycle < minduty){
		duty_cycle = minduty;
	}
	
	
	PWM->PWM_CH_NUM[1].PWM_CDTY = 40000-duty_cycle;
	
}

void set_duty_joystick(uint8_t x_pos, uint8_t y_pos){
	uint8_t x_prosent = joystick_to_percent(x_pos);
	uint8_t y_prosent = joystick_to_percent(y_pos);
	
	uint32_t duty_x = minduty + ((uint32_t)x_prosent * (maxduty - minduty)) / 100;
	uint32_t duty_y = minduty + ((uint32_t)y_prosent * (maxduty - minduty)) / 100;
	set_duty_cycle(duty_x);
}




uint8_t joystick_to_percent(uint8_t verdi) {
	if (verdi < ADC_MIN) verdi = ADC_MIN;
	if (verdi > ADC_MAX) verdi = ADC_MAX;

	// Scale linearly: 0 ? 0%, ADC_MAX ? 100%
	return ((uint32_t)(verdi - ADC_MIN) * 100) / (ADC_MAX - ADC_MIN);
}

