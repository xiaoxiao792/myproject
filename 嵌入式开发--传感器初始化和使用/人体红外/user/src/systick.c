#include "systick.h"
#include "led.h"

/*
函数的功能：systick_us延时函数
形参：需要延时时间
返回值：void
备注：168MHZ / 8 = 21MHZ
*/
void Systick_us(u32 us)
{
	SysTick->CTRL &= ~(1 << 2);   //选择外部时钟源
	
	SysTick->LOAD = SYSCLK * us;  //写入重载值
	SysTick->VAL = 0;    					//清计数器
	
	SysTick->CTRL |= 1 << 0;      //使能计数器
	
	while(!(SysTick->CTRL & (1 << 16)))
	{
		/* 等待时间到 */
	}
	SysTick->CTRL &= ~(1 << 0);   //关闭计数器
}

/*
函数的功能：systick_ms延时函数
形参：需要延时时间
返回值：void
备注：168MHZ / 8 = 21MHZ
*/
void Systick_ms(u32 ms)
{
	SysTick->CTRL &= ~(1 << 2);   //选择外部时钟源
	
	SysTick->LOAD = SYSCLK * ms * 1000;  //写入重载值
	SysTick->VAL = 0;    					//清计数器
	
	SysTick->CTRL |= 1 << 0;      //使能计数器
	
	while(!(SysTick->CTRL & (1 << 16)))
	{
		/* 等待时间到 */
	}
	SysTick->CTRL &= ~(1 << 0);   //关闭计数器
}

/*
函数的功能：systick_inter_ms延时函数
形参：需要延时时间
返回值：void
备注：168MHZ / 8 = 21MHZ
*/
void systick_inter_ms(u32 ms)
{
	SysTick->CTRL &= ~(1 << 2);   //选择外部时钟源
	
	SysTick->LOAD = SYSCLK * ms * 1000;  //写入重载值
	
	SysTick->VAL = 0;    					//清计数器
	
	SysTick->CTRL |= 1 << 1;     //使能中断
	SysTick->CTRL |= 1 << 0;      //使能计数器
}

void SysTick_Handler(void)
{
	if(SysTick->CTRL & (1 << 16))
	{
		 GPIOF->ODR ^= 1 << 6;
	}
}





