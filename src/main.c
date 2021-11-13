/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2021-11-10

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "uart.h"
#include "macro_utiles.h"
#include "lcd.h"
#include "utils.h"
#include "string.h"
#include "pins.h"
#include "timer.h"
#include "led.h"
#include "commandParser.h"

static volatile uint32_t lastTimeRead = -1;
static volatile uint32_t lastTransmissionNumber = 0;

int main(void)
{
	uart_init_uart();
	lcd_init();
    lcd_write_first_row();
    goToSecondLine();
    configureLEDs();
    timer2_init();

	receivedBytes[0] = 'C';
	receivedBytes[1] = '0';
	receivedBytes[2] = 0x8d;
	receptionComplete = 1;

	while (1) {
		/* // USART2->CR1 |= BIT13; // USART Enable
		volatile int a = USART2->SR;
		while (!(USART2->SR & BIT7));
		a = USART2->SR;
		USART2->DR = 0xAA;
		volatile int b = USART2->DR;
		// USART2->CR1 &= ~BIT13; // USART Disable*/
		uart_transmit_echo();

		if(lastTimeRead != second){
			lastTimeRead = second;
			lcd_write_time(lastTimeRead);
		}

		if(receptionComplete == 1){
			parseCommand(receivedBytes);
		}
	}
}
