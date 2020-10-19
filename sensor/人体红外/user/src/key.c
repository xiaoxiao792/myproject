#include "key.h"

/*
�����Ĺ��ܣ�KEY��ʼ��
�βΣ�void
����ֵ��void
��ע��PA0  - û�а��µ͵�ƽ������Ϊ�ߵ�ƽ
*/
void KEY_Init(void)
{
	RCC->AHB1ENR |= 1 << 0;  //ʹ��GPIOAʱ��
	RCC->AHB1ENR |= 1 << 4;  //ʹ��GPIOEʱ��
	
	/* PA0 ���� */
	GPIOA->MODER &= ~(3 << (2 * 0)); //����ģʽ
	GPIOA->PUPDR &= ~(3 << (2 * 0));
	GPIOA->PUPDR |= 2 << (2 * 0);   //����
	
	/* PE2 ���� */
	GPIOE->MODER &= ~(3 << (2 * 2)); //����ģʽ
	GPIOE->PUPDR &= ~(3 << (2 * 2));
	GPIOE->PUPDR |= 1 << (2 * 2);   //����
	
	/* PE3 ���� */
	GPIOE->MODER &= ~(3 << (2 * 3)); //����ģʽ
	GPIOE->PUPDR &= ~(3 << (2 * 3));
	GPIOE->PUPDR |= 1 << (2 * 3);   //����
	
	/* PE4 ���� */
	GPIOE->MODER &= ~(3 << (2 * 4)); //����ģʽ
	GPIOE->PUPDR &= ~(3 << (2 * 4));
	GPIOE->PUPDR |= 1 << (2 * 4);   //����
	
}

/*
�����Ĺ��ܣ�KEYɨ��
�βΣ�void
����ֵ������1 -- ����1���� 
��ע��PA0  - û�а��µ͵�ƽ������Ϊ�ߵ�ƽ
			PE2  - û�а��¸ߵ�ƽ������Ϊ�͵�ƽ
			PE3  - û�а��¸ߵ�ƽ������Ϊ�͵�ƽ
			PE4  - û�а��¸ߵ�ƽ������Ϊ�͵�ƽ
*/
u8 KEY_Scan(void)
{
	static u8 flag = 1;  //������״̬ 0��û�а���  1������
	u8 key = 0;
	
	if((KEY1 || KEY2 || KEY3 || KEY4) && flag == 1)
	{
		 delay(200000);   //10ms
		 if(KEY1)
		 {
			 flag = 0;
			 key = 1;
		 }
		 else if(KEY2)
		 {
			 flag = 0;
			 key = 2;
		 }
		 else if(KEY3)
		 {
			 flag = 0;
			 key = 3;
		 }
		 else if(KEY4)
		 {
			 flag = 0;
			 key = 4;
		 }
	} 
	
	else if(!KEY1 && !KEY2 && !KEY3 && !KEY4)  //û�а���
	{ 
		 flag = 1;   //Ϊ��һ�ΰ���������׼��
	}
	return key;
}


void delay(u32 t)
{
	 while(t)
	 {
		 t--;
	 }
}



