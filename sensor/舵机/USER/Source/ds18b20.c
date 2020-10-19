#include "ds18b20.h"
#include "systick.h"
#include "stm32f4xx.h"
#include "key.h"
//b20��ʼ������
void ds18b20_reset()
{
  io_out();     //������ó�ʼ��
	DQ_out=0;     //��������͵�ƽ
	Delay_us(750);//��ʱ����480us��������λ����
	DQ_out=1;     //�����ͷ����ߣ���ƽ������
	Delay_us(20); //��ʱ15-60us�������������ģʽ
}
//���18b20�Ƿ���Ӧ���Ƿ���ڣ�
//����0�����ڣ�1��������
u8 ds18b20_cheak()
{
	u8 retry=0;
	io_in();    //��ʼ��������Ϊ����
  while( DQ_in&& (retry<200) )
	{
	  retry++; 
		Delay_us(1);
	};
	if(retry>=200) return 1;
	else  retry=0;
	while(!DQ_in&& (retry<240) )
	{
	  retry++;
		Delay_us(1);
	};                  //�ȴ�ds18b20��Ӧ����
	if(retry>=240) return 1;
	return 0;           //��⵽ds18b20����
}
//��ds18b20��ȡһ��λ:0��1
//����һ�ֺܵ��͵Ķ�ʱ�����
u8 readbit()
{
  u8 data;
	io_out();          //��ʼ��������Ϊ���
	DQ_out=0;          //��������͵�ƽ��������ʱ��
	Delay_us(2);       //��ʱ2����
	DQ_out=1;          //��һ������ȥ����
	io_in();           //������Ϊ�����ʼ����������������ģʽ
	Delay_us(12);      //��ʱ12us��
	if(DQ_in)  data=1;
	else       data=0;
	Delay_us(50);      //��ʱ50us
	return data;       //������1λ���ݷ��ظ�������
}
//��ȡһ���ֽڵ�����
//����ֵΪ����������
u8 readbyte()
{
  u8 i,j,data;
	data=0;
	for(i=1;i<=8;i++)
	{
	  j=readbit();
		data=(j<<7)|(data>>1);
		/*j<<=7;           //j��ֵ����7λ
		data>>=1;        //data��ֵ����1λ
		data|=j;*/
	}
	return data;       //���ض��������ݸ�������
}
//��ds18b20д��һ���ֽ�����
//�Ƚϵ��͵�дʱ�����
void  writebyte(u8 data)
{
 u8 j,testb;
	io_out();          //��ʼ��������Ϊ���
	for(j=0;j<8;j++)
	{
	  testb=data&0x01;
		data=data>>1;
		if(testb)        //д1
		{
		  DQ_out=0;      //����������͵�ƽ
		   Delay_us(2);  //����2us,��������1us
			DQ_out=1;      //��������ߵ�ƽ
			 Delay_us(60); //��ʱ60us���������� (60-x) us,x�����͵�ƽ��ʱ��
		}
		else             //д0
		{
		  DQ_out=0;      //����������͵�ƽ����ʱ60us
			 Delay_us(60); //��ʱ60us
		  DQ_out=1;      //��������ߵ�ƽ2us
			 Delay_us(2);  //��ʱ2us
		}
			 DQ_out=1;      //��������ߵ�ƽ2us
			 Delay_us(2);  //��ʱ2us
		//����д����֮�䣬���ٱ���1us�Ļָ�ʱ��,����ʱ����Ϊ��,
		//Ҳ���Բ�д����Ϊÿ��д���ں󶼱��ָߵ�ƽ2us����
	}
}
//����ds18b20,��ʼ�¶�ת��
void ds18b20_convert()
{
  ds18b20_reset();
	ds18b20_cheak();
	writebyte(0xcc);   //����rom������
	writebyte(0x44);   //��ʼ�¶�ת��
}
//��ʼ��ds18b20io�ڣ����ds18b20�Ƿ����
u8 ds18b20_init()
{
  RCC->AHB1ENR |=1<<1;  //����GPIOBʱ��
	
	GPIOB->MODER &=~(3<<(2*12)); 
	GPIOB->MODER |=1<<(2*12);    //ͨ�����
	GPIOB->OTYPER &=~(1<<12);    //�������
	
	GPIOB->ODR |=1<<12;          //���߿���״̬Ϊ�ߵ�ƽ
	ds18b20_reset();
	return ds18b20_cheak();     //����ds18b20�Ƿ����
}
//��ȡ�¶�ֵ
float get_temperature(void)
{
	u8  temperature,tl,th;
	u16 tem;
	float temp=0;
	ds18b20_convert();         //��ʼת��
	ds18b20_reset();
	ds18b20_cheak();
	writebyte(0xcc);   //����rom������
	writebyte(0xbe);   //��ʼ�¶�ת��
	tl=readbyte();     //lsb
	th=readbyte();
	if(th>7)
	{
	  th=~th;
		tl=~tl;
		temperature=0;  //�¶�Ϊ����
	}
	else temperature=1; //�¶�Ϊ����
	tem=th;           //��ȡ�߰�λ
	tem<<=8;
	tem+=tl;          //��ȡ�Ͱ�λ
	temp=(float)tem*0.0625;  //ת����ʽ
	if(temperature) return temp;       //�����¶�ֵ	
	else            return -temp; 
}
//���������ʼ������
void io_in()
{
  GPIOF->MODER &=~(3<<(2*5));  //����
	GPIOF->PUPDR |=1<<5;         //��������
}
//���������ʼ������
void io_out()
{
  GPIOF->MODER &=~(3<<(2*5));
	GPIOF->MODER |=1<<(2*5);    //ͨ�����
	GPIOF->OTYPER &=~(1<<5);    //�������
}

