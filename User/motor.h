#ifndef __MOTOR_H
#define __MOTOR_H
#include "status.h"

void Motor_Init(void);
void motor_tick(void);
void changeMotorPositon(motorPosition_t positon);
void startMotorOn(void);

#endif
