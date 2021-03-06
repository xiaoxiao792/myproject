#ifndef  _DTH11_H
#define  _DTH11_H

#include "stm32f4xx.h"

extern void humiture_init(void);
extern int32_t humiture_get_distance(uint8_t *data);
extern void humiture_mode(GPIOMode_TypeDef Mode);

#endif
