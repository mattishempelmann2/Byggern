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
	ADC_init();
	Calibrate_joystick();
	
	
	display_initialize();
	display_clear();
	display_init_SRAM();
// 	display_print("hello",0);
// 	display_all_pages();
// 	
// 	display_print("newlinetest",1);
// 	display_all_pages();
// 	
// 	display_print("line4",3);
// 	display_all_pages();
	display_pixel_on(0,0);
	display_pixel_on(127,0);
	display_pixel_on(0,63);
	display_pixel_on(127,63);
	update_menu(3);
	//draw_filled_circle(64,32,10);

	display_all_pages();
	
	menu_pos menu;
	menu.current_pos = 3;
	update_menu(menu.current_pos);
    while (1) 
    {		
		change_menu(&menu);
		display_all_pages();
		
		//spi_transmit('x', IO);
// 		k = spi_tranceive('x', IO);
// 		printf("mainloop\n\r");
// 		printf("k='%c'\r\n", (char)k);  
 		//updateJoystick();
 		//printf("Joystick X pos: %d, Joystick Y pos: %d, Joystick retning: %d \n\r", controller.x_prosent, controller.y_prosent, controller.dir);
 		//printf("Touchpad X pos: %d, Touchpad Y pos: %d \n\r", controller.touchpad_x, controller.touchpad_y);
	}
}

