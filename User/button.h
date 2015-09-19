/* BUTTON.H file
 * Date:2015.6.3
 * Auth:Jason.H_{
 */
#ifndef __BUTTON_H
#define __BUTTON_H


#define ShutDown_TimeOut 30000


void Button_Init(void);
void check_button(void);
void _button_timeout_hander(void);

#endif