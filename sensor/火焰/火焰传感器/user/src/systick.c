#include "stm32f4xx.h"
#include "led.h"


/****************** 微秒延时函数 ******************
SysCLK： 系统时钟
us：     需要延时的微秒数
对于168M条件下，最大计算值为798915us
Cortex系统定时器时钟，等于系统总线时钟(HCLK) 8分频
所以168/8=21M
根据公式：LOAD - 1 =（24 * us)->  LOAD的值不能大于16777216-1。
us-->（16777215/21=798915）
***************************************************/
void Delay_us(u8 SysClk,u32 us)
{
	u32 tmp;
	//1.选择定时器时钟源
	SysTick->CTRL &=~(0x01<<2);//AHB时钟8分频后作为SysTick时钟
	//2.确定定时器定时时长,根据定时时间计数定时初值，并把初始值写入LOAD寄存器
	SysTick->LOAD=us*(SysClk/8);
	//3.对VAL寄存器进行写操作以对计数值进行清零
	SysTick->VAL=0; //计数寄存器清零
	//4.启动定时器
	SysTick->CTRL |=1<<0;   //使能systick
	//5.等待时间完成
	//while(!(SysTick->CTRL&(1<<16)));//（查询CTRL.16是否为1）
	do
	{
		tmp=SysTick->CTRL;   //读取控制&状态寄存器的值
	}while(!(tmp &(1<<16)));  //等待时间到达
	//6.关闭定时器
	SysTick->CTRL &=~(1<<0);   //失能systick

}
/****************** 毫秒延时函数 ******************
SysCLK： 系统时钟
ms：     需要延时的毫秒数
对于168M条件下，最大计算值为798ms
***************************************************/
void Delay_ms(u8 SysCLK, u16 ms)
{
	u32 temp;
	
	SysTick->CTRL &= ~(1 << 2);                //AHB时钟8分频后作为SysTick时钟
	SysTick->LOAD = ms * 1000 * (SysCLK / 8);  //把延时计数值写入重载寄存器
	SysTick->VAL = 0;                          //把计数寄存器清零
	SysTick->CTRL |= 1 << 0;                   //使能SysTick
	//等待时间到达
	while(!(SysTick->CTRL&(1<<16)));//（查询CTRL.16是否为1）
	SysTick->CTRL &= ~(1 << 0);                //关闭SysTick

}




/****************** SysTick中断初始化函数 ******************
SysCLK： 系统时钟
ms：     ms毫秒产生一次中断
State：  SysTick状态位：1开启，0，关闭
***********************************************************/
void systick_interrupt_init(u8 SysClk,u16 ms,u8 state)
{
//	1.	选择外部时钟源sysclk/8
	SysTick->CTRL &=~(0x01<<2);
//2.	设置load寄存器-----设定计数初值
	SysTick->LOAD=ms*1000*SysClk/8;
//3.	对VAL写操作------VAL会被清零?重装载
	SysTick->VAL=0;
//开中断
//	SysTick->CTRL |=0x01<<1; //计数到0时产生中断
	
//		NVIC_SetPriorityGrouping(7-2);                      //设置优先级分组
 //  NVIC_SetPriority(SysTick_IRQn ,NVIC_EncodePriority(7-2,3,3));   //设置中断源优先级
	//系统中断，  
	
	//根据需要绝对是否要开启定时器
	if(state==1)
		SysTick->CTRL |=0x01<<0; //	开启SYSTICK
  else 
		SysTick->CTRL &= ~( 0x01 << 0 ); // 关闭SYSTICK

}










