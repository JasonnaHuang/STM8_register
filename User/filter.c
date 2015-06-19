/* FILTER.C file
 * Date:2015.6.4
 * Auth:Jason.H_{
 */
#include "filter.h"
#include "led.h"

#define N 12

static unsigned char adc_count = 0;
//static u8 vaild_value_count = 0;//有效值标号计数
static unsigned short vaild_value[N+1];//取出有效值作为平均计算
volatile static unsigned short expect_final;//最终计算值
unsigned long total_vaild = 0;
static unsigned short uart_adc_value = 0;
static unsigned short display_value = 0;
static unsigned char compute_count = 0;
static unsigned char compute_rate = 0;
static void compute_display_value(void);

unsigned short filter(void)
{
  unsigned char i;
  total_vaild = 0;
  
  vaild_value[N] = uart_adc_value;
  for(i=0;i<N;i++)
  {
    vaild_value[i] = vaild_value[i+1];   
    total_vaild += vaild_value[i];
  }
  expect_final = total_vaild/N;
  return expect_final;
}
//10ms do once
void filter_irq(void)
{
  adc_count ++;
    if(adc_count > 100)
    {
      adc_count = 0;
      filter();
      /* Toggles LEDs */
//      GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
    }
  compute_count ++;
  if(compute_count > compute_rate)
  {
    compute_count = 0;
    compute_display_value();
  }
    return;
}

void send_uart_value(unsigned short uart_value)
{
  uart_adc_value = uart_value;
  return;
}

static unsigned char compute_gap(unsigned short fly_past)
{
  unsigned char temp;
  if(fly_past > 100)
  {
    temp = 12;
    compute_rate = 70;
  }
  else
  {
    temp = fly_past/10 + 1;
    compute_rate = 200;
  }
  return temp;
}

static void compute_display_value(void)
{
  unsigned char gap;
  unsigned short des_value;
  des_value = (unsigned short)(700.0*expect_final/1024*5.0);
  if(des_value > 532)
    des_value = 532;
  if(display_value > des_value)
  {    
    gap = compute_gap(display_value - des_value);
    display_value -= (gap/2 + 1);
  }
  if(display_value < des_value)
  {
    gap = compute_gap(des_value - display_value);
    display_value += gap;
  }
  return;
}

unsigned short get_PM2_5_value(void)
{
  return display_value;
}