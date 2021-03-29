#ifndef  KEY_H   //名字和文件名最好一样
#define  KEY_H
#include "stm32f4xx.h"

void Delay(u32 time);
void KEY_Init(void);
u8 Key_Scan(void);
#define  KEY1  ( GPIOA->IDR &(1<<0))
#define  KEY2  ( GPIOE->IDR &(1<<2))
#define  KEY3  ( GPIOE->IDR &(1<<3))
#define  KEY4  ( GPIOE->IDR &(1<<4))
#endif







