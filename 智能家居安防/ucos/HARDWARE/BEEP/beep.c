#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"

static GPIO_InitTypeDef		GPIO_InitStructure;
void beep_init()
{
		//使能端口F的硬件时钟，端口F才能工作，说白了就是对端口F上电
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);	

	
	//配置硬件，配置GPIO，端口F，第9个引脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;			//第9 个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;		//输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
}
