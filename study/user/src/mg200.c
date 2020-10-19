#include "mg200.h"
#include "string.h"
#include "usart.h"
#include "stdio.h"

u8 Send_Buff[7];   //发送数据缓冲区
u8 Recv_Buff[8];   //接收数据缓冲区
u8 RecvCount = 0;   //数据接收下标
u8 RecvFlag = 0;    //接收完成标志位
/***************************************************************
函数功能：指纹模块初始化函数
函数参数：
	Bound：波特率
硬件接口：
		USART2_TX-----PA2
		USART2_RX-----PA3
		FING_PWR ----- PB9 ------高电平指纹模块工作
		FING_DETECT----PC13 ------ 感应上电信号（手指触摸指纹传感器时输出高电平）
***************************************************************/
void MG200_USART2_Init(u32 bps)
{
 	u32 pri;
	//端口时钟使能
	RCC->APB2ENR |= 1 << 2;//A
	RCC->APB2ENR |= 1 << 3;//B
	RCC->APB2ENR |= 1 << 4;//C	
 
	//FING_PWR-----PB9--指纹模块供电引脚
	GPIOB->CRH &= ~(0XF << (4 * (9 - 8)));
	GPIOB->CRH |=  (3 << (4 * (9 - 8)));		//通用推挽50M
	GPIOB->ODR |= 1 << 9;      //一直给模块供电
	
	//FING_DETECT----PC13----感应上电信号
	GPIOC->CRH &= ~(0XF << (4 * (13 - 8)));
	GPIOC->CRH |=  (3 << (4 * (13 - 8)));		//通用推挽50M
	
	//PA2  PA3 
	//端口模式配置
	GPIOA->CRL &= ~(0XF << (4 * 2));
	GPIOA->CRL |=  (0XB << (4 * 2));		//复用推挽50M
	
	GPIOA->CRL &= ~(0XF << (4 * 3));
	GPIOA->CRL |=  (0X4 << (4 * 3));		//浮空输入
	
	/*串口2控制器配置*/
	//串口1模块时钟使能
	RCC->APB1ENR |= 1 << 17;
	//CR1
	USART2->CR1 &= ~(1<<12);        //8位字长
	USART2->CR1 |= (1<<3);          //发送使能
	USART2->CR1 |= (1<<2);          //接收使能
	USART2->CR1 |= (1<<5);          //接收中断使能
	USART2->CR1 |= (1<<4);          //空闲中断使能	
	//CR2
	USART2->CR2 &= ~(3<<12);        //1个停止位
	//BRR
	USART2->BRR = 36000000 / bps;

  /*NVIC控制器配置*/
	//优先级分组  抢占2位响应 两位  写入就是5
	//在主函数中
	//计算优先级编码值
	 pri = NVIC_EncodePriority(5,1,2);
	//设置具体中断源优先级
	NVIC_SetPriority(USART2_IRQn,pri);
	//使能NVIC响应通道
	NVIC_EnableIRQ(USART2_IRQn);	

	//串口使能
	USART2->CR1 |= (1<<13); 

}
/*************************串口2中断服务函数********************************************/
void USART2_IRQHandler()
{
	if(USART2->SR & (1<<5))  //判断是否是接收中断
	{
		Recv_Buff[RecvCount] = USART2->DR; //接收数据
		RecvCount++;   //下标自增
	}
	if(USART2->SR & (1<<4))  //判断是否是空闲中断
	{
		USART2->SR;     //请标志位
		USART2->DR;
		RecvFlag = 1;    //接收标志位置1		
	}
}
/*****************************************************************************************
函数功能：发送命令函数
函数参数：
	Command：要发送的命令
	Data：要发送的数据
*****************************************************************************************/
void MG200_Send_Data(u8 Command,u8 Data)
{
	u8 i = 0,Checksum = 0;
	memset(Send_Buff,0,7);  //清零
	Send_Buff[0] = 0x6C;    //起始码
	Send_Buff[1] = 0x63;    //发送地址
	Send_Buff[2] = 0x62;    //接收地址
	Send_Buff[3] = Command;   //命令
	Send_Buff[4] = Data;      //参数
	Send_Buff[5] = 0;          //保留
	for(i = 1; i <6 ;i++)
	{
		Checksum = Checksum + Send_Buff[i];
	}
	Send_Buff[6] = Checksum;   //校验和
	for(i = 0;i < 7; i++)
	{
		//等待之前的发送完成
   	while(!(USART2->SR & (1<<6)));
   	//将要发送的数据给数据寄存器
	  USART2->DR = Send_Buff[i];		
	}
}
/********************************************************************************************
函数功能：接收到的数据
函数参数：
command：命令
parameter：参数
函数返回值：
接收数据包错误返回-1,数据包接收正确返回处理结果
********************************************************************************************/
int MG200_Recv_Check(u8 command,u8 *parameter)
{
	u8 i;
	u8 result,checksum = 0;
	if(Recv_Buff[0] != 0x6c)		return -1;   //检查起始码
	if(Recv_Buff[1] != 0x62)		return -1;   //检查指纹模块地址
	if(Recv_Buff[2] != 0x63)		return -1;   //检查主控MCU地址
	if(Recv_Buff[3] != command)	    return -1;   //检查目标指令
	result = Recv_Buff[4];           //接收应答码
	if(parameter != NULL)
	{
			*parameter = Recv_Buff[5];  //判断是否有参数
	}		
	for(i=1;i<6;i++)
	{
		checksum = checksum + Recv_Buff[i];   //校验和
	}
	if(Recv_Buff[7] != checksum)	 return -1;//检查校验和
	memset(Recv_Buff,0,8);      //清零
	RecvCount = 0;
	RecvFlag = 0;
	return result;
}
/***********************************************************************************************
函数功能：注册用户
函数参数：
	ID:注册的ID号(取值范围为1~100，最大用户ID为100,如果写0，则注册成功的ID是系统随机分配的)
函数返回值：
	0：注册成功
	1：注册失败
***********************************************************************************************/
u8 ReqEnroll(u8 ID)
{
	u8 result = 0;   //接收返回值
	MG200_Send_Data(ReqEnroll_Command,ID);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqEnroll_Command,0x00);
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x83: printf("  ID  error      \r\n");    break;
		case 0x91: printf("  用户区域已满   \r\n");    break;
		case 0x93: printf("  此ID已经注册过 \r\n");    break;
		case 0x94: printf("  指纹提取数<3   \r\n");    break;
		default:   printf("  数据包错误     \r\n");    break;
	}
	printf("result: %x\r\n",result);
	if(!result)  return result;  //注册成功
	else         return 1;  //注册失败
}
/*********************************************************************************************
函数功能：抓取指纹图像和提取特征点
函数参数：
	num:要传递的次数
函数返回值：
	0：成功
	1：失败
函数说明：
主控单元 MCU 在使用该注册用户指令前必须先执行 3~5 次（执行次数可根据用户
需求定制） 0x51 指令，提取要注册用户指纹的特征量
*********************************************************************************************/
u8 ReqCaptureAndExtract(u8 parameter)
{
	u8 result = 0;   //接收返回值
	MG200_Send_Data(ReqCaptureAndExtract_Command,parameter);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqCaptureAndExtract_Command,0x00);	
	switch(result)
	{
		case 0x00:printf("		syccess     	\r\n");break;
		case 0xB1:printf("		指纹过小		\r\n");break;
		case 0xB2:printf("		无指纹			\r\n");break;
		case 0xC0:printf("		特征提取错误	\r\n");break;
		default:printf("		接收数据包错误	\r\n");break;
	}
	if(!result)  return 0;  //成功
	else         return 1;  //失败	
}

/********************************************************************************************
函数功能：删除指定ID用户
函数参数：
	ID：要删除的ID号
函数返回值：
	0：删除成功
	1：删除失败
********************************************************************************************/
u8 ReqEraseOne(u8 ID)
{
	u8 result = 0;   //接收返回值
	MG200_Send_Data(ReqEraseOne_Command,0x00);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqEraseOne_Command,0x00);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x83: printf("  参数错误       \r\n");    break;
		case 0x90: printf("  未注册过此用户 \r\n");    break;
		case 0xFF: printf("  写入错误       \r\n");    break;
		default:   printf("  数据包错误     \r\n");    break;
	}
	if(!result)  return 0;  //成功
	else         return 1;  //失败
}


/********************************************************************************************
函数功能：删除所有用户
函数返回值：
	0：删除成功
	1：删除失败
********************************************************************************************/
u8 ReqEraseAll(void)
{
	u8 result = 0;   //接收返回值
	MG200_Send_Data(ReqEraseAll_Command,0x00);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqEraseAll_Command,0x00);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x90: printf("  删除失败       \r\n");    break;
		default:   printf("  数据包错误     \r\n");    break;
	}
	if(!result)  return 0;  //成功
	else         return 1;  //失败
}

/********************************************************************************************
函数功能：获取已注册用户数量
函数返回值：
	成功：返回已注册的数量
	失败：1
********************************************************************************************/
u8 ReqGetUserNum(void)
{
	u8 result = 0,parameter = 0;   //接收返回值
	MG200_Send_Data(ReqGetUserNum_Command,0x00);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqGetUserNum_Command,&parameter);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		default:   printf("  数据包错误     \r\n");    break;
	}
	if(!result)  return parameter;  //成功
	else         return 1;  //失败
}


/********************************************************************************************
函数功能：1： N 比对对比用户指纹
函数返回值：
	成功：返回对比成功的ID号
	失败：1
********************************************************************************************/
u8 ReqMatch1N(void)
{
	u8 result = 0,parameter = 0;   //接收返回值
	MG200_Send_Data(ReqMatch1N_Command,0x00);
	while(RecvFlag == 0);   //循环等待接收完成标志位置1
	result = MG200_Recv_Check(ReqMatch1N_Command,&parameter);	
	switch(result)
	{
		case 0x00: printf("   success       \r\n");    break;
		case 0x92: printf("   比对失败      \r\n");    break;
		default:   printf("  数据包错误     \r\n");    break;
	}
	if(!result)  return result;  //成功
	else         return -1;  //失败
}




















