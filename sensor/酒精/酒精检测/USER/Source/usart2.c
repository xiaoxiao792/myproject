#include "usart2.h"

#include "USART2.h"

void USART2_Init(u32 bound)
{
	float USARTDIV=0;      
	u16   DIV_Mantissa=0;  //��������
	u8    DIV_Fraction=0;  //С������
	//1)GPIO����
	RCC->AHB1ENR  |=1<<0;            //GPIOA ʱ��ʹ��
	GPIOA->MODER  &=~(0xF<<(2*2));   //ģʽ����PA2,PA3
	GPIOA->MODER  |=0xA<<(2*2);      //����ģʽ
	GPIOA->AFR[0] &=~(0xFF<<8);      //���ù���ѡ��
	GPIOA->AFR[0] |=0x77<<8;   
  
	RCC->APB1ENR  |=1<<17;//USART2ʱ��ʹ��
	//2)USART��ز������ã���������ģʽ���ֳ�����żУ�飬ֹͣλ��
	USART2->CR1   &=~(1<<15);        //16��������ģʽ
	USART2->CR1   &=~(1<<12);        //1 ��ʼλ�� 8 ����λ�� n ֹͣλ

	//3)���ڲ����ʼ����д��

	USARTDIV     =42*1000000/( 16.0*bound  ) ;  //����16.0���õ�����������
	DIV_Mantissa = USARTDIV;                     //�õ���������
	DIV_Fraction = (USARTDIV -DIV_Mantissa)*16;  //�õ�С������
	USART2->BRR  = (DIV_Mantissa<<4) | DIV_Fraction;	//д�벨���ʼĴ���
	
	//4)���ʹ��
	USART2->CR1  |=1<<3;                //������ʹ��
	USART2->CR1  |=1<<2;                //������ʹ��
	USART2->CR1  |=1<<13;               //����ģ��ʹ��	
}


