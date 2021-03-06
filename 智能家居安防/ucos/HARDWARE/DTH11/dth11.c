#include "stm32f4xx.h"
#include "sys.h"
#include <stdio.h>
#include "delay.h"

static GPIO_InitTypeDef		GPIO_InitStructure;
void  humiture_init(void)
{

	//ʹ�ܶ˿�G��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	
	
	
	//����PG9Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;			//��9������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;		//���ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//���Ÿ��ٹ������յ�ָ������������ȱ�㣺���ĸ�
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//�����������������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//����Ҫ����������
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
	
	//PG6�����ӵ������ź����ţ���ʼ��ƽΪ�͵�ƽ
	PGout(9)=1;
}
void humiture_mode(GPIOMode_TypeDef Mode)
{
		//����PG6Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;			//��9������
	GPIO_InitStructure.GPIO_Mode=Mode;		//���ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//���Ÿ��ٹ������յ�ָ������������ȱ�㣺���ĸ�
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//�����������������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//����Ҫ����������
	GPIO_Init(GPIOG,&GPIO_InitStructure);
}
int32_t humiture_get_distance(uint8_t *data)
{
	uint8_t d=0;
	uint32_t t=0;
	int i,j;
	humiture_mode(GPIO_Mode_OUT);
	PGout(9)=0;
	
	delay_ms(20);
	
	PGout(9)=1;	
	
	delay_us(40);
	
	humiture_mode(GPIO_Mode_IN);
	while(PGin(9))
	{
		t++;
		delay_us(1);
		
		if(t >= 4000)
			return -1;
	}	
	t=0;
	while(PGin(9)==0)
	{
		t++;
		delay_us(1);	
	
		if(t >= 4000)
			return -2;		
	}
	t=0;
	while(PGin(9))
	{
		t++;
		delay_us(1);	
	
		if(t >= 4000)
			return -3;		
	}
	//�����ߵ�ƽ�ĳ���ʱ��
	for(j=0;j<5;j++)
	{
		d=0;
		for(i=7;i>=0;i--)
		{
			t=0;
			//�ȴ������ź���������ߵ�ƽ
			while(PGin(9)==0)
			{
				t++;
				delay_us(1);
				
				if(t >= 4000)
					return -4;
			}	

			delay_us(40);
			if(PGin(9))
			{
				d|=1<<i;
				
				//�ȴ�����1�ĸߵ�ƽʱ��������
				t=0;
				while(PGin(9))
				{
				
					t++;
					
					delay_us(1);
					
					if(t >= 100)
						return -5;
				}			
			
			}
			
		}
		data[j]=d;
	}
	
	//ͨ�ŵĽ���
	delay_us(200);
	d=0;
	for(i=0;i<4;i++)
	{
		d+=data[i];
	}
	if((d&0xFF)==(data[4]&0xFF))//�����
	{
		
		return 0;
	}
	return -6;
	
}
