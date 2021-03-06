#include "sys.h"
#include "mifare522.h"	
#include "usart.h"
#include "delay.h"
#include "includes.h"
#include "oled.h"
							//ms延时倍乘数,在os下,代表每个节拍的ms数
//读取设备的命令
u8 readCmd[6]={0x06,0x01,0x41,0x00,0xB9,0x03};
//请求读卡
u8 requestCmd[7]={0x07,0x02,0x41,0x01,0x52,0x00,0x03};
//防碰撞
u8 piccAnticollCmd[8]={0x08,0x02,0x42,0x02,0x93,0x00,0x00,0x03};

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	
static RTC_TimeTypeDef  	RTC_TimeStructure;
static RTC_DateTypeDef  	RTC_DateStructure;
extern volatile uint8_t id_count;		
extern OS_FLAG_GRP g_flag_grp;
extern OS_MUTEX	g_mutex_oled;			//互斥量的对象
//初始化IO 串口1 
//bound:波特率
void uart2_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOB时钟 使能USART1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//串口3对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOB10复用为USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOB11复用为USART2
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOB10与GPIOB11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PB10，PB11

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口3

	
  USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART2, USART_FLAG_TC);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接收中断

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3 数值越小优先级越高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3; //子优先级3,响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器、


}


void USART2_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART2);//(USART2->DR);	//读取接收到的数据
		if(USART2_RX_STA==0)
		{
			USART2_RX_BUF[0]=Res;
			USART2_RX_STA++;
		}
		else
		{		
				USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
				USART2_RX_STA++;
				if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	 
				if(USART2_RX_BUF[0]==USART2_RX_STA)USART2_RX_STA|=0x8000;				
			
		}	  
	} 
}

void USART2_SendByte(u8 Data)
{
   while (!(USART2->SR & USART_FLAG_TXE));	 // while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		USART_SendData(USART2, Data);	 
   
}

void print3RX(u8 * data,u16 nub)			     // 打印定长字符串
{
	u16 i;
	for (i=0; i<nub; i++){
		USART2_SendByte(data[i]);
	}
}

void UART3_Send_Enter(void)
{
    USART2_SendByte(0x0d);
    USART2_SendByte(0x0a);
}

/*计算校验和*/
u8 CalBCC(u8 *buf, int n)
{
	u8 i;
	u8 bcc=0;
	for(i = 0; i < n; i++)
	{
		bcc ^= *(buf+i);
	}
	return (~bcc);
}

/**********************************
//函数：void mifare522Read() 
//发送数据：06 01 41 00 B9 03
//返回值：14 01 00 0E 52 43 35 32 32 20 56 31 2E 32 30 31 38 00 A2 03  
**************************************/
void mifare522ReadDevice(void)
{
	u16 len,t;
	print3RX(readCmd,6);	
	while(!(USART2_RX_STA&0x8000))
	{
		delay_ms(1);
	}
	if(USART2_RX_STA&0x8000)
	{					   
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(USART2_RX_BUF[2]==0x00)
			{
				printf("\r\n扫描设备信息为:\r\n");
				for(t=4;t<(len-2);t++)
				{
					USART_SendData(USART1, USART2_RX_BUF[t]);         //向串口1发送数据
					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				}
				printf("\r\n\r\n");//插入换行

			}
			else
			{
				printf("扫描设备失败\r\n");
			}
			USART2_RX_STA=0;
			memset(USART2_RX_BUF,0,200);
	}
}

void mifare522Request(void)
{
	u16 len,t;
	requestCmd[5]=CalBCC(requestCmd,requestCmd[0]-2);
	print3RX(requestCmd,7);	
	while(!(USART2_RX_STA&0x8000))
	{
		delay_ms(1);
	}
	if(USART2_RX_STA&0x8000)
	{					   
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(USART2_RX_BUF[2]==0x00)
			{
					printf("\r\n请求成功，其ATQ:0x");
					for(t=4;t<(len-2);t++)
					{
						printf("%x",USART2_RX_BUF[t]);
					}
					printf("\r\n\r\n");//插入换行
					USART2_RX_STA=0;
					memset(USART2_RX_BUF,0,200);
					mifare522ReadID();

			}else
			{
					//printf("\r\n请求失败\r\n");
			}
		USART2_RX_STA=0;
		memset(USART2_RX_BUF,0,200);
	}
}

void mifare522ReadID(void)
{
	uint8_t buf[16];
	OS_ERR err;
	u16 len,t;
	uint32_t id=0;
	uint32_t default_id;
	int8_t i=2;
	char save_buf[64];
	piccAnticollCmd[6]=CalBCC(piccAnticollCmd,piccAnticollCmd[0]-2);
	print3RX(piccAnticollCmd,8);
	while(!(USART2_RX_STA&0x8000))
	{
		delay_ms(1);
	
	}
	if(USART2_RX_STA&0x8000)
	{					   
			len=USART2_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(USART2_RX_BUF[2]==0x00)
			{
					//printf("\r\n防碰撞成功，其卡号:0x");
					for(t=(len-3);t>4;t--)
					{
						printf("%x",USART2_RX_BUF[t]);
						id|=USART2_RX_BUF[t]<<(i*8);
						i--;
					}
					printf("\r\n\r\n");//插入换行
					//printf("id=0x%x\r\n",id);//插入换行
					// 获取日期
					RTC_GetDate(RTC_Format_BCD,&RTC_DateStructure);
					// 获取时间
					RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure);
					id_count++;
					default_id=*(volatile uint32_t *)(0x08020004);
					//printf("default_id=0x%x\r\n",default_id);
					if(id==default_id)
					{
						OSFlagPost(&g_flag_grp,0x08,OS_OPT_POST_FLAG_SET,&err);	
						PFout(9)=0;
						memset(buf,' ',16);
						OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
						OLED_ShowString(0,4,buf);
						OLED_ShowCHinese(40,4,11);//默
						OLED_ShowCHinese(56,4,12);//认
						OLED_ShowCHinese(72,4,13);//卡
						OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
						sprintf((char *)save_buf,"[%03d]20%02x/%02x/%02x Week:%x %02x:%02x:%02x id=%x  1\r\n", \
						id_count,\
						RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_WeekDay,\
						RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds,\
						id);
						//printf("%s\r\n",save_buf);
					}
					else
					{
						PFout(9)=1;
						OSFlagPost(&g_flag_grp,0x40,OS_OPT_POST_FLAG_SET,&err);
						memset(buf,' ',16);
						OSMutexPend(&g_mutex_oled,0,OS_OPT_PEND_BLOCKING,NULL,&err);
						OLED_ShowString(0,4,buf);
						OLED_ShowCHinese(40,4,14);//非
						OLED_ShowCHinese(56,4,15);//法
						OLED_ShowCHinese(72,4,13);//卡

						OSMutexPost(&g_mutex_oled,OS_OPT_POST_NONE,&err);
						sprintf((char *)save_buf,"[%03d]20%02x/%02x/%02x Week:%x %02x:%02x:%02x id=%x  0\r\n", \
						id_count,\
						RTC_DateStructure.RTC_Year, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Date,RTC_DateStructure.RTC_WeekDay,\
						RTC_TimeStructure.RTC_Hours, RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds,\
						id);
						//printf("%s\r\n",save_buf);
					}
					if(id_count<=100)
					{
							//解除写保护，解锁FLASH
						FLASH_Unlock();
						for(i=0;i<64;)
						{
							if(FLASH_COMPLETE!=FLASH_ProgramWord(0x08020000+8+i+(id_count-1)*64,*(uint32_t *)&save_buf[i]))
							{
								printf("FLASH_ProgramWord fail\r\n");
								while(1);					
							}
							i+=4;
						}
						//添加写保护，锁定FLASH
						FLASH_Lock();
					}
			}else
			{
					//printf("\r\n读卡失败\r\n");
			}
			USART2_RX_STA=0;
			memset(USART2_RX_BUF,0,200);
	}
}





