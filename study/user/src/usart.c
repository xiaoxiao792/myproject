#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"
#include "usart.h" 
/*******************************************
*函数名    :usart1_init
*函数功能  :串口1所初始化配置
*函数参数  :u32 bps
*函数返回值:无
*函数描述  :PA9--------USART1_TX
		        PA10--------USART1_RX
*********************************************/
void usart1_init(u32 bps)
{
	u32 pri;
	/*IO口控制器配置*/
	//端口时钟使能
	RCC->APB2ENR |= 1 << 2;//A
 
	//端口模式配置
	GPIOA->CRH &= ~(0XF << (4 * (9 - 8)));
	GPIOA->CRH |=  (0XB << (4 * (9 - 8)));		//复用推挽50M
	
	GPIOA->CRH &= ~(0XF << (4 * (10 - 8)));
	GPIOA->CRH |=  (0X4 << (4 * (10 - 8)));		//浮空输入
	
	/*串口1控制器配置*/
	//串口1模块时钟使能
	RCC->APB2ENR |= 1 << 14;
	//CR1
	USART1->CR1 &= ~(1<<12);        //8位字长
	USART1->CR1 |= (1<<3);          //发送使能
	USART1->CR1 |= (1<<2);          //接收使能
	USART1->CR1 |= (1<<5);          //接收中断使能
	USART1->CR1 |= (1<<4);          //空闲中断使能	
	//CR2
	USART1->CR2 &= ~(3<<12);        //1个停止位
	//BRR
	USART1->BRR = 72000000 / bps;

  /*NVIC控制器配置*/
	//优先级分组  抢占2位响应 两位  写入就是5
	//在主函数中
	//计算优先级编码值
	 pri = NVIC_EncodePriority(5,1,2);
	//设置具体中断源优先级
	NVIC_SetPriority(USART1_IRQn,pri);
	//使能NVIC响应通道
	NVIC_EnableIRQ(USART1_IRQn);	

	//串口使能
	USART1->CR1 |= (1<<13);
}
/*******************************************
*函数名    :USART1_IRQHandler
*函数功能  :串口1的中断服务函数
*函数参数  :无
*函数返回值:无
*函数描述  :
*********************************************/
u8 ch1[50] = {0};
void USART1_IRQHandler(void)
{
	static u8 i = 0;
	//判断是否为接收中断触发
	if(USART1->SR & (1<<5))
	{
		//清除中断标志位
		//紧急事件
		ch1[i++] = USART1->DR;                 
	}
	
	//判断是空闲中断触发    就表示字符串接收完成
	if(USART1->SR & (1<<4))
	{
		//清除空闲中断标志位
		USART1->SR;
		USART1->DR;
		//紧急事件
		ch1[i]  = '\0';
		printf("%s",ch1);
		i = 0;		 
	}
}	
/*******************************************
*函数名    :usart1 send_byte
*函数功能  :串口1发送一个字节函数
*函数参数  :u8 data
*函数返回值:无
*函数描述  :发送前要检测之前的是否发送完后，等待
*********************************************/
void usart1_send_byte(u8 data)
{
	//等待之前的发送完成
	while(!(USART1->SR & (1<<6)));
	//将要发送的数据给数据寄存器
	USART1->DR = data;
}
/*******************************************
*函数名    :usart1_rec_byte
*函数功能  :串口1接收一个字节函数
*函数参数  :无
*函数返回值:u8
*函数描述  :要等待接收完成，在读数据
*********************************************/
u8 usart1_rec_byte(void)
{
	u8 data;
	//等待接收完成
	while(!(USART1->SR & (1<<5)));
	//将数据寄存器中的数据赋值给变量
	data = USART1->DR;
	//将接收到的数据返回
	return data;
}
/*******************************************
*函数名    :usart1_send_str
*函数功能  :串口1发送一个字符串函数
*函数参数  :u8 *str
*函数返回值:无
*函数描述  :
*********************************************/
void usart1_send_str(u8 *str)
{
	while(*str != '\0')
	{
		usart1_send_byte(*str);
		str++;
	}
}
/*******************************************
*函数名    :usart1_rec_str
*函数功能  :串口1收一个字符串函数
*函数参数  :u8 *str
*函数返回值:无
*函数描述  :
*********************************************/
void usart1_rec_str(u8 *str)    
{
	while(1)
	{
		//接收一个字符
		*str = usart1_rec_byte();
		//判断收到字符是否为#
		if(*str == '#')
		{
			break;
		}
		str++;
	}
	//将#用'\0'替换
	*str = '\0';
}

#if 1
	#pragma import(__use_no_semihosting)             
	//标准库需要的支持函数                 
	struct __FILE 
	{ 
		int handle; 
		/* Whatever you require here. If the only file you are using is */ 
		/* standard output using printf() for debugging, no file handling */ 
		/* is required. */ 
	}; 
	/* FILE is typedef’ d in stdio.h. */ 
	FILE __stdout;       
	//定义_sys_exit()以避免使用半主机模式    
	_sys_exit(int x) 
	{ 
		x = x; 
	} 
	//重定义fputc函数 
	int fputc(int ch, FILE *f)
	{      
		while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
		USART1->DR = (u8) ch;      
		return ch;
	}
	#endif 