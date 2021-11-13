#ifndef TIMER_H_
#define TIMER_H_

#define TIM2_PERIOD_SECONDS			0.5
#define TIM2_PREVIOUS_PRESCALERS 	2
#define TIM2_PRESCALER 				1
#define TIM2_AUTO_RELOAD			(SystemCoreClock / (TIM2_PREVIOUS_PRESCALERS * TIM2_PRESCALER)) * TIM2_PERIOD_SECONDS

void timer2_init();
void TIM2_IRQHandler();

extern int second;

#endif /* TIMER_H_ */
