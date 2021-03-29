#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "usart1.h"
#include  <stdio.h>
#include "systick.h"
#include "beep.h"
#include "timer.h"
/*******************************************************************************************************
**** 程序名称：   main
**** 设计者:      Zhangxx    日期：2018年11月09日
**** 修改者:      Zhangxx    日期：2018年11月09日
**** 功  能：	    PWM驱动舵机
**** 版本信息:    V0.1
**** 说  明：     
****编程思路：    调节占空比驱动舵机
****信盈达官网：  www.edu118.com   成才热线：18948782707
********************************************************************************************************/
int main(void)
{
	u8 key=0;
	u16 ccr=80;
	u16 data=0;
	LED_Init();
	KEY_Init();
	beep_init();
	NVIC_SetPriorityGrouping(5);       //分组为第5组
	USART1_Init(115200);
	TIM5_CH2_Init(8400-1,200,ccr);    //20ms一个周期，高电平占周期时间0.5ms
  while(1)
	{	
		key = Key_Scan();
		if( key ==1 )
		{
			ccr+=1;
			if(ccr>195) //调节角度变小
			{
				ccr=195;
			}
				printf("ccr=%d\r\n",ccr);
		}
		else if( key == 2)
		{
			ccr-=1;
			if(ccr<175)    //调节角度变大 
			{
				ccr=175;
			}		
				printf("ccr=%d\r\n",ccr);
		}
		if( key )  
		{
			printf("ccr=%d\r\n",ccr);
			TIM5->CCR2 = ccr;     //写入输出比较值	
		}
	}
}

