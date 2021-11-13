#ifndef UTILS_H_
#define UTILS_H_

// common board utility functions

#define GPIO_INPUT_MODE			0b00
#define GPIO_OUTPUT_MODE		0b01

#define GPIO_OUTPUT_PUSH_PULL	0b0
#define GPIO_OUTPUT_OPEN_DRAIN	0b1

#define GPIO_PUPDR_NONE			0b00
#define GPIO_PUPDR_PULL_UP		0b01
#define GPIO_PUPDR_PULL_DOWN	0b10

void delay_cycles(int time);
void set_gpio_mode(char port, int pin_number, int mode);
void set_gpio_output_type(char port, int pin_number, int type);
void set_gpio_pupdr_mode(char port, int pin_number, int pupdr_mode);
void set_gpio_output(char port, int pin_number, int value);
int get_gpio_input(char port, int pin_number);

#endif /* UTILS_H_ */
