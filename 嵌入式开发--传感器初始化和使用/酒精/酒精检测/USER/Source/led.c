#include "led.h"
#include "key.h"
	
void LED_Init(void)
{
	RCC->AHB1ENR   |=1<<0;       //GPIOA时钟使能
	
	GPIOA->MODER   &=~(0xFF<<(4*2));//配置GPIOF.6输出模式
	GPIOA->MODER   |=0x55<<(4*2);
	GPIOA->OTYPER  &=~(0xF<<4);    //输出推挽
	GPIOA->OSPEEDR &=~(0xFF<<(4*2));//输出速度2MHz
	GPIOA->PUPDR   &=~(0xFF<<(4*2));//端口上下拉
	GPIOA->ODR     |=0xFF<<4;//初始化
}

void LED_Triggle(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOA->ODR ^=1<<4; break;
		case 2:
			GPIOA->ODR ^=1<<5; break;
		case 3:
			GPIOA->ODR ^=1<<6; break;
		case 4:
			GPIOA->ODR ^=1<<7;	break;
		case ALL:
		GPIOA->ODR ^=1<<4;
		GPIOA->ODR ^=1<<5;
		GPIOA->ODR ^=1<<6;
		GPIOA->ODR ^=1<<7;
			break;
		default: break;
	}
}

void LED_OFF(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOA->BSRRL =1<<4; break;
		case 2:
			GPIOA->BSRRL =1<<5; break;
		case 3:
			GPIOA->BSRRL =1<<6; break;
		case 4:
			GPIOA->BSRRL =1<<7;	break;
		case ALL:
		GPIOA->BSRRL =1<<4;
		GPIOA->BSRRL =1<<5;
		GPIOA->BSRRL =1<<6;
		GPIOA->BSRRL =1<<7;
			break;
		default: break;
	}
}

void LED_ON(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOA->BSRRH =1<<4; break;
		case 2:
			GPIOA->BSRRH =1<<5; break;
		case 3:
			GPIOA->BSRRH =1<<6; break;
		case 4:
			GPIOA->BSRRH =1<<7;	break;
		case ALL:
		GPIOA->BSRRH =1<<4;
		GPIOA->BSRRH =1<<5;
		GPIOA->BSRRH =1<<6;
		GPIOA->BSRRH =1<<7;
			break;
		default: break;
	}
}




