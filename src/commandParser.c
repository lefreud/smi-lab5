#include "macro_utiles.h"
#include "stm32f4xx.h"
#include "commandParser.h"
#include "lcd.h"

static char allReceivedBytes[16];
static unsigned int bytesToShow = 0;

void parseCommand(char* receivedBytes){
	static int value;
	char command = *receivedBytes;
	receivedBytes++;
	char parameter = *receivedBytes;
	receivedBytes++;
	char checksum = *receivedBytes;
	value = (int)command + (int)parameter + (int)checksum;
	if(value % 256 == 0){
		if(command == 0x41){
		   if(parameter == 0x30) {
			   turnOffTheLed();
		   } else if (parameter == 0x31) {
			   turnOnTheLed();
		   }
		} else if (command == 0x42){
			goToSecondLine();
			for(int i = 0; i < 16; i++){
				lcd_write_blank_space();
			}
		} else if(command == 0x43) {
			allReceivedBytes[bytesToShow] = parameter;
			bytesToShow++;
			if(16 <= bytesToShow){
				bytesToShow = 0;
			}
			goToSecondLine();
			lcd_write_characters(allReceivedBytes);
		}
	}
}
