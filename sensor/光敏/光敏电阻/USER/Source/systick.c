#include "systick.h"

void Delay_ms(u32 ms)
{
	u32 last_ms=0;
	while(ms)
	{
		if( ms>=500 ) last_ms=500;
		else          last_ms=ms;  
		Delay_xms(last_ms);
		ms -= last_ms;
	}
}

void Delay_xms(u32 xms)
{
	SysTick->CTRL &=~(1<<0); //�رն�ʱ��
	SysTick->CTRL &=~(1<<1); //�رյδ��ж�
	SysTick->CTRL &=~(1<<2); //ѡ��ʱ��Դ21MHz
	SysTick->LOAD  =21000*xms  ; //������װ�ؼĴ���
	SysTick->VAL   =0      ; //��ʼ����ǰֵ�Ĵ���
	SysTick->CTRL |=(1<<0) ; //������ʱ��
	while( ( SysTick->CTRL &(1<<16) )==0) 
	{
		//�ȴ���ʱ����
	}
	SysTick->CTRL &=~(1<<0); //�رն�ʱ��	
}


void Delay_us(u32 us)
{
	SysTick->CTRL &=~(1<<0); //�رն�ʱ��
	SysTick->CTRL &=~(1<<1); //�رյδ��ж�
	SysTick->CTRL &=~(1<<2); //ѡ��ʱ��Դ21MHz
	SysTick->LOAD  =21*us  ; //������װ�ؼĴ���
	SysTick->VAL   =0      ; //��ʼ����ǰֵ�Ĵ���
	SysTick->CTRL |=(1<<0) ; //������ʱ��
	while( ( SysTick->CTRL &(1<<16) )==0) 
	{
		//�ȴ���ʱ����
	}
	SysTick->CTRL &=~(1<<0); //�رն�ʱ��	
}









