#include "lcd.h"
#include "utils.h"
#include "pins.h"
#include "stm32f4xx.h"
#include "macro_utiles.h"
#include "string.h"
#include <stdlib.h>


static char* INSTRUCTION;


//Numbers of the Keypad
#define NUMBER0				"00110000"
#define NUMBER1				"00110001"
#define NUMBER2				"00110010"
#define NUMBER3				"00110011"
#define NUMBER4				"00110100"
#define NUMBER5				"00110101"
#define NUMBER6				"00110110"
#define NUMBER7				"00110111"
#define NUMBER8				"00111000"
#define NUMBER9				"00111001"

/* Private functions */

char* charToBinary(char c){
	char* binaryForm;
	binaryForm = (char*)malloc(8);
	int i;
	for (i = 0; i < 8; ++i) {
		if ((c & (1 << i)) == 0) {
			binaryForm[7 - i] = '0';
		} else {
			binaryForm[7 - i] = '1';
		}
	}
	binaryForm[i] = '\0';
	return (char*)binaryForm;
}

void LCD_pre_Send_Command(){
	set_gpio_output(LCD_PORT, LCD_RS, 0); //Command Mode
	set_gpio_output(LCD_PORT, LCD_RW, 0); //R/W to 0
	delay_cycles(12000);
	set_gpio_output(LCD_PORT, LCD_EN, 1); //Set Enable to 1
}

void LCD_post_Send(){
	set_gpio_output(LCD_PORT, LCD_EN, 0); //Set Enable to 0
}

void LCD_pre_Write_Command(){
	set_gpio_output(LCD_PORT, LCD_RS, 1); //Data Mode
	set_gpio_output(LCD_PORT, LCD_RW, 0); //R/W to 0
	delay_cycles(12000);
	set_gpio_output(LCD_PORT, LCD_EN, 1); //Set Enable
}

void LCD_write_Instruction(char* instruction){
	// write instruction on 8 bit data bus
	set_gpio_output(LCD_PORT_D4_D7, D7, (int)instruction[0]);
	set_gpio_output(LCD_PORT_D4_D7, D6, (int)instruction[1]);
	set_gpio_output(LCD_PORT_D4_D7, D5, (int)instruction[2]);
	set_gpio_output(LCD_PORT_D4_D7, D4, (int)instruction[3]);
	set_gpio_output(LCD_PORT_D0_D3, D3, (int)instruction[4]);
	set_gpio_output(LCD_PORT_D0_D3, D2, (int)instruction[5]);
	set_gpio_output(LCD_PORT_D0_D3, D1, (int)instruction[6]);
	set_gpio_output(LCD_PORT_D0_D3, D0, (int)instruction[7]);
}

void lcd_init(){
	// enable clock
	RCC->AHB1ENR |= BIT4;
	RCC->AHB1ENR |= BIT1;
	RCC->AHB1ENR |= BIT0;

	// set GPIO modes
	set_gpio_mode(LCD_PORT, LCD_RS, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT, LCD_RW, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT, LCD_EN, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D0_D3, D0, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D0_D3, D1, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D0_D3, D2, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D0_D3, D3, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D4_D7, D4, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D4_D7, D5, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D4_D7, D6, GPIO_OUTPUT_MODE);
	set_gpio_mode(LCD_PORT_D4_D7, D7, GPIO_OUTPUT_MODE);
	//Next command set the display
	LCD_pre_Send_Command();
	INSTRUCTION = "00111000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	LCD_pre_Send_Command();
	INSTRUCTION = "00111000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	LCD_pre_Send_Command();
	INSTRUCTION = "00111000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command display off
	LCD_pre_Send_Command();
	INSTRUCTION = "00001000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command clear display
	LCD_pre_Send_Command();
	INSTRUCTION = "00000001";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command entry mode set
	LCD_pre_Send_Command();
	INSTRUCTION = "00000110";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command set function
	LCD_pre_Send_Command();
	INSTRUCTION = "00111000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command display on
	LCD_pre_Send_Command();
	INSTRUCTION = "00001110";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();

	//Next command entry mode set
	LCD_pre_Send_Command();
	INSTRUCTION = "00000110";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();
}

void lcd_write_first_row(){
	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('F'));
	LCD_post_Send();

	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('F'));
	LCD_post_Send();

	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('C'));
	LCD_post_Send();

	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('J'));
	LCD_post_Send();

	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('H'));
	LCD_post_Send();

	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary('_'));
	LCD_post_Send();
}

void goToSecondLine(){
	// go to second line
	LCD_pre_Send_Command();
	INSTRUCTION = "11000000";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();
}

void goToFirstLine(){
	// go to first line
	LCD_pre_Send_Command();
	INSTRUCTION = "00000010";
	LCD_write_Instruction(INSTRUCTION);
	LCD_post_Send();
}

void lcd_write_characters(char* characters){
	for (int i = 0; i < strlen(characters); i++) {
		LCD_pre_Write_Command();
		LCD_write_Instruction(charToBinary(characters[i]));
		LCD_post_Send();
	}
}

void lcd_write_time(int currentTime){
	goToFirstLine();
	lcd_write_first_row();
	// Count digits in number of seconds
	int m = currentTime;
	int digit = 0;
	while (m) {
		digit++;
		m /= 10;
	}
	// Declare char array for result
	char* arr;
	// Declare duplicate char array
	char arr1[digit];
	// Memory allocation of array
	arr = (char*)malloc(digit);
	// Separating integer into digits and
	// accommodate it to character array
	int index = 0;
	while (currentTime) {
		// Separate last digit from
		// the number and add ASCII
		// value of character '0' is 48
		arr1[++index] = currentTime % 10 + '0';
		// Truncate the last
		// digit from the number
		currentTime /= 10;
	}
	// Reverse the array for result
	int i;
	for (i = 0; i < index; i++) {
		arr[i] = arr1[index - i];
	}
	// Char array truncate by null
	arr[i] = '\0';
	lcd_write_characters((char*)arr);
}

void lcd_write_blank_space(){
	LCD_pre_Write_Command();
	LCD_write_Instruction(charToBinary(' '));
	LCD_post_Send();
}

