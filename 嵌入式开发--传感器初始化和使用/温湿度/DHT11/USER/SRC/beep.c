#include "beep.h"

void BEEP_Init(void)
{
	RCC->AHB1ENR |=1<<4;           //����Ӧ��GPIOE��ʱ��
	                               
	GPIOE->MODER   &=~(3<<(2*0));  //����GPIOE.0�˿�ģʽ
	GPIOE->MODER   |=1<<(2*0);     //����GPIOE.0Ϊͨ�����ģʽ
	GPIOE->OTYPER  &=~(1<<0);      //�١������������
	GPIOE->OSPEEDR &=~(3<<(2*0));  //�ڡ���������ٶ�Ϊ2MHz
	GPIOE->PUPDR   &=~(3<<(2*0));  //����GPIOE.0�˿�������
	GPIOE->ODR     &=~(1<<0);      //��ʼ��GPIO��
}



