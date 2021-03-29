#include "spi.h"
/*
CS     PB14   推挽输出，与SPI控制器无关 
SCK    PB3    复用+推挽+无上下拉
MISO   PB4    复用+无上下拉
MOSI   PB5    复用+推挽+无上下拉
模拟时序：
模拟控制器发出时钟信号，模拟控制器准备输出，模拟控制器进行数据采样
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
	GPIOB->MODER   |=0x2A<<(3*2);        //10 1010 PB3/4/5复用
	GPIOB->OSPEEDR &=~(0x33<<(3*2));     //11 0011  
	GPIOB->OSPEEDR |=0x22<<(3*2);        //10 0010  ,PB3/4/5复用 50MHz
	
	GPIOB->AFR[0]  &=~(0xFFF<<(3*4)); 
	GPIOB->AFR[0]  |=0x555<<(3*4);       //PB3/4/5复用到AF5
	/* SPI配置 */
	RCC->APB2ENR   |=1<<12;
	SPI1->CR1      &=~(1<<15);           //选择4线SPI
	SPI1->CR1      &=~(1<<11);           //数据帧格式选择8位
	SPI1->CR1      &=~(1<<10);           //全双工
	SPI1->CR1      |=3<<8;               //软件从器件管理，配置为主机
	SPI1->CR1      &=~(1<<7);            //MSB在前
	SPI1->CR1      &=~(7<<3);            //2分频，42MHz
	SPI1->CR1      |=1<<2;               //配置为主模式
	SPI1->CR1      &=~(3<<0);            //时序0
	
	SPI1->CR1      |=1<<6;               //开启SPI	
}

u8 spi_send_read(u8 byte)
{	
	while( 0 == (SPI1->SR &(1<<1)) ) ;
	SPI1->DR =byte;
	while( 0 == (SPI1->SR &(1<<0)) ) ;
	return SPI1->DR;
}
