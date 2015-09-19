/* STATUS.C file
 * Date:2015.6.9
 * Auth:Jason.H_{
 */

#include "status.h"
#include "stdlib.h"
#include "motor.h"
#include "led.h"
#include "filter.h"

context_status_t *status;

static unsigned char smartFlag = SMART_OFF;

unsigned char Status_Init(void)
{
  status = (context_status_t *)calloc(1,sizeof(context_status_t));
  if(!(status))
    return 0;
  return 1;
}

void status_tick(void)
{
    static unsigned char keep_count = 0 ;
    static unsigned short count = 0;
    static unsigned char air_class_old = 0;
    static unsigned short PM2_5Value = 0;
    static unsigned short PM2_5ValueLast = 0;
    
    if( SMART_OFF == smartFlag )
      return;
    
    count ++;
    if( count >= 50000 )//5s do once
    {
        count = 0;
        if(((air_class_old == 3 && status->sensorStatus.air_class == 2) || \
            (PM2_5Value < PM2_5ValueLast)) && (keep_count < 4) )//20s
        {
            keep_count ++;
            PM2_5Value = get_PM2_5_value();
            if( PM2_5Value < PM2_5ValueLast )
                return;
            else
                goto TEST;
        }

        PM2_5Value = get_PM2_5_value();
        
        if( ((air_class_old == 3 && status->sensorStatus.air_class == 2) ||\
            (PM2_5Value < PM2_5ValueLast)) && (keep_count == 0xFF) && \
            (status->sensorStatus.air_class > 1) )
        {
            keep_count = 0;
            return;
        }
    TEST:
        air_class_old = status->sensorStatus.air_class;
        if( PM2_5Value > 200 )
        {
            if( PM2_5ValueLast <= 100)
            {
                status->sensorStatus.air_class = 2;
            }
            else
            {
                status->sensorStatus.air_class = 3;
            }
        }
        else if(PM2_5Value > 100)
        {
            status->sensorStatus.air_class = 2;
        }
        else
        {
            if(PM2_5ValueLast > 200)
            {
                status->sensorStatus.air_class = 2;
            }
            else
            {
                status->sensorStatus.air_class = 1;
            }
        }
        PM2_5ValueLast = PM2_5Value;
        if(keep_count != 0xff)
            keep_count = 0xff;
        
        if(air_class_old != status->sensorStatus.air_class)
        {
            switch(status->sensorStatus.air_class)
            {
            case 1:
                LED_BLUE_ON();
                changeMotorPositon(MOTOR_LOW);
                break;
            case 2:
                LED_YELLOW_ON();
                changeMotorPositon(MOTOR_MIDIUM);
                break;
            case 3:
                LED_RED_ON();
                changeMotorPositon(MOTOR_HIGH);
                break;
            default:
                break;
            }
        }
    }
}

void statusSmartMode(SmartCmd_t cmd)
{
    unsigned short PM2_5Value = get_PM2_5_value();
    smartFlag = cmd;
    if(SMART_ON == smartFlag)
    {
        if(PM2_5Value > 200 )
        {
            LED_RED_ON();
            changeMotorPositon(MOTOR_HIGH);
        }
        else if(PM2_5Value > 100)
        {
            LED_YELLOW_ON();
            changeMotorPositon(MOTOR_MIDIUM);
        }
        else
        {
            LED_BLUE_ON();
            changeMotorPositon(MOTOR_LOW);
        }
    }
}