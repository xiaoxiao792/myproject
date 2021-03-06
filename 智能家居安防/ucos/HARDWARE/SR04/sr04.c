#include "sys.h"
#include "delay.h"


static GPIO_InitTypeDef		GPIO_InitStructure;

void sr04_init(void)
{
	//ʹ�ܶ˿�B�Ͷ˿�E��Ӳ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);	
	
	//����PB6Ϊ���ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;			//��6������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;		//���ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_High_Speed;		//���Ÿ��ٹ������յ�ָ������������ȱ�㣺���ĸ�
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;		//�����������������
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;		//����Ҫ����������
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
	
	
	//����PE6Ϊ����ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;			//��6������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;		//����ģʽ
	GPIO_Init(GPIOE,&GPIO_InitStructure);	


	//PB6�����ӵ������ź����ţ���ʼ��ƽΪ�͵�ƽ
	PCout(11)=0;
}



int32_t sr04_get_distance(void)
{
	uint32_t t=0;
	
	uint32_t d;

	PCout(11)=1;
	
	delay_us(20);
	
	PCout(11)=0;
	
	//�ȴ������ź���������ߵ�ƽ
	while(PEin(5)==0)
	{
		t++;
		delay_us(1);
		
		if(t >= 1000000)
			return -1;
	}
	
	
	//�����ߵ�ƽ�ĳ���ʱ��
	t=0;
	while(PEin(5))
	{
		t++;
		delay_us(9);	//����9usʱ��ľ������3mm
		
		if(t >= 1000000)
			return -2;		
	}


	d = 3*t/2;
	
	return d;
}
