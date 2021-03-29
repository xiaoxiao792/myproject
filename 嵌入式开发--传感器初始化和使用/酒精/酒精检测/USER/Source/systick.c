#include "systick.h"

void Delay_ms(u32 ms)
{
	u32 last_ms=0;
	while(ms)
	{
		if( ms>=500 ) last_ms=500;
		else          last_ms=ms;  
		Delay_xms(last_ms);
		ms -= last_ms;
	}
}

void Delay_xms(u32 xms)
{
	SysTick->CTRL &=~(1<<0); //关闭定时器
	SysTick->CTRL &=~(1<<1); //关闭滴答中断
	SysTick->CTRL &=~(1<<2); //选择时钟源21MHz
	SysTick->LOAD  =21000*xms  ; //配置重装载寄存器
	SysTick->VAL   =0      ; //初始化当前值寄存器
	SysTick->CTRL |=(1<<0) ; //开启定时器
	while( ( SysTick->CTRL &(1<<16) )==0) 
	{
		//等待定时到达
	}
	SysTick->CTRL &=~(1<<0); //关闭定时器	
}


void Delay_us(u32 us)
{
	SysTick->CTRL &=~(1<<0); //关闭定时器
	SysTick->CTRL &=~(1<<1); //关闭滴答中断
	SysTick->CTRL &=~(1<<2); //选择时钟源21MHz
	SysTick->LOAD  =21*us  ; //配置重装载寄存器
	SysTick->VAL   =0      ; //初始化当前值寄存器
	SysTick->CTRL |=(1<<0) ; //开启定时器
	while( ( SysTick->CTRL &(1<<16) )==0) 
	{
		//等待定时到达
	}
	SysTick->CTRL &=~(1<<0); //关闭定时器	
}









