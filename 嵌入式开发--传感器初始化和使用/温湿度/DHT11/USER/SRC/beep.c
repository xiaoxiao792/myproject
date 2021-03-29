#include "beep.h"

void BEEP_Init(void)
{
	RCC->AHB1ENR |=1<<4;           //打开相应的GPIOE口时钟
	                               
	GPIOE->MODER   &=~(3<<(2*0));  //配置GPIOE.0端口模式
	GPIOE->MODER   |=1<<(2*0);     //配置GPIOE.0为通用输出模式
	GPIOE->OTYPER  &=~(1<<0);      //①　配置输出类型
	GPIOE->OSPEEDR &=~(3<<(2*0));  //②　配置输出速度为2MHz
	GPIOE->PUPDR   &=~(3<<(2*0));  //配置GPIOE.0端口上下拉
	GPIOE->ODR     &=~(1<<0);      //初始化GPIO口
}



