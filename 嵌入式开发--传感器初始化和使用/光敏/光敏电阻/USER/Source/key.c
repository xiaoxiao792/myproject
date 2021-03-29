#include "key.h"

void KEY_Init(void)
{
	RCC->AHB1ENR |=1<<0;  //使能GPIOA
	RCC->AHB1ENR |=1<<4;  //使能GPIOE
	
	GPIOA->MODER  &=~(3<<(0*2)); //PA0模式为输入模式
	GPIOA->PUPDR  &=~(3<<(0*2)); //PA0无上下拉	
	
	GPIOE->MODER  &=~(3<<(2*2));  //PE2模式为输入模式
	GPIOE->PUPDR   &=~(3<<(2*2)); //PE2无上下拉	
	
	GPIOE->MODER  &=~(3<<(3*2));  //PE3模式为输入模式
	GPIOE->PUPDR   &=~(3<<(3*2)); //PE3无上下拉	
	
	GPIOE->MODER  &=~(3<<(4*2));  //PE4模式为输入模式
	GPIOE->PUPDR   &=~(3<<(4*2)); //PE4无上下拉	
}

u32 count=0;
u32 temp=0;
u8 Key_Scan(void)
{
	static u8 key=0;
	static u8 sta=1;  //按键锁定
	if( ( KEY1 ||(!KEY2) ||(!KEY3) ||(!KEY4) ) &&sta)     //如果按键按下 ，并且按键没有被锁定
	{
		//按键锁定：前一次按键按下后，没有松开，锁定按键，不再产生有效按键值
		//如果 （按键1按下或者 按键2按下 或者 按键3按下 或者 按键4按下） 并且 按键没有被锁定，则扫描按键
		Delay(50000);             //延时进行消抖，滤除抖动
		if(KEY1)         key=1;   //再次判断按键按下
		else if(!KEY2)   key=2;  
		else if(!KEY3)   key=3;  
		else if(!KEY4)   key=4;  
		
		if(key)          sta=0;
	}
	//怎么知道按键是一直按下，判断sta为0即可
	if( (sta==0) && temp<100)   //长按检测
	{
		count++;
		if(count==35000)
		{
			count=0;
			temp++;
			if(temp==100)    return  key+4;
		}
	}
	
	if( ((KEY1==0) &&KEY2 &&KEY3 &&KEY4 )  && (sta==0))  //松开检测
	{	
		Delay(50000);
		if( (KEY1==0) &&KEY2 &&KEY3 &&KEY4 )
		{
				sta=1;   //按键松开了，按键解锁
				if(temp==100)  key=0;
				temp =0;
				return key;
		}
	}
	
	return 0;       //返回按键值
}

void Delay(u32 time)
{
	while(time--);
}
