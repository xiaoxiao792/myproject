#include "stm32f10x.h"                  // Device header
#include "led.h"

/*******************************************************************
函数功能：LED初始化
硬件接口：
	LED1-----PB6------------低电平点亮
	LED2-----PB8------------低电平点亮
*******************************************************************/
void LED_Init(void)
{
	//开启B口时钟 
	RCC->APB2ENR |= 1 << 3;				// 或与 |=  3号位写1 1<<3 寄存器用->
	//PB6
  GPIOB->CRL &=~(15 << 4*6);  
	GPIOB->CRL |=(3 << 4*6);
	GPIOB->ODR |=1 << 6;
	//PB8
  GPIOB->CRH &=~(15 << 0);  
	GPIOB->CRH |=(3 << 0);
	GPIOB->ODR |=1 << 8;	
}

