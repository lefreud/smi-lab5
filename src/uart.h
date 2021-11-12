
#ifndef UART_H_
#define UART_H_

void uart_init_uart();
int uart_get_received_byte(char* buffer);
void uart_transmit_echo();

#endif /* UART_H_ */
