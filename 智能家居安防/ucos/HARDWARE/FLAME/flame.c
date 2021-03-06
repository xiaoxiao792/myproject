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
//��adc��������ΪPA6
void adc_falame_init(void)//����
{


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;			//��5������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AN;		//ģ���ź�����ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//���Ÿ��ٹ������յ�ָ������������ȱ�㣺���ĸ�
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//�����������������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//����Ҫ����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;				//����������һ��ADCӲ����ĳͨ������ת��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;				//ADCӲ��ʱ��=84MHz/2=42MHz
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	//ȡ��DMA��direct memory acces��
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//2��������ļ��ʱ��=5*(1/42MHz)
	ADC_CommonInit(&ADC_CommonInitStructure);
	

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;					//12bit����

	ADC_InitStructure.ADC_ScanConvMode = DISABLE;							//ɨ�赥��ͨ��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//����ת��������������
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ʹ���ⲿ��������������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//���������Ҷ���洢
	ADC_InitStructure.ADC_NbrOfConversion = 1;								//ת��1��ͨ��
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	//ָ��ADC1ת��ͨ��5
	//ת�����ȼ�Ϊ1
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime_3Cycles);//������ʱ��=3*(1/42MHz)
	
	
	//ʹ��ADC1Ӳ������
	ADC_Cmd(ADC1, ENABLE);
}


void  EXIT9_init(void)//����
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

	//�����ж�
	OSIntEnter(); 

	if(EXTI_GetITStatus(EXTI_Line6) == SET)//����
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
	if(EXTI_GetITStatus(EXTI_Line7) == SET)//��ȼ��
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
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//����
	{
		//�����¼���־��
		OSFlagPost(&g_flag_grp,0x01,OS_OPT_POST_FLAG_SET,&err);
		
		EXTI_ClearITPendingBit(EXTI_Line8);
	}

	//�˳��ж�
	OSIntExit();
}
