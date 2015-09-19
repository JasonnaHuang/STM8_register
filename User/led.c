#include <stdio.h>
#include <math.h>
#include "iostm8s103f3.h"
#include "led.h"

static unsigned char sleepFlag = SLEEP_OFF;

void LED_Init(void)
{       
	//GPIO_Init(LED_RED_PORT,   (GPIO_Pin_TypeDef)LED_RED_PINS,   GPIO_MODE_OUT_PP_LOW_FAST);
	//GPIO_Init(LED_GREEN_PORT, (GPIO_Pin_TypeDef)LED_GREEN_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
	//GPIO_Init(LED_BLUE_PORT,  (GPIO_Pin_TypeDef)LED_BLUE_PINS,  GPIO_MODE_OUT_PP_LOW_FAST);
	PC_DDR |= 0xd0;
	PC_CR1 |= 0xd0;
	PC_CR2 |= 0xd0;
	//TIM1_OC1Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,TIM1_OUTPUTNSTATE_DISABLE,\
	0,TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	TIM1_CCMR1 = 0x60;
	TIM1_CCER1 &= ~0x0f;
	TIM1_CCER1 |= 0x09;//0x0b;
	TIM1_CCR1H = 0x00;
	TIM1_CCR1L = 0x00;
	//TIM1_OISR |= 0x01;
	TIM1_OISR &= ~0x03;
	TIM1_OISR |= 0x01;
	//TIM1_OC2Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,TIM1_OUTPUTNSTATE_DISABLE,\
    0,TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	TIM1_CCMR2 = 0x60;
	TIM1_CCER1 &= ~0xf0;
	TIM1_CCER1 |= 0x90;//0xb0;
	TIM1_CCR2H = 0x00;
	TIM1_CCR2L = 0x00;
	//TIM1_OISR |= 0x04;
	TIM1_OISR &= ~0xc0;
	TIM1_OISR |= 0x04;
	//TIM1_OC4Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,0,TIM1_OCPOLARITY_HIGH,TIM1_OCIDLESTATE_SET);
	TIM1_CCMR4 = 0x60;
	TIM1_CCER2 |= 0x10;//0x30
	TIM1_CCR4H = 0x00;
	TIM1_CCR4L = 0x00;
	TIM1_OISR &= ~0x40;
	//TIM1_CCxCmd(TIM1_CHANNEL_1, ENABLE);
	//TIM1_CCxCmd(TIM1_CHANNEL_2, ENABLE);
	//TIM1_CCxCmd(TIM1_CHANNEL_4, ENABLE);
	TIM1_CCER1 |= 0x01;
	TIM1_CCER1 |= 0x10;
	TIM1_CCER2 |= 0x10;
	//TIM1_OC1PreloadConfig(ENABLE);
	//TIM1_OC2PreloadConfig(ENABLE);
	//TIM1_OC4PreloadConfig(ENABLE);
	TIM1_CCMR1 |= 0x08;
	TIM1_CCMR2 |= 0x08;
	TIM1_CCMR4 |= 0x08;
}
/*
void LED_All_OFF(void)
{
        TIM1_CCR1H = 0x03;
	TIM1_CCR1L = 0xe8;
        TIM1_CCR2H = 0x03;
	TIM1_CCR2L = 0xe8;
        TIM1_CCR4H = 0x03;
	TIM1_CCR4L = 0xe8;
}

void LED_All_ON(void)
{
        TIM1_CCR1H = 0x00;
	TIM1_CCR1L = 0x00;
        TIM1_CCR2H = 0x00;
	TIM1_CCR2L = 0x00;
        TIM1_CCR4H = 0x00;
	TIM1_CCR4L = 0x00;
}

void LED_RED_ON(void)
{
        TIM1_CCR1H = 0x00;
	TIM1_CCR1L = 0x00;
        TIM1_CCR2H = 0x03;
	TIM1_CCR2L = 0xe8;
        TIM1_CCR4H = 0x03;
	TIM1_CCR4L = 0xe8;
}

void LED_BLUE_ON(void)
{
        TIM1_CCR1H = 0x03;
	TIM1_CCR1L = 0xe8;
        TIM1_CCR2H = 0x00;
	TIM1_CCR2L = 0x00;
        TIM1_CCR4H = 0x03;
	TIM1_CCR4L = 0xe8;
}

void LED_GREEN_ON(void)
{
        TIM1_CCR1H = 0x03;
	TIM1_CCR1L = 0xe8;
        TIM1_CCR2H = 0x03;
	TIM1_CCR2L = 0xe8;
        TIM1_CCR4H = 0x00;
	TIM1_CCR4L = 0x00;
}*/

void set_led_color(uint16_t R_value,uint16_t G_value,uint16_t B_value)
{  
    TIM1_CCR1H = R_value >> 8;
    TIM1_CCR1L = R_value;
    TIM1_CCR4H = B_value >> 8;
    TIM1_CCR4L = B_value; 
    TIM1_CCR2H = G_value >> 8;
    TIM1_CCR2L = G_value;
}

static void ledSleepHandle(void)
{
    static unsigned char count = 0;
    static unsigned char R = 100;
    unsigned char pluse_count = 0;
    
    count += 1;
    if(count > 200)
    {
        count = 0;
        return;
    }
    
    if(count < 100)
    {
        pluse_count = R - (int)sqrt(R*R - count*count);
    }
    if(count > 100)
    {
        pluse_count = R - (int)sqrt(R*R - (200 - count)*(200 - count));    
    }
    if(pluse_count < 3)//±ÜÃâµÆÃðµ¼ÖÂÉÁË¸¸Ð
        return;
    set_led_color(0,0,pluse_count);
}

void led_tick(void)
{
    static unsigned char count = 0;
    
    if(SLEEP_OFF == sleepFlag)
      return;
    
    count ++;
    if(count >= 200)
    {
        count = 0;
        ledSleepHandle();
    }
}

void ledSleepMode(sleepCmd_t cmd)
{
      sleepFlag = cmd;
}
