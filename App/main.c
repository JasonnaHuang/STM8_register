#include "iostm8s103f3.h"
#include "led.h"
#include "tim.h"
#include "motor.h"
#include "beep.h"
#include "buzzer.h"
#include "button.h"
#include "status.h"
#include "uart.h"
#include "sys.h"
#include "filter.h"

int main(void)
{
  unsigned short display_value;
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  CLK_CKDIVR = 0x00;
  Tim1_Init();
  LED_Init();
  Motor_Init();
  Beep_Init();
  Button_Init();
  Status_Init();
  Uart_Init();
  asm("rim");//开全局中断
  
  LED_All_ON();
  BuzzerStart(POLY_ON);
  UART1_SendString("hello,world");
  delay_ms(1000);
  while (1)
  {
    if(display_value != get_PM2_5_value())
    {
          display_value = get_PM2_5_value();
          Send_4Bit_Num( display_value );
    }
//    PB_ODR ^= 0x20;
    delay_ms(1000);
  }
}