#include "iostm8s103f3.h"
#include "button.h"
#include "sys.h"
//#include "led.h"
#include "status.h"
#include "buzzer.h"

static unsigned long _default_start_time = 0;

void Button_Init(void)
{
	PA_DDR &= ~0x08;
	PA_CR1 |= 0x08;
	PA_CR2 |= 0x08;
	
  //EXTI_DeInit();
  //EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA,EXTI_SENSITIVITY_RISE_FALL);
	EXTI_CR1 &= ~0x03;
	EXTI_CR1 |= 0x03;
}

void check_button(void)
{
    signed short interval = -1;        
 
	if(!(PA_IDR & 0x08))//GPIO_ReadInputPin(BUTTON_KEY_PORT,(GPIO_Pin_TypeDef)BUTTON_KEY_PINS))
	{
	  _default_start_time = get_time() + 1;
          set_long_press_flag();
	}
	else
	{
	  interval = get_time() + 1 - _default_start_time;
	  if ( (_default_start_time != 0) && (interval > 10) && (interval < ShutDown_TimeOut)){
//           GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
		switch(status->deviceStatus.mode)
		{
		case MODE_CLOSE:
		  status->deviceStatus.mode = MODE_SMART;
		  BuzzerStart(POLY_ON);
		  break;
		case MODE_SMART:
		  status->deviceStatus.mode = MODE_SLEEP;
		  BuzzerStart(MONO);
		  break;
		case MODE_SLEEP:
		  status->deviceStatus.mode = MODE_FLY;
		  BuzzerStart(MONO);
		  break;
		case MODE_FLY:
		  status->deviceStatus.mode = MODE_SMART;
		  BuzzerStart(MONO);
		  break;
		default:
		  break;
		}
	  }
	  _default_start_time = 0;
	  reset_long_press_flag();
	}
	return;
}

void _button_timeout_hander(void)
{
  _default_start_time = 0;
  status->deviceStatus.mode = MODE_CLOSE;
  BuzzerStart(POLY_OFF);
  //GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
 // PA_ODR ^= 0x08;
}