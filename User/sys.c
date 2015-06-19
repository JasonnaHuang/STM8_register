/* SYS.C file
 * Date:2015.6.3
 * Auth:Jason.H_{
 */
#include "sys.h"
#include "button.h"

static volatile unsigned long sys_count = 0;
static unsigned char long_press_flag = 0;

static unsigned long now_time = 0;
//16MHz
void delay_ms(unsigned long ms)
{
  unsigned char i;
  unsigned long time_now = 0;
  time_now = sys_count;
  while(sys_count - time_now >= ms)
  {
    if(i >= 200)
      i = 0;
  }
  return;
}

void sys_tick_irq(void)
{
  sys_count ++;
  if(long_press_flag)
  {
    if((sys_count - now_time) >= ShutDown_TimeOut)
    {
      long_press_flag = 0;
      _button_timeout_hander();
    }
  }
}

unsigned long get_time(void)
{
  return sys_count;
}

void set_long_press_flag(void)
{
  long_press_flag = 1;
  now_time = sys_count;
}

void reset_long_press_flag(void)
{
  long_press_flag = 0;
}