#include "spi.h"
/*
CS     PB14   �����������SPI�������޹� 
SCK    PB3    ����+����+��������
MISO   PB4    ����+��������
MOSI   PB5    ����+����+��������
ģ��ʱ��
ģ�����������ʱ���źţ�ģ�������׼�������ģ��������������ݲ���
*/

void spi_init(void)
{
	RCC->AHB1ENR |=1<<1;
	/* CS PB14 */
	GPIOB->MODER   &=~(3<<(14*2));
	GPIOB->MODER   |=1<<(14*2);
	GPIOB->OTYPER  &=~(1<<14);
	Flash_CS_H();
	
	GPIOB->MODER   &=~(0x3F<<(3*2)); 
	GPIOB->MODER   |=0x2A<<(3*2);        //10 1010 PB3/4/5����
	GPIOB->OSPEEDR &=~(0x33<<(3*2));     //11 0011  
	GPIOB->OSPEEDR |=0x22<<(3*2);        //10 0010  ,PB3/4/5���� 50MHz
	
	GPIOB->AFR[0]  &=~(0xFFF<<(3*4)); 
	GPIOB->AFR[0]  |=0x555<<(3*4);       //PB3/4/5���õ�AF5
	/* SPI���� */
	RCC->APB2ENR   |=1<<12;
	SPI1->CR1      &=~(1<<15);           //ѡ��4��SPI
	SPI1->CR1      &=~(1<<11);           //����֡��ʽѡ��8λ
	SPI1->CR1      &=~(1<<10);           //ȫ˫��
	SPI1->CR1      |=3<<8;               //�����������������Ϊ����
	SPI1->CR1      &=~(1<<7);            //MSB��ǰ
	SPI1->CR1      &=~(7<<3);            //2��Ƶ��42MHz
	SPI1->CR1      |=1<<2;               //����Ϊ��ģʽ
	SPI1->CR1      &=~(3<<0);            //ʱ��0
	
	SPI1->CR1      |=1<<6;               //����SPI	
}

u8 spi_send_read(u8 byte)
{	
	while( 0 == (SPI1->SR &(1<<1)) ) ;
	SPI1->DR =byte;
	while( 0 == (SPI1->SR &(1<<0)) ) ;
	return SPI1->DR;
}
