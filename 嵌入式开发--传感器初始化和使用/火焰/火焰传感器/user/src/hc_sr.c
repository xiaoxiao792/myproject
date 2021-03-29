#include "stm32f4xx.h"
#include "led.h"


/*
 Out----PC1
 PC1 管脚低电平，则有火焰进入
 
*/
void HC_SR_init()
{
	//打开PC管脚时钟
	RCC->AHB1ENR |=(1<<2);
	//PC1 通用输入模式
	GPIOC->MODER &= ~(0x3<<2);
	
	//PC1 无上拉/下拉 可以选择默认值
	GPIOC->PUPDR &=~(0x3<<2);
}


int HC_SR_input()
{
	if((GPIOC->IDR & (1 << 1)) == 0)  //输入低电平
	{
		return 1;
	}	
	else   return 0;
}











