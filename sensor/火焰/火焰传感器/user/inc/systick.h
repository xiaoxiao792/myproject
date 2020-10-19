#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f4xx.h"

void Delay_us(u8 SysClk,u32 us);

void Delay_ms(u8 SysCLK, u16 ms);

void systick_interrupt_init(u8 SysClk,u16 ms,u8 state);

#endif


