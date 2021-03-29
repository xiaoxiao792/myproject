#include "stm32f4xx.h"
#include "led.h"


/*
 Out----PC1
 PC1 �ܽŵ͵�ƽ�����л������
 
*/
void HC_SR_init()
{
	//��PC�ܽ�ʱ��
	RCC->AHB1ENR |=(1<<2);
	//PC1 ͨ������ģʽ
	GPIOC->MODER &= ~(0x3<<2);
	
	//PC1 ������/���� ����ѡ��Ĭ��ֵ
	GPIOC->PUPDR &=~(0x3<<2);
}


int HC_SR_input()
{
	if((GPIOC->IDR & (1 << 1)) == 0)  //����͵�ƽ
	{
		return 1;
	}	
	else   return 0;
}











