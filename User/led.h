#ifndef __LED_H
#define __LED_H

#include "iostm8s103f3.h"

#define LED_GREEN_ON() { ledSleepMode(SLEEP_OFF); set_led_color(0,100,0); }
#define LED_BLUE_ON() { ledSleepMode(SLEEP_OFF); set_led_color(0,11,100); }
#define LED_RED_ON() { ledSleepMode(SLEEP_OFF); set_led_color(100,0,1); }
#define LED_YELLOW_ON() { ledSleepMode(SLEEP_OFF); set_led_color(89,34,0); }

#define LED_All_ON() { ledSleepMode(SLEEP_OFF); set_led_color(100,100,100); }
#define LED_All_OFF() { ledSleepMode(SLEEP_OFF); set_led_color(0,0,0); }

typedef enum {
    SLEEP_ON = 0x00,
    SLEEP_OFF = 0x01 
}sleepCmd_t;

typedef unsigned short uint16_t;

void LED_Init(void);

//void LED_All_ON(void);
//void LED_All_OFF(void);
//void LED_RED_ON(void);
//void LED_GREEN_ON(void);
//void LED_BLUE_ON(void);
void set_led_color(uint16_t R_value,uint16_t G_value,uint16_t B_value);
void led_tick(void);
void ledSleepMode(sleepCmd_t cmd);

#endif