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

CANMessage received_message;

//Remember callback interrup tips from the TA
int main(void)
{	
	UART_init(MYUBRR);
	init_SPI();
	ADC_init();
	Calibrate_joystick();
	
	
	display_initialize();
	display_clear();
	display_init_SRAM();
	
	display_pixel_on(0,0);
	display_pixel_on(127,0);
	display_pixel_on(0,63);
	display_pixel_on(127,63);
	
	char* main_items[] = {"Welcome" , " ", "start game", "quit"};
	char* pause_items[] ={"Pause", " ","continue", "quit", "Highscore: 52"};
	menu main_menu;
	main_menu.menu_items = main_items;
	main_menu.length = 4;
	menu pause_menu;
	pause_menu.menu_items = pause_items;
	pause_menu.length = 5;
	
	display_print_menu(2,pause_menu);

	display_all_pages();
	
	menu_pos menu_p;
	menu_p.current_pos = 2;
	
	CAN_initialize();
// 	CANMessage message;
// 	message.id = 0;
// 	uint8_t	data[] = {'3', '4', '5', 'c', 'd', 'e', 'f', 'z'};
// 	message.data_length = 8;
// 	for(int i = 0; i < sizeof(data); i++) message.data[i] = data[i];
// 	CAN_write(1, message);
	printf("menu pos is:	\n\r");
	
    while (1) 
    {
		updateJoystick();
		Joystick_CAN();

		//CAN_write(1, message);

		//_delay_ms(500);
		
// 		int x = display_update_menu(&menu_p, pause_menu);
// 		if(x != 0){
// 			
// 		}
// 		IO_button_init(values);
// 		if(values[0] == 32) {
// 			IO_button_on_leds(0);
// 			_delay_ms(100);
// 		}
		printf("Joystick X pos: %d, Joystick Y pos: %d, Joystick retning: %d \n\r", controller.x_prosent, controller.y_prosent, controller.dir);
		//printf("Joystick X pos: %d, Joystick Y pos: %d\n\r", controller.x_int, controller.y_int);

		_delay_ms(100);
		
		/* if(receivedMessage.id == X && receivedMessage.byte[0] == 1) {
			score++;
			updateMenu();
		*/}
	}
	
}

/*
ISR(INT0_vect) {

	uint8_t intf;
	mcp2515_read(&intf, MCP_CANINTF, 1);

	if (intf & (MCP_RX0IF)) {
		CAN_receive(&received_message);
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00);
	}
	if (intf & (MCP_RX1IF)) {
		CAN_receive(&received_message);
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX1IF, 0x00);
	}
	
	if (intf & (MCP_TX1IF)) {
		mcp2515_bit_modify(MCP_CANINTF,  MCP_TX1IF, 0x00);
	}
	
	if (intf & (MCP_TX2IF)) {
		mcp2515_bit_modify(MCP_CANINTF,  MCP_TX2IF, 0x00);
	}
	
	if (intf & (MCP_TX0IF)) {
		mcp2515_bit_modify(MCP_CANINTF,  MCP_TX0IF, 0x00);
	}
}
*/