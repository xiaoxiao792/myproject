#include "iic.h"
#include "systick.h"

void iic_init(void)
{
	RCC->AHB1ENR    |=1<<1; //GPIOBʱ��ʹ��
	GPIOB->MODER    &=~(0xF<<(8*2));
	GPIOB->MODER    |=0x5<<(8*2); //PB8/9���ģʽ
	GPIOB->OTYPER   |=3<<8;       //PB8/9�����©
	GPIOB->OSPEEDR  &=~(0xF<<(8*2));
	GPIOB->OSPEEDR  |=0x5<<(8*2);  //����ٶ�25MHz
	SCL_H();
	SDA_H();  //���߸ߵ�ƽ������״̬
}

/*
IIC�������ֽ�
������  u8 ack
0��     ������ȡ���ݺ󣬷���Ӧ���ź�
1��     ������ȡ���ݺ󣬷��ͷ�Ӧ���ź�
����ֵ��������ȡ��������
*/
u8 iic_read(u8 ack)
{
	u8 byte=0;
	u8 i=0; 
	SDA_IN();                 //������ȡ���ݣ�SDAΪ���뷽��
	
	for(i=0;i<8;i++)          //ǰ8��ʱ�ӣ���ȡ8������λ
	{
		SCL_L();                
		Delay_us(5);
		SCL_H();	             //������SCLΪ���ڼ��������
		Delay_us(5); 
		if( SDA_Read() )        byte |=0x80>>i;
		else                    byte &=~(0x80>>i);
	}
	
	SCL_L();                 //��9��ʱ�ӣ���������Ӧ���ź�
	if( ack )               SDA_H();   
	else                    SDA_L(); 
	Delay_us(5);
	SCL_H();
	Delay_us(5);
	return byte;
}


/*
IIC����д�ֽ�
������  u8 byte���������͸��ӻ�������
����ֵ���ӻ��յ����ݺ󷵻ص�Ӧ���ź�
0��ACK    �ӻ�����Ӧ��
1��NoACK  �ӻ����ͷ�Ӧ��
*/
u8 iic_write(u8 byte)
{
	u8 ack=0;
	u8 i=0;
	for(i=0;i<8;i++)          //ǰ8��ʱ�ӣ�����8������λ
	{
		SCL_L();                //������SCLΪ���ڼ�׼������
		if( byte&(0x80>>i) )    SDA_H();  
		else                    SDA_L(); 
		Delay_us(5);
		SCL_H();
		Delay_us(5);
	}
	
	SCL_L();                //��9��ʱ�ӣ���ȡӦ��λ��SDAӦ��Ϊ���뷽��
	  SDA_IN();               //�����л�
	Delay_us(5);            //SCLwΪ�ͣ�SDAΪ���뷽�򣬴ӻ�׼�����ݻ���Ӧ��
	SCL_H();
	Delay_us(5);
	if( SDA_Read() )       ack=NoACK;    //������SCLΪ���ڼ��������
	else                   ack=ACK;
	return ack;
}

/*
IIC�����ź�
*/
void iic_stop(void)
{
	SCL_L();     //������SCL���ٲ���SDA����ֹ�쳣��ʼ�����ź�	
	Delay_us(5);
	SDA_L();     //�п��ܲ����½��أ���ʼ�ź�
	SCL_H();    
	Delay_us(5); //�����źŽ���ʱ�䣬��С5us
	
	SDA_H();     //SCLΪ���ڼ䣬SDA�������أ� �����ź�
	Delay_us(5); //�µ���ʼ�źſ�ʼǰ���߿���ʱ�䣬��С5us
}
/*
IIC��ʼ�ź�
*/
void iic_start(void)
{
	SCL_L();     //������SCL���ٲ���SDA����ֹ�쳣��ʼ�����ź�	
	Delay_us(5);
	SDA_H();     //�п��ܲ��������أ������ź�
	SCL_H();    
	Delay_us(5); //��ʼ�źŽ���ʱ�䣬��С5us
	
	SDA_L();     //SCLΪ���ڼ䣬SDA�½��أ� ��ʼ�ź�
	Delay_us(5); //��ʼ�źű���ʱ�䣬��С5us
	SCL_L();     //����æ
}











