#include "adc.h"

void adc1_init(void)
{
	//1）GPIO配置
	RCC->AHB1ENR  |=1<<2;
	GPIOC->MODER  |=3<<(2*2); //PC2模拟模式
	//2）ADC时钟使能
	RCC->APB2ENR  |=1<<8; //ADC1使能
	//3）CR1寄存器配置
	ADC1->CR1     &=~(3<<24); //12位分辨率
	ADC1->CR1     &=~(1<<8);  //禁止扫描
	
	//4）CR2寄存器配置
	ADC1->CR2     &=~(1<<11); //数据右对齐
	ADC1->CR2     |=1<<10;    //每个规则转换结束EOC都置1
	ADC1->CR2     &=~(1<<1);  //单次转换
	//5）采样时间配置
	ADC1->SMPR1    |=8<<6;  //通道12采样周期480个时钟
	//6）转换序列配置
	ADC1->SQR1     =0;         //序列长度为1
	ADC1->SQR3     =0;
	ADC1->SQR3    |=12<<0;      //规则序列的第一个通道为通道12
	
	//7）ADON使能，开启AD转换。
	ADC1->CR2     |=1<<0;     //开启模数转换器
	
}

u16 get_adc_val(void)
{
	u16 ad_val=0;
	u8  i=0;
	for(i=0;i<10;i++)
	{
		ADC1->CR2     |=1<<30;     //开启AD转换
		while( 0==( ADC1->SR & (1<<1) ) )
		{
			//等待AD转换结束
		}
		ADC1->SR &=~(1<<1);
		ad_val += ADC1->DR;
	}
	return (ad_val/10);
}



