#ifndef BEEP_H
#define BEEP_H
#include "stm32f4xx.h"
void BEEP_Init(void);

#define BEEP_ON() (GPIOE->BSRRL = 1<<0)
#define BEEP_OFF() (GPIOE->BSRRH = 1<<0)

#endif

