#include "usart2.h"

#include "USART2.h"

void USART2_Init(u32 bound)
{
	float USARTDIV=0;      
	u16   DIV_Mantissa=0;  //整数部分
	u8    DIV_Fraction=0;  //小数部分
	//1)GPIO配置
	RCC->AHB1ENR  |=1<<0;            //GPIOA 时钟使能
	GPIOA->MODER  &=~(0xF<<(2*2));   //模式配置PA2,PA3
	GPIOA->MODER  |=0xA<<(2*2);      //复用模式
	GPIOA->AFR[0] &=~(0xFF<<8);      //复用功能选择
	GPIOA->AFR[0] |=0x77<<8;   
  
	RCC->APB1ENR  |=1<<17;//USART2时钟使能
	//2)USART相关参数配置（，过采样模式，字长，奇偶校验，停止位）
	USART2->CR1   &=~(1<<15);        //16倍过采样模式
	USART2->CR1   &=~(1<<12);        //1 起始位， 8 数据位， n 停止位

	//3)串口波特率计算和写入

	USARTDIV     =42*1000000/( 16.0*bound  ) ;  //乘以16.0，得到浮点型数据
	DIV_Mantissa = USARTDIV;                     //得到整数部分
	DIV_Fraction = (USARTDIV -DIV_Mantissa)*16;  //得到小数部分
	USART2->BRR  = (DIV_Mantissa<<4) | DIV_Fraction;	//写入波特率寄存器
	
	//4)相关使能
	USART2->CR1  |=1<<3;                //发送器使能
	USART2->CR1  |=1<<2;                //接收器使能
	USART2->CR1  |=1<<13;               //串口模块使能	
}


