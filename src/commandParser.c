#include "macro_utiles.h"
#include "stm32f4xx.h"
#include "commandParser.h"
#include "lcd.h"
#include "led.h"

#define COMMAND_BUFFER_SIZE 3
#define LCD_LINE_SIZE 16

static char allReceivedBytes[16];
static unsigned int bytesToShow = 0;
static int current_byte_index = 0;
static char command_buffer[COMMAND_BUFFER_SIZE];

void command_parser_init() {
	current_byte_index = 0;
	for (int i = 0; i < COMMAND_BUFFER_SIZE; i++) {
		command_buffer[i] = 0;
	}
	for (int i = 0; i < LCD_LINE_SIZE; i++) {
		allReceivedBytes[i] = ' ';
	}
}

void consume_byte(char received_byte) {

	command_buffer[current_byte_index] = received_byte;
	if (current_byte_index == 2) {
		char command = command_buffer[0];
		char parameter = command_buffer[1];
		char checksum = command_buffer[2];

		// checksum (modulo 256 is implicit, char will overflow)
		if (((int) command + (int) parameter + (int) checksum) % 256 == 0) {
			if(command == 0x41){
			   if(parameter == 0x30) {
				   turnOffTheLed();
			   } else if (parameter == 0x31) {
				   turnOnTheLed();
			   }
			} else if (command == 0x42){
				goToSecondLine();
				for(int i = 0; i < LCD_LINE_SIZE; i++){
					lcd_write_blank_space();
					allReceivedBytes[i] = ' ';
					bytesToShow = 0;
				}
			} else if(command == 0x43) {
				allReceivedBytes[bytesToShow] = parameter;
				bytesToShow = (bytesToShow + 1) % LCD_LINE_SIZE;
				goToSecondLine();
				lcd_write_characters(allReceivedBytes);
			}
		}
	}

	current_byte_index = (current_byte_index + 1) % COMMAND_BUFFER_SIZE;
}
