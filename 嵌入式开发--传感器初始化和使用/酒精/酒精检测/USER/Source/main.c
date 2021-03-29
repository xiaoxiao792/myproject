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
**** 设计者:      Zhangxx    日期：2018年9月02日
**** 修改者:      Zhangxx    日期：2018年9月02日
**** 功  能：	    酒精检测
**** 版本信息:    V2
**** 说  明：    
****编程思路：    利用ADC获取外界的模拟量，转换成数字量，根据公式打印模拟量，打印获取的电压值
									设定一个电压阈值，超过一定的电压值，则可以检测是否含酒精
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
		printf("数字量 ： %d\r\n",ad_val);
		printf("电压值 ：%.1f\r\n",(ad_val*3.3/4096) );
//		temp = (float)(ad_val * 100 / 4096);
//		printf("光线强度：%d%%\r\n", temp);
	}
}

