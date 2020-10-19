#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "usart.h" 
/*******************************************
*������    :usart1_init
*��������  :����1����ʼ������
*��������  :u32 bps
*��������ֵ:��
*��������  :PA9--------USART1_TX
		        PA10--------USART1_RX
*********************************************/
void usart1_init(u32 bps)
{
	u32 pri;
	/*IO�ڿ���������*/
	//�˿�ʱ��ʹ��
	RCC->APB2ENR |= 1 << 2;//A
 
	//�˿�ģʽ����
	GPIOA->CRH &= ~(0XF << (4 * (9 - 8)));
	GPIOA->CRH |=  (0XB << (4 * (9 - 8)));		//��������50M
	
	GPIOA->CRH &= ~(0XF << (4 * (10 - 8)));
	GPIOA->CRH |=  (0X4 << (4 * (10 - 8)));		//��������
	
	/*����1����������*/
	//����1ģ��ʱ��ʹ��
	RCC->APB2ENR |= 1 << 14;
	//CR1
	USART1->CR1 &= ~(1<<12);        //8λ�ֳ�
	USART1->CR1 |= (1<<3);          //����ʹ��
	USART1->CR1 |= (1<<2);          //����ʹ��
	USART1->CR1 |= (1<<5);          //�����ж�ʹ��
	USART1->CR1 |= (1<<4);          //�����ж�ʹ��	
	//CR2
	USART1->CR2 &= ~(3<<12);        //1��ֹͣλ
	//BRR
	USART1->BRR = 72000000 / bps;

  /*NVIC����������*/
	//���ȼ�����  ��ռ2λ��Ӧ ��λ  д�����5
	//����������
	//�������ȼ�����ֵ
	 pri = NVIC_EncodePriority(5,1,2);
	//���þ����ж�Դ���ȼ�
	NVIC_SetPriority(USART1_IRQn,pri);
	//ʹ��NVIC��Ӧͨ��
	NVIC_EnableIRQ(USART1_IRQn);	

	//����ʹ��
	USART1->CR1 |= (1<<13);
}
/*******************************************
*������    :USART1_IRQHandler
*��������  :����1���жϷ�����
*��������  :��
*��������ֵ:��
*��������  :
*********************************************/
u8 ch1[50] = {0};
void USART1_IRQHandler(void)
{
	static u8 i = 0;
	//�ж��Ƿ�Ϊ�����жϴ���
	if(USART1->SR & (1<<5))
	{
		//����жϱ�־λ
		//�����¼�
		ch1[i++] = USART1->DR;                 
	}
	
	//�ж��ǿ����жϴ���    �ͱ�ʾ�ַ����������
	if(USART1->SR & (1<<4))
	{
		//��������жϱ�־λ
		USART1->SR;
		USART1->DR;
		//�����¼�
		ch1[i]  = '\0';
		printf("%s",ch1);
		i = 0;		 
	}
}	
/*******************************************
*������    :usart1 send_byte
*��������  :����1����һ���ֽں���
*��������  :u8 data
*��������ֵ:��
*��������  :����ǰҪ���֮ǰ���Ƿ�����󣬵ȴ�
*********************************************/
void usart1_send_byte(u8 data)
{
	//�ȴ�֮ǰ�ķ������
	while(!(USART1->SR & (1<<6)));
	//��Ҫ���͵����ݸ����ݼĴ���
	USART1->DR = data;
}
/*******************************************
*������    :usart1_rec_byte
*��������  :����1����һ���ֽں���
*��������  :��
*��������ֵ:u8
*��������  :Ҫ�ȴ�������ɣ��ڶ�����
*********************************************/
u8 usart1_rec_byte(void)
{
	u8 data;
	//�ȴ��������
	while(!(USART1->SR & (1<<5)));
	//�����ݼĴ����е����ݸ�ֵ������
	data = USART1->DR;
	//�����յ������ݷ���
	return data;
}
/*******************************************
*������    :usart1_send_str
*��������  :����1����һ���ַ�������
*��������  :u8 *str
*��������ֵ:��
*��������  :
*********************************************/
void usart1_send_str(u8 *str)
{
	while(*str != '\0')
	{
		usart1_send_byte(*str);
		str++;
	}
}
/*******************************************
*������    :usart1_rec_str
*��������  :����1��һ���ַ�������
*��������  :u8 *str
*��������ֵ:��
*��������  :
*********************************************/
void usart1_rec_str(u8 *str)    
{
	while(1)
	{
		//����һ���ַ�
		*str = usart1_rec_byte();
		//�ж��յ��ַ��Ƿ�Ϊ#
		if(*str == '#')
		{
			break;
		}
		str++;
	}
	//��#��'\0'�滻
	*str = '\0';
}

#if 1
	#pragma import(__use_no_semihosting)             
	//��׼����Ҫ��֧�ֺ���                 
	struct __FILE 
	{ 
		int handle; 
		/* Whatever you require here. If the only file you are using is */ 
		/* standard output using printf() for debugging, no file handling */ 
		/* is required. */ 
	}; 
	/* FILE is typedef�� d in stdio.h. */ 
	FILE __stdout;       
	//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
	_sys_exit(int x) 
	{ 
		x = x; 
	} 
	//�ض���fputc���� 
	int fputc(int ch, FILE *f)
	{      
		while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
		USART1->DR = (u8) ch;      
		return ch;
	}
	#endif 