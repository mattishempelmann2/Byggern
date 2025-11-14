/*
 * IO_board.h
 *
 * Created: 09.10.2025 10:49:44
 *  Author: johankna
 */ 


#ifndef IO_BOARD_H_
#define IO_BOARD_H_

void IO_cmd(uint8_t command, int size, uint8_t* data);

void IO_button_init(uint8_t* data);

void IO_button_on_leds(uint8_t led_num);

uint8_t button_pressed();

#endif /* IO_BOARD_H_ */