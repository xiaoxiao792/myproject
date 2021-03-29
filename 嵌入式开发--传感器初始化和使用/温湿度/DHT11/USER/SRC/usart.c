#include "usart.h"
#include "stdio.h"

#include "usart.h"

/*
�������ܣ�usart��ʼ��
�βΣ�1)ʱ��Ƶ�� 2�������� 3��������
����ֵ����
��ע��RXD -- PA9  TXD -- PA10
*/
void USART1_Init(u32 Fclk, u32 Band, u8 Over8)
{
	u32 Mantissa;    //�洢����
	u32 Fraction;    //�洢С��
	float USARTDIV;      //�洢�����ʵ�ֵ
	
	/* ʱ��ʹ�� */
	RCC->AHB1ENR |= 1 << 0;         //ʹ��GPIOAʱ��
	
	/* ����PA9 -- RXD */
	GPIOA->MODER &= ~(3 << (2 * 9));
	GPIOA->MODER |= 2 << (2 * 9);    //���ù���
	
	GPIOA->AFR[1] &= ~(15 << (4 * (9 - 8)));
	GPIOA->AFR[1] |= 7 << (4 * (9 - 8));  //����ΪUSART1
	
	/* ����PA10 -- TXD */
	GPIOA->MODER &= ~(3 << (2 * 10));
	GPIOA->MODER |= 2 << (2 * 10);         //���ù���
	GPIOA->AFR[1] &= ~(15 << (4 * (10 - 8)));
	GPIOA->AFR[1] |= 7 << (4 * (10 - 8));  //����ΪUSART1
	
	/* ����ʱ������ */
	RCC->APB2ENR |= 1 << 4;     //ʹ��USART1ʱ��
	USART1->CR1 &= ~(1 << 12);  //����λΪ8λ
	USART1->CR1 &= ~(1 << 10);  //��ֹУ��λ
	USART1->CR1 |= 1 << 3;      //����ʹ��
	USART1->CR1 |= 1 << 2;      //����ʹ��
	
	/* ���ò����� */
	if(Over8 == 0)
	{
		USART1->CR1 &= ~(1 << 15);    //16��������
	}
	else
	{
		USART1->CR1 |= 1 << 15;      //8��������
	}
		
	USARTDIV = (Fclk * 1000000) / ((8 * (2 - Over8)) * Band );
	
	Mantissa = (u32)USARTDIV;   //ȡ��������
	Fraction = (USARTDIV - Mantissa) * 16;
	
	USART1->BRR = (Mantissa << 4 | Fraction);   //�����ʴ洢�Ľ��
	
	/* ����ʹ�� */
	USART1->CR1 |= 1 << 13;    //usart ʹ��
}


/**************************************
�ַ������ͺ���
***************************************/
void USART1_Send_Str(u8 *str)
{
	while(*str !='\0')
	{
		while( !(USART1->SR &(1<<7)) )
		{
		 //�ȴ���������Ϊ��
		}
		USART1->DR =*str;
		str++;
	}
}

/******************** ���ڴ�ӡ���� ***************************************/
/* fputc��printf��ײ�ĵ��ú��� */
int fputc(int data,FILE *file)
{
	while( !(USART1->SR & (1 << 6)) );//�ȴ��������
	USART1->DR = data;   //��������
	return data;
} 



