#ifndef __BEEP_H
#define __BEEP_H

#include "iostm8s103f3.h"


void Beep_Init(void);
void BEEP_SetFreq(unsigned short iFreq);
void BeepPwrOn(void);
void BeepPwrOff(void);
void BEEP_On(void);
void BEEP_Off(void);
void Beep_tick(void);

#endif
