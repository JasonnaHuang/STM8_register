#include "iostm8s103f3.h"
#include "motor.h"


#define MOTOR_HALT_GEAR         0
#define MOTOR_SLEEP_GEAR        68
#define MOTOR_LOW_GEAR          70  
#define MOTOR_MIDIUM_GEAR       74
#define MOTOR_HIGH_GEAR         80
#define MOTOR_FLY_GEAR          86
#define MOTOR_START_GEAR        50

static unsigned short motor_now_ccr;
static unsigned short motor_target_ccr;
static motorPosition_t motor_positon = MOTOR_HALT;

void Motor_Init(void)
{
	//GPIO_Init(MOTOR_GPIO_PROT, (GPIO_Pin_TypeDef)MOTOR_GPIO_PINS,\
	GPIO_MODE_OUT_PP_LOW_FAST);
	PC_DDR |= 0x08;
	PC_CR1 |= 0x08;
	PC_CR2 |= 0x08;
	//TIM1_OC3Init(TIM1_OCMODE_PWM1,TIM1_OUTPUTSTATE_ENABLE,TIM1_OUTPUTNSTATE_DISABLE,\
    0,TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	TIM1_CCMR3 = 0x60;
	//TIM1_CCER2 |= 0x0B;
	TIM1_CCER2 &= ~0x0f;
	TIM1_CCER2 |= 0x09;//0x0B;
	TIM1_CCR3H = 0x00;
	TIM1_CCR3L = 0x00;
	//TIM1_OISR |= 0x10;
	TIM1_OISR &= ~0x30;
	TIM1_OISR |= 0x10;
	//TIM1_CCxCmd(TIM1_CHANNEL_3, ENABLE);
	TIM1_CCER2 |= 0x01;
	//TIM1_OC3PreloadConfig(ENABLE); 
	TIM1_CCMR3 |= 0x08;
        
	changeMotorPositon(MOTOR_HALT);
}

static void setPWMPluse(const unsigned short pluse)
{
        TIM1_CCR3H = pluse >> 8;
	TIM1_CCR3L = pluse;
}

static unsigned short getPWNPluse(void)
{
      unsigned char tempH = TIM1_CCR3H;
      unsigned char tempL = TIM1_CCR3L;
      return ((unsigned short)(tempH << 8) | tempL);
}

/*缓冲改变风机的转速*/
/*参数：目标占空比，取值0~100*/
static void Motor_Gear(unsigned short target_ccr)
{
    if(target_ccr > 100)
      return;
    motor_target_ccr = target_ccr;
    motor_now_ccr = getPWNPluse();//(unsigned short)(TIM1_CCR3H << 8 | TIM1_CCR3L);	
}

void changeMotorPositon(motorPosition_t positon)
{
    motor_positon = positon;
    switch(motor_positon)
    {
        case MOTOR_HALT:
        {
            Motor_Gear(MOTOR_HALT_GEAR);
        }
        break;
        case MOTOR_SLEEP:
	    {
            Motor_Gear(MOTOR_SLEEP_GEAR);
        }
        break;
        case MOTOR_LOW:
        {
            Motor_Gear(MOTOR_LOW_GEAR);
        }
        break;
        case MOTOR_MIDIUM:
        {
            Motor_Gear(MOTOR_MIDIUM_GEAR);
        }
        break;
        case MOTOR_HIGH:
        {
            Motor_Gear(MOTOR_HIGH_GEAR);
        }
        break;
        case MOTOR_FLY:
        {
            Motor_Gear(MOTOR_FLY_GEAR);
        }
        break;
        default:
        break;
    }
}

static void _motor_tick(void)
{
    if(motor_now_ccr < motor_target_ccr)
    {
        //TIM1_CCR3H = ++motor_now_ccr >> 8 ;
        //TIM1_CCR3L = motor_now_ccr;
        setPWMPluse(++motor_now_ccr);
    }
    if(motor_now_ccr > motor_target_ccr)
    {
        //TIM1_CCR3H = --motor_now_ccr >> 8 ;
        //TIM1_CCR3L = motor_now_ccr;
        setPWMPluse(--motor_now_ccr);
    }
    if(motor_now_ccr == motor_target_ccr)
    {
      return;
    }
}

void motor_tick(void)
{
    static unsigned short count = 0;
    count ++;
    if(count >= 5000)
    {
       count = 0 ;
       _motor_tick();
    }
}

void startMotorOn(void)
{
    setPWMPluse(MOTOR_START_GEAR);
}