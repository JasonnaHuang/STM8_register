#include "iostm8s103f3.h"

#include "buzzer.h"

void Beep_Init(void)
{
/*	//PD3:BEEP
	PD_DDR |= 0x08;
	PD_CR1 |= 0x08;
	//PD2:SWBEEP
	PD_DDR |= 0x04;
	PD_CR1 |= 0x04;
	PD_ODR |= 0x04;
*/
        //PD2:BEEP
        PD_DDR |= 0x04;
        PD_CR1 |= 0x04;
        //PC5:SWBEEP
//        PC_DDR |= 0x20;
//        PC_CR1 |= 0x20;
//        PC_ODR |= 0x20;
        //PB5:SWBEEP
        PB_DDR |= 0x20;
        PB_CR1 |= 0x20;
        PB_ODR |= 0x20;
        
}

void BEEP_SetFreq(unsigned short iFreq)
{
	unsigned short PERIOD = 1000000/iFreq - 1;
	unsigned short WIDTH = PERIOD/2;
	//TIM2_TimeBaseInit(TIM2_PRESCALER_16,PERIOD);
	TIM2_PSCR = 0x04;
	TIM2_ARRH = PERIOD >> 8;
	TIM2_ARRL = PERIOD;
	//TIM2_ARRPreloadConfig(ENABLE); 
	TIM2_CR1 |= 0x80;
	//TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,WIDTH,TIM2_OCPOLARITY_LOW);
	TIM2_CCMR3 |= 0x60;
	TIM2_CCER2 |= 0x03;
	TIM2_CCR3H = WIDTH >> 8;
	TIM2_CCR3L = WIDTH;
	//TIM2_OC3PreloadConfig(ENABLE);
	TIM2_CCMR3 |= 0x08;	
}

void BeepPwrOn(void)
{
	//GPIO_WriteHigh(SWBEEP_GPIO_PORT,SWBEEP_GPIO_PINS);
	//PB_ODR &= ~0x20;
        PB_ODR |= 0x20;
}

void BeepPwrOff(void)
{
	//GPIO_WriteLow(SWBEEP_GPIO_PORT,SWBEEP_GPIO_PINS);
	//PB_ODR |= 0x20;
        PB_ODR &= ~0x20;
}

void BEEP_On(void)
{
	//TIM2_Cmd(ENABLE);
	TIM2_CR1 |= 0x01;
}

void BEEP_Off(void)
{
	//TIM2_Cmd(DISABLE);
	TIM2_CR1 &= ~0x01;
}

void Beep_tick(void)
{
  static unsigned char count = 0;
  count ++;
  if(count >= 100)
  {
    count = 0;
    BuzzerCtrl();
  }
}