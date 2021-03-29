#ifndef USART_H
#define USART_H
#include "stm32f4xx.h"
void USART1_Init(u32 Fclk, u32 Band, u8 Over8);
void USART1_Send_Str(u8 *str);


#endif



