#include "systick.h"
#include "key.h"
#include "usart.h"

void Delay_ms(u32 ms)
{
	u8 count=ms/500;
	u32 lest_time=ms%500;
	while(count--)  Delay_xms(500);
	if(lest_time)   Delay_xms(lest_time);	  
}


void Delay_xms(u32 ms)
{
	SysTick->CTRL &=~(1<<0); //关闭滴答定时器
	SysTick->CTRL &=~(1<<2); //选择时钟源为 21 MHz
	SysTick->CTRL &=~(1<<1); //关闭滴答中断
	SysTick->LOAD = 21000*ms;   //向自动重载寄存器写入计数值
	SysTick->VAL =0;         //初始化当前值寄存器
	SysTick->CTRL |=1<<0;    //打开滴答定时器
	while( !( SysTick->CTRL & (1<<16) ))
	{
	 //等待定时到达
	}
	SysTick->CTRL &=~(1<<0); //关闭滴答定时器
}


void SysTick_Interrupt_ms(u32 ms)
{
	SysTick->CTRL &=~(1<<0);    //关闭滴答定时器
	SysTick->CTRL &=~(1<<2);    //选择时钟源为 21 MHz
	SysTick->CTRL |=1<<1;       //打开滴答中断
	SysTick->LOAD = 21000*ms;   //向自动重载寄存器写入计数值
	SysTick->VAL =0;            //初始化当前值寄存器
}

void SysTick_Handler(void)
{
	if( SysTick->CTRL & (1<<16) ) //判断滴答中断到达，并且清除中断标志位
	{		
		//rec_flag=1;                 //数据接收完成
		SysTick->CTRL &=~(1<<0);    //关闭滴答定时器		
	}			
}



void Delay_us(u32 us)
{
	SysTick->CTRL &=~(1<<0); //关闭滴答定时器
	SysTick->CTRL &=~(1<<2); //选择时钟源为 21 MHz
	SysTick->CTRL &=~(1<<1); //关闭滴答中断
	SysTick->LOAD = 21*us;   //向自动重载寄存器写入计数值
	SysTick->VAL =0;         //初始化当前值寄存器
	SysTick->CTRL |=1<<0;    //打开滴答定时器
	while( !( SysTick->CTRL & (1<<16) ))
	{
	 //等待定时到达
	}
	SysTick->CTRL &=~(1<<0); //关闭滴答定时器
}
