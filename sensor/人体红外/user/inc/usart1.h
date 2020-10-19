#ifndef _USART1_H_
#define _USART1_H_

#include <stm32f4xx.h>
#include <stdio.h>
void USART1_Init(u32 pck, u32 fck, u8 over8);
void USART_Send_str(u8 * str);
extern u8 flag;
extern u8 rec_buff[20];

#endif






