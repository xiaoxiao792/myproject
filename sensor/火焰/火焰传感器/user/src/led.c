#include "stm32f4xx.h"
#include "led.h"

#include "led.h"
#include "key.h"

/*
函数功能：led初始化
形参：无
返回值：无
备注：LED1  -- PC4  LED2  -- PC5  LED3  -- PA6  LED4  -- PA7   
*/
void LED_Init(void)
{
	/* 使能GPIO时钟 */
	RCC->AHB1ENR |= 1 << 0;   //GPIOA时钟使能
	RCC->AHB1ENR |= 1 << 2;   //GPIOC时钟使能

	
	/* 设置PC4工作模式 */
	GPIOC->MODER &= ~(3 << (2 * 4));
	GPIOC->MODER |= 1 << (2 * 4);  //设置为输出模式
	
	/* 设置输出类型 */
	GPIOC->OTYPER &= ~(1 << 4);    //设置为推挽输出
	
	/* 设置输出速度 */
	GPIOC->OSPEEDR &= ~(3 << (2 * 4));
	GPIOC->OSPEEDR |= 2 << (2 * 4);  //设置为50MHZ
	
	/* 设置上下拉 */
	GPIOC->PUPDR &= ~(3 << (2 * 4));  //无上下拉
	
	/*设置GPIO初始状态 */
	GPIOC->ODR |= 1 << 4;     //初始状态为高电平
	
	
	/* 设置PC5工作模式 */
	GPIOC->MODER &= ~(3 << (2 * 5));
	GPIOC->MODER |= 1 << (2 * 5);  //设置为输出模式
	
	/* 设置输出类型 */
	GPIOC->OTYPER &= ~(1 << 5);    //设置为推挽输出
	
	/* 设置输出速度 */
	GPIOC->OSPEEDR &= ~(3 << (2 * 5));
	GPIOC->OSPEEDR |= 2 << (2 * 5);  //设置为50MHZ
	
	/* 设置上下拉 */
	GPIOC->PUPDR &= ~(3 << (2 * 5));  //无上下拉
	
	/*设置GPIO初始状态 */
	GPIOC->ODR |= 1 << 5;     //初始状态为高电平
	
	/* 设置PA6工作模式 */
	GPIOA->MODER &= ~(3 << (2 * 6));
	GPIOA->MODER |= 1 << (2 * 6);  //设置为输出模式
	
	/* 设置输出类型 */
	GPIOA->OTYPER &= ~(1 << 6);    //设置为推挽输出
	
	/* 设置输出速度 */
	GPIOA->OSPEEDR &= ~(3 << (2 * 6));
	GPIOA->OSPEEDR |= 2 << (2 * 6);  //设置为50MHZ
	
	/* 设置上下拉 */
	GPIOA->PUPDR &= ~(3 << (2 * 6));  //无上下拉
	
	/*设置GPIO初始状态 */
	GPIOA->ODR |= 1 << 6;     //初始状态为高电平
	
	
	/* 设置PA7工作模式 */
	GPIOA->MODER &= ~(3 << (2 * 7));
	GPIOA->MODER |= 1 << (2 * 7);  //设置为输出模式
	
	/* 设置输出类型 */
	GPIOA->OTYPER &= ~(1 << 7);    //设置为推挽输出
	
	/* 设置输出速度 */
	GPIOA->OSPEEDR &= ~(3 << (2 * 7));
	GPIOA->OSPEEDR |= 2 << (2 * 7);  //设置为50MHZ
	
	/* 设置上下拉 */
	GPIOA->PUPDR &= ~(3 << (2 * 7));  //无上下拉
	
	/*设置GPIO初始状态 */
	GPIOA->ODR |= 1 << 7;     //初始状态为高电平
}

void LED_Triggle(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOC->ODR ^=1<<4; break;
		case 2:
			GPIOC->ODR ^=1<<5; break;
		case 3:
			GPIOA->ODR ^=1<<6; break;
		case 4:
			GPIOA->ODR ^=1<<7;	break;
		case ALL:
		GPIOC->ODR ^=1<<4;
		GPIOC->ODR ^=1<<5;
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
			GPIOC->BSRRL =1<<4; break;
		case 2:
			GPIOC->BSRRL =1<<5; break;
		case 3:
			GPIOA->BSRRL =1<<6; break;
		case 4:
			GPIOA->BSRRL =1<<7;	break;
		case ALL:
		GPIOC->BSRRL =1<<4;
		GPIOC->BSRRL =1<<5;
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
			GPIOC->BSRRH =1<<4; break;
		case 2:
			GPIOC->BSRRH =1<<5; break;
		case 3:
			GPIOA->BSRRH =1<<6; break;
		case 4:
			GPIOA->BSRRH =1<<7;	break;
		case ALL:
		GPIOC->BSRRH =1<<4;
		GPIOC->BSRRH =1<<5;
		GPIOA->BSRRH =1<<6;
		GPIOA->BSRRH =1<<7;
			break;
		default: break;
	}
}




void delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++);
}
//作业：实现4个灯，流水灯
