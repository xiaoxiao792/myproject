#include "ds18b20.h"
#include "systick.h"
#include "stm32f4xx.h"
#include "key.h"
//b20初始化函数
void ds18b20_reset()
{
  io_out();     //输出设置初始化
	DQ_out=0;     //主机输出低电平
	Delay_us(750);//延时至少480us，产生复位脉冲
	DQ_out=1;     //主机释放总线，电平被拉高
	Delay_us(20); //延时15-60us，主机进入接收模式
}
//检测18b20是否响应（是否存在）
//返回0，存在，1：不存在
u8 ds18b20_cheak()
{
	u8 retry=0;
	io_in();    //初始化引脚作为输入
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
	};                  //等待ds18b20回应结束
	if(retry>=240) return 1;
	return 0;           //检测到ds18b20存在
}
//从ds18b20读取一个位:0或1
//这是一种很典型的读时序过程
u8 readbit()
{
  u8 data;
	io_out();          //初始化引脚作为输出
	DQ_out=0;          //主机输出低电平，发出读时序
	Delay_us(2);       //延时2毫秒
	DQ_out=1;          //这一步可以去掉吗？
	io_in();           //引脚作为输入初始化，主机进入输入模式
	Delay_us(12);      //延时12us，
	if(DQ_in)  data=1;
	else       data=0;
	Delay_us(50);      //延时50us
	return data;       //读出的1位数据返回给调用者
}
//读取一个字节的数据
//返回值为读出的数据
u8 readbyte()
{
  u8 i,j,data;
	data=0;
	for(i=1;i<=8;i++)
	{
	  j=readbit();
		data=(j<<7)|(data>>1);
		/*j<<=7;           //j的值左移7位
		data>>=1;        //data的值右移1位
		data|=j;*/
	}
	return data;       //返回读出的数据给调用者
}
//向ds18b20写入一个字节数据
//比较典型的写时序过程
void  writebyte(u8 data)
{
 u8 j,testb;
	io_out();          //初始化引脚作为输出
	for(j=0;j<8;j++)
	{
	  testb=data&0x01;
		data=data>>1;
		if(testb)        //写1
		{
		  DQ_out=0;      //主机先输出低电平
		   Delay_us(2);  //延续2us,拉低至少1us
			DQ_out=1;      //主机输出高电平
			 Delay_us(60); //延时60us，拉高至少 (60-x) us,x是拉低电平的时间
		}
		else             //写0
		{
		  DQ_out=0;      //主机先输出低电平，延时60us
			 Delay_us(60); //延时60us
		  DQ_out=1;      //主机输出高电平2us
			 Delay_us(2);  //延时2us
		}
			 DQ_out=1;      //主机输出高电平2us
			 Delay_us(2);  //延时2us
		//两个写周期之间，至少保持1us的恢复时间,即此时总线为高,
		//也可以不写，因为每个写周期后都保持高电平2us以上
	}
}
//启动ds18b20,开始温度转换
void ds18b20_convert()
{
  ds18b20_reset();
	ds18b20_cheak();
	writebyte(0xcc);   //跳过rom的命令
	writebyte(0x44);   //开始温度转换
}
//初始化ds18b20io口，检测ds18b20是否存在
u8 ds18b20_init()
{
  RCC->AHB1ENR |=1<<1;  //开启GPIOB时钟
	
	GPIOB->MODER &=~(3<<(2*12)); 
	GPIOB->MODER |=1<<(2*12);    //通用输出
	GPIOB->OTYPER &=~(1<<12);    //推挽输出
	
	GPIOB->ODR |=1<<12;          //总线空闲状态为高电平
	ds18b20_reset();
	return ds18b20_cheak();     //返回ds18b20是否存在
}
//读取温度值
float get_temperature(void)
{
	u8  temperature,tl,th;
	u16 tem;
	float temp=0;
	ds18b20_convert();         //开始转换
	ds18b20_reset();
	ds18b20_cheak();
	writebyte(0xcc);   //跳过rom的命令
	writebyte(0xbe);   //开始温度转换
	tl=readbyte();     //lsb
	th=readbyte();
	if(th>7)
	{
	  th=~th;
		tl=~tl;
		temperature=0;  //温度为负数
	}
	else temperature=1; //温度为正数
	tem=th;           //获取高八位
	tem<<=8;
	tem+=tl;          //获取低八位
	temp=(float)tem*0.0625;  //转换公式
	if(temperature) return temp;       //返回温度值	
	else            return -temp; 
}
//引脚输入初始化设置
void io_in()
{
  GPIOF->MODER &=~(3<<(2*5));  //输入
	GPIOF->PUPDR |=1<<5;         //上拉输入
}
//引脚输出初始化设置
void io_out()
{
  GPIOF->MODER &=~(3<<(2*5));
	GPIOF->MODER |=1<<(2*5);    //通用输出
	GPIOF->OTYPER &=~(1<<5);    //推挽输出
}

