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
uint8_t available_message = 0;

//Remember callback interrup tips from the TA
int main(void)
{	
	UART_init(MYUBRR);
	init_SPI();
	ADC_init();
	Calibrate_joystick();
	CAN_initialize();
	
	printf("Restarted	\n\r");
	
	display_initialize();
	display_clear();
	display_init_SRAM();
	
	display_pixel_on(0,0);
	display_pixel_on(127,0);
	display_pixel_on(0,63);
	display_pixel_on(127,63);
	
	uint8_t score = 0;
	uint8_t points = 0;
	uint8_t highscores[2];
	
	char* main_items[] = {"Welcome" , " ", "start game", "highscores"};
	char* start_game_items[] = {"Good luck" , " ", "Points left: " +score};
	char* highscores_items[] = {"Highscores", " ", highscores[0], highscores[1], highscores[2]};
	char* game_over_items[] = {"Game Over", " ", "Your score" + score, "Restart", "Quit"};
	

	menu main_menu;
	main_menu.menu_items = main_items;
	main_menu.length = 4;
	
	menu start_menu;
	start_menu.menu_items = start_game_items;
	start_menu.length = 3;
	
	menu highscore_menu;
	highscore_menu.menu_items = highscores_items;
	highscore_menu.length = 5;
	
	menu game_over_menu;
	game_over_menu.menu_items = game_over_items;
	game_over_menu.length = 5;
	
	menu_pos menu_p;
	menu_p.current_pos = 2;
	
	display_print_menu(menu_p.current_pos,main_menu);
	display_all_pages();
	
	menu *current_menu = &main_menu;
	
    while (1) 
    {
		updateJoystick();
		uint8_t selected_option = display_update_menu(&menu_p, *current_menu);
		if(current_menu == &main_menu) {
			if(selected_option == 2){
				CAN_start();
				
				display_clear();
				current_menu = &start_menu;
				display_print_menu(menu_p.current_pos,*current_menu);
				
				
			}
		}
		else if( current_menu == &start_menu) selected_option = display_update_menu(&menu_p, start_menu);
		
		Joystick_CAN();
		
		_delay_ms(5);
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
	
	available_message = 1;
}
*/


/*

1. MAIN MENU -> PLAY |highscores
2. PLAY => SEND MESSAGE AND CHANGE MENU TO SOMETHIG (goodluck and points)
3. "SCORE" starts at 5 and the timer is your final score
4. WHEN 0 -> game over to node 1
5. GAME OVER = Play again or go to main menu

*/