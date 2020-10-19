#include "systick.h"

/**************************** 微秒延时函数 ****************************
功  能：实现微秒级别的时间延时
参  数：需要延时的微秒时间值（取值范围：1～1342177us） 
返回值：无
***********************************************************************/
void Delay_us(u32 us)
{
    u32 Temp;
	   
   	/* 设置延时时间以及计数平率 */
   	SysTick->CTRL &= ~ ( 1 << 2 );              /* SYSTICK使用外部时钟源 */
    SysTick->LOAD = us * (100 / 8);             /* 时间加载 */
    SysTick->VAL = 0x00;                        /* 清空计数器 */
    SysTick->CTRL = 0x01 ;                      /* 开始倒数 */
	
	/* 等待时间到达 */
    do
    {
        Temp = SysTick->CTRL;
    }
	while ( (Temp & 0x01) && (!(Temp & (1 << 16))) ); 
	
	/* 关闭定时器 */
    SysTick->CTRL = 0x00;                        /* 关闭计数器 */
    SysTick->VAL = 0X00;                         /* 清空计数器 */
}

/**************************** 毫秒延时函数 ****************************
功  能：实现毫秒级别的时间延时
参  数：需要延时的毫秒时间值（取值范围：1～1342ms）
返回值：无
***************************************************************************/
void Delay_ms(u16 ms)
{
    u32 Temp;
	
	/* 设置延时时间以及计数平率 */
    SysTick->LOAD = ( u32 ) ms * (100 / 8) * 1000;      /* 时间加载(SysTick->LOAD为24bit) */
    SysTick->VAL = 0x00;                                /* 清空计数器 */
    SysTick->CTRL = 0x01 ;                              /* 开始倒数 */
	
	/* 等待时间到达 */
    do
    {
        Temp = SysTick->CTRL;
    }
	while ( (Temp & 0x01) && (!(Temp & ( 1 << 16))) ); 
	
	/* 关闭定时器 */
    SysTick->CTRL = 0x00;                        /* 关闭计数器 */
    SysTick->VAL = 0X00;                         /* 清空计数器 */
}









