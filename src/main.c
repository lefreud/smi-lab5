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
#include "global_config.h"
#include "partie2.h"
#include "system_stm32f4xx.h"

static volatile uint32_t lastTimeRead = -1;
static volatile uint32_t lastTransmissionNumber = 0;

int main(void)
{
    command_parser_init();
	uart_init_uart();
	lcd_init();
    lcd_write_first_row();
    goToSecondLine();
    configureLEDs();
    timer2_init();

#ifdef PARTIE_2
    partie2_init();
#endif
    char latest_byte;

	while (1) {
		if (uart_get_received_byte(&latest_byte)) {
			consume_byte(latest_byte);
		}

		if(lastTimeRead != second){
			lastTimeRead = second;
			lcd_write_time(lastTimeRead);
		}
#ifdef PARTIE_2
		partie2_dispatch_main_event();
#endif
	}
}
