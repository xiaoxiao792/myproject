#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "ir.h"
#include "includes.h"
static ADC_InitTypeDef       ADC_InitStructure;
static ADC_CommonInitTypeDef ADC_CommonInitStructure;
static EXTI_InitTypeDef   EXTI_InitStructure;
static NVIC_InitTypeDef   NVIC_InitStructure;
static GPIO_InitTypeDef		GPIO_InitStructure;
extern OS_FLAG_GRP g_flag_grp;
//将adc引脚配置为PA6
void adc_falame_init(void)//火焰
{


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;			//第5个引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;		//模拟信号引脚模式
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//引脚高速工作，收到指令立即工作；缺点：功耗高
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//增加输出电流的能力
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//不需要上下拉电阻
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;				//独立工作，一个ADC硬件对某通道进行转换
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;				//ADC硬件时钟=84MHz/2=42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	//取消DMA（direct memory acces）
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//2个采样点的间隔时间=5*(1/42MHz)
	ADC_CommonInit(&ADC_CommonInitStructure);
	

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;					//12bit精度

	ADC_InitStructure.ADC_ScanConvMode = DISABLE;							//扫描单个通道
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//连续转换，不断输出结果
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//不使用外部脉冲来触发工作
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//输出结果是右对齐存储
	ADC_InitStructure.ADC_NbrOfConversion = 1;								//转换1个通道
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	//指定ADC1转换通道5
	//转换优先级为1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_3Cycles);//采样点时间=3*(1/42MHz)
	
	
	//使能ADC1硬件工作
	ADC_Cmd(ADC1, ENABLE);
}


void  EXIT9_init(void)//火焰
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource6);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling ;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI9_5_IRQHandler(void)
{
	OS_ERR err;

	//进入中断
	OSIntEnter(); 

	if(EXTI_GetITStatus(EXTI_Line6) == SET)//火焰
	{
		if(PCin(6))
		{
			OSFlagPost(&g_flag_grp,0x100,OS_OPT_POST_FLAG_SET,&err);	
			//PFout(8)=0;
		}
		else
		{
			OSFlagPost(&g_flag_grp,0x80,OS_OPT_POST_FLAG_SET,&err);	
			//PFout(8)=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
	if(EXTI_GetITStatus(EXTI_Line7) == SET)//可燃气
	{
		if(PBin(7))
		{

			//OSFlagPost(&g_flag_grp,0x100,OS_OPT_POST_FLAG_SET,&err);	
			PFout(8)=0;
		}
		else
		{
			//OSFlagPost(&g_flag_grp,0x80,OS_OPT_POST_FLAG_SET,&err);	
			PFout(8)=1;
		}
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//红外
	{
		//设置事件标志组
		OSFlagPost(&g_flag_grp,0x01,OS_OPT_POST_FLAG_SET,&err);
		
		EXTI_ClearITPendingBit(EXTI_Line8);
	}

	//退出中断
	OSIntExit();
}
