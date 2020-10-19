#include "at24c02.h"
#include "iic.h"
#include "systick.h"
#include  <stdio.h>

/*
AT24C02连续读函数
参数1：u8 byte_addr，数据所在的存储地址： AT24C02的存储地址 。
参数2：u8 *buff，数据缓冲区，接下来存储的数据的空间
参数3：u8 count，需要读取的字节数
返回值：
TRUE   ：连续读成功
ERROR  ：页连续读失败
*/
u8 at24c02_read(u8 byte_addr,u8 *buff,u16 count)
{
	u8  ack=0;
	u16 i=0;
	/* 伪写操作 */
	iic_start();                    //发送起始信号
	ack = iic_write(Wite_ADDR);     //发送写器件地址
	if( ack == NoACK ) 	 return  ERROR;
	
	ack = iic_write(byte_addr);     //发送存储地址
	if( ack == NoACK ) 	 return  ERROR;
	
	/* 立即读操作 */
	iic_start();                    //发送起始信号
	ack = iic_write(Read_ADDR);     //发送写器件地址
	if( ack == NoACK ) 	 return  ERROR;
	for(i=0;i<count-1;i++)  
	{
	  *buff = iic_read(ACK);        //前面 count-1 数据需要应答  
		buff++;
	}
	*buff = iic_read(NoACK);        //最后一个数据不需要应答
	iic_stop();                     //发送结束信号
	return  TRUE;
}
/*
AT24C02连续写函数
参数1：u8 byte_addr，数据要存储到的地方： AT24C02的存储地址 。
参数2：u8 *buff，数据缓冲区，接下来需要存储的数据
参数3：u8 count，需要存储的字节数
返回值：
TRUE   ：连续写成功
ERROR  ：页连续写失败
*/
u8 at24c02_write(u8 byte_addr,u8 *buff,u16 count)
{
	u8  error=0;
	u8  i=0;
	u16 last_count = 256 - byte_addr;                 //计算从此地址开始，整个芯片还能写入多少数据
	if( last_count < count )   return  ERROR;         //存储空间不足
	
	last_count = Page_Count -   byte_addr%Page_Count;   //计算从当前地址开始，此页还能写入的数据
	if( count < last_count )    last_count = count;     //当前页能写完，重新赋值last_count，等下全部写完
	while( count )
	{		
		error = at24c02_page_program( byte_addr,buff,last_count );  //页编程函数
		if( error == ERROR )                     return  ERROR;   //页编程出错 
		/* 存储地址，数据缓冲区，字节数都需要偏移 */
		/* 偏移量为刚写完的字节数 */
		byte_addr	 += last_count;
		buff	     += last_count;
		count      -= last_count;

		if( count>Page_Count )        last_count = Page_Count;   //剩余需要写入的字节数比一页多，写一页
		else                          last_count = count;        //剩余需要写入的字节数比不足一页，全部写完
	}
	return  TRUE;  //编程正确
}

/*
AT24C02页编程函数
参数1：u8 byte_addr，数据要存储到的地方： AT24C02的存储地址 。
参数2：u8 *buff，数据缓冲区，接下来需要存储的数据
参数3：u8 count，需要存储的字节数
返回值：
TRUE   ：页编程成功
ERROR  ：页编程失败
*/ 
u8 at24c02_page_program(u8 byte_addr,u8 *buff,u8 count)
{
	u8 ack=0;
	u8 i=0;
	u8 last_count = Page_Count - byte_addr%Page_Count ;  //计算从当前地址开始，此页还能写入的数据
	if( last_count < count )   return  ERROR;
	iic_start();                    //发送起始信号
	ack = iic_write(Wite_ADDR);     //发送写器件地址
	if( ack == NoACK ) 	 return  ERROR;
	
	ack = iic_write(byte_addr);     //发送存储地址
	if( ack == NoACK ) 	 return  ERROR;
	
	for(i=0;i<count;i++)  
	{
		ack = iic_write(buff[i]);     //发送数据
		if( ack == NoACK ) 	 return  ERROR;
	}
	
	iic_stop();                     //发送结束信号
	 Delay_ms(10);
	 return  TRUE;
}



