#include "iostm8s103f3.h"
#include "tim.h"

void Tim1_Init(void)
{
	//TIM1_TimeBaseInit(16,TIM1_COUNTERMODE_UP,1000,0);
	TIM1_PSCRL |= 0x10;
	TIM1_ARRH = 0x03;
	TIM1_ARRL = 0xE8;
	//TIM1_ARRPreloadConfig(ENABLE);
	TIM1_CR1 |= 0x80;
	//TIM1_CtrlPWMOutputs(ENABLE); 
	TIM1_BKR |= 0x80;
	//TIM1_ITConfig(TIM1_IT_UPDATE , ENABLE);
	TIM1_IER |= 0x01;
	//TIM1_Cmd(ENABLE);
	TIM1_CR1 |= 0x81;
}