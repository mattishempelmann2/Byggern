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

void display_goto_line(int line);

void display_goto_column(int column);

void display_clear_line(int line);

void display_clear_column(int column);

void display_position(int row,int column);

void display_print(char* letter);

//void display_line(uint8_t start, uint8_t end);

void display_all_pages();

void display_init_SRAM();

uint8_t display_validate_line(uint8_t line);





#endif /* DISPLAY_H_ */