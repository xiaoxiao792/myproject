#include "led.h"
#include "key.h"
#include "beep.h"
#include "usart1.h"
#include "stdio.h"
#include <string.h>
#include "hw_sr.h"
#include "hc_sr.h"
#include "systick.h"
/*******************************************************************************************************
**** 程序名称：   main
**** 设计者:      Zhangxx    日期：2018年9月02日
**** 修改者:      Zhangxx    日期：2018年9月02日
**** 功  能：	    检测是否有遮挡
**** 版本信息:    V0.1
**** 说  明：     
****编程思路：    如果读到红外避障模块是高电平则LED1亮，如果是低电平，则LED1灭
****信盈达官网：  www.edu118.com   成才热线：18948782707
********************************************************************************************************/
int main()
{
	u8 data = 0;
	LED_Init();  
	KEY_Init();
	beep_init();
  USART1_Init(115200, 84, 0);
//	Hw_SR_init();  								//红外避障IO初始化
	HC_SR_init();                 //人体红外IO初始化
	printf("上电后需要等待一分钟模块才能进入待机状态！！！\r\n");
	while(1)
	{
		data = HC_SR_input();
		if(data == 1)               //如果检测有人体
		{
			 LED_ON(1);				//亮LED1
		}
		else
		{
			 LED_OFF(1); 						//灭LED1
		}
		Systick_ms(500);
	}
}








