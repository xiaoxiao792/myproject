#include "stm32f4xx.h"
#include "sys.h"
#include "includes.h"

static NVIC_InitTypeDef		NVIC_InitStructure;
static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

void iwdg_init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	IWDG_SetPrescaler(IWDG_Prescaler_128); 
	
	IWDG_SetReload(4000-1);
	
	IWDG_ReloadCounter();
	
	IWDG_Enable();
}

void TIM2_init()//36ms<t<49ms时间内喂狗不复位，其余时间为非法喂狗
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period =(38000)-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 25600-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Enable the TIM2 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x04;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* TIM Interrupts enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void  TIM2_IRQHandler  (void)
{
	//申请CPU状态保存
	CPU_SR_ALLOC();
	//进入中断
	OSIntEnter(); 
	if (TIM_GetITStatus(TIM2, TIM_IT_Update)== SET)
	{
		
		IWDG_ReloadCounter();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update );
	}
		//退出临界区,解锁关中断
	OS_CRITICAL_EXIT() ; 
	//退出中断
	OSIntExit();
}
