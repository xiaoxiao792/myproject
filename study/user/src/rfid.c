#include "rfid.h"
#include "string.h"

/*************************************************************************************
* 函数名：     RFID_Init
* 功能描述 ：  初始化管脚
           SDA (CS)<----->PA6
           RST <----->PA7
 *************************************************************************************/
void RFID_Init(void)
{
  RCC->APB2ENR |=1<<2;  //使能B时钟
	
	/*CS-----PA6*/ //推挽输出 50MHZ
	GPIOA->CRL&=~(15<<6*4);
	GPIOA->CRL|=3<<(6*4);
	CS_H;
	
	/*RST-----PA7*/ //推挽输出 50MHZ
	GPIOA->CRL&=~(15<<7*4);
	GPIOA->CRL|=3<<(7*4);
	RST_H;	
}

/*******************************************************************
* 函数名：     WriteRawRC()
* 功能描述 ：  写RC632寄存器
* 参数说明:   
	Address:寄存器地址
	value:写入的值
*******************************************************************/
void WriteRawRC(u8 Address, u8 value)
{  
    u8 ucAddr;
	  //选中rfid从机
		CS_L;
	  //处理寄存器的地址，取低七位
    ucAddr = ((Address<<1)&0x7E);  //0111 1110
		//发送要写入的寄存器地址
	  SPI_Read_Write_Byte(ucAddr);
	  //发送写入的数据
		SPI_Read_Write_Byte(value);
		CS_H;
}
/*******************************************************************
* 函数名：     ReadRawRC()
* 功能描述 ：  读RC632寄存器
* 参数说明:    Address:寄存器地址
* 返回值说明： 读出的值
*******************************************************************/
u8 ReadRawRC(u8 Address)
{
		u8 ucAddr;
		u8 ucResult=0;
		CS_L;
		ucAddr = ((Address<<1)&0x7E)|0x80;
		SPI_Read_Write_Byte(ucAddr);
		ucResult=SPI_Read_Write_Byte(0);
		CS_H;
		return ucResult;
}
/*******************************************************************
* 函数名：     SetBitMask()
* 功能描述 ：  置RC522寄存器位
* 参数说明:    
	reg:寄存器地址
	mask:置位1
*******************************************************************/
void SetBitMask(u8 reg,u8 mask)  
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp|mask);  //设置某个位位1
}

/*******************************************************************
* 函数名：     ClearBitMask()
* 功能描述 ：  清RC522寄存器位
* 参数说明:    
	reg:寄存器地址
	mask:清位0

*******************************************************************/
void ClearBitMask(u8 reg,u8 mask)  
{
    char tmp = 0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  //给某个位清0
} 





/*******************************************************************
* 函数名：     PcdAntennaOn()
* 功能描述 ：  开启天线 
*******************************************************************/
void PcdAntennaOn(void)
{
    u8   i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}

/*******************************************************************
* 函数名：     PcdAntennaOff()
* 功能描述 ：  关闭天线 
*******************************************************************/
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}






/*******************************************************************
* 函数名：     Reset_RC522()
* 功能描述 ：   复位RC522
*******************************************************************/
void Reset_RC522(void)
{
	RST_H;
  Delay_us(2);
	RST_L;
  Delay_us(2);
	RST_H;
  Delay_us(2);
  //复位
  WriteRawRC(CommandReg,PCD_RESETPHASE);
  Delay_us(2);
  //定义发送接收的常用模式,和Mifare卡通讯，CRC初始值0x6363
	WriteRawRC(ModeReg,0x3D);  
  //描述定时器重装在值	
	WriteRawRC(TReloadRegL,30);           
	WriteRawRC(TReloadRegH,0);
	//定义内部定时器的设置
	WriteRawRC(TModeReg,0x8D);
	WriteRawRC(TPrescalerReg,0x3E);
	//控制天线驱动器的设置,//调制发送信号为100%ASK
	WriteRawRC(TxAutoReg,0x40); 

  //关闭天线
	PcdAntennaOff(); 
	//开启天线
	PcdAntennaOn();  
}    


/*******************************************************************
* 函数名：     PcdComMF522()
* 功能描述 ：  通过RC522和ISO14443卡通讯
* 参数说明:   
	Command :RC522命令字
	pIn :通过RC522发送到卡片的数据
	InLenByte :发送数据的字节长度
	pOut :接收到的卡片返回数据
	*pOutLenBit :返回数据的位长度

*******************************************************************/
char PcdComMF522(u8   Command, 
                 u8 *pIn , 
                 u8   InLenByte,
                 u8 *pOut , 
                 u8 *pOutLenBit)
{
    char status = MI_ERR;
    u8 irqEn   = 0x00;
    u8 waitFor = 0x00;
    u8 lastBits;
    u8 n;
    u16 i;
    switch (Command)
    {
			  ////验证密钥
        case PCD_AUTHENT:    //Mifare认证
													irqEn   = 0x12; //允许错误中断请求ErrIEn  允许空闲中断IdleIEn
													waitFor = 0x10; //认证寻卡等待时候 查询空闲中断标志位
													break;
				//发送并接收数据
				case PCD_TRANSCEIVE:  //接收发送 发送接收
													irqEn   = 0x77;  //允许TxIEn RxIEn IdleIEn LoAlertIEn ErrIEn TimerIEn
													waitFor = 0x30;  //寻卡等待时候 查询接收中断标志位与 空闲中断标志位
													break;
				default:	break;
    }
    //中断请求传递的使能和禁能控制位，IRqInv置位管脚IRQ与Status1Reg的IRq位的值相反
    WriteRawRC(ComIEnReg,irqEn|0x80);
		//清所有中断位，Set1该位清零时，CommIRqReg的屏蔽位清零
    ClearBitMask(ComIrqReg,0x80);	
		//启动停止命令的执行，取消当前命令，写空闲命令
    WriteRawRC(CommandReg,PCD_IDLE);
		//清FIFO缓存，置位FlushBuffer清除内部FIFO的读和写指针以及ErrReg的BufferOvfl标志位被清除
    SetBitMask(FIFOLevelReg,0x80);	 	
    
    for (i=0; i<InLenByte; i++)
    {
			//64字节FIFO缓冲区的输入和输出（把数据写入到FIFO）
			WriteRawRC(FIFODataReg, pIn [i]);    
		}
		//启动命令字，//写命令
    WriteRawRC(CommandReg, Command);	  
 
    //判断命令是否是发送或接收数据
    if (Command == PCD_TRANSCEIVE)
    {
			 //StartSend置位启动数据发送 该位与收发命令使用时才有效
		   SetBitMask(BitFramingReg,0x80);   //开始传送
		}	
    										 
    i = 600;//根据时钟频率调整，操作M1卡最大等待时间25ms
    do 
    {
			 //读取中断请求标志位，//查询事件中断
        n = ReadRawRC(ComIrqReg);   
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor)); //退出条件i=0,定时器中断，与写空闲命令
		//清理允许StartSend位
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0) //计数未完成  
    {    
			  ////读错误标志寄存器BufferOfI CollErr ParityErr ProtocolEr
        if(!(ReadRawRC(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if(n & irqEn & 0x01) //是否发生定时器中断
            {
   						status = MI_NOTAGERR;     
						}
						//检测命令是否为发送接收数据
            if(Command == PCD_TRANSCEIVE)
            { 
							  //读FIFO中保存的字节数
               	n = ReadRawRC(FIFOLevelReg);
							  ////最后接收到得字节的有效位数
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if(lastBits)//不为0 
                {
									//N个字节数减去1（最后一个字节）+最后一位的位数 读取到的数据总位数
								  *pOutLenBit = (n-1)*8 + lastBits;   
								}
                else 
                {
									//最后接收到的字节整个字节有效
   								*pOutLenBit = n*8;   
								}
                if (n == 0)
                {
								   n = 1;    
								}
                if(n > MAXRLEN)  //FIFO的长度
                {
   								n = MAXRLEN;   
								}
                for (i=0; i<n; i++)
                {
									 //从FIFO读取数据
								   pOut [i] = ReadRawRC(FIFODataReg);    
								}
             }
        }
        else
        {   status = MI_ERR;   }
        
    }
   
    //停止定时器
    SetBitMask(ControlReg,0x80); 
    //停止当前命令，写空闲命令		
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}








/*******************************************************************
* 函数名：     PcdRequest()
* 功能描述 ：   	寻卡
*参数说明: 
req_code:寻卡方式
                0x52 = 寻感应区内所有符合14443A标准的卡
                0x26 = 寻未进入休眠状态的卡
pTagType：卡片类型代码
                0x4400 = Mifare_UltraLight
                0x0400 = Mifare_One(S50)
                0x0200 = Mifare_One(S70)
                0x0800 = Mifare_Pro(X)
                0x4403 = Mifare_DESFire
* 返回值说明：成功返回MI_OK
*******************************************************************/               
char PcdRequest(u8 req_code,u8 *pTagType)
{
	char status;  
	u8 unLen;
	u8 ucComMF522Buf[MAXRLEN]; 
 ////清理指示MIFARECyptol单元接通以及所有卡的数据通信被加密的情况
	ClearBitMask(Status2Reg,0x08);
	//定义发送的最后一个字节的七位
	WriteRawRC(BitFramingReg,0x07);
	//控制天线驱动器的管脚//TX1,TX2的输出信号传递经发送调制的13.56的能量载波信号
	SetBitMask(TxControlReg,0x03);
  //将寻卡方式存到数组
	ucComMF522Buf[0] = req_code;
  //发送寻卡方式并接受返回的数据及字长
	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);
//寻卡成功，判断返回卡类型 
	if ((status == MI_OK) && (unLen == 0x10))  
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   status = MI_ERR;   }
   
	return status;
}

/*******************************************************************
* 函数名：     PcdAnticoll()
* 功能描述 ：   防冲撞
* 参数说明：     pSnr :卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
*******************************************************************/
char PcdAnticoll(u8 *pSnr)
{
    char   status;
    u8   i,snr_check=0;
    u8   unLen;
    u8   ucComMF522Buf[MAXRLEN]; 
	  //清除接收发送器的标志位
    ClearBitMask(Status2Reg,0x08);
	  //清理寄存器 停止收发
    WriteRawRC(BitFramingReg,0x00);
	  //清所有接收的位在冲突后将被清除
    ClearBitMask(CollReg,0x80);
    //将防冲撞命令存到数组
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;
    //发送防冲撞命令
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);
    //通信成功
    if (status == MI_OK)
    {
    	 for (i=0; i<4; i++)
         {   
             *(pSnr+i)  = ucComMF522Buf[i];//返回的卡序列号存到参数
             snr_check ^= ucComMF522Buf[i];
         }
         if (snr_check != ucComMF522Buf[i]) //校验返回的数据是否正确
         {
   				 status = MI_ERR;    
				 }
    }
    //恢复该寄存器的7号位，要求只在防冲突设为0，其他情况应当设为,1
    SetBitMask(CollReg,0x80);
    return status;
}



/*******************************************************************
* 函数名：     PcdSelect()
* 功能描述 ：   选定卡片 
* 参数说明：     pSnr:卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
*******************************************************************/
char PcdSelect(u8 *pSnr)
{
    char status;
    u8 i;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN]; 
    //防冲撞命令存到数组   
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
	
    for (i=0; i<4; i++) //验证卡号号
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
		//CRC校验
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
    //清除标志位
    ClearBitMask(Status2Reg,0x08);
		//发送卡号并选定该卡
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    //检验是否选中
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}
 


/*******************************************************************
* 函数名：     CalulateCRC()
* 功能描述 ：  用MF522计算CRC16函数
*******************************************************************/
void CalulateCRC(u8 *pIn ,u8 len,u8 *pOut )
{
    u8   i,n;
	  //允许CRC中断请求
    ClearBitMask(DivIrqReg,0x04);
	  //取消当前命令
    WriteRawRC(CommandReg,PCD_IDLE);
	  //清除FIFO缓冲区的标志位
    SetBitMask(FIFOLevelReg,0x80);
	  
    for (i=0; i<len; i++)
    {
			//写入数据到FIFO
		  WriteRawRC(FIFODataReg, *(pIn +i));   
		}
		//开始CRC校验命令  
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
			  //等待CRC校验结束
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
		//将校验结果存入数组
    pOut [0] = ReadRawRC(CRCResultRegL);
    pOut [1] = ReadRawRC(CRCResultRegM);
}


/*------------------------------------------------------读/写卡--------------------------------------------------------------*/





/*******************************************************************
* 函数名：     PcdAuthState()
* 功能描述 ：   验证卡片密码
*参数说明: auth_mode : 密码验证模式
                 0x60 = 验证A密钥
                 0x61 = 验证B密钥 
								addr ：块地址
								pKey ：密码
								pSnr ：卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
*******************************************************************/             
char PcdAuthState(u8 auth_mode,u8 addr,u8 *pKey,u8 *pSnr)
{
    char status;
    u8 unLen;
		u8 ucComMF522Buf[MAXRLEN]; 
    //将密码存到数组
    ucComMF522Buf[0] = auth_mode;
    //将块地址存到数组
	  ucComMF522Buf[1] = addr;
	  //将密码和序列号复制到数组中  
    memcpy(&ucComMF522Buf[2], pKey, 6); 
    memcpy(&ucComMF522Buf[8], pSnr, 4);
	  //发送验证密码命令并接受数据
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    //判断密码验证成功还是失败
	  if((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {
  		status = MI_ERR;   
		}
    return status;
}

/*******************************************************************
* 函数名：     PcdRead()
* 功能描述 ：   读取M1卡一块数据 
*参数说明: addr ：块地址
           p  ：读出的数据，16字节
* 返回值说明：   成功返回MI_OK
*******************************************************************/ 
char PcdRead(u8 addr,u8 *p )
{
    char status;
    u8 unLen;
    u8 i,ucComMF522Buf[MAXRLEN]; 
	  //将读块命令存到数组
    ucComMF522Buf[0] = PICC_READ;
	  //将读取的地址存到数组
    ucComMF522Buf[1] = addr;
	  //校验
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    //接收读取到的数据
  	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    //判断是否接受成功   
  	if ((status == MI_OK) && (unLen == 0x90))
    {
        for (i=0; i<16; i++) //成功就将接受到的数据给P
        {
  				*(p +i) = ucComMF522Buf[i];   
				}
    }
    else
    {
   		status = MI_ERR;   
		}
    return status;
}

/*******************************************************************
* 函数名：     PcdWrite()
* 功能描述 ：   写数据到M1卡一块
*参数说明: addr ：块地址
           p  ：读出的数据，16字节
* 返回值说明：   成功返回MI_OK
*******************************************************************/                  
char PcdWrite(u8   addr,u8 *p )
{
    char   status;
    u8   unLen;
    u8   i,ucComMF522Buf[MAXRLEN]; 
    //将写块命令存入数组
    ucComMF522Buf[0] = PICC_WRITE;
	  //将写的块地址存到数组
    ucComMF522Buf[1] = addr;
	  //校验
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    //发送命令到块中
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    //判断是否发送成功
    if((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
  		status = MI_ERR;   
		}    
    if (status == MI_OK)   //命令发送成功
    {
        for (i=0; i<16; i++)  //将数据存到数组中  
        {    
        	ucComMF522Buf[i] = *(p +i);   
        }
				//校验
        CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);
        //发送数据到块  
        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
				//判断是否发送成功
        if((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {
	  			status = MI_ERR;   
				}
    }
    
    return status;
}

 