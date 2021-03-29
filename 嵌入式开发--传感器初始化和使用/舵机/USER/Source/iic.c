#include "iic.h"
#include "systick.h"

void iic_init(void)
{
	RCC->AHB1ENR    |=1<<1; //GPIOB时钟使能
	GPIOB->MODER    &=~(0xF<<(8*2));
	GPIOB->MODER    |=0x5<<(8*2); //PB8/9输出模式
	GPIOB->OTYPER   |=3<<8;       //PB8/9输出开漏
	GPIOB->OSPEEDR  &=~(0xF<<(8*2));
	GPIOB->OSPEEDR  |=0x5<<(8*2);  //输出速度25MHz
	SCL_H();
	SDA_H();  //总线高电平，空闲状态
}

/*
IIC主机读字节
参数：  u8 ack
0：     主机读取数据后，发送应答信号
1：     主机读取数据后，发送非应答信号
返回值：主机读取到的数据
*/
u8 iic_read(u8 ack)
{
	u8 byte=0;
	u8 i=0; 
	SDA_IN();                 //主机读取数据，SDA为输入方向
	
	for(i=0;i<8;i++)          //前8个时钟，读取8个数据位
	{
		SCL_L();                
		Delay_us(5);
		SCL_H();	             //主机在SCL为高期间采样数据
		Delay_us(5); 
		if( SDA_Read() )        byte |=0x80>>i;
		else                    byte &=~(0x80>>i);
	}
	
	SCL_L();                 //第9个时钟，主机发送应答信号
	if( ack )               SDA_H();   
	else                    SDA_L(); 
	Delay_us(5);
	SCL_H();
	Delay_us(5);
	return byte;
}


/*
IIC主机写字节
参数：  u8 byte是主机发送给从机的数据
返回值：从机收到数据后返回的应答信号
0：ACK    从机发送应答
1：NoACK  从机发送非应答
*/
u8 iic_write(u8 byte)
{
	u8 ack=0;
	u8 i=0;
	for(i=0;i<8;i++)          //前8个时钟，发送8个数据位
	{
		SCL_L();                //主机在SCL为低期间准备数据
		if( byte&(0x80>>i) )    SDA_H();  
		else                    SDA_L(); 
		Delay_us(5);
		SCL_H();
		Delay_us(5);
	}
	
	SCL_L();                //第9个时钟，读取应答位：SDA应该为输入方向
	  SDA_IN();               //方向切换
	Delay_us(5);            //SCLw为低，SDA为输入方向，从机准备数据或者应答
	SCL_H();
	Delay_us(5);
	if( SDA_Read() )       ack=NoACK;    //主机在SCL为高期间采样数据
	else                   ack=ACK;
	return ack;
}

/*
IIC结束信号
*/
void iic_stop(void)
{
	SCL_L();     //先拉低SCL，再操作SDA，防止异常起始结束信号	
	Delay_us(5);
	SDA_L();     //有可能产生下降沿：起始信号
	SCL_H();    
	Delay_us(5); //结束信号建立时间，最小5us
	
	SDA_H();     //SCL为高期间，SDA下上升沿： 结束信号
	Delay_us(5); //新的起始信号开始前总线空闲时间，最小5us
}
/*
IIC起始信号
*/
void iic_start(void)
{
	SCL_L();     //先拉低SCL，再操作SDA，防止异常起始结束信号	
	Delay_us(5);
	SDA_H();     //有可能产生上升沿，结束信号
	SCL_H();    
	Delay_us(5); //起始信号建立时间，最小5us
	
	SDA_L();     //SCL为高期间，SDA下降沿： 起始信号
	Delay_us(5); //起始信号保持时间，最小5us
	SCL_L();     //总线忙
}











