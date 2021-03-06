#include "stm32f4xx.h"
#include "sys.h"
#include <stdio.h>
#include "delay.h"

static GPIO_InitTypeDef		GPIO_InitStructure;
void  humiture_init(void)
{

	//使能端口G的硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	
	
	
	//配置PG9为输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;			//第9个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;		//输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
	
	//PG6是连接到触发信号引脚，初始电平为低电平
	PGout(9)=1;
}
void humiture_mode(GPIOMode_TypeDef Mode)
{
		//配置PG6为输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;			//第9个引脚
	GPIO_InitStructure.GPIO_Mode=Mode;		//输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}
int32_t humiture_get_distance(uint8_t *data)
{
	uint8_t d=0;
	uint32_t t=0;
	int i,j;
	humiture_mode(GPIO_Mode_OUT);
	PGout(9)=0;
	
	delay_ms(20);
	
	PGout(9)=1;	
	
	delay_us(40);
	
	humiture_mode(GPIO_Mode_IN);
	while(PGin(9))
	{
		t++;
		delay_us(1);
		
		if(t >= 4000)
			return -1;
	}	
	t=0;
	while(PGin(9)==0)
	{
		t++;
		delay_us(1);	
	
		if(t >= 4000)
			return -2;		
	}
	t=0;
	while(PGin(9))
	{
		t++;
		delay_us(1);	
	
		if(t >= 4000)
			return -3;		
	}
	//测量高电平的持续时间
	for(j=0;j<5;j++)
	{
		d=0;
		for(i=7;i>=0;i--)
		{
			t=0;
			//等待回响信号引脚输出高电平
			while(PGin(9)==0)
			{
				t++;
				delay_us(1);
				
				if(t >= 4000)
					return -4;
			}	

			delay_us(40);
			if(PGin(9))
			{
				d|=1<<i;
				
				//等待数据1的高电平时间持续完毕
				t=0;
				while(PGin(9))
				{
				
					t++;
					
					delay_us(1);
					
					if(t >= 100)
						return -5;
				}			
			
			}
			
		}
		data[j]=d;
	}
	
	//通信的结束
	delay_us(200);
	d=0;
	for(i=0;i<4;i++)
	{
		d+=data[i];
	}
	if((d&0xFF)==(data[4]&0xFF))//检验和
	{
		
		return 0;
	}
	return -6;
	
}
