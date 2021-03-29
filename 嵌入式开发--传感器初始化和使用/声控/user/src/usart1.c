#include "usart1.h"

/*
�����Ĺ��ܣ�USART1��ʼ��
�βΣ�pck:������   fck��ʱ������Ƶ��  over8: ������
����ֵ��void
��ע��PA9  -- TX
      PA10 -- RX
*/
void USART1_Init(u32 pck, u32 fck, u8 over8)
{
	u32 Priority;
	float USARTDIV;
	u32  Mantissa;  //����
	u32  Fraction;  //С������
	
	RCC->AHB1ENR |= 1 << 0;  //ʹ��GPIOAʱ��
	
	/* PA9 -- TX*/
	GPIOA->MODER &= ~(3 << (2 * 9));
	GPIOA->MODER |= 2 << (2 * 9);  //����ģʽ
	GPIOA->AFR[1] &= ~(15 << (4 *(9 - 8)));
	GPIOA->AFR[1] |= 7 << (4 *(9 - 8));  //����Ϊ����1
	
	/* PA10 -- RX*/
	GPIOA->MODER &= ~(3 << (2 * 10));
	GPIOA->MODER |= 2 << (2 * 10);  //����ģʽ
	GPIOA->AFR[1] &= ~(15 << (4 *(10 - 8)));
	GPIOA->AFR[1] |= 7 << (4 *(10 - 8));  //����Ϊ����1
	
	/* ���ô���1 */
	RCC->APB2ENR |= 1 << 4;     //ʹ�ܴ���1ʱ��
	USART1->CR1 &= ~(1 << 12);  //8λ����λ
	USART1->CR2 &= ~(3 << 12);  //1λֹͣλ
	USART1->CR1 |= 1 << 3;      //����ʹ��
	USART1->CR1 |= 1 << 2;      //����ʹ��
	
	/* ���������� */
	if(over8 == 0)
	{
		USART1->CR1 &= ~(1 << 15);   //16��������
	}
	else
	{
		USART1->CR1 |= 1 << 15;     //8��������
	}
	USARTDIV = (fck * 1000000) /(pck * (8 * (2- over8)));
	
	Mantissa = (u32)USARTDIV;
	Fraction = (USARTDIV - Mantissa) * 16;
	USART1->BRR =  Mantissa << 4 | Fraction;
	
	/* �����ж�ʹ�� */
	USART1->CR1 |= 1 << 5;   //�����ж�ʹ��
	
	/* ����NVIC */
	NVIC_SetPriorityGrouping(7 - 2);
	Priority =  NVIC_EncodePriority (7 - 2,  1 , 2) ;
	NVIC_SetPriority(USART1_IRQn, Priority );
	NVIC_EnableIRQ(USART1_IRQn) ;
	
	/* ʹ�ܴ��� */
	USART1->CR1 |= 1 << 13;   //ʹ�ܴ���
}

/* �жϷ����� */
u8 rec_buff[20] = {0};
u8 i = 0;
u8 flag = 0; //����״̬ 1���������  0��û�н������

void USART1_IRQHandler(void)
{
	if(USART1->SR & (1 << 5))
	{
		USART1->SR &= ~(1 << 5);  //�����жϱ�־λ����
		rec_buff[i] = USART1->DR; //"LED_ON#"
		
	  if(rec_buff[i] == '#' && flag == 0)
		{
			i = 0;
			flag = 1;
		}
		else
		{
			 i++;
		}
	}
}








/*
�����Ĺ��ܣ�USART1�����ַ���
�βΣ���Ҫ������ַ���
����ֵ��void
��ע��
*/
void USART_Send_str(u8 * str) //hello world\0
{
	while(*str != '\0')
	{
		USART1->DR = *str;
		while(!(USART1->SR & (1 << 7)))
		{
			/* �ȴ�������� */
		}
		str++;
	}
}

/*
�����Ĺ��ܣ�printf�ĵײ㺯��
�βΣ���Ҫ������ַ�
����ֵ��void
��ע��
*/
int fputc( int ch, FILE *stream )
{
	USART1->DR = ch;
	while(!(USART1->SR & (1 << 7)))
	{
		/* �ȴ�������� */
	}
	return ch;
}






