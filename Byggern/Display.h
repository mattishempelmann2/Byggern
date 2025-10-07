/*
 * Display.h
 *
 * Created: 02.10.2025 08:52:45
 *  Author: johankna
 */ 

#include "Includes.h"


#ifndef DISPLAY_H_
#define DISPLAY_H_

void display_initialize();

void display_cmd(uint8_t* command, int size);
	
void display_data(uint8_t* data, int size);

void display_reset();

void display_clear();

void display_home();

void display_go_to_line(uint8_t line);

void display_go_to_column(uint8_t column);

void display_clear_line(uint8_t line);

void display_clear_column(uint8_t column);

void display_position(uint8_t row,uint8_t column);

void display_print(char* letter, uint8_t page);

//void display_line(uint8_t start, uint8_t end);

void display_all_pages();

void display_init_SRAM();

uint8_t display_validate_line(uint8_t line);

uint8_t diplay_validate_column(uint8_t column);

void display_pixel_on(uint8_t x, uint8_t y);

void display_pixel_off(uint8_t x, uint8_t y);

void draw_filled_circle(uint8_t cx, uint8_t cy, uint8_t r);

display_invert_page(uint8_t page);

void update_menu(uint8_t page);

typedef struct {
	uint8_t current_pos;
	uint8_t previous_pos;
}menu_pos;

void change_menu(menu_pos* menu);











#endif /* DISPLAY_H_ */