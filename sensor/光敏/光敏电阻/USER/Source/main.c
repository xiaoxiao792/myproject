#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "usart1.h"
#include  <stdio.h>
#include "systick.h"
#include "beep.h"
#include "timer.h"
#include "adc.h"
/*******************************************************************************************************
**** 程序名称：   main
**** 设计者:      Zhangxx   日期：2018年9月02日
**** 修改者:      Zhangxx    日期：2018年9月02日
**** 功  能：	    光线强度检测
**** 版本信息:    V0.1
**** 说  明：    
****编程思路：    利用ADC获取外界的模拟量，转换成数字量，根据公式打印模拟量，打印获取的电压值
									设定一个阈值，根据阈值可检测光线强度
****信盈达官网：  www.edu118.com   成才热线：18948782707
********************************************************************************************************/
int main(void)
{ 
	u16 ad_val=0;
	u16 temp;
	LED_Init();
	KEY_Init();
	beep_init();
	USART1_Init(115200);
	adc1_init();
  while(1)
	{	
		/*  PC2  ADC1_CH12  */
		Delay_ms(100);
		ad_val=get_adc_val();	
		printf("ad_val=%d\r\n",ad_val);
		printf("电压值为%.1f\r\n",(ad_val*3.3/4096) );

		temp = (100-(ad_val * 100)/ 4096);
		printf("光线强度：%d%%\r\n", temp);
	}
}

