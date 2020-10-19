#include "w25q64.h"
#include "spi.h"
u8 secotr_buff[4096];

u8 w25q64_write_No_erase(u32 addr,u8 *buff,u32 num)
{
	u32 i=0;
	u8  error=0;
	u16 count;
	u32 last_count= 0x800000 - addr; 
	if( last_count < num )  return 1;	          //从此地址开始，芯片无法写入全部数据
	last_count = addr%W25Q64_SECTOR;            //计算此地址在扇区的位置
	count = W25Q64_SECTOR -  last_count;        //计算扇区剩余空间
	if( num<count )  count = num;
	while( num )
	{
		w25q64_read( addr&0xFFF000, secotr_buff,W25Q64_SECTOR); //数据备份
		for(i=last_count;i<(last_count+count);i++)
			secotr_buff[i] = buff[i-last_count];  //数据替换
		w25q64_erase_sector(addr);              //扇区擦除
		error = w25q64_sector_program(addr,secotr_buff); //数据写入	
		if( error )    return 1; //写入失败
		addr +=count;
		buff +=count;
		num  -=count;
		last_count = 0;
		if( num<W25Q64_SECTOR )  count = num;
		else                     count = W25Q64_SECTOR;
	}
	return 0;
}
u8 w25q64_sector_program(u32 addr,u8 *buff)
{
	u8 i=0;
	u8 error=0;
	addr &=0xFFF000; //得到扇区首地址
	for(i=0;i<16;i++)
	{
		error= w25q64_page_program(addr,buff,W25Q64_PAGE);
		if(error)   return 1;
		addr +=W25Q64_PAGE;
		buff +=W25Q64_PAGE;
	}
	return 0;
}


/* 连续写 */
u8 w25q64_write(u32 addr,u8 *buff,u32 num)
{
	u32 i=0;
	u8  error=0;
	u32 last_count = 0x800000 - addr; 
	if( last_count < num )  return 1;	          //从此地址开始，芯片无法写入全部数据
	last_count = W25Q64_PAGE- addr%W25Q64_PAGE; //计算此地址所在页能写入的字节数
	if( num < last_count )  last_count=num;
	while( num )
	{
		error = w25q64_page_program(addr,buff,last_count);
		if( error )    return 1; //写入失败
		addr +=last_count;
		buff +=last_count;
		num  -=last_count;
		if( num>W25Q64_PAGE )  last_count=W25Q64_PAGE;
		else                   last_count=num;
	}
	return 0;
}

/* 页连续读 */
void w25q64_read(u32 addr,u8 *buff,u16 num)
{	
	u32 i=0;
	Flash_CS_L();
	spi_send_read(0x03);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	for(i=0;i<num;i++) 
	{
		*buff = spi_send_read( 0xFF ); 
		buff++;
	}
	Flash_CS_H();
}


/* 
页编程 
返回值：
0：  页编程成功
1：  页编程失败
*/
u8 w25q64_page_program(u32 addr,u8 *buff,u16 num)
{
	u8  status=0;
	u16 i=0;
	u16 last_count=W25Q64_PAGE- addr%W25Q64_PAGE;
	if( last_count < num )  return 1;	
	w25q64_write_enable();     //写使能
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //等待进入写使能
	Flash_CS_L();
	spi_send_read(0x02);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	for(i=0;i<num;i++) 
	{
		spi_send_read( *buff ); 
		buff++;
	}
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //等待芯片忙完	
}
/* 芯片擦除 */
void w25q64_chip_sector(void)
{
	u8 status=0;
	w25q64_write_enable();     //写使能
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //等待进入写使能
	Flash_CS_L();
	spi_send_read(0xC7);	
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //等待芯片忙完
}
/* 块擦除 */
void w25q64_block_sector(u32 addr)
{
	u8 status=0;
	w25q64_write_enable();     //写使能
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //等待进入写使能
	Flash_CS_L();
	spi_send_read(0xD8);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //等待芯片忙完
}

/* 扇区擦除 */
void w25q64_erase_sector(u32 addr)
{
	u8 status=0;
	w25q64_write_enable();
	do
	{
		status = w25q64_read_status();
	}while( 0 == ( status&(1<<1) ) ); //等待进入写使能
	Flash_CS_L();
	spi_send_read(0x20);	
	spi_send_read( addr>>16); 
	spi_send_read( addr>>8); 
	spi_send_read( addr>>0); 
	Flash_CS_H();
	do
	{
		status = w25q64_read_status();
	}while( status&(1<<0)  ); //等待芯片忙完
}

/* 读状态寄存器 */
u8 w25q64_read_status(void)
{
	u8 status=0;
	Flash_CS_L();
	spi_send_read(0x05);
	status = spi_send_read(0xFF); //发送的是无效数据,任意数据
	Flash_CS_H();
	return status;
}

/*写使能*/
void w25q64_write_enable(void)
{
	Flash_CS_L();
	spi_send_read(0x06);
	Flash_CS_H();
}

/*  读取W25Q64器件ID 正确返回0xEF16 */
u16 w25q64_read_id(void)
{
	u16 device_id=0;
	u8 device_id_h=0,device_id_l=0;
	Flash_CS_L();
	spi_send_read(0x90);
	spi_send_read(0x00);
	spi_send_read(0x00);
	spi_send_read(0x00);
	device_id_h = spi_send_read(0xFF);
	device_id_l = spi_send_read(0xFF);
	Flash_CS_H();
	device_id = (device_id_h<<8) | device_id_l;
	return device_id;
}