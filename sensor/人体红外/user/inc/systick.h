#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include <stm32f4xx.h>
#define SYSCLK  (168 / 8)
void Systick_us(u32 us);
void Systick_ms(u32 ms);
void systick_inter_ms(u32 ms);

#endif





