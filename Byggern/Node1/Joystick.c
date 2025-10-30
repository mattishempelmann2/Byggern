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
	joystick_button_init();
	controller.x_max_seen = 240;
	controller.x_min_seen = 70;
	controller.y_max_seen = 240; // ble addet i et forsøk på å fikse elendig joystick sensitivitet, men hjalp ikke egt, fortsatt god design så beholder det
	controller.y_min_seen = 70;
}






signed int joystick_to_percent(uint8_t verdi, uint8_t null, uint8_t min_seen, uint8_t max_seen){
//pos prosent
	if (verdi > null) {
		uint8_t range = (max_seen > null) ? (max_seen - null) : 1;
		int16_t p = ((int16_t)(verdi - null) * 100) / range;
		if (p > 100) p = 100;
		return p;
	}
	// neg prosent
	else if (verdi < null) {
		uint8_t range = (null > min_seen) ? (null - min_seen) : 1;
		int16_t p = ((int16_t)(null - verdi) * 100) / range;
		if (p > 100) p = 100;
		return -p;
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

volatile void updateJoystick(){
	volatile uint8_t *p = adc_read();
	
	uint8_t y = *p;
	uint8_t x = *(p+1);
	if(x > controller.x_max_seen) controller.x_max_seen = x;
	if(x + 1 < controller.x_min_seen) controller.x_min_seen = x;
	if(y > controller.y_max_seen) controller.y_max_seen = y;
	if(y + 1 < controller.y_min_seen) controller.y_min_seen = y;
	
	
	
	controller.x_int = x;
	controller.y_int = y;
	controller.x_prosent = joystick_to_percent(controller.x_int, controller.x_zero, controller.x_min_seen, controller.x_max_seen);
	controller.y_prosent = joystick_to_percent(controller.y_int, controller.y_zero, controller.y_min_seen, controller.y_max_seen);
	controller.dir = calc_direction(controller.x_prosent,controller.y_prosent);
	
	controller.touchpad_y = *(p+2);
	controller.touchpad_x = *(p+3);
	
	_NOP();
}

void joystick_button_init(){
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

volatile void Joystick_CAN(){
	CANMessage joystick;
	joystick.id = 0;
	joystick.data_length = 5;
	joystick.data[0] = controller.x_zero;
	joystick.data[1] = controller.y_zero;
	joystick.data[2] = controller.x_int;
	joystick.data[3] = controller.y_int;
	joystick.data[4] = controller.dir;
	CAN_write(0,joystick);
}

