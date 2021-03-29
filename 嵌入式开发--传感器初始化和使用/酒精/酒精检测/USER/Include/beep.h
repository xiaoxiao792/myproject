#ifndef  BEEP_H
#define  BEEP_H
#include "stm32f4xx.h"
void beep_init(void);

#define beep_on()   ( GPIOE->BSRRL =1<<0)
#define beep_off()  ( GPIOE->BSRRH =1<<0)

#endif








