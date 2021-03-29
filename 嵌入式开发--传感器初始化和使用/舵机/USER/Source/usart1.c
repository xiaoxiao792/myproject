#include "usart1.h"
#include  <stdio.h>
void  USART1_IRQHandler(void)
{
	u8 data=0;
	if( USART1->SR&(1<<5)  )//����жϱ�־λ
	{
		USART1->SR  &=~(1<<5);
		data = USART1->DR;
		while( 0==( USART1->SR&(1<<7)) );
		USART1->DR = data;
	}
}


void USART1_Init(u32 bound)
{
	float USARTDIV=0;      
	u16   DIV_Mantissa=0;  //��������
	u8    DIV_Fraction=0;  //С������
	//1)GPIO����
	RCC->AHB1ENR  |=1<<0;            //GPIOA ʱ��ʹ��
	GPIOA->MODER  &=~(0xF<<(9*2));   //ģʽ����PA9,PA10
	GPIOA->MODER  |=0xA<<(9*2);      //����ģʽ
	GPIOA->AFR[1] &=~(0xFF<<4);      //���ù���ѡ��
	GPIOA->AFR[1] |=0x77<<4;   
  
	RCC->APB2ENR  |=1<<4;//USART1ʱ��ʹ��
	//2)USART��ز������ã���������ģʽ���ֳ�����żУ�飬ֹͣλ��
	USART1->CR1   &=~(1<<15);        //16��������ģʽ
	USART1->CR1   &=~(1<<12);        //1 ��ʼλ�� 8 ����λ�� n ֹͣλ

	//3)���ڲ����ʼ����д��

	USARTDIV     =84*1000000/( 16.0*bound  ) ;  //����16.0���õ�����������
	DIV_Mantissa = USARTDIV;                     //�õ���������
	DIV_Fraction = (USARTDIV -DIV_Mantissa)*16;  //�õ�С������
	USART1->BRR  = (DIV_Mantissa<<4) | DIV_Fraction;	//д�벨���ʼĴ���
	
	USART1->CR1  |=1<<5;                     //�����жϣ��ж�Դʹ�� 
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(5,1,1) ); //���ȼ�����
	NVIC_EnableIRQ(USART1_IRQn);             //�ж�ͨ��ʹ��
	//4)���ʹ��
	USART1->CR1  |=1<<3;                //������ʹ��
	USART1->CR1  |=1<<2;                //������ʹ��
	USART1->CR1  |=1<<13;               //����ģ��ʹ��	
	
}


void  USART1_Send_Str(u8 *str)
{
	while(*str !='\0')
	{
		while( !(USART1->SR &(1<<7)) )
		{
		
		}
		USART1->DR = *str;
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



