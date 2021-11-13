#include "utils.h"
#include "stm32f4xx.h"
#include "macro_utiles.h"

void delay_cycles(int time){
	volatile int i;
	for(i = 0; i < time; i++);
}

void set_gpio_mode(char port, int pin_number, int mode)
{
	int shifted_mask = 0b11 << (2 * pin_number);
	int shifted_mode = mode << (2 * pin_number);

	switch(port) {
	case 'A':
		GPIOA->MODER = (GPIOA->MODER & ~shifted_mask) ^ shifted_mode;
		break;
	case 'B':
		GPIOB->MODER = (GPIOB->MODER & ~shifted_mask) ^ shifted_mode;
		break;
	case 'C':
		GPIOC->MODER = (GPIOC->MODER & ~shifted_mask) ^ shifted_mode;
		break;
	case 'D':
		GPIOD->MODER = (GPIOD->MODER & ~shifted_mask) ^ shifted_mode;
		break;
	case 'E':
			GPIOE->MODER = (GPIOE->MODER & ~shifted_mask) ^ shifted_mode;
			break;
	default:
		break;
	}
}

void set_gpio_output_type(char port, int pin_number, int type)
{
	int shifted_mask = 0b1 << pin_number;
	int shifted_type = type << pin_number;

	switch (port) {
	case 'A':
		GPIOA->OTYPER = (GPIOA->OTYPER & ~shifted_mask) ^ shifted_type;
		break;
	case 'B':
		GPIOB->OTYPER = (GPIOB->OTYPER & ~shifted_mask) ^ shifted_type;
		break;
	case 'C':
		GPIOC->OTYPER = (GPIOC->OTYPER & ~shifted_mask) ^ shifted_type;
		break;
	case 'D':
		GPIOD->OTYPER = (GPIOD->OTYPER & ~shifted_mask) ^ shifted_type;
		break;
	case 'E':
		GPIOE->OTYPER = (GPIOE->OTYPER & ~shifted_mask) ^ shifted_type;
		break;
	default:
		break;
	}
}

void set_gpio_pupdr_mode(char port, int pin_number, int pupdr_mode)
{
	int shifted_mask = 0b11 << (2 * pin_number);
	int shifted_mode = pupdr_mode << (2 * pin_number);

	switch(port) {
	case 'A':
		GPIOA->PUPDR = (GPIOA->PUPDR & ~shifted_mask) ^ shifted_mode;
		break;
	case 'B':
		GPIOB->PUPDR = (GPIOB->PUPDR & ~shifted_mask) ^ shifted_mode;
		break;
	case 'C':
		GPIOC->PUPDR = (GPIOC->PUPDR & ~shifted_mask) ^ shifted_mode;
		break;
	case 'D':
		GPIOD->PUPDR = (GPIOD->PUPDR & ~shifted_mask) ^ shifted_mode;
		break;
	case 'E':
		GPIOE->PUPDR = (GPIOE->PUPDR & ~shifted_mask) ^ shifted_mode;
		break;
	default:
		break;
	}
}

void set_gpio_output(char port, int pin_number, int value)
{
	int shifted_mask = 0b1 << pin_number;
	int shifted_value = value << pin_number;

	switch(port) {
	case 'A':
		GPIOA->ODR = (GPIOA->ODR & ~shifted_mask) ^ shifted_value;
		break;
	case 'B':
		GPIOB->ODR = (GPIOB->ODR & ~shifted_mask) ^ shifted_value;
		break;
	case 'C':
		GPIOC->ODR = (GPIOC->ODR & ~shifted_mask) ^ shifted_value;
		break;
	case 'D':
		GPIOD->ODR = (GPIOD->ODR & ~shifted_mask) ^ shifted_value;
		break;
	case 'E':
		GPIOE->ODR = (GPIOE->ODR & ~shifted_mask) ^ shifted_value;
		break;
	default:
		break;
	}
}

int get_gpio_input(char port, int pin_number)
{
	int shifted_mask = 0b1 << pin_number;
	int data = 0;

	switch(port) {
	case 'A':
		data = GPIOA->IDR & shifted_mask;
		break;
	case 'B':
		data = GPIOB->IDR & shifted_mask;
		break;
	case 'C':
		data = GPIOC->IDR & shifted_mask;
		break;
	case 'D':
		data = GPIOD->IDR & shifted_mask;
		break;
	case 'E':
		data = GPIOE->IDR & shifted_mask;
		break;
	default:
		break;
	}
	return data != 0;
}
