#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 


extern void usart_init(uint32_t baud);
extern void usart3_init(uint32_t baud);
extern void bluetooth_config(void);
void usart3_send_str(char *str);
#endif


