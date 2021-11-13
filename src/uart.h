
#ifndef UART_H_
#define UART_H_

void USART2_IRQHandler();

void uart_init_uart();
int uart_get_received_byte(char* buffer);
void uart_transmit_echo();
char* last_three_received_bytes();


extern char* receivedBytes[3];

#endif /* UART_H_ */
