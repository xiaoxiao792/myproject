#include "systick.h"
#include "key.h"
#include "usart.h"

void Delay_ms(u32 ms)
{
	u8 count=ms/500;
	u32 lest_time=ms%500;
	while(count--)  Delay_xms(500);
	if(lest_time)   Delay_xms(lest_time);	  
}


void Delay_xms(u32 ms)
{
	SysTick->CTRL &=~(1<<0); //�رյδ�ʱ��
	SysTick->CTRL &=~(1<<2); //ѡ��ʱ��ԴΪ 21 MHz
	SysTick->CTRL &=~(1<<1); //�رյδ��ж�
	SysTick->LOAD = 21000*ms;   //���Զ����ؼĴ���д�����ֵ
	SysTick->VAL =0;         //��ʼ����ǰֵ�Ĵ���
	SysTick->CTRL |=1<<0;    //�򿪵δ�ʱ��
	while( !( SysTick->CTRL & (1<<16) ))
	{
	 //�ȴ���ʱ����
	}
	SysTick->CTRL &=~(1<<0); //�رյδ�ʱ��
}


void SysTick_Interrupt_ms(u32 ms)
{
	SysTick->CTRL &=~(1<<0);    //�رյδ�ʱ��
	SysTick->CTRL &=~(1<<2);    //ѡ��ʱ��ԴΪ 21 MHz
	SysTick->CTRL |=1<<1;       //�򿪵δ��ж�
	SysTick->LOAD = 21000*ms;   //���Զ����ؼĴ���д�����ֵ
	SysTick->VAL =0;            //��ʼ����ǰֵ�Ĵ���
}

void SysTick_Handler(void)
{
	if( SysTick->CTRL & (1<<16) ) //�жϵδ��жϵ����������жϱ�־λ
	{		
		//rec_flag=1;                 //���ݽ������
		SysTick->CTRL &=~(1<<0);    //�رյδ�ʱ��		
	}			
}



void Delay_us(u32 us)
{
	SysTick->CTRL &=~(1<<0); //�رյδ�ʱ��
	SysTick->CTRL &=~(1<<2); //ѡ��ʱ��ԴΪ 21 MHz
	SysTick->CTRL &=~(1<<1); //�رյδ��ж�
	SysTick->LOAD = 21*us;   //���Զ����ؼĴ���д�����ֵ
	SysTick->VAL =0;         //��ʼ����ǰֵ�Ĵ���
	SysTick->CTRL |=1<<0;    //�򿪵δ�ʱ��
	while( !( SysTick->CTRL & (1<<16) ))
	{
	 //�ȴ���ʱ����
	}
	SysTick->CTRL &=~(1<<0); //�رյδ�ʱ��
}
