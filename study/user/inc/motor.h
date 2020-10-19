#ifndef _MOTOR_H
#define _MOTOR_H
#include "stm32f10x.h"  

void lock_init(void);
void set_lock_sta(u8 mplus,u8 msub);
void open_lock(u8 s);
 
#endif







