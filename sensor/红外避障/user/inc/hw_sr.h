#ifndef _HW_H_
#define _HW_H_

#include <stm32f4xx.h>

#define   HW      (GPIOC->IDR & (1 << 4))


void Hw_SR_init(void);
u8 Hw_SR_input(void);

#endif

