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

volatile CANMessage received_message;
volatile uint8_t available_message = 0;

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
	

	
	uint8_t score = 1;
	uint8_t points = 0;
	uint8_t highscores[2];
	char* buffer[16];
	char* buffer2[16];
	
	sprintf(buffer, "Points left:  %d", score);
	sprintf(buffer2, "Your score:  %d", score);

	
	char* main_items[] = {"Welcome" , " ", "start game", "highscores"};
	char* start_game_items[] = {"Good luck" , " ", buffer};
	char* highscores_items[] = {"Highscores", " ", highscores[0], highscores[1], highscores[2]};
	char* game_over_items[] = {"Game Over", " ", buffer2, "Restart", "Quit"};
	

	menu main_menu;
	main_menu.menu_items = main_items;
	main_menu.length = 4;
	
	menu game_menu;
	game_menu.menu_items = start_game_items;
	game_menu.length = 3;
	
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
	
	score = 5;
	
    while (1) 
    {

		updateJoystick();
		uint8_t selected_option = display_update_menu(&menu_p, *current_menu);
		//uint8_t selected_option = 0;
		if(current_menu == &main_menu) {
			if(selected_option == 2){
				
				CAN_start();
				//start timer
				display_clear();
				current_menu = &game_menu;
				sprintf(buffer, "Points left: %d", score);
				char* start_game_items[] = {"Good luck" , " ", buffer};
				menu_p.current_pos = 2;
				display_print_menu(menu_p.current_pos,*current_menu);
				
				
				
				display_pixel_on(0,0);
				display_pixel_on(127,0);
				display_pixel_on(0,63);
				display_pixel_on(127,63);
				
				
			}
		}
 		else if( current_menu == &game_menu) {
			Joystick_CAN();
	 		if(score == 0) {
		 		display_clear();
		 		current_menu = &game_over_menu;
				menu_p.current_pos = 3;
		 		display_print_menu(menu_p.current_pos,*current_menu);
				 
				 //stop timer
				 //save value
	 		}
	 		else if(available_message) {
		 		score--;
		 		available_message = 0;
		 		sprintf(buffer, "Points left:  %d", score);
		 		char* start_game_items[] = {"Good luck" , " ", buffer};
		 		display_invert_page(menu_p.current_pos);
		 		display_print_menu(menu_p.current_pos,*current_menu);
	 		}
 		} else if (current_menu = &game_over_menu) {
			 score = 5;
			if(selected_option == 3) {
				display_clear();
				current_menu = &game_menu;
				sprintf(buffer, "Points left: %d", score);
				char* start_game_items[] = {"Good luck" , " ", buffer};
				menu_p.current_pos = 2;
				display_print_menu(menu_p.current_pos,*current_menu);
				
			}
			else if (selected_option == 4) {
				display_clear();
				current_menu = &main_menu;
				menu_p.current_pos = 2;
				display_print_menu(menu_p.current_pos,*current_menu);
				
			}
		 }
		
		//
		
		_delay_ms(5);
		
		//printf("nothing \n\r");

	}
	
}


ISR(INT0_vect) {
	uint8_t intf;
	mcp2515_read(&intf, MCP_CANINTF, 1);
	if (intf & (MCP_RX0IF)) {
		//CAN_receive(&received_message);
		//printf("0");
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0x00);
		available_message = 1;
	}
	if (intf & (MCP_RX1IF)) {
		//CAN_receive(&received_message);
		//printf("1");
		mcp2515_bit_modify(MCP_CANINTF, MCP_RX1IF, 0x00);
		available_message = 1;
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
	
	if(intf & (MCP_MERRF)){
		mcp2515_bit_modify(MCP_CANINTF, MCP_MERRF, 0x00);
	}
	
	if(intf & (MCP_ERRIF)){
		mcp2515_bit_modify(MCP_CANINTF, MCP_ERRIF, 0x00);
	}
	
	if(intf & (MCP_WAKIF)){
		mcp2515_bit_modify(MCP_CANINTF, MCP_WAKIF, 0x00);
	}
	
	//printf(" %d,", intf);
	
// 	if (intf & (MCP_ERRIF | MCP_WAKIF | MCP_MERRF)) {
// 		mcp2515_bit_modify(MCP_CANINTF, intf & (MCP_ERRIF | MCP_WAKIF | MCP_MERRF), 0x00);
// 	}
	
}



/*

1. MAIN MENU -> PLAY |highscores
2. PLAY => SEND MESSAGE AND CHANGE MENU TO SOMETHIG (goodluck and points)
3. "SCORE" starts at 5 and the timer is your final score
4. WHEN 0 -> game over to node 1
5. GAME OVER = Play again or go to main menu

*/