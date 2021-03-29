#include "key.h"

/*
函数功能：key初始化
函数返回值：无
函数形参：无
备注：KEY1 -- PA0  没有按下是低电平，按下是高电平
			KEY2 -- PE2  没有按下是高电平，按下是低电平
			KEY3 -- PE3  没有按下是高电平，按下是低电平
			KEY4 -- PE4  没有按下是高电平，按下是低电平
*/
void KEY_Init(void)
{
	 RCC->AHB1ENR |= 1 << 0;  //使能GPIOA时钟
	 RCC->AHB1ENR |= 1 << 4;  //使能GPIOE时钟
	 
	/* 设置PA0 */
	 GPIOA->MODER &= ~(3 << (0 * 2));   //输入模式
	 GPIOA->PUPDR &= ~(3 << (0 * 2)); //无上下拉
	/* 设置PE2 */
	 GPIOE->MODER &= ~(3 << (2 * 2));   //输入模式
	 GPIOE->PUPDR &= ~(3 << (2 * 2)); //无上下拉
	
	/* 设置PE3 */
	 GPIOE->MODER &= ~(3 << (3 * 2));   //输入模式
	 GPIOE->PUPDR &= ~(3 << (3 * 2)); //无上下拉
	
	/* 设置PE4 */
	 GPIOE->MODER &= ~(3 << (4 * 2));   //输入模式
	 GPIOE->PUPDR &= ~(3 << (4 * 2)); //无上下拉
}

/*
函数功能：key扫描
函数返回值：返回按键值
函数形参：无
备注：return 1 : key1按下  return 2 : key2按下
      return 3 : key3按下  return 4 : key4按下
      return 0 : 没有按键按下
*/
u8 key_Scan(void)
{
	 static u8 flag = 1;
	 u8 key = 0;
	 
	 if((KEY1 || KEY2 || KEY3 || KEY4) && flag == 1)
	 {
		  delay(50000);  //延时10ms
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
	 else if(!KEY1 && !KEY2  && !KEY3 && !KEY4)  //按键没有按下
	 {
		  flag = 1;     //为下一次按键按下做准备
		  key = 0;
	 }
	  return key;
}


void delay(u32 t)
{
	while(t--);
}





