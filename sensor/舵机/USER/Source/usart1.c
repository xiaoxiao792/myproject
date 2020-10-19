#include "usart1.h"
#include  <stdio.h>
void  USART1_IRQHandler(void)
{
	u8 data=0;
	if( USART1->SR&(1<<5)  )//清除中断标志位
	{
		USART1->SR  &=~(1<<5);
		data = USART1->DR;
		while( 0==( USART1->SR&(1<<7)) );
		USART1->DR = data;
	}
}


void USART1_Init(u32 bound)
{
	float USARTDIV=0;      
	u16   DIV_Mantissa=0;  //整数部分
	u8    DIV_Fraction=0;  //小数部分
	//1)GPIO配置
	RCC->AHB1ENR  |=1<<0;            //GPIOA 时钟使能
	GPIOA->MODER  &=~(0xF<<(9*2));   //模式配置PA9,PA10
	GPIOA->MODER  |=0xA<<(9*2);      //复用模式
	GPIOA->AFR[1] &=~(0xFF<<4);      //复用功能选择
	GPIOA->AFR[1] |=0x77<<4;   
  
	RCC->APB2ENR  |=1<<4;//USART1时钟使能
	//2)USART相关参数配置（，过采样模式，字长，奇偶校验，停止位）
	USART1->CR1   &=~(1<<15);        //16倍过采样模式
	USART1->CR1   &=~(1<<12);        //1 起始位， 8 数据位， n 停止位

	//3)串口波特率计算和写入

	USARTDIV     =84*1000000/( 16.0*bound  ) ;  //乘以16.0，得到浮点型数据
	DIV_Mantissa = USARTDIV;                     //得到整数部分
	DIV_Fraction = (USARTDIV -DIV_Mantissa)*16;  //得到小数部分
	USART1->BRR  = (DIV_Mantissa<<4) | DIV_Fraction;	//写入波特率寄存器
	
	USART1->CR1  |=1<<5;                     //接收中断，中断源使能 
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(5,1,1) ); //优先级设置
	NVIC_EnableIRQ(USART1_IRQn);             //中断通道使能
	//4)相关使能
	USART1->CR1  |=1<<3;                //发送器使能
	USART1->CR1  |=1<<2;                //接收器使能
	USART1->CR1  |=1<<13;               //串口模块使能	
	
}


void  USART1_Send_Str(u8 *str)
{
	while(*str !='\0')
	{
		while( !(USART1->SR &(1<<7)) )
		{
		
		}
		USART1->DR = *str;
		str++;
	}
}


/******************** 串口打印函数 ***************************************/
/* fputc是printf最底层的调用函数 */

int fputc(int data,FILE *file)
{
	while( !(USART1->SR & (1 << 6)) );//等待发送完成
	USART1->DR = data;   //发送数据
	return data;
} 



