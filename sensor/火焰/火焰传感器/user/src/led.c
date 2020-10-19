#include "stm32f4xx.h"
#include "led.h"

#include "led.h"
#include "key.h"

/*
�������ܣ�led��ʼ��
�βΣ���
����ֵ����
��ע��LED1  -- PC4  LED2  -- PC5  LED3  -- PA6  LED4  -- PA7   
*/
void LED_Init(void)
{
	/* ʹ��GPIOʱ�� */
	RCC->AHB1ENR |= 1 << 0;   //GPIOAʱ��ʹ��
	RCC->AHB1ENR |= 1 << 2;   //GPIOCʱ��ʹ��

	
	/* ����PC4����ģʽ */
	GPIOC->MODER &= ~(3 << (2 * 4));
	GPIOC->MODER |= 1 << (2 * 4);  //����Ϊ���ģʽ
	
	/* ����������� */
	GPIOC->OTYPER &= ~(1 << 4);    //����Ϊ�������
	
	/* ��������ٶ� */
	GPIOC->OSPEEDR &= ~(3 << (2 * 4));
	GPIOC->OSPEEDR |= 2 << (2 * 4);  //����Ϊ50MHZ
	
	/* ���������� */
	GPIOC->PUPDR &= ~(3 << (2 * 4));  //��������
	
	/*����GPIO��ʼ״̬ */
	GPIOC->ODR |= 1 << 4;     //��ʼ״̬Ϊ�ߵ�ƽ
	
	
	/* ����PC5����ģʽ */
	GPIOC->MODER &= ~(3 << (2 * 5));
	GPIOC->MODER |= 1 << (2 * 5);  //����Ϊ���ģʽ
	
	/* ����������� */
	GPIOC->OTYPER &= ~(1 << 5);    //����Ϊ�������
	
	/* ��������ٶ� */
	GPIOC->OSPEEDR &= ~(3 << (2 * 5));
	GPIOC->OSPEEDR |= 2 << (2 * 5);  //����Ϊ50MHZ
	
	/* ���������� */
	GPIOC->PUPDR &= ~(3 << (2 * 5));  //��������
	
	/*����GPIO��ʼ״̬ */
	GPIOC->ODR |= 1 << 5;     //��ʼ״̬Ϊ�ߵ�ƽ
	
	/* ����PA6����ģʽ */
	GPIOA->MODER &= ~(3 << (2 * 6));
	GPIOA->MODER |= 1 << (2 * 6);  //����Ϊ���ģʽ
	
	/* ����������� */
	GPIOA->OTYPER &= ~(1 << 6);    //����Ϊ�������
	
	/* ��������ٶ� */
	GPIOA->OSPEEDR &= ~(3 << (2 * 6));
	GPIOA->OSPEEDR |= 2 << (2 * 6);  //����Ϊ50MHZ
	
	/* ���������� */
	GPIOA->PUPDR &= ~(3 << (2 * 6));  //��������
	
	/*����GPIO��ʼ״̬ */
	GPIOA->ODR |= 1 << 6;     //��ʼ״̬Ϊ�ߵ�ƽ
	
	
	/* ����PA7����ģʽ */
	GPIOA->MODER &= ~(3 << (2 * 7));
	GPIOA->MODER |= 1 << (2 * 7);  //����Ϊ���ģʽ
	
	/* ����������� */
	GPIOA->OTYPER &= ~(1 << 7);    //����Ϊ�������
	
	/* ��������ٶ� */
	GPIOA->OSPEEDR &= ~(3 << (2 * 7));
	GPIOA->OSPEEDR |= 2 << (2 * 7);  //����Ϊ50MHZ
	
	/* ���������� */
	GPIOA->PUPDR &= ~(3 << (2 * 7));  //��������
	
	/*����GPIO��ʼ״̬ */
	GPIOA->ODR |= 1 << 7;     //��ʼ״̬Ϊ�ߵ�ƽ
}

void LED_Triggle(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOC->ODR ^=1<<4; break;
		case 2:
			GPIOC->ODR ^=1<<5; break;
		case 3:
			GPIOA->ODR ^=1<<6; break;
		case 4:
			GPIOA->ODR ^=1<<7;	break;
		case ALL:
		GPIOC->ODR ^=1<<4;
		GPIOC->ODR ^=1<<5;
		GPIOA->ODR ^=1<<6;
		GPIOA->ODR ^=1<<7;
			break;
		default: break;
	}
}

void LED_OFF(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOC->BSRRL =1<<4; break;
		case 2:
			GPIOC->BSRRL =1<<5; break;
		case 3:
			GPIOA->BSRRL =1<<6; break;
		case 4:
			GPIOA->BSRRL =1<<7;	break;
		case ALL:
		GPIOC->BSRRL =1<<4;
		GPIOC->BSRRL =1<<5;
		GPIOA->BSRRL =1<<6;
		GPIOA->BSRRL =1<<7;
			break;
		default: break;
	}
}

void LED_ON(u8 led)
{
	switch(led)
	{
		case 1: 
			GPIOC->BSRRH =1<<4; break;
		case 2:
			GPIOC->BSRRH =1<<5; break;
		case 3:
			GPIOA->BSRRH =1<<6; break;
		case 4:
			GPIOA->BSRRH =1<<7;	break;
		case ALL:
		GPIOC->BSRRH =1<<4;
		GPIOC->BSRRH =1<<5;
		GPIOA->BSRRH =1<<6;
		GPIOA->BSRRH =1<<7;
			break;
		default: break;
	}
}




void delay(int n)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++);
}
//��ҵ��ʵ��4���ƣ���ˮ��
