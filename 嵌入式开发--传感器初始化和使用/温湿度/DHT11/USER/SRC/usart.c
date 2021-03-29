#include "usart.h"
#include "stdio.h"

#include "usart.h"

/*
函数功能：usart初始化
形参：1)时钟频率 2）波特率 3）过采样
返回值：无
备注：RXD -- PA9  TXD -- PA10
*/
void USART1_Init(u32 Fclk, u32 Band, u8 Over8)
{
	u32 Mantissa;    //存储整数
	u32 Fraction;    //存储小数
	float USARTDIV;      //存储波特率的值
	
	/* 时钟使能 */
	RCC->AHB1ENR |= 1 << 0;         //使能GPIOA时钟
	
	/* 设置PA9 -- RXD */
	GPIOA->MODER &= ~(3 << (2 * 9));
	GPIOA->MODER |= 2 << (2 * 9);    //复用功能
	
	GPIOA->AFR[1] &= ~(15 << (4 * (9 - 8)));
	GPIOA->AFR[1] |= 7 << (4 * (9 - 8));  //复用为USART1
	
	/* 设置PA10 -- TXD */
	GPIOA->MODER &= ~(3 << (2 * 10));
	GPIOA->MODER |= 2 << (2 * 10);         //复用功能
	GPIOA->AFR[1] &= ~(15 << (4 * (10 - 8)));
	GPIOA->AFR[1] |= 7 << (4 * (10 - 8));  //复用为USART1
	
	/* 串口时钟设置 */
	RCC->APB2ENR |= 1 << 4;     //使能USART1时钟
	USART1->CR1 &= ~(1 << 12);  //数据位为8位
	USART1->CR1 &= ~(1 << 10);  //禁止校验位
	USART1->CR1 |= 1 << 3;      //发送使能
	USART1->CR1 |= 1 << 2;      //接收使能
	
	/* 设置波特率 */
	if(Over8 == 0)
	{
		USART1->CR1 &= ~(1 << 15);    //16倍过采样
	}
	else
	{
		USART1->CR1 |= 1 << 15;      //8倍过采样
	}
		
	USARTDIV = (Fclk * 1000000) / ((8 * (2 - Over8)) * Band );
	
	Mantissa = (u32)USARTDIV;   //取整数部分
	Fraction = (USARTDIV - Mantissa) * 16;
	
	USART1->BRR = (Mantissa << 4 | Fraction);   //波特率存储的结果
	
	/* 串口使能 */
	USART1->CR1 |= 1 << 13;    //usart 使能
}


/**************************************
字符串发送函数
***************************************/
void USART1_Send_Str(u8 *str)
{
	while(*str !='\0')
	{
		while( !(USART1->SR &(1<<7)) )
		{
		 //等待发送数据为空
		}
		USART1->DR =*str;
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



