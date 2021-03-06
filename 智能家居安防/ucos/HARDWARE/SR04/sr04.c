#include "sys.h"
#include "delay.h"


static GPIO_InitTypeDef		GPIO_InitStructure;

void sr04_init(void)
{
	//使能端口B和端口E的硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	
	//配置PB6为输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;			//第6个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;		//输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
	
	
	//配置PE6为输入模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;			//第6个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;		//输入模式
	GPIO_Init(GPIOE,&GPIO_InitStructure);	


	//PB6是连接到触发信号引脚，初始电平为低电平
	PCout(11)=0;
}



int32_t sr04_get_distance(void)
{
	uint32_t t=0;
	
	uint32_t d;

	PCout(11)=1;
	
	delay_us(20);
	
	PCout(11)=0;
	
	//等待回响信号引脚输出高电平
	while(PEin(5)==0)
	{
		t++;
		delay_us(1);
		
		if(t >= 1000000)
			return -1;
	}
	
	
	//测量高电平的持续时间
	t=0;
	while(PEin(5))
	{
		t++;
		delay_us(9);	//传输9us时间的距离就是3mm
		
		if(t >= 1000000)
			return -2;		
	}


	d = 3*t/2;
	
	return d;
}
