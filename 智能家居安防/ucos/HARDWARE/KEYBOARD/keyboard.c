
#include <stdio.h>
#include "stm32f4xx.h"
#include "sys.h"

static GPIO_InitTypeDef		GPIO_InitStructure;
void keyboard_init(void)
{
		RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOD, ENABLE);
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_14|GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;
		GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
		
		
		RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
		GPIO_Init(GPIOE,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_15;
		GPIO_Init(GPIOE,&GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
		GPIO_Init(GPIOD,&GPIO_InitStructure);
		PDout(4)=1;
		PDout(14)=1;
		PDout(0)=1;
		PEout(7)=1;

}
