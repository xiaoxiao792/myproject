#ifndef  _IR_H
#define  _IR_H
#include "stm32f4xx.h"
extern int32_t infrared_get_distance(uint8_t *data);
extern void infrared_init(void );
extern void TIM1_PWM_init(void);
#endif 
