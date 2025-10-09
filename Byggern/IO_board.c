/*
 * IO_board.c
 *
 * Created: 09.10.2025 10:49:32
 *  Author: johankna
 */ 

#include "Includes.h"

int turn = 0;
void IO_button_init(uint8_t* data){
	uint8_t command = 0x04;
	spi_command_read(command, IO, data, sizeof(data));
	//printf("\n\n Values: ");
	//for(int i = 0; i < sizeof(data); i++) printf(" %d ", data[i]);
}

void IO_button_on_leds(uint8_t led_num){
	//led 0 button 6 
	uint8_t command[] = {0x05, 0x00, 0xFF};
	if(turn) command[2] = ~command[2];
	spi_write_bytes(command, sizeof(command),IO);
	turn = !turn;
}





