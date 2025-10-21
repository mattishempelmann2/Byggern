/*
 * Joystick.c
 *
 * Created: 18.09.2025 15:33:20
 *  Author: johankna
 */ 
#include "Joystick.h"


void Calibrate_joystick(){
	volatile uint8_t *p;
	p=adc_read();

	controller.y_zero = *p;
	controller.x_zero = *(p+1);
	joysick_button_init();
}

signed int joystick_to_percent(uint8_t verdi, uint8_t null){
	if (verdi > null){
		// positiv prosent
		if(((signed int)(verdi - null) * 100 / (ADC_MAX - null)) > 100){
			return 100;
		}
		
		else{
			return ((signed int)(verdi - null) * 100 / (ADC_MAX - null));
		}
	}
	
	else if (verdi < null){
		//negativ prosent
		if(((signed int)(verdi-null) * 100 / (null - ADC_MIN)) < -100){
			return -100;
		}
		else{
			return ((signed int)(verdi-null) * 100 / (null - ADC_MIN));
		}
	}
	return 0;
}

enum direction calc_direction(signed int x, signed int y){
	signed int dodsone = 20; //prøver 10% dødsone
	if(abs(x) > abs(y)){ // x verdi større høyre/venstre det er snakk om
		if(x > dodsone){
			return RIGHT;
		}
		else if(x < -dodsone){
			return LEFT;
		}
	}
	else{ // hvis ikke venstre/høyre er det Opp/ned
		if(y > dodsone){
			return UP;
		}
		else if (y < -dodsone){
			return DOWN;
		}
	}
	return CENTER;
};

void updateJoystick(){
	volatile uint8_t *p = adc_read();
	
	controller.y_int = *p;
	controller.x_int = *(p+1);
	controller.x_prosent = joystick_to_percent(controller.x_int, controller.x_zero);
	controller.y_prosent = joystick_to_percent(controller.y_int, controller.y_zero);
	controller.dir = calc_direction(controller.x_prosent,controller.y_prosent);
	
	controller.touchpad_y = *(p+2);
	controller.touchpad_x = *(p+3);
	
	_NOP();
}

void joysick_button_init(){
	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);
}

int joystick_btn_press(){
	if(PINB & (1 << PB0)){
		return 0;
	}
	else{
		return 1;
	}
}

