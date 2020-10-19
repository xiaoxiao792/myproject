#ifndef _KEY_H
#define _KEY_H
#include "stm32f10x.h"  

#define KEY_State  (GPIOB->IDR & (1 << 7))
 
void Key_Init(void);
u8 Key_Scan(void);

#endif

