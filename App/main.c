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
  //CLK_HSIPrescalerConfig(CLK_PRESCA LER_HSIDIV1);
  CLK_CKDIVR = 0x00;
  Tim1_Init();
  LED_Init();
  Motor_Init();
  Beep_Init();
  Button_Init();
  Uart_Init();
  if(!Status_Init())
    return 0;
  asm("rim");//开全局中断
  
  UART1_SendString("start running...");
  delay_ms(1000);
  while (1)
  {
    if(display_value != get_PM2_5_value())
    {
          display_value = get_PM2_5_value();
          Send_4Bit_Num( display_value );
    }
    delay_ms(1000);
  }
}