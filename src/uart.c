#include <uart.h>
#include "stm32f4xx.h"
#include "macro_utiles.h"

#define CIRCULAR_BUFFER_SIZE 20

#define USART_FLAG_TXE BIT7 // transmit buffer empty
#define USART_FLAG_RXNE BIT5 // receive buffer not empty

// baud rate
#define BAUD_RATE_MANTISSA 43
#define BAUD_RATE_FRACTION 12 // TODO: validate this

static uint8_t circular_buffer[CIRCULAR_BUFFER_SIZE];

static int head = 0;
static int tail = 0;
static int bytesReceived = 0;

/*
 * INTERRUPT HANDLER
 */

void USART2_IRQHandler()
{
	if (USART2->SR & USART_FLAG_RXNE) {
		circular_buffer[head] = USART2->DR;
		head = (head + 1) % CIRCULAR_BUFFER_SIZE;
	}
}

/*
 * FUNCTIONS
 */

void uart_init_uart()
{

	NVIC->ISER[1] |= BIT6; // Enable USART2 global interrupt
	RCC->APB1ENR |= BIT17; // Enable USART2 clock

	RCC->AHB1ENR |= BIT0; // GPIOA clock

	// set gpio mode, etc.
	GPIOA->MODER |= BIT5 | BIT7; // Alternate function for PA2 and PA3
	GPIOA->AFR[0] |= (0b0111 << 8) | (0b0111 << 12); // Alternate function 7: USART1-3

	USART2->CR1 &= ~BIT12; // 8 data bits

	USART2->CR1 |=
			BIT13 | // USART Enable
			BIT10 | // Enable parity bit
			BIT5 | // RXNE interrupt enable
			BIT3 | // Transmitter enable TODO: avoid transmitting
			BIT2 // Receiver enable
			;

	USART2->CR2 &= ~(BIT12 | BIT13); // 1 stop bit

	// set baud rate
	USART2->BRR = (BAUD_RATE_MANTISSA << 4) | (BAUD_RATE_FRACTION & 0b1111);
}

int uart_get_received_byte(char* buffer) {
	if (head != tail) {
		(*buffer) = circular_buffer[tail];
		tail = (tail + 1) % CIRCULAR_BUFFER_SIZE;
		return 1;
	} else {
		return 0;
	}
}

void uart_transmit_echo() {
	if (head != tail) {
		while (!(USART2->SR & USART_FLAG_TXE));
		USART2->DR = circular_buffer[tail];
		tail = (tail + 1) % CIRCULAR_BUFFER_SIZE;
	}
}
