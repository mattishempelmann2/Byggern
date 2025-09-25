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
	init_SPI();
	//ADC_init();
	//Calibrate_joystick();
	
// 	char d;
// 	spi_transmit('x', IO);
// 	d = spi_receive(IO);
// 	printf(d);
	uint8_t k[10];
	for(int i = 0; i < 10; i ++){
		k[i] = 'A' + i;
	}
	
	spi_tranceive_bytes(k, 10, IO);
	
	for(int i = 0; i < 10; i ++){
 		printf("k='%c'\r\n", k[i]);
	}


	
    while (1) 
    {		
		//spi_transmit('x', IO);
// 		k = spi_tranceive('x', IO);
// 		printf("mainloop\n\r");
// 		printf("k='%c'\r\n", (char)k);  
// 		updateJoystick();
// 		printf("Joystick X pos: %d, Joystick Y pos: %d, Joystick retning: %d \n\r", controller.x_prosent, controller.y_prosent, controller.dir);
// 		printf("Touchpad X pos: %d, Touchpad Y pos: %d \n\r", controller.touchpad_x, controller.touchpad_y);
	}
}

