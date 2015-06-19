/* SYS.H file
 * Date:2015.6.3
 * Auth:Jason.H_{
 */
#ifndef __SYS_H
#define __SYS_H

void delay_ms(unsigned long ms);
void sys_tick_irq(void);
unsigned long get_time(void);
void set_long_press_flag(void);
void reset_long_press_flag(void);

#endif