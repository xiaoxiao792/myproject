#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "systick.h"
#include "dht11.h"
/*******************************************************************************************************
**** 程序名称：   main
**** 设计者:      Zhangxx    日期：2018年11月09日
**** 修改者:      Zhangxx    日期：2018年11月09日
**** 功  能：	    温湿度检测
**** 版本信息:    V0.1
**** 说  明：    
****编程思路：    利用单总线时序单字节读取数据
****信盈达官网：  www.edu118.com   成才热线：18948782707
********************************************************************************************************/
int main(void)
{
	USART1_Init(84, 115200, 0);
	DHT11_Init();
	while(1)
	{ 
		DHT11_Show_Data();  
		Delay_ms(500);
	}
}
















 
