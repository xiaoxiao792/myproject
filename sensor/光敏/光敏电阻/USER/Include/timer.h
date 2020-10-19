#ifndef TIMER_H
#define TIMER_H
#include "stm32f4xx.h"
extern  u32 capture_H;
extern  u32 capture_L;
extern  u8  Get_Glag;
void TIM13_CH1_Init(u16 psc,u16 arr,u16 ccr1);
void TIM14_CH1_Init(u16 psc,u16 arr);
#endif

