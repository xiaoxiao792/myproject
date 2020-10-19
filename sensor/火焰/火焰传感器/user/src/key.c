#include "stm32f4xx.h"
#include "led.h"
#include "key.h"
void key_init()
{
	/* ����ʱ������ */
	RCC->AHB1ENR |=((1<<0)|(1<<4)); //��GPIOA GPIOE������ʱ��
	
	/* PA0�ܽ�ģʽ���� */
	/* �˿�ģʽ���� */
	GPIOA->MODER &=~(0X3<<0);  //PA0����Ϊ����ģʽ
	/* �������Ĵ������� */
	GPIOA->PUPDR &=~(0X3<<0);  //PA0����Ϊ��������-����
	
	/* PE2��PE3 ��PE4�ܽ�ģʽ���� */
	/* �˿�ģʽ���� */
	GPIOE->MODER &=~(0X3F<<4); //PE2 PE3 PE4 ����Ϊ����ģʽ
	/* �������Ĵ������� */
	GPIOE->PUPDR &=~(0X3F<<4);  //PE2 PE3 PE4 ����Ϊ��������-����
}

int key_scan()
{
	static int key_sta=1;
	if(key_sta && (KEY0==0 || KEY1==0 || KEY2==0 ||WK_UP==1))
	{
				
		key_sta=0;
			delay(200);
		if(KEY0==0)  return 1;
		if(KEY1==0)  return 2;
		if(KEY2==0)  return 3;
		if(WK_UP==1) return 4;
	}
	else if(KEY0!=0 && KEY1!=0 && KEY2!=0 &&WK_UP==0)
	{
		key_sta=1;
	}
	return 0;
}










