#include "macro_utiles.h"
#include "stm32f4xx.h"
#include "led.h"

void configureLEDs(){
	RCC->AHB1ENR |= BIT3;
	GPIOD->MODER |= BIT24;
	GPIOD->MODER &= ~BIT25;
	GPIOD->MODER |= BIT26;
	GPIOD->MODER &= ~BIT27;
	GPIOD->MODER |= BIT28;
	GPIOD->MODER &= ~BIT29;
	GPIOD->MODER |= BIT30;
	GPIOD->MODER &= ~BIT31;
}

void turnOnTheLed(){
	GPIOD->ODR |= LED_VERTE;
}

void turnOffTheLed(){
	GPIOD->ODR &= ~(LED_VERTE);
}
