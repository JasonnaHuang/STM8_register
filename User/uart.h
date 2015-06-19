/* UART.H file
 * Date:2015.6.3
 * Auth:Jason.H_{
 */
#ifndef __UART_H
#define __UART_H

void Uart_Init(void);
void UART1_SendByte(unsigned char data);
void UART1_SendString(unsigned char * data);
void Send_4Bit_Num(unsigned short num);

#endif