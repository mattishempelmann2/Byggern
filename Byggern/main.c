/*
 * Byggern.c
 *
 * Created: 04.09.2025 10:42:48
 * Author : johankna
 */ 

#define F_CPU 4915200


#include "Includes.h"

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
// 	uint8_t k[10];
// 	for(int i = 0; i < 10; i ++){
// 		k[i] = 'A' + i;
// 	}
// 	
// 	spi_tranceive_bytes(k, 10, IO);
// 	
// 	for(int i = 0; i < 10; i ++){
//  		printf("k='%c'\r\n", k[i]);
// 	}
// 	uint8_t command = 0x05;
// 	uint8_t led_number = 0x04;
// 	uint8_t led_on = 0x01;
// 	uint8_t led_off = 0x00;
//  	
//  	uint8_t turn_on_led[] = {command, led_number, led_on};
//  	spi_write_bytes(turn_on_led,3,IO);
// 	
// 	command = 0x07;
// 	uint8_t info[35];
// 	spi_command_read(command, IO, info, 35);
// 	
// 	printf("\n\r");
// 	for(int i=0; i<19; i++){
// 		printf("%c, ",info[i]);
// 	}
// 	for(int i=19; i<35; i++){
// 		printf("%d, ",info[i]);
// 	}
	
	
	
	display_initialize();
	display_clear();
	display_SRAM();
	display_print("abcd");
	printf("\n\r");
	printf("\n\r");
	display_all_pages();
	
    while (1) 
    {		
		
		//spi_transmit('x', IO);
// 		k = spi_tranceive('x', IO);
// 		printf("mainloop\n\r");
// 		printf("k='%c'\r\n", (char)k);  
 		//updateJoystick();
 		//printf("Joystick X pos: %d, Joystick Y pos: %d, Joystick retning: %d \n\r", controller.x_prosent, controller.y_prosent, controller.dir);
 		//printf("Touchpad X pos: %d, Touchpad Y pos: %d \n\r", controller.touchpad_x, controller.touchpad_y);
	}
}

