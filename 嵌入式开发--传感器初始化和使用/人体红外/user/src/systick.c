#include "systick.h"
#include "led.h"

/*
�����Ĺ��ܣ�systick_us��ʱ����
�βΣ���Ҫ��ʱʱ��
����ֵ��void
��ע��168MHZ / 8 = 21MHZ
*/
void Systick_us(u32 us)
{
	SysTick->CTRL &= ~(1 << 2);   //ѡ���ⲿʱ��Դ
	
	SysTick->LOAD = SYSCLK * us;  //д������ֵ
	SysTick->VAL = 0;    					//�������
	
	SysTick->CTRL |= 1 << 0;      //ʹ�ܼ�����
	
	while(!(SysTick->CTRL & (1 << 16)))
	{
		/* �ȴ�ʱ�䵽 */
	}
	SysTick->CTRL &= ~(1 << 0);   //�رռ�����
}

/*
�����Ĺ��ܣ�systick_ms��ʱ����
�βΣ���Ҫ��ʱʱ��
����ֵ��void
��ע��168MHZ / 8 = 21MHZ
*/
void Systick_ms(u32 ms)
{
	SysTick->CTRL &= ~(1 << 2);   //ѡ���ⲿʱ��Դ
	
	SysTick->LOAD = SYSCLK * ms * 1000;  //д������ֵ
	SysTick->VAL = 0;    					//�������
	
	SysTick->CTRL |= 1 << 0;      //ʹ�ܼ�����
	
	while(!(SysTick->CTRL & (1 << 16)))
	{
		/* �ȴ�ʱ�䵽 */
	}
	SysTick->CTRL &= ~(1 << 0);   //�رռ�����
}

/*
�����Ĺ��ܣ�systick_inter_ms��ʱ����
�βΣ���Ҫ��ʱʱ��
����ֵ��void
��ע��168MHZ / 8 = 21MHZ
*/
void systick_inter_ms(u32 ms)
{
	SysTick->CTRL &= ~(1 << 2);   //ѡ���ⲿʱ��Դ
	
	SysTick->LOAD = SYSCLK * ms * 1000;  //д������ֵ
	
	SysTick->VAL = 0;    					//�������
	
	SysTick->CTRL |= 1 << 1;     //ʹ���ж�
	SysTick->CTRL |= 1 << 0;      //ʹ�ܼ�����
}

void SysTick_Handler(void)
{
	if(SysTick->CTRL & (1 << 16))
	{
		 GPIOF->ODR ^= 1 << 6;
	}
}





