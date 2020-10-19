#include "key.h"

void KEY_Init(void)
{
	RCC->AHB1ENR |=1<<0;  //ʹ��GPIOA
	RCC->AHB1ENR |=1<<4;  //ʹ��GPIOE
	
	GPIOA->MODER  &=~(3<<(0*2)); //PA0ģʽΪ����ģʽ
	GPIOA->PUPDR  &=~(3<<(0*2)); //PA0��������	
	
	GPIOE->MODER  &=~(3<<(2*2));  //PE2ģʽΪ����ģʽ
	GPIOE->PUPDR   &=~(3<<(2*2)); //PE2��������	
	
	GPIOE->MODER  &=~(3<<(3*2));  //PE3ģʽΪ����ģʽ
	GPIOE->PUPDR   &=~(3<<(3*2)); //PE3��������	
	
	GPIOE->MODER  &=~(3<<(4*2));  //PE4ģʽΪ����ģʽ
	GPIOE->PUPDR   &=~(3<<(4*2)); //PE4��������	
}

u32 count=0;
u32 temp=0;
u8 Key_Scan(void)
{
	static u8 key=0;
	static u8 sta=1;  //��������
	if( ( KEY1 ||(!KEY2) ||(!KEY3) ||(!KEY4) ) &&sta)     //����������� �����Ұ���û�б�����
	{
		//����������ǰһ�ΰ������º�û���ɿ����������������ٲ�����Ч����ֵ
		//��� ������1���»��� ����2���� ���� ����3���� ���� ����4���£� ���� ����û�б���������ɨ�谴��
		Delay(50000);             //��ʱ�����������˳�����
		if(KEY1)         key=1;   //�ٴ��жϰ�������
		else if(!KEY2)   key=2;  
		else if(!KEY3)   key=3;  
		else if(!KEY4)   key=4;  
		
		if(key)          sta=0;
	}
	//��ô֪��������һֱ���£��ж�staΪ0����
	if( (sta==0) && temp<100)   //�������
	{
		count++;
		if(count==35000)
		{
			count=0;
			temp++;
			if(temp==100)    return  key+4;
		}
	}
	
	if( ((KEY1==0) &&KEY2 &&KEY3 &&KEY4 )  && (sta==0))  //�ɿ����
	{	
		Delay(50000);
		if( (KEY1==0) &&KEY2 &&KEY3 &&KEY4 )
		{
				sta=1;   //�����ɿ��ˣ���������
				if(temp==100)  key=0;
				temp =0;
				return key;
		}
	}
	
	return 0;       //���ذ���ֵ
}

void Delay(u32 time)
{
	while(time--);
}
