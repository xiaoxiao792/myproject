#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
void key_init()
{
	/* 外设时钟配置 */
	RCC->AHB1ENR |=((1<<0)|(1<<4)); //打开GPIOA GPIOE的外设时钟
	
	/* PA0管脚模式配置 */
	/* 端口模式配置 */
	GPIOA->MODER &=~(0X3<<0);  //PA0配置为输入模式
	/* 上下拉寄存器配置 */
	GPIOA->PUPDR &=~(0X3<<0);  //PA0配置为无上下拉-浮空
	
	/* PE2、PE3 、PE4管脚模式配置 */
	/* 端口模式配置 */
	GPIOE->MODER &=~(0X3F<<4); //PE2 PE3 PE4 配置为输入模式
	/* 上下拉寄存器配置 */
	GPIOE->PUPDR &=~(0X3F<<4);  //PE2 PE3 PE4 配置为无上下拉-浮空
}

int key_scan()
{
	static int key_sta=1;
	if(key_sta && (KEY0==0 || KEY1==0 || KEY2==0 ||WK_UP==1))
	{
				
		key_sta=0;
			delay(200);
		if(KEY0==0)  return 1;
		if(KEY1==0)  return 2;
		if(KEY2==0)  return 3;
		if(WK_UP==1) return 4;
	}
	else if(KEY0!=0 && KEY1!=0 && KEY2!=0 &&WK_UP==0)
	{
		key_sta=1;
	}
	return 0;
}










