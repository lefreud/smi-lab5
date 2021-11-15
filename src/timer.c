#include "timer.h"
#include "macro_utiles.h"
#include "stm32f4xx.h"
#include "global_config.h"
#include "partie2.h"
#include "system_stm32f4xx.h"

volatile uint32_t tim2CycleCounter = 0;

second = 0;

void timer2_init(){
	RCC->APB1ENR |= BIT0; //TIM2 clock enable
	TIM2->PSC = TIM2_PRESCALER - 1;
	TIM2->ARR = (TIM2_AUTO_RELOAD - 1)/500; //Needs to be 1 millisec to work with the if conditions
	TIM2->DIER |= BIT0; //Update interrupt enable
	NVIC->ISER[0] = BIT28; //Enable TIM2 interrupt
	TIM2->CR1 |= BIT0; //TIM2 counter enable
}

void BoucleDAttente(short Nombre_microseconde_Dattente)
{
	int N = (int) Nombre_microseconde_Dattente * (SystemCoreClock / (1000000 * 12.5));
	for (volatile int i = 0; i < N; i++);
}

void TIM2_IRQHandler(){
	TIM2->SR &= ~BIT0;
	if (tim2CycleCounter == 0) {
		second++; // We increment the number of second since the last reset.
	}
	if(second == 100000){
		second = 0;
	}
	tim2CycleCounter = (tim2CycleCounter + 1) % 1000;

#ifdef PARTIE_2
    partie2_dispatch_timer_event();
    BoucleDAttente(PARTIE_2_DELAI_US);
#endif
}
