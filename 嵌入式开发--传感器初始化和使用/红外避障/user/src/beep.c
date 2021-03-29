#include "beep.h"

void beep_init(void)
{
	RCC->AHB1ENR   |=1<<4;       //GPIOEÊ±ÖÓÊ¹ÄÜ
	GPIOE->MODER   &=~(0x3<<(0*2));
	GPIOE->MODER   |=1<<(0*2);
	GPIOE->OTYPER  &=~(1<<0);
	GPIOE->OSPEEDR &=~(0x3<<(0*2));
	GPIOE->PUPDR   &=~(0x3<<(0*2));
	GPIOE->ODR     &=~(1<<0);
}

