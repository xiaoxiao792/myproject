#ifndef _KEY_H_
#define _KEY_H_

#include <stm32f4xx.h>
void KEY_Init(void);
void delay(u32 t);
u8 KEY_Scan(void);
#define KEY1  (GPIOA->IDR & (1 << 0)) 
#define KEY2  (!(GPIOE->IDR & (1 << 2)))
#define KEY3  (!(GPIOE->IDR & (1 << 3)))
#define KEY4  (!(GPIOE->IDR & (1 << 4)))
#endif




