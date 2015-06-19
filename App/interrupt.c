#include "iostm8s103f3.h"
#include "beep.h"
#include "sys.h"
#include "button.h"
#include "filter.h"

#pragma vector = TIM1_OVR_UIF_vector
__interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  Beep_tick();
  sys_tick_irq();
  filter_irq();
  //TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
  TIM1_SR1 = ~0x01;
}

#pragma vector = 0x05
__interrupt void EXTI_PORTA_IRQHandler(void)
{
  check_button();
}

unsigned char uart_data_flag = 0;
unsigned char uart_rec_count = 0;
unsigned char uart_rec_data[7] = {0};
unsigned short vout_value =0;

#pragma vector = UART1_R_RXNE_vector
__interrupt void UART1_RX_IRQHandler(void)
{
  unsigned char USART1_RX_BUF;

	//while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
  //while((UART1_SR & 0x20) == 0x00);
	//USART1_RX_BUF = UART1_ReceiveData8();
  USART1_RX_BUF = UART1_DR;

  if(USART1_RX_BUF == 0xaa)
  {
    uart_data_flag = 1;
    uart_rec_count = 0;
  }
  if(uart_data_flag == 1)
  {
    uart_rec_data[uart_rec_count] = USART1_RX_BUF;
		
    if(uart_rec_count == 6)
    {
      uart_data_flag = 0;
      if((uart_rec_data[6] == 0xff) && (uart_rec_data[5] == (unsigned char)(uart_rec_data[1] \
			+ uart_rec_data[2] + uart_rec_data[3] + uart_rec_data[4]))) 
      {
	vout_value = uart_rec_data[1]*256 + uart_rec_data[2];
	send_uart_value(vout_value);
      }
    }
    uart_rec_count ++;
  }
}