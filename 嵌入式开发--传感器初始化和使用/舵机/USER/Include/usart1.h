#ifndef USART1_H
#define USART1_H
#include "stm32f4xx.h"

void 	USART1_Init(u32 bound);
void  USART1_Send_Str(u8 *str);

#endif