#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
static EXTI_InitTypeDef   	EXTI_InitStructure;
static GPIO_InitTypeDef		GPIO_InitStructure;
static NVIC_InitTypeDef		NVIC_InitStructure;
static TIM_OCInitTypeDef  TIM_OCInitStructure;
static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
int32_t infrared_get_distance(uint8_t *data)
{
	uint8_t d=0;

	uint32_t t=0;
	int i,j;
	
	if(PAin(8))
		return -3;
	while(PAin(8)==0)
	{
		t++;
		delay_us(1);
		
		if(t >=10000)
			return -1;
	}	
	t=0;
	while(PAin(8))
	{
		t++;
		delay_us(1);	
	
		if(t >= 6000)
			return -2;		
	}
	t=0;

	//测量高电平的持续时间
	for(j=0;j<4;j++)
	{
		d=0;
		for(i=0;i<8;i++)
		{
			t=0;
			//等待回响信号引脚输出高电平
			while(PAin(8)==0)
			{
				t++;
				delay_us(1);
				
				if(t >= 4000)
					return -4;
			}	
			t=0;
			delay_us(700);
			if(PAin(8))
			{
				d|=(1<<i);
			}
			while(PAin(8))
			{
				t++;
				delay_us(1);
				
				if(t >= 4000)
					return -5;
			}			
		}
		data[j]=d;
	}
	delay_us(600);
	if((data[0]+data[1]==0xFF)&&(data[2]+data[3]==0xFF))//检验和
	{
		return 0;
	}
	return -6;	
}
void infrared_init(void)
{
	//使能端口B和端口E的硬件时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource8);

	//配置PG6为输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;			//第6个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;		//输入模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ; 
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

}
void TIM1_PWM_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	/* GPIOC clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;

	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);

	
	TIM_TimeBaseStructure.TIM_Period = (20000/200)-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse =100;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

	/* TIM3 enable counter */
	TIM_Cmd(TIM1, ENABLE);	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
}
