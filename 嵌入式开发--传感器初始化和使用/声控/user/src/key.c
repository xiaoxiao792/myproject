#include "key.h"

/*
函数的功能：KEY初始化
形参：void
返回值：void
备注：PA0  - 没有按下低电平，按下为高电平
*/
void KEY_Init(void)
{
	RCC->AHB1ENR |= 1 << 0;  //使能GPIOA时钟
	RCC->AHB1ENR |= 1 << 4;  //使能GPIOE时钟
	
	/* PA0 配置 */
	GPIOA->MODER &= ~(3 << (2 * 0)); //输入模式
	GPIOA->PUPDR &= ~(3 << (2 * 0));
	GPIOA->PUPDR |= 2 << (2 * 0);   //下拉
	
	/* PE2 配置 */
	GPIOE->MODER &= ~(3 << (2 * 2)); //输入模式
	GPIOE->PUPDR &= ~(3 << (2 * 2));
	GPIOE->PUPDR |= 1 << (2 * 2);   //上拉
	
	/* PE3 配置 */
	GPIOE->MODER &= ~(3 << (2 * 3)); //输入模式
	GPIOE->PUPDR &= ~(3 << (2 * 3));
	GPIOE->PUPDR |= 1 << (2 * 3);   //上拉
	
	/* PE4 配置 */
	GPIOE->MODER &= ~(3 << (2 * 4)); //输入模式
	GPIOE->PUPDR &= ~(3 << (2 * 4));
	GPIOE->PUPDR |= 1 << (2 * 4);   //上拉
	
}

/*
函数的功能：KEY扫描
形参：void
返回值：返回1 -- 按键1按下 
备注：PA0  - 没有按下低电平，按下为高电平
			PE2  - 没有按下高电平，按下为低电平
			PE3  - 没有按下高电平，按下为低电平
			PE4  - 没有按下高电平，按下为低电平
*/
u8 KEY_Scan(void)
{
	static u8 flag = 1;  //按键的状态 0：没有按下  1：按下
	u8 key = 0;
	
	if((KEY1 || KEY2 || KEY3 || KEY4) && flag == 1)
	{
		 delay(200000);   //10ms
		 if(KEY1)
		 {
			 flag = 0;
			 key = 1;
		 }
		 else if(KEY2)
		 {
			 flag = 0;
			 key = 2;
		 }
		 else if(KEY3)
		 {
			 flag = 0;
			 key = 3;
		 }
		 else if(KEY4)
		 {
			 flag = 0;
			 key = 4;
		 }
	} 
	
	else if(!KEY1 && !KEY2 && !KEY3 && !KEY4)  //没有按下
	{ 
		 flag = 1;   //为下一次按键按下做准备
	}
	return key;
}


void delay(u32 t)
{
	 while(t)
	 {
		 t--;
	 }
}



