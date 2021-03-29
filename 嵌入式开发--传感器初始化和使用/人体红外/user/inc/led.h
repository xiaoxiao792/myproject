#ifndef _LED_H_
#define _LED_H_
#include "stm32f4xx.h"
#define ALL 0

void LED_Init(void);
void LED_ON(u8 led);
void LED_OFF(u8 led);
void LED_Triggle(u8 led);


#endif



