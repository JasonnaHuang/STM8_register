/* FILTER.H file
 * Date:2015.6.4
 * Auth:Jason.H_{
 */
#ifndef __FILTER_H
#define __FILTER_H

void filter_irq(void);
void send_uart_value(unsigned short uart_value);
unsigned short get_PM2_5_value(void);

#endif
