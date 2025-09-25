/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#include <avr/io.h>
#include "avr/iom162.h"
#include "Uart.h"
#include "time.h"
#include "SRAM.h"
#include "Joystick.h"
#include "Adc.h"
#include "SPI.h"

#define BAUD 9600 //Baud Rate
#define FOSC 4915200 //Clock speed
#define MYUBRR 31



int main(void)
{	
	UART_init(MYUBRR);
	ADC_init();
	Calibrate_joystick();

	

    while (1) 
    {
		updateJoystick();
		printf("Joystick X pos: %d, Joystick Y pos: %d, Joystick retning: %d \n\r", controller.x_prosent, controller.y_prosent, controller.dir);
		printf("Touchpad X pos: %d, Touchpad Y pos: %d \n\r", controller.touchpad_x, controller.touchpad_y);
	}
}

