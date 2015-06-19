#include "iostm8s103f3.h"
#include "uart.h"

void Uart_Init(void)
{
	PD_CR2 &= ~0x60;
	PD_DDR &= ~0x40;
	PD_DDR |= 0x20;
	PD_CR1 |= 0x62;
	PD_CR2 |= 0x20;
	//UART1_Init((u32)2400, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, \
				UART1_PARITY_NO , UART1_SYNCMODE_CLOCK_DISABLE , \
				UART1_MODE_TXRX_ENABLE);
	/*UART1_CR1 &= ~0x10;
	UART1_CR1 |= 0x00;
	UART1_CR3 &= ~0x30;
	UART1_CR3 |= 0x00;
	
	UART1_CR1 &= ~0x06;
	UART1_CR1 |= 0x00;
	
	UART1_BRR1 &= ~0xff;
	UART1_BRR2 &= ~0xf0;
	UART1_BRR2 &= ~0x0f;
	UART1_BRR1 |= 0xA0;
	UART1_BRR2 |= 0x1A;
	
	UART1_CR2 &= ~0x0c;
	UART1_CR3 &= ~0x07;
	UART1_CR3 |= 0x00;
	
	UART1_CR2 |= 0x04;
	UART1_CR2 |= 0x08;
	//UART1_CR2 |= 0x0c;
	UART1_CR3 &= ~0x08;
	//UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
	UART1_CR2 |= 0x20;
	//UART1_Cmd( ENABLE );
	UART1_CR1 &= ~0x20;*/
	
        UART1_CR1 = 0x00;
        UART1_CR2 = 0x00;
        UART1_CR3 = 0x00;
        // 设置波特率，必须注意以下几点：
      // (1) 必须先写BRR2
      // (2) BRR1存放的是分频系数的第11位到第4位，
      // (3) BRR2存放的是分频系数的第15位到第12位，和第3位
      // 到第0位
      // 例如对于波特率位9600时，分频系数=2000000/9600=208
      // 对应的十六进制数为00D0，BBR1=0D,BBR2=00
        UART1_BRR2 = 0x1A;
	UART1_BRR1 = 0xA0;
	
	UART1_CR2 = 0x2c; 
}

static void UART1_SendByte(unsigned char data)
{
	//UART1_SendData8((unsigned char)data);
	
	//while(UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
	while((UART1_SR & 0x80) == 0x00);
        UART1_DR = data;
}

void UART1_SendString(unsigned char * data)
{
	do
	{
		UART1_SendByte(*data);
	}
	while(*++data != '\0');
}

void Send_4Bit_Num(unsigned short num)
{
	UART1_SendByte(num/1000 + 0x30);
	UART1_SendByte(num%1000/100 + 0x30);
	UART1_SendByte(num%100/10 + 0x30);
	UART1_SendByte(num%10 + 0x30);
}