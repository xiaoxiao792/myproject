#ifndef _USART_H
#define _USART_H
#include "stm32f10x.h"                  // Device header

void usart1_init(u32 bps);
void usart1_send_byte(u8 data);
u8 usart1_rec_byte(void);
void usart1_send_str(u8 *str);
void usart1_rec_str(u8 *str);
 
#endif









