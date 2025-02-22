#ifndef _KEY_H
#define _KEY_H

#include <stm32f4xx.h>
#define KEY1   (GPIOA->IDR & (1 << 0))
#define KEY2   (!(GPIOE->IDR & (1 << 2)))
#define KEY3   (!(GPIOE->IDR & (1 << 3)))
#define KEY4   (!(GPIOE->IDR & (1 << 4)))

void KEY_Init(void);
void delay(u32 t);
u8 key_Scan(void);

#endif





