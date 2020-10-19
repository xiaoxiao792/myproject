#include "stm32f4xx.h"
#include "led.h"

//1s��ʱ
void time7_init(void)
{
	//	1.	ģ��ʱ��ʹ��--TIME7
	RCC->APB1ENR |=0X01<<5;
	//2.	����Ԥ��Ƶ���Զ���װ��ֵ
	TIM7->PSC =9999;   //10000   84*10^6 /10000 = 8400
	TIM7->ARR =8399;   //��ʱʱ��1s = ����ֵ* ʱ������   x = 1s/ʱ������  = 1s * 8400
	//3.	����UG����������¼�
	
	//4.	����UGλ�������������
	TIM7->EGR |=0X01;
	//5.	����±�־
	TIM7->SR &=~(0X01);
	//����ʱ�ж�
	TIM7->DIER |=0X01;
	NVIC_SetPriority(TIM7_IRQn,NVIC_EncodePriority(7-2,1,1));
	//��NVIC��ʹ�ܴ����ж�
	NVIC_EnableIRQ(TIM7_IRQn);
	
	//6.	����ʱ��
	TIM7->CR1 |=0X01<<0;
}

void TIM7_IRQHandler(void)
{
	static int cnt=0;
	
	TIM7->SR &=~(0X01);  //���־
	LED_Triggle(2);
	
	
	cnt++;
	if(cnt>1000)
	{
		cnt=0;
		//�������ֹͣת��
	//	motor_stop();
		//�رն�ʱ��
		TIM7->CR1 &=0;	
	}
}

