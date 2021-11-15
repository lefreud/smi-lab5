#include "partie2.h"
#include "stm32f4xx.h"
#include "macro_utiles.h"

// PB11, PB12, PB13
#define UART_EVENT_PIN 11
#define TIMER_EVENT_PIN 12
#define MAIN_EVENT_PIN 13

void partie2_init()
{
	RCC->AHB1ENR |= BIT1;
	GPIOB->MODER |= (0b01 << UART_EVENT_PIN * 2)
				| (0b01 << TIMER_EVENT_PIN * 2)
				| (0b01 << MAIN_EVENT_PIN * 2);

}

inline void partie2_dispatch_uart_event()
{
	GPIOB->ODR ^= (1 << UART_EVENT_PIN);
}
inline void partie2_dispatch_timer_event()
{
	GPIOB->ODR ^= (1 << TIMER_EVENT_PIN);
}
inline void partie2_dispatch_main_event()
{
	GPIOB->ODR ^= (1 << MAIN_EVENT_PIN);
}
