#ifndef _LED_H
#define _LED_H
 
#define LED1_ON GPIOB->ODR &=~(1 << 6)
#define LED1_OFF GPIOB->ODR |=1 << 6
#define LED2_ON GPIOB->ODR &=~(1 << 8)
#define LED2_OFF GPIOB->ODR |=1 << 8

void LED_Init(void);
 
#endif

